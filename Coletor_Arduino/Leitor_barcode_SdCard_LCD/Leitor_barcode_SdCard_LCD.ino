/**/
/* COLETOR DE DADOS DE ESTOQUE
/* AUTOR: CLEBSON M BARBOSA
CONFIGURAÇÃO CARTAO SDCARD ARDUINO
SD board CS pin            -> Arduino UNO digital pin 4               -> Arduino MEGA digital pin 53
SD board MOSI pin          -> Arduino UNO digital pin 11              -> Arduino MEGA digital pin 51
SD board MISO pin          -> Arduino UNO digital pin 12              -> Arduino MEGA digital pin 50
SD board SCK pin           -> Arduino UNO digital pin 13              -> Arduino MEGA digital pin 52 
SD board 3,3v pin          -> Arduino 3,3V pin
SD board GND pin           -> Arduino GND pin
/**/

#include <avrpins.h>
#include <max3421e.h>
#include <usbhost.h>
#include <usb_ch9.h>
#include <Usb.h>
#include <usbhub.h>
#include <avr/pgmspace.h>
#include <address.h>
#include <SD.h> //bliblioteca do Leitor de cartao sd card
#include <adk.h>
#include <LiquidCrystal.h> //bliblioteca do display LCD
#include <hidboot.h>

USB Usb;
USBHub Hub1(&Usb);
USBHub Hub2(&Usb);     
HIDBoot<HID_PROTOCOL_KEYBOARD> Keyboard(&Usb);

/*
VARIAVEIS DO LEITOR DE CARTAO------------------------------------------------
*/
 File myFile; //VARIAVEL QUE ARMAZENA DO ARQUIVO CRIADO EM MEMORIA
 int  t=0; //FLAG DE CONTROLE DE ABERTUDO DO ARQUIVO
 int opcao=-1; //FLAG DE CONTROLE DE OPÇÃO DE ABERTURA DO ARQUIVO
 char buffer[18]; // VARIAVEL PARA ARMAZENA OS DADOS DIGITADOS PELO USUARIO
 char * nomedoarquivo= "dados.txt";               
//---------------------------------------------------------------------------

String  inputString = ""; // String para acumula os dados do leitor

// LCD Display - configura pinagem do painei  
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
 
// LCD Display - define as variaves com valores usados nos botoes
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
 
// LCD Display - realiza a leitura dos botoes
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

//USB SHIELD - cria os eventos do teclado 
class KbdRptParser : public KeyboardReportParser
{
 
protected:
	virtual void OnKeyDown	(uint8_t mod, uint8_t key);
	virtual void OnKeyPressed(uint8_t key);
};
 
void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)	
{
  uint8_t c = OemToAscii(mod, key);
 
  if (c)
      OnKeyPressed(c);
}
 
/* what to do when symbol arrives */
void KbdRptParser::OnKeyPressed(uint8_t key)	
{
 uint8_t keylcl;
 
keylcl = key;
 //verifica se o leitor dei enter e descarrega os dados da leitura
if( keylcl == 0x13 ) {
  lcd.print(inputString);
 // Serial.print( inputString );
  escrita(inputString);  //escrevendo no cartao de memoria
  //Serial.println( " Enter...........................");
  inputString = "";
}
else 
{
  inputString += (char) keylcl;
}    
 
};
 
KbdRptParser Prs;

void setup()
{
//inicializa o display
 lcd.begin(16, 2);              // start the library
 lcd.setCursor(0,0);
 lcd.print("PASSE O PRODUTO"); // print a simple message

//inicializa a porta serial  
Serial.begin(9600);
Serial.println("\r\nColetor de Dados 1.0");
Serial.println("\r\nInicializando....................."); 


 
//INICIALIZANDO CARTAO DE MEMORIA
 inicializaSdcard();

//inicializando o Shiel USB
if (Usb.Init() == -1) {
  Serial.println("Falha na Inicializacao");
  lcd.print("Falha na Inicializacao");
  while(1); //halt
}
      
Keyboard.SetReportParser(0, (HIDReportParser*)&Prs);

delay( 200 );

 //faz uma leitura dos dados do cartao   
leitura ();

}

void loop()
{
//lendo portas de entrada Shield USB
Usb.Task();
lcdInicializa;
}

 //inicializa o cartao de memoria
void inicializaSdcard(){
// Pino 10 deve ser definido como uma saída para a comunicação SD para trabalhar. 
pinMode(53, OUTPUT); ///ARDUINO UNO 10 MEGA 53

///ARDUINO UNO 4 MEGA 53            
if (!SD.begin(53)) {
  lcd.print("Falha ao abrir o SDCard!");
  Serial.println("Falha ao abrir o SDCard!");

t =1;
return;
}
 lcd.print("SDCard Aberto");
 Serial.println("\n SDCard Aberto com sucesso!");
                        
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
lcd.print("Falhar ao abrir SDCard");
Serial.println("ERRO AO ABRIR O ARQUIVO....");
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
  lcd.print("Falhar ao abrir SDCard");
  Serial.println("error ao abrir");
}
 
}
else
{
 lcd.print("Arquivo Não Encontrado");
  Serial.println("ARQUIVO NAO ENCONTRADO VERIFICA O NOME DO ARQUIVO.....");  
}

}
//classe do disply LCD onde fica no loop inicialia e verifica os botoes
void lcdInicializa (){

  lcd.setCursor(9,1);            // move cursor to second line "1" and 9 spaces over
 lcd.print(millis()/1000);      // display seconds elapsed since power-up
 
 
 lcd.setCursor(0,1);            // move to the begining of the second line
 lcd_key = read_LCD_buttons();  // read the buttons
 
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
     break;
     }
     case btnNONE:
     {
     lcd.print("NONE  ");
     break;
     }
  }
 }
