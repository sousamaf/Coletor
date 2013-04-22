/**/
/* COLETOR DE DADOS DE ESTOQUE
/* AUTOR: CLEBSON M BARBOSA
*/

#include <Usb.h>
#include <usbhub.h>

#include <adk.h>
#include <hidboot.h>

USB Usb;
USBHub Hub1(&Usb);
USBHub Hub2(&Usb);     
HIDBoot<HID_PROTOCOL_KEYBOARD> Keyboard(&Usb);


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
 
 Serial.println( inputString );
  inputStringaux = inputString;
  
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

//inicializando o Shiel USB
if (Usb.Init() == -1) {
  Serial.println("Falha na USB;");

  while(1); //halt
}
      
Keyboard.SetReportParser(0, (HIDReportParser*)&Prs);

delay( 200 );

}

void loop()
{
//lendo portas de entrada Shield USB
Usb.Task();
Serial.flush();
}


