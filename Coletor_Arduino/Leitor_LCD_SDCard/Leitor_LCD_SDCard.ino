/*
CONFIGURAÇÃO CARTAO SDCARD ARDUINO
SD board CS pin            -> Arduino UNO digital pin 4               -> Arduino MEGA digital pin 53
SD board MOSI pin          -> Arduino UNO digital pin 11              -> Arduino MEGA digital pin 51
SD board MISO pin          -> Arduino UNO digital pin 12              -> Arduino MEGA digital pin 50
SD board SCK pin           -> Arduino UNO digital pin 13              -> Arduino MEGA digital pin 52 
SD board 3,3v pin          -> Arduino 3,3V pin
SD board GND pin           -> Arduino GND pin
/**/

//Sample using LiquidCrystal library
#include <LiquidCrystal.h>
#include <SD.h> //bliblioteca do Leitor de cartao sd card
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


String SerialBuffer = "";
/*
VARIAVEIS DO LEITOR DE CARTAO------------------------------------------------
*/
 File myFile; //VARIAVEL QUE ARMAZENA DO ARQUIVO CRIADO EM MEMORIA
 int  t=0; //FLAG DE CONTROLE DE ABERTUDO DO ARQUIVO
 int opcao=-1; //FLAG DE CONTROLE DE OPÇÃO DE ABERTURA DO ARQUIVO
 char buffer[18]; // VARIAVEL PARA ARMAZENA OS DADOS DIGITADOS PELO USUARIO
 char * nomedoarquivo= "dados.txt";               
//---------------------------------------------------------------------------

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
  Serial.println("Coletor 1.0");
  delay(1000);
  Serial.println("Inicializando.."); 
  //INICIALIZANDO CARTAO DE MEMORIA
  inicializaSdcard();
 
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
          //verifica a posição de 0 a 4 se contem a palavra poll de scanner da porta usb
         if (SerialBuffer.substring(0,4) != "Poll") {
            SerialBuffer.trim(); //remove os espaços vazios
           lcd.setCursor(0,0);
           lcd.print(SerialBuffer);
           lcd.setCursor(0,1);
           lcd.print("Digite Qtd:");
           lcd.setCursor(11,1);
           lcd.print("1.00");
         }
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
      escrita("SELECT");  //escrevendo no cartao de memoria
     // lcd.print("SELECT");
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

}
 //realiza a leitura dos dados
 void leitura (){    
//VERIFICA SE O ARQUIVO EXISTE ANTES DE ABRIR-LO
if ( SD.exists (nomedoarquivo)) { 
  //abrir o arquivo e prepara para leitura
  myFile = SD.open(nomedoarquivo, FILE_READ);

// re-abrir o arquivo e prepara para percore
myFile = SD.open(nomedoarquivo);
if (myFile) {
  Serial.println(nomedoarquivo);

  // percore ate o final do aquivo
  while (myFile.available()) {
    Serial.write(myFile.read());
  }
  // fecha o arquivo
  myFile.close();
} 
else {
  // se nao conseguir abrir apresenta mensagem de eroo

  Serial.println("error ao abrir");
}
 
}
else
{

  Serial.println("Arquivo Nao Encontrado");  
}

}
//escreve os dados no arquivo
void escrita (String dadosescrita){

// ABRIR O ARQUINO PARA ESCRITA
myFile = SD.open(nomedoarquivo, FILE_WRITE);

// SE O AQRUIVO FOI ABERTO ESCREVE NELE
if (myFile) {
//ESCREVE DOS DADOS NO ARQUIVO;
myFile.println(dadosescrita);
 // FECHA O ARQUIVO:
myFile.close();

} else {
// if the file didn't open, print an error:

Serial.println("\nErro no Arquivo");
}

}
 //inicializa o cartao de memoria
void inicializaSdcard(){
// Pino 10 deve ser definido como uma saída para a comunicação SD para trabalhar. 
pinMode(10, OUTPUT); ///ARDUINO UNO 10 MEGA 53

///ARDUINO UNO 4 MEGA 53            
if (!SD.begin(4)) {

  Serial.println("Falha no SDCard");

t =1;
return;
}

 Serial.println("SDCard Ok");
                        
}
