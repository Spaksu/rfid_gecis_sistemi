#include <SPI.h>
#include <RFID.h>
RFID rfid(10,9); 
const int hoparlor = 5;

void setup() {
  SPI.begin();
  rfid.init();
  pinMode(hoparlor, OUTPUT);
  digitalWrite(hoparlor, LOW);
  pinMode(3, OUTPUT);  
  pinMode(2, OUTPUT);  
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
}
byte kartim[5] = {0xA3,0xF7,0xF5,0xF7,0x56}; // YETKİLİ KART NO Kart Tanıtma Kısmından alınacak

void loop() {
  boolean gecerlikart = true; 

  if(rfid.isCard()) 
  {
    if(rfid.readCardSerial())
    {
      Serial.print("Kart ID: ");
      Serial.print(rfid.serNum[0],HEX);
      Serial.print(rfid.serNum[1],HEX);
      Serial.print(rfid.serNum[2],HEX);
      Serial.print(rfid.serNum[3],HEX);
      Serial.println(rfid.serNum[4],HEX);
    }
    for(int i=0; i<5; i++)
    {
      if(rfid.serNum[i] != kartim[i]) // YETKİLİ KART İLE KARŞILAŞTIRMA
      {
        gecerlikart = false; // YETKİSİZ KART İSE DEĞİŞKENİ FALSE YAP
      }
    }
    if(gecerlikart==true) // YETKİLİ KART İSE AŞAĞIDAKİLERİ GERÇEKLEŞTİR
    {
      digitalWrite(3, HIGH);
      digitalWrite(2, LOW); 
      delay(3000);
      digitalWrite(2, LOW); 
     }
    else // YETKİSİZ KART İSE (YETKİLİ KARTTAN FARKLI İSE) AŞAĞIDAKİLERİ GERÇEKLEŞTİR
    {
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW); 
      digitalWrite(hoparlor,HIGH);
      delay(50);
      digitalWrite(hoparlor,LOW);
     }
    rfid.halt();
  }
}