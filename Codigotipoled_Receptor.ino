#include <Wire.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// Configuración de los pines para el Arduino Uno
SoftwareSerial mySerial(10, 11); // RX en el pin 10, TX en el pin 11
DFRobotDFPlayerMini myDFPlayer;

 int valorxsintoma;
 int nsintoma;

void setup() {
  // Pin del LED en modo salida
  pinMode(13, OUTPUT);
  valorxsintoma=0;
  nsintoma=0;
  // Unimos este dispositivo al bus I2C con dirección 1 (Esclavo 1)
pinMode(4,INPUT);

  pinMode(5,INPUT);

  pinMode(6,INPUT);

  pinMode(7,INPUT);
  pinMode(8,INPUT);
  // Registramos el evento al recibir datos

  Serial.begin(115200); // Inicializamos el puerto serie para la salida de estado

  // Inicializar DFPlayer Mini
  mySerial.begin(9600);
  if (!myDFPlayer.begin(mySerial)) {
    Serial.println(F("No se pudo inicializar el DFPlayer Mini."));
    while (true); // Detiene el programa si no se puede inicializar el DFPlayer
  }
  myDFPlayer.volume(10);  // Ajusta el volumen (0~30)

  Serial.println(F("DFPlayer Mini listo para recibir comandos."));
}

void loop() {
  // Pequeña pausa en el bucle principal
  delay(30);


// Función que se ejecuta siempre que se reciben datos del maestro



    if ((digitalRead(8)==0)&&(digitalRead(7)==0)&&(digitalRead(6)==1)&&(digitalRead(5)==0)&&(digitalRead(4)==0)) {////Fiebre

      valorxsintoma=valorxsintoma+3;
      nsintoma=nsintoma+1;
    } 
    if ((digitalRead(8)==0)&&(digitalRead(7)==0)&&(digitalRead(6)==1)&&(digitalRead(5)==0)&&(digitalRead(4)==1)) {////Tos
      valorxsintoma=valorxsintoma+4;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==0)&&(digitalRead(7)==0)&&(digitalRead(6)==1)&&(digitalRead(5)==1)&&(digitalRead(4)==0)) {///Fatiga
      valorxsintoma=valorxsintoma+5;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==0)&&(digitalRead(7)==0)&&(digitalRead(6)==1)&&(digitalRead(5)==1)&&(digitalRead(4)==1)) {///DGarganta
      valorxsintoma=valorxsintoma+6;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==0)&&(digitalRead(7)==1)&&(digitalRead(6)==0)&&(digitalRead(5)==0)&&(digitalRead(4)==0)) {///Estornudos
      valorxsintoma=valorxsintoma+7;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==0)&&(digitalRead(7)==1)&&(digitalRead(6)==0)&&(digitalRead(5)==0)&&(digitalRead(4)==1)) {///Picazon
      valorxsintoma=valorxsintoma+8;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==0)&&(digitalRead(7)==1)&&(digitalRead(6)==0)&&(digitalRead(5)==1)&&(digitalRead(4)==0)) {///CNasal
      valorxsintoma=valorxsintoma+9;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==0)&&(digitalRead(7)==1)&&(digitalRead(6)==0)&&(digitalRead(5)==1)&&(digitalRead(4)==1)) {///DRespirar
      valorxsintoma=valorxsintoma+11;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==0)&&(digitalRead(7)==1)&&(digitalRead(6)==1)&&(digitalRead(5)==0)&&(digitalRead(4)==0)){////DMusculares
      valorxsintoma=valorxsintoma+12;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==0)&&(digitalRead(7)==1)&&(digitalRead(6)==1)&&(digitalRead(5)==0)&&(digitalRead(4)==1)) {///DCabeza
      valorxsintoma=valorxsintoma+14;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==0)&&(digitalRead(7)==1)&&(digitalRead(6)==1)&&(digitalRead(5)==1)&&(digitalRead(4)==0)) {///POlfato
      valorxsintoma=valorxsintoma+15;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==0)&&(digitalRead(7)==1)&&(digitalRead(6)==1)&&(digitalRead(5)==1)&&(digitalRead(4)==1)) {///DArticulares
      valorxsintoma=valorxsintoma+17;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==0)&&(digitalRead(7)==0)&&(digitalRead(6)==0)&&(digitalRead(5)==0)&&(digitalRead(4)==1)) {///Buenos Dias
      myDFPlayer.play(1); // Reproduce la pista 2
      Serial.println("Buenos Dias");
    }
    if ((digitalRead(8)==0)&&(digitalRead(7)==0)&&(digitalRead(6)==0)&&(digitalRead(5)==1)&&(digitalRead(4)==0)) {////Necesito un diagnostico
      myDFPlayer.play(2); // Reproduce la pista 2
            Serial.println(" Cuales son tus sintomas");

    }
    if ((digitalRead(8)==0)&&(digitalRead(7)==0)&&(digitalRead(6)==0)&&(digitalRead(5)==1)&&(digitalRead(4)==1)) {//////Gracias
      myDFPlayer.play(3); // Reproduce la pista 2
                  Serial.println(" Gracias");
                  valorxsintoma=0; 
                  nsintoma=0;

    }
    if ((digitalRead(8)==1)&&(digitalRead(7)==0)&&(digitalRead(6)==0)&&(digitalRead(5)==0)&&(digitalRead(4)==0)) {///ECutanea
      valorxsintoma=valorxsintoma+18;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==1)&&(digitalRead(7)==0)&&(digitalRead(6)==0)&&(digitalRead(5)==0)&&(digitalRead(4)==1)) {///MKoplik
      valorxsintoma=valorxsintoma+19;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==1)&&(digitalRead(7)==0)&&(digitalRead(6)==0)&&(digitalRead(5)==1)&&(digitalRead(4)==0)) {///Ppeso
      valorxsintoma=valorxsintoma+20;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==1)&&(digitalRead(7)==0)&&(digitalRead(6)==0)&&(digitalRead(5)==1)&&(digitalRead(4)==1)) {///Mucosidad
      valorxsintoma=valorxsintoma+21;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==1)&&(digitalRead(7)==0)&&(digitalRead(6)==1)&&(digitalRead(5)==0)&&(digitalRead(4)==0)){///Diarrea
      valorxsintoma=valorxsintoma+22;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==1)&&(digitalRead(7)==0)&&(digitalRead(6)==1)&&(digitalRead(5)==0)&&(digitalRead(4)==1)) {///Nauseas
      valorxsintoma=valorxsintoma+23;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==1)&&(digitalRead(7)==0)&&(digitalRead(6)==1)&&(digitalRead(5)==1)&&(digitalRead(4)==0)) {///DAbdominal
      valorxsintoma=valorxsintoma+24;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==1)&&(digitalRead(7)==0)&&(digitalRead(6)==1)&&(digitalRead(5)==1)&&(digitalRead(4)==1)) {///Vomitos
      valorxsintoma=valorxsintoma+25;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==1)&&(digitalRead(7)==1)&&(digitalRead(6)==0)&&(digitalRead(5)==0)&&(digitalRead(4)==0)) {///Ictericia
      valorxsintoma=valorxsintoma+26;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==1)&&(digitalRead(7)==1)&&(digitalRead(6)==0)&&(digitalRead(5)==0)&&(digitalRead(4)==1)) {///Llagas
      valorxsintoma=valorxsintoma+27;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==1)&&(digitalRead(7)==1)&&(digitalRead(6)==0)&&(digitalRead(5)==1)&&(digitalRead(4)==0)) {///Mdolorosa
      valorxsintoma=valorxsintoma+28;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==1)&&(digitalRead(7)==1)&&(digitalRead(6)==0)&&(digitalRead(5)==1)&&(digitalRead(4)==1)) {///GInflamados
      valorxsintoma=valorxsintoma+29;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==1)&&(digitalRead(7)==1)&&(digitalRead(6)==1)&&(digitalRead(5)==0)&&(digitalRead(4)==0)) {//SHeces
      valorxsintoma=valorxsintoma+30;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==1)&&(digitalRead(7)==1)&&(digitalRead(6)==1)&&(digitalRead(5)==0)&&(digitalRead(4)==1)) {///Ampollas
      valorxsintoma=valorxsintoma+31;
      nsintoma=nsintoma+1;
    }
    if ((digitalRead(8)==1)&&(digitalRead(7)==1)&&(digitalRead(6)==1)&&(digitalRead(5)==1)&&(digitalRead(4)==0)) {///GuardarDatosdelPaciente
      myDFPlayer.play(4); // Reproduce la pista 2
      Serial.println("Introduzca sus datos mediante el teclado");
    }
    
    delay(1000);
    
    
    

    if((valorxsintoma==24)&&(nsintoma>=4)&&(nsintoma<=5)){////Gripe
    myDFPlayer.play(5); // Reproduce la pista 2
    delay(5000);
    }
    if((valorxsintoma==26)&&(nsintoma>=4)&&(nsintoma<=5)){////Resfriado
    myDFPlayer.play(6); // Reproduce la pista 2
    }
    if((valorxsintoma==33)&&(nsintoma>=4)&&(nsintoma<=5)){////Covid19
    myDFPlayer.play(7); // Reproduce la pista 2
    }
    if((valorxsintoma==46)&&(nsintoma>=4)&&(nsintoma<=5)){////Dengue
    myDFPlayer.play(8); // Reproduce la pista 2
    }
    if((valorxsintoma==44)&&(nsintoma>=4)&&(nsintoma<=5)){////Sarampion
    myDFPlayer.play(9); // Reproduce la pista 2
    }
    if((valorxsintoma==53)&&(nsintoma>=4)&&(nsintoma<=5)){////Varicela
    myDFPlayer.play(10); // Reproduce la pista 2
    }
    if((valorxsintoma==41)&&(nsintoma>=4)&&(nsintoma<=5)){////Bronquitis
    myDFPlayer.play(11); // Reproduce la pista 2
    }
    if((valorxsintoma==97)&&(nsintoma>=4)&&(nsintoma<=5)){////Gastro
    myDFPlayer.play(12); // Reproduce la pista 2
    }
    if((valorxsintoma==103)&&(nsintoma>=4)&&(nsintoma<=5)){////Hepatitis
    myDFPlayer.play(13); // Reproduce la pista 2
    }
    if((valorxsintoma==66)&&(nsintoma>=4)&&(nsintoma<=5)){////Herpes
    myDFPlayer.play(14); // Reproduce la pista 2
    }
    if((valorxsintoma==96)&&(nsintoma>=4)&&(nsintoma<=5)){////Colitis
    myDFPlayer.play(15); // Reproduce la pista 2
    }
    if((valorxsintoma==64)&&(nsintoma>=4)&&(nsintoma<=5)){////Rubeola
    myDFPlayer.play(16); // Reproduce la pista 2
    }
    Serial.println(valorxsintoma);
    Serial.println(nsintoma);
  delay(1000);
  }





