void printSignature(uint8_t *buf, int len)
{
  int i;
  for(i=0; i<len; i++){
    if(buf[i]>0x19 && buf[i]<0x7F){
      Serial.write(buf[i]);
    }
    else{
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}

/**
  @brief   Print signature, if the character is invisible, 
           print hexible value instead.
  @param   buf  -->  VR module return value when voice is recognized.
             buf[0]  -->  Group mode(FF: None Group, 0x8n: User, 0x0n:System
             buf[1]  -->  number of record which is recognized. 
             buf[2]  -->  Recognizer index(position) value of the recognized record.
             buf[3]  -->  Signature length
             buf[4]~buf[n] --> Signature
*/
void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC);
  Serial.print("\t\t");

  if(buf[0] == 0xFF){
    Serial.print("NONE");
  }
  else if(buf[0]&0x80){
    Serial.print("UG ");
    Serial.print(buf[0]&(~0x80), DEC);
  }
  else{
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if(buf[3]>0){
    printSignature(buf+4, buf[3]);
  }
  else{
    Serial.print("NONE");
  }
//  Serial.println("\r\n");
  Serial.println();
}

void printRecord(uint8_t *buf, uint8_t len)
{
  Serial.print(F("Record: "));
  for(int i=0; i<len; i++){
    Serial.print(buf[i], DEC);
    Serial.print(", ");
  }
}

/**
  ******************************************************************************
  * @file    vr_sample_multi_cmd.ino
  * @author  JiapengLi
  * @brief   This file provides a demostration on 
              how to implement a multi voice command project (exceed 7 voice command) 
              by using VoiceRecognitionModule
  ******************************************************************************
  * @note:
        voice control led
  ******************************************************************************
  * @section  HISTORY
    
    2013/06/13    Initial version.
  */
  
#include <SoftwareSerial.h>
#include <Wire.h>
#include "VoiceRecognitionV3.h"

/**        
  Connection
  Arduino    VoiceRecognitionModule
   2   ------->     TX
   3   ------->     RX
*/
VR myVR(10,11);    // 2:RX 3:TX, you can choose your favourite pins.

uint8_t record[7]; // save record
uint8_t buf[64];

int led = 13;

int group = 0;

#define BuenosDias (0)//Buenos dias                          000001
#define Diagnostico (1)//Necesito un diagnostico medico      000010
#define Gracias (2)//Gracias por la atención                 000011 
//////////////////////Sintomas////////////////////////////// 000100
#define Fiebre (3)  //////////////////////////////           000101
#define Tos (4) //////////////////////////////               000110
#define Fatiga (5) //////////////////////////////            000111
#define DGarganta (6) //////////////////////////////         001000
#define Estornudos (7) //////////////////////////////        001001
#define Picazon (8)  //////////////////////////////          001010
#define CNasal (9)  //////////////////////////////           001011

#define DRespirar (11) //////////////////////////////        001100
#define DMusculares (12) //////////////////////////////      001101

#define DCabeza (14)  //////////////////////////////         001110
#define POlfato (15)//////////////////////////////           001111

#define DArticulares (17)//////////////////////////////      010000
#define ECutanea (18)//////////////////////////////          010001
#define MKoplik (19) //////////////////////////////          010010
#define PPeso (20) //////////////////////////////            010011
#define Mucosidad (21) //////////////////////////////        010100
#define Diarrea (22) //////////////////////////////          010101
#define Nauseas (23) //////////////////////////////          010110
#define DAbdominal (24)  //////////////////////////////      010111
#define Vomitos (25)  //////////////////////////////         011000
#define Ictericia (26) //////////////////////////////        011001
#define Llagas (27)  //////////////////////////////          011010
#define MDolorosa (28)  //////////////////////////////       011011
#define GInflamados (29)  //////////////////////////////     011100
#define SHeces (30) //////////////////////////////           011101
#define Ampollas (31) //////////////////////////////         011110
#define GuardarDatosPaciente (32)////////////////////////////


void setup()
{
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  /** initialize */
  myVR.begin(9600);
  
  Serial.begin(115200);
  Serial.println("Elechouse Voice Recognition V3 Module\r\nMulti Commands sample");
  
  pinMode(led, OUTPUT);
    
  if(myVR.clear() == 0){
    Serial.println("Recognizer cleared.");
  }else{
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while(1);
  }
  
  record[0] = BuenosDias;
  record[1] = Diagnostico;
  record[2] = Gracias;
 
  if(myVR.load(record, 3) >= 0){
    printRecord(record, 3);
    Serial.println(F("loaded."));
  }
  Wire.begin();
}

void loop()
{

  
  int ret;
  ret = myVR.recognize(buf, 50);
  if(ret>0){

    switch(buf[1]){

      case BuenosDias:
        /** turn on LED */
          myVR.clear();
          record[0] = BuenosDias;
          record[1] = Diagnostico;
          record[2] = Gracias;
          if(myVR.load(record, 3) >= 0){
            printRecord(record, 3);
            Serial.println(F("loaded."));
          }
           cero(); 
         digitalWrite(8,0);digitalWrite(7,0);digitalWrite(6,0);digitalWrite(5,0);digitalWrite(4,1);
        delay(1800);
                 cero(); 
        break;

        case Diagnostico:
          myVR.clear();
          record[0] =Diagnostico;
          record[1] =Fiebre;
          record[2] = Fatiga;
          record[3] = Estornudos;
          record[4] = DAbdominal;
          record[5] = Gracias;
          
          if(myVR.load(record, 6) >= 0){
            printRecord(record, 6);
            Serial.println(F("loaded."));
          
        }
        cero(); 
         digitalWrite(8,0);digitalWrite(7,0);digitalWrite(6,0);digitalWrite(5,1);digitalWrite(4,0);
        delay(1800);
                 cero();
        break;
        
        case Gracias:
          myVR.clear();
          record[0] = BuenosDias;
          record[1] = Diagnostico;
          record[2] = Gracias;
          record[3] = GuardarDatosPaciente;
          if(myVR.load(record, 4) >= 0){
            printRecord(record, 4);
            Serial.println(F("loaded."));
          
        }
        cero(); 
         digitalWrite(8,0);digitalWrite(7,0);digitalWrite(6,0);digitalWrite(5,1);digitalWrite(4,1);
        delay(1800);
                 cero();
        break;
        
        case Fiebre:
          myVR.clear();
          record[0] = Fiebre;
          record[1] =DMusculares ;
          record[2] =Tos ;
          record[3] = DCabeza;
          record[4] = Llagas;
          record[5] = Nauseas;
          
          if(myVR.load(record, 6) >= 0){
            printRecord(record, 6);
            Serial.println(F("loaded."));
          }
        
        cero(); 
         digitalWrite(8,0);digitalWrite(7,0);digitalWrite(6,1);digitalWrite(5,0);digitalWrite(4,0);
        delay(1800);
                 cero();
        break;
        
        case Tos:
          myVR.clear();
          record[0] =Tos ;
          record[1] = POlfato;
          record[2] = ECutanea;
          record[3] = Fatiga;
          record[4] = Mucosidad;
          record[5] = Gracias;
          if(myVR.load(record, 6) >= 0){
            printRecord(record, 6);
            Serial.println(F("loaded."));
          }
        
       cero(); 
         digitalWrite(8,0);digitalWrite(7,0);digitalWrite(6,1);digitalWrite(5,0);digitalWrite(4,1);
        delay(1800);
                 cero();
        break;
        
        case Fatiga:
          myVR.clear();
          record[0] =Fatiga ;
          record[1] = Tos;
          record[2] = Nauseas;
          record[3] = Gracias;
          if(myVR.load(record, 4) >= 0){
            printRecord(record, 4);
            Serial.println(F("loaded."));
          }
        
        cero(); 
         digitalWrite(8,0);digitalWrite(7,0);digitalWrite(6,1);digitalWrite(5,1);digitalWrite(4,0);
        delay(1800);
                 cero();
        break;
        
        case DGarganta:
          myVR.clear();
          record[0] =DGarganta ;
          record[1] = Tos ;
          record[2] = Gracias;
          if(myVR.load(record, 3) >= 0){
            printRecord(record, 3);
            Serial.println(F("loaded."));
          }
        
        cero(); 
         digitalWrite(8,0);digitalWrite(7,0);digitalWrite(6,1);digitalWrite(5,1);digitalWrite(4,1);
        delay(1800);
                 cero();
        break;
        
        case Estornudos:
          myVR.clear();
          record[0] =Estornudos ;
          record[1] = CNasal;
          record[2] = Gracias;
          if(myVR.load(record, 3) >= 0){
            printRecord(record, 3);
            Serial.println(F("loaded."));
          }
        
        cero(); 
         digitalWrite(8,0);digitalWrite(7,1);digitalWrite(6,0);digitalWrite(5,0);digitalWrite(4,0);
        delay(1800);
                 cero();
        break;
        
        case Picazon:
          myVR.clear();
          record[0] =Picazon ;
          record[1] =MDolorosa ;
          record[2] = Gracias;
          if(myVR.load(record, 3) >= 0){
            printRecord(record, 3);
            Serial.println(F("loaded."));
          }
        
       cero(); 
         digitalWrite(8,0);digitalWrite(7,1);digitalWrite(6,0);digitalWrite(5,0);digitalWrite(4,1);
        delay(1800);
                 cero();
        break;
        
        case CNasal:
          myVR.clear();
          record[0] =CNasal ;
          record[1] = DGarganta;
          record[2] =Gracias ;
          if(myVR.load(record, 3) >= 0){
            printRecord(record, 3);
            Serial.println(F("loaded."));
          }
        
        cero(); 
         digitalWrite(8,0);digitalWrite(7,1);digitalWrite(6,0);digitalWrite(5,1);digitalWrite(4,0);
        delay(1800);
                 cero();
        break;
        
        case DRespirar:
          myVR.clear();
          record[0] =DRespirar;
          record[1] = Gracias;
          if(myVR.load(record, 2) >= 0){
            printRecord(record, 2);
            Serial.println(F("loaded."));
          }
        
        cero(); 
         digitalWrite(8,0);digitalWrite(7,1);digitalWrite(6,0);digitalWrite(5,1);digitalWrite(4,1);
        delay(1800);
                 cero();
        break;
        
        case DMusculares:
          myVR.clear();
          record[0] = DMusculares;
          record[1] = Tos;
          record[2] = Fatiga;
          record[3] = DCabeza;
          record[4] = DArticulares;
          record[5] =Gracias;
          if(myVR.load(record, 6) >= 0){
            printRecord(record, 6);
            Serial.println(F("loaded."));
          }
        
        cero(); 
         digitalWrite(8,0);digitalWrite(7,1);digitalWrite(6,1);digitalWrite(5,0);digitalWrite(4,0);
        delay(1800);
                 cero();
        break;
        
        case DCabeza:
          myVR.clear();
          record[0] = Ampollas;
          record[1] = ECutanea;
          record[2] =DCabeza;
          record[3] = DArticulares;
          record[4] = Gracias;
          if(myVR.load(record, 5) >= 0){
            printRecord(record, 5);
            Serial.println(F("loaded."));
          
        }
        cero(); 
         digitalWrite(8,0);digitalWrite(7,1);digitalWrite(6,1);digitalWrite(5,0);digitalWrite(4,1);
        delay(1800);
                 cero();
        break;
        
        case POlfato:
          myVR.clear();
          record[0] =POlfato;
          record[1] =DRespirar ;
          record[2] = Gracias;
          if(myVR.load(record, 3) >= 0){
            printRecord(record, 3);
            Serial.println(F("loaded."));
          }
        
        cero(); 
         digitalWrite(8,0);digitalWrite(7,1);digitalWrite(6,1);digitalWrite(5,1);digitalWrite(4,0);
        delay(1800);
                 cero();
        break;
        
        case DArticulares:
          myVR.clear();
          record[0] =DArticulares ;
          record[1] = DCabeza;
          record[2] = Gracias;
          if(myVR.load(record, 3) >= 0){
            printRecord(record, 3);
            Serial.println(F("loaded."));
          
        }
       cero(); 
         digitalWrite(8,0);digitalWrite(7,1);digitalWrite(6,1);digitalWrite(5,1);digitalWrite(4,1);
        delay(1800);
                 cero();
        break;
        
        case ECutanea:
          myVR.clear();
          record[0] =ECutanea;
          record[1] = GInflamados;
          if(myVR.load(record, 2) >= 0){
            printRecord(record, 2);
            Serial.println(F("loaded."));
          }
        
       cero(); 
         digitalWrite(8,1);digitalWrite(7,0);digitalWrite(6,0);digitalWrite(5,0);digitalWrite(4,0);
        delay(1800);
                 cero();
        break;
        
        case MKoplik:
          myVR.clear();
          record[0] = MKoplik;
          record[1] =Gracias ;
          if(myVR.load(record, 2) >= 0){
            printRecord(record, 2);
            Serial.println(F("loaded."));
          
        }
        cero(); 
         digitalWrite(8,1);digitalWrite(7,0);digitalWrite(6,0);digitalWrite(5,0);digitalWrite(4,1);
        delay(1800);
                 cero();
        break;
        
        case PPeso:
          myVR.clear();
          record[0] =PPeso ;
          record[1] = Gracias;
          if(myVR.load(record, 2) >= 0){
            printRecord(record, 2);
            Serial.println(F("loaded."));
          
        }
       cero(); 
         digitalWrite(8,1);digitalWrite(7,0);digitalWrite(6,0);digitalWrite(5,1);digitalWrite(4,0);
        delay(1800);
                 cero();
        break;
        
        case Mucosidad:
          myVR.clear();
          record[0] =Mucosidad ;
          record[1] =DRespirar ;
          record[2] = Gracias;
          if(myVR.load(record, 3) >= 0){
            printRecord(record, 3);
            Serial.println(F("loaded."));
          
        }
       cero(); 
         digitalWrite(8,1);digitalWrite(7,0);digitalWrite(6,0);digitalWrite(5,1);digitalWrite(4,1);
        delay(1800);
                 cero();
        break;
        
        case Diarrea:
          myVR.clear();
          record[0] = Diarrea;
          record[1] = SHeces;
          record[2] = DAbdominal;
          record[3] =Gracias ;
          if(myVR.load(record, 4) >= 0){
            printRecord(record, 4);
            Serial.println(F("loaded."));
          }
        
        cero(); 
         digitalWrite(8,1);digitalWrite(7,0);digitalWrite(6,1);digitalWrite(5,0);digitalWrite(4,0);
        delay(1800);
                 cero();
        break;
        
        case Nauseas:
          myVR.clear();
          record[0] = Nauseas;
          record[1] =Vomitos ;
          record[2] =Gracias ;
          if(myVR.load(record, 3) >= 0){
            printRecord(record, 3);
            Serial.println(F("loaded."));
          }
        
        cero(); 
         digitalWrite(8,1);digitalWrite(7,0);digitalWrite(6,1);digitalWrite(5,0);digitalWrite(4,1);
        delay(1800);
                 cero();
        break;
        
        case DAbdominal:
          myVR.clear();
          record[0] = DAbdominal;
          record[1] =Diarrea ;
          record[2] =Gracias ;
          if(myVR.load(record, 3) >= 0){
            printRecord(record, 3);
            Serial.println(F("loaded."));
          }
        
        cero(); 
         digitalWrite(8,1);digitalWrite(7,0);digitalWrite(6,1);digitalWrite(5,1);digitalWrite(4,0);
        delay(1800);
                 cero();
        break;
        
        case Vomitos :
          myVR.clear();
          record[0] =Vomitos ;
          record[1] = Ictericia;
          record[2] = Diarrea;
          if(myVR.load(record, 3) >= 0){
            printRecord(record, 3);
            Serial.println(F("loaded."));
          
        }
        cero(); 
         digitalWrite(8,1);digitalWrite(7,0);digitalWrite(6,1);digitalWrite(5,1);digitalWrite(4,1);
        delay(1800);
                 cero();
        break;
        
        case Ictericia:
          myVR.clear();
          record[0] = Ictericia;
          record[1] = DAbdominal;
          if(myVR.load(record, 2) >= 0){
            printRecord(record, 2);
            Serial.println(F("loaded."));
          }
        
        cero(); 
         digitalWrite(8,1);digitalWrite(7,1);digitalWrite(6,0);digitalWrite(5,0);digitalWrite(4,0);
        delay(1800);
                 cero();
        break;
        
        case Llagas:
          myVR.clear();
          record[0] =Llagas ;
          record[1] =Picazon ;
          record[2] = MDolorosa;
          if(myVR.load(record, 3) >= 0){
            printRecord(record, 3);
            Serial.println(F("loaded."));
          }
        
        cero(); 
         digitalWrite(8,1);digitalWrite(7,1);digitalWrite(6,0);digitalWrite(5,0);digitalWrite(4,1);
        delay(1800);
                 cero();
        break;
        
        case MDolorosa:
          myVR.clear();
          record[0] = MDolorosa;
          record[1] = Picazon;
          record[2] = Gracias ;
          if(myVR.load(record, 3) >= 0){
            printRecord(record, 3);
            Serial.println(F("loaded."));
          }
        
       cero(); 
         digitalWrite(8,1);digitalWrite(7,1);digitalWrite(6,0);digitalWrite(5,1);digitalWrite(4,0);
        delay(1800);
                 cero();
        break;
        
        case GInflamados:
          myVR.clear();
          record[0] =GInflamados ;
          record[1] = Gracias;
          if(myVR.load(record, 2) >= 0){
            printRecord(record, 2);
            Serial.println(F("loaded."));
          
        }
        cero(); 
         digitalWrite(8,1);digitalWrite(7,1);digitalWrite(6,0);digitalWrite(5,1);digitalWrite(4,1);
        delay(1800);
                 cero();
        break;
        
        case SHeces:
          myVR.clear();
          record[0] = SHeces;
          record[1] = PPeso;
          record[2] = Gracias;
          if(myVR.load(record, 3) >= 0){
            printRecord(record, 3);
            Serial.println(F("loaded."));
          }
        
        cero(); 
         digitalWrite(8,1);digitalWrite(7,1);digitalWrite(6,1);digitalWrite(5,0);digitalWrite(4,0);
        delay(1800);
                 cero();
        break;
        
        case Ampollas:
          myVR.clear();
          record[0] = Ampollas;
          record[1] =Fatiga ;
          
          if(myVR.load(record, 2) >= 0){
            printRecord(record, 2);
            Serial.println(F("loaded."));
          
        }
       cero(); 
         digitalWrite(8,1);digitalWrite(7,1);digitalWrite(6,1);digitalWrite(5,0);digitalWrite(4,1);
        delay(1800);
                 cero();
        break;

        case GuardarDatosPaciente:
          myVR.clear();
          record[0] =GuardarDatosPaciente;
          record[1] =Gracias;
          
          
          if(myVR.load(record, 2) >= 0){
            printRecord(record, 2);
            Serial.println(F("loaded."));
          
        }
        cero(); 
         digitalWrite(8,1);digitalWrite(7,1);digitalWrite(6,1);digitalWrite(5,1);digitalWrite(4,0);
        delay(1800);
                 cero();
        break;
        
        
        
      default:
        break;
    }
    printVR(buf);
    }
    /** voice recognized */
    
  }

void cero(){
         digitalWrite(8,0);digitalWrite(7,0);digitalWrite(6,0);digitalWrite(5,0);digitalWrite(4,0);
        

  }
