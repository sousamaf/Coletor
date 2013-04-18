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

String  inputString,inputStringaux,inputStringcomp = ""; // String para acumula os dados do leitor
int tamString =0; //armazena o tamanho da string para usa na função completa.

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
 //verifica se o leitor deu enter e descarrega os dados da leitura
if( keylcl == 0x13 ) {
  
// Serial.print( " Cod.Barras: ");
 
 
 tamString=0;
 tamString = inputString.length();  
 if (tamString < 13) {
    int tamaux =0;
    
    String aux="";//varivave auxilia para receber o texto completado
    tamaux = 13-tamString;

    
     //realiza um for para completa com zero o codigo   
      for (int i=0; i < tamaux; i++){
       inputStringcomp += "0";
     }

     //completa o codigo de barras com zero
     aux= inputStringcomp+inputString;
     inputString =aux;
     inputStringcomp="";
 }
 
 Serial.print( inputString );
  inputStringaux = inputString+" 1.00";
  escrita(inputStringaux);  //escrevendo no cartao de memoria
  Serial.println( "1.00");
  //Serial.println( " Qtd.: 1.00");
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

//inicializa a porta serial  
Serial.begin(9600);
Serial.println("Coletor 1.0");
delay(1000);
Serial.println("Inicializando.."); 
//Serial.println("\r\n"); 
delay(1000);

 
//INICIALIZANDO CARTAO DE MEMORIA
 inicializaSdcard();

//inicializando o Shiel USB
if (Usb.Init() == -1) {
  Serial.println("Falha ao Iniciar");

  while(1); //halt
}
      
Keyboard.SetReportParser(0, (HIDReportParser*)&Prs);

delay( 200 );

 //faz uma leitura dos dados do cartao   
//leitura ();

}

void loop()
{
//lendo portas de entrada Shield USB
Usb.Task();

}

 //inicializa o cartao de memoria
void inicializaSdcard(){
// Pino 10 deve ser definido como uma saída para a comunicação SD para trabalhar. 
pinMode(10, OUTPUT); ///ARDUINO UNO 10 MEGA 53

///ARDUINO UNO 4 MEGA 53            
if (!SD.begin(4)) {

  Serial.println("Falha no SDCard!");

t =1;
return;
}

 Serial.println("SDCard Ok!");
                        
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

Serial.println("Erro no Arquivo");
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

