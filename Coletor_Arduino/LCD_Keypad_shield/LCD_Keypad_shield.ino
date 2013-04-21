//Sample using LiquidCrystal library
#include <LiquidCrystal.h>

/*******************************************************
 * 
 * This program will test the LCD panel and the buttons
 * Mark Bramwell, July 2010
 * 
 ********************************************************/

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
char * leituraserial ="";
char buffer[20];
String str;

String SerialBuffer = "";

// read the buttons
int read_LCD_buttons()
{
  adc_key_in = analogRead(0);      // read the value from the sensor 
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  if (adc_key_in < 50)   return btnRIGHT;  
  if (adc_key_in < 195)  return btnUP; 
  if (adc_key_in < 380)  return btnDOWN; 
  if (adc_key_in < 555)  return btnLEFT; 
  if (adc_key_in < 790)  return btnSELECT;   
  return btnNONE;  // when all others fail, return this...
}

void setup()
{

  SerialBuffer.reserve(200);

  //inicializa a porta serial  
  Serial.begin(9600); //os dois devem ter o mesmo rate

  lcd.begin(16, 2);              // quantidade de linhas e colunas
  lcd.setCursor(0,0);
  //lcd.print("Push the buttons"); // print a simple message
}

void loop()
{

  // lcd.setCursor(9,1);            // move cursor to second line "1" and 9 spaces over
  //lcd.print(millis()/1000);      // display seconds elapsed since power-up
  lcd.setCursor(0,0);            // move to the begining of the second line
  lcd_key = read_LCD_buttons();  // read the buttons

    if (Serial.available() > 0){
      //enquanto estiver recebendo bytes executa o while
    while (Serial.available() != 0) {
      //recebe dados da serial e armazena em uma string
      char inChar = (char)Serial.read(); 
 
      if (inChar == '\n') {
        //Imprime no LCD a string do SerialBuffer
        Serial.print(SerialBuffer);
        
        lcd.print(SerialBuffer);
        SerialBuffer = "";
      }
      else {
        SerialBuffer += inChar; //Add to buffer
        
      }
    }
  }



  switch (lcd_key)               // depending on which button was pushed, we perform an action
  {
  case btnRIGHT:
    {
      lcd.print("RIGHT ");

      break;
    }
  case btnLEFT:
    {
      lcd.print("LEFT   ");
      break;
    }
  case btnUP:
    {
      lcd.print("UP    ");
      break;
    }
  case btnDOWN:
    {
      lcd.print("DOWN  ");
      break;
    }
  case btnSELECT:
    {
      lcd.print("SELECT");
      lcd.clear();
      break;
    }
  case btnNONE:
    {
      //  lcd.clear(); 
      // lcd.print("NONE  ");
      break;
    }

  }
  // Realiza um Delay de 1 Segundo (1000 milisegundos)
  delay(1000);
}

