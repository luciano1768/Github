
//#include <SoftwareSerial.h>

//SoftwareSerial btSerial(2, 3); // RX, TX

#include <Servo.h>
//Servo ServoMot
Servo ServoG;  // create servo object to control a servo
Servo ServoC1;  // create servo object to control a servo
Servo ServoC2;  // create servo object to control a servo
Servo ServoT;  // create servo object to control a servo

int LecturaCAD = 0;

void setup() {

  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  // put your setup code here, to run once:

    //btSerial.begin(9600);
    //btSerial.print("AT+ROLE0"); //seteo como esclavo
    //btSerial.print("AT+ROLE1"); //seteo como master
Serial.begin(19200);
  
Serial.println("MULTI-SIS Expansor E/S Digital para PC (PROPOSITOS MULTIPLES)");
for(int n = 4 ; n < 54 ; n++){ pinMode(n,OUTPUT); digitalWrite(n,LOW); }
//Serial.println("ATENCION - OPERAR CON LOGICA DE 3.3V");
//delay(10000);
//btSerial.print("test I am slave ");
}



int contador = 0;
void loop() {
  // put your main code here, to run repeatedly:

  if (contador == 0 ) {contador ++; Rutina1();}


 // if ( btSerial.available()  ) {char i = char(btSerial.read());
  if (Serial.available()   ) {char i = char(Serial.read()  );
      
      switch (i){
        case 'I': //INP
            INP(); break;
        case 'O': //OUT
            OUT(); break;
        case 'P': //PWM
            PWMM(); break;
        case 'A': //ANL
            ANALOG(); break;
        case 'M': //MLS
            Serial.print("MilliSeg= "); Serial.println(millis()); break;
        case 'm': //MCS
            Serial.print("microSeg= "); Serial.println(micros()); break;
        case 'R': //RDM
            Serial.print("Random= "); Serial.println(random(0,4095)); break;
        case 'X': //MAP
            MAPEADO();break;
        case 'x':
          
           Serial.println("MULTI-SIS Expansor E/S Digital para PC (Propositos Múltiples)"); 
           Rutina1();
           break;

           
// ADAPTACION NASA
        case 'G'://ROTAR SERVO X GRADOS
              //Rotar();
              break;
        case 'c':// CODO 1
             // Codo1();
              break;
        case 'C':// CODO 2
             // Codo2();
              break;
        case 'T':// TENAZA
              //Pinza();
              break;
        case 'F':// carro
              //AvanceCarro();
              break;
        case 'B':// carro
              //RetrocesoCarro();
              break;
        case 'i':// carro
              //Izquierda();
              break;
        case 'd':// carro
             //Derecha();
              break;
      }
  }

}


String inSer = ""; int tipo = 0;
void INP(){//Serial.println("INP");
    int Pin = 255; 
    do{
        delay(5);
        inSer = String(char(Serial.read()));  delay(1);
        inSer += String(char(Serial.read())); delay(1);
        //Serial.println(inSer);
        Pin = inSer.toInt();
        if (Pin == 0) {Pin = 50;}
        if (Pin == 1) {Pin = 51;}
        if (Pin == 20) {Pin = 52;}
        if (Pin == 21) {Pin = 53;}
         // int(inSer);
        inSer = String(char(Serial.read())); delay(1);
        tipo = inSer.toInt();
        switch (tipo){
          case 0:
              pinMode(Pin,INPUT); break;
               
          case 1:
              pinMode(Pin,INPUT_PULLUP);break;
        
        }
     }while(Serial.read() == char(13));
        //Serial.print(Pin); Serial.print("   TIPO "); Serial.println(tipo); Serial.println(tipo);
        if (Pin == 50) {Pin = 0;}
        if (Pin == 51) {Pin = 1;}
        if (Pin == 52) {Pin = 20;}
        if (Pin == 53) {Pin = 21;}
        Serial.print("I"); Serial.print(Pin); Serial.print("="); Serial.println(digitalRead(Pin)); 
}


void OUT(){ 
  //Serial.println("OUT");
    int Pin = 255; 
    int Estado = 0;
    do{
        delay(5);
        inSer = String(char(Serial.read()));  delay(1);
        inSer += String(char(Serial.read())); delay(1);
        //Serial.println(inSer);
        Pin = inSer.toInt();
        if (Pin == 0) {Pin = 50;}
        if (Pin == 1) {Pin = 51;}
        if (Pin == 20) {Pin = 52;}
        if (Pin == 21) {Pin = 53;}
         // int(inSer);
        inSer = String(char(Serial.read())); delay(1);
        Estado = inSer.toInt();
        switch (Estado){
          case 0:
              pinMode(Pin,OUTPUT); 
              digitalWrite(Pin, LOW); break;
               
          case 1:
              pinMode(Pin,OUTPUT);
              digitalWrite(Pin, HIGH); break;
        }
     }while(Serial.read() == char(13));
        //Serial.print(Pin); Serial.print("   Estado "); Serial.println(Estado);
        if (Pin == 50) {Pin = 0;}
        if (Pin == 51) {Pin = 1;}
        if (Pin == 52) {Pin = 20;}
        if (Pin == 53) {Pin = 21;}
        Serial.print("O"); Serial.print(Pin); Serial.print("="); Serial.println(Estado); 
}



void PWMM(){ 
  //Serial.println("PWM");
    int Pin = 255; 
    int VALOR = 0;

        delay(5);
        inSer = String(char(Serial.read()));  delay(1);
        inSer += String(char(Serial.read())); delay(1);
        //Serial.println(inSer);
        Pin = inSer.toInt();
        if (Pin == 0) {Pin = 50;}
        if (Pin == 1) {Pin = 51;}
        if (Pin == 20) {Pin = 52;}
        if (Pin == 21) {Pin = 53;}
         // int(inSer);
        inSer = String(char(Serial.read())); delay(1);
        inSer += String(char(Serial.read())); delay(1);
        inSer += String(char(Serial.read())); delay(1);
        inSer += String(char(Serial.read())); delay(1);
        VALOR = inSer.toInt();
        //analogWriteResolution(10); // PARA ARDUINO DUE
        analogWrite(Pin, VALOR);
        //float v = (3.3/1023)* VALOR;
        if (Pin == 50) {Pin = 0;}
        if (Pin == 51) {Pin = 1;}
        if (Pin == 52) {Pin = 20;}
        if (Pin == 53) {Pin = 21;}
        Serial.print("P"); Serial.print(Pin); Serial.print("="); Serial.println(VALOR);
        
}


void ANALOG(){
  //Serial.println("ANALOG");
    int Pin = 255; 
    
        delay(5);
        //inSer = char(Serial.read());  delay(1);
        inSer = String(char(Serial.read()));  delay(1);
        inSer += String(char(Serial.read())); delay(1);
        //Serial.println(inSer);
        Pin = inSer.toInt();
       /// analogReadResolution(12); 
        Serial.print("A"); Serial.print(Pin); Serial.print("="); 
        switch (Pin){
          case 0:
              Serial.println(analogRead(A0)); break;
          case 1:
              Serial.println(analogRead(A1)); break;
          case 2:
              Serial.println(analogRead(A2)); break;
          case 3:
              Serial.println(analogRead(A3)); break;
          case 4:
              Serial.println(analogRead(A4)); break;
          case 5:
              Serial.println(analogRead(A5)); break;
//          case 6:
//              Serial.println(analogRead(A6)); break;
//          case 7:
//              Serial.println(analogRead(A7)); break;
//          case 8:
//              Serial.println(analogRead(A8)); break;
//          case 9:
//              Serial.println(analogRead(A9)); break;
//          case 10:
//              Serial.println(analogRead(A10)); break;
//          case 11:
//              Serial.println(analogRead(A11)); break;
   
        }          

}


void MAPEADO(){
  int cMax = 0;
  int cMin = 0;
  int xMax = 0;
  int xMin = 0;
  int vInp = 0;
  int vOut = 0;
  String in = "";
  double t = millis();
    delay(5); 
    inSer = "";
    do{//adquiero vInp
        in = String(char(Serial.read()));  delay(1);
        if(in == ";"){break;}
        if(in != ";"){inSer += in; in = "";}
    }while((millis() - t) < 10);
    vInp = inSer.toInt();

LEERCONVERSOR(vInp);
    
    t = millis();
    inSer = ""; in = "";
    do{//adquiero cMin
        in = String(char(Serial.read()));  delay(1);
        if(in == ";"){break;}
        if(in != ";"){inSer += in;in = "";}
    }while((millis() - t) < 10);
    cMin = inSer.toInt();


    t = millis();
    inSer = ""; in = "";
    do{//adquiero cMax
        in = String(char(Serial.read()));  delay(1);
        if(in == ";"){break;}
        if(in != ";"){inSer += in;in = "";}
    }while((millis() - t) < 10);
    cMax = inSer.toInt();


    t = millis();
    inSer = ""; in = "";
    do{//adquiero xMin
        in = String(char(Serial.read()));  delay(1);
        if(in == ";"){break;}
        if(in != ";"){inSer += in;in = "";}
    }while((millis() - t) < 10);
    xMin = inSer.toFloat();


    t = millis();
    inSer = ""; in = "";
    do{//adquiero xMax
        in = String(char(Serial.read()));  delay(1);
        if(in == ";"){break;}
        if(in != ";"){inSer += in;in = "";}
    }while((millis() - t) < 10);
    xMax = inSer.toFloat();

    Serial.print("CAD=");Serial.println(vInp);
    Serial.print("vInp=");Serial.println(LecturaCAD);
    Serial.print("cMin=");Serial.println(cMin); 
    Serial.print("cMax=");Serial.println(cMax); 
    Serial.print("xMin=");Serial.println(xMin); 
    Serial.print("xMax=");Serial.println(xMax); 


    
    vOut = map(LecturaCAD,cMin,cMax,xMin,xMax);
    
 
    Serial.print("XMap=");Serial.println(vOut); 
  
}



void LEERCONVERSOR(int c ){
    LecturaCAD = 0;
    LecturaCAD = analogRead(c);
  
}

//void Rotar(){int VALOR = 0;
void Rotar(int VALOR){
  Serial.print("Rotar = "); Serial.println(VALOR);
    ServoG.attach(8);
    

        delay(5);
        inSer = String(char(Serial.read())); delay(1);
        inSer += String(char(Serial.read())); delay(1);
        inSer += String(char(Serial.read())); delay(1);
        //inSer += String(char(Serial.read())); delay(1);
        //VALOR = inSer.toInt();

        ServoG.write(VALOR); 
        //Serial.print("Rotar");  Serial.print("="); Serial.println(VALOR);
        
  }

//void Codo1(){int VALOR = 0;
void Codo1(int VALOR ){
  Serial.print("Codo1 = "); Serial.println(VALOR);
    ServoC1.attach(9);
    

        delay(5);
        inSer = String(char(Serial.read())); delay(1);
        inSer += String(char(Serial.read())); delay(1);
        inSer += String(char(Serial.read())); delay(1);
        //inSer += String(char(Serial.read())); delay(1);
        //VALOR = inSer.toInt();

        ServoC1.write(VALOR); 
        //Serial.print("Codo 1");  Serial.print("="); Serial.println(VALOR);
        
  }

  
//void Codo2(){int VALOR = 0;
void Codo2(int VALOR){
  Serial.print("Codo2 = "); Serial.println(VALOR);
    ServoC2.attach(10);
    

        delay(5);
        inSer = String(char(Serial.read())); delay(1);
        inSer += String(char(Serial.read())); delay(1);
        inSer += String(char(Serial.read())); delay(1);
        //inSer += String(char(Serial.read())); delay(1);
        //VALOR = inSer.toInt();

        ServoC2.write(VALOR); 
        //Serial.print("Codo 2");  Serial.print("="); Serial.println(VALOR);
        
  }

void Pinza(int VALOR){
//void Pinza(){int VALOR = 0;
  Serial.print("Pinza = "); Serial.println(VALOR);
    ServoT.attach(11);
    

        delay(5);
        inSer = String(char(Serial.read())); delay(1);
        inSer += String(char(Serial.read())); delay(1);
        inSer += String(char(Serial.read())); delay(1);
        //inSer += String(char(Serial.read())); delay(1);
        //VALOR = inSer.toInt();

        ServoT.write(VALOR); 
        //
        Serial.print("Pinza");  Serial.print("="); Serial.println(VALOR);   
 }


  void AvanceCarro(int VALOR = 0){
    int Pin = 7; 
    digitalWrite(6,LOW);
    
//
//        delay(5);
//        inSer = String(char(Serial.read())); delay(1);
//        inSer += String(char(Serial.read())); delay(1);
//        inSer += String(char(Serial.read())); delay(1);
//        VALOR = inSer.toInt();
//        VALOR = map(VALOR,0,255,255,0);
//        //analogWriteResolution(10); // PARA ARDUINO DUE
        analogWrite(Pin, VALOR);
        Serial.print("P"); Serial.print(Pin); Serial.print("="); Serial.println(VALOR);
 }

  void RetrocesoCarro(int VALOR = 0){
    int Pin = 6; 
    digitalWrite(7,LOW);
    //int VALOR = 0;

//        delay(5);
//        inSer = String(char(Serial.read())); delay(1);
//        inSer += String(char(Serial.read())); delay(1);
//        inSer += String(char(Serial.read())); delay(1);
//        VALOR = inSer.toInt();
//        VALOR = map(VALOR,0,255,255,0);
        //analogWriteResolution(10); // PARA ARDUINO DUE
        analogWrite(Pin, VALOR);
        Serial.print("B"); Serial.print(Pin); Serial.print("="); Serial.println(VALOR);
 }


  void Izquierda(int VALOR = 0){
     int Pin = 5; 
    digitalWrite(4,LOW);
    
//        delay(5);
//        inSer = String(char(Serial.read())); delay(1);
//        inSer += String(char(Serial.read())); delay(1);
//        inSer += String(char(Serial.read())); delay(1);
//        VALOR = inSer.toInt();
//        //analogWriteResolution(10); // PARA ARDUINO DUE
        analogWrite(Pin, VALOR);
        Serial.print("P"); Serial.print(Pin); Serial.print("="); Serial.println(VALOR);
 }


  void Derecha(int VALOR = 0){
     int Pin = 4; 
    digitalWrite(5,LOW);
//
//        delay(5);
//        inSer = String(char(Serial.read())); delay(1);
//        inSer += String(char(Serial.read())); delay(1);
//        inSer += String(char(Serial.read())); delay(1);
//        VALOR = inSer.toInt();
        //analogWriteResolution(10); // PARA ARDUINO DUE
        analogWrite(Pin, VALOR);
        Serial.print("P"); Serial.print(Pin); Serial.print("="); Serial.println(VALOR);
 }



void Rutina1(){
  AvanceCarro(50); delay(500);
  AvanceCarro(100); delay(500);
  AvanceCarro(150); delay(500);
  AvanceCarro(255); delay(500);
  AvanceCarro(0); delay(1000); //detengo
  
  RetrocesoCarro(50); delay(500);
  RetrocesoCarro(150); delay(500);
  RetrocesoCarro(255); delay(500);
  RetrocesoCarro(0); delay(0); //detengo
//
//  Derecha(255); delay(1000);
//  Derecha(0); //delay(0);
//  Izquierda(255); delay(1000);
//  Izquierda(0); //delay(0);
//taladro


  digitalWrite(2,HIGH);delay(1000);
  digitalWrite(3,HIGH);delay(1000);
  digitalWrite(3,LOW);delay(1000);
  digitalWrite(3,LOW);//delay(1000);

  
  Rotar(0); delay(1500);
  Codo1(10); delay(1500); //arriba
  Codo1(90); delay(500);  //abajo
  Codo1(10); delay(1500); //arriba
  Rotar(180); delay(1500); //giro
  Codo1(90); delay(500);  //abajo
  Codo1(10); delay(1500); //arriba
  Rotar(180); delay(1500);
  Rotar(0); delay(500);
  Codo1(10); delay(0);


  

  
//  Codo1(10); delay(500);
//  Codo2(10); delay(1000);
//  Codo2(90); delay(1000);
//  Codo2(180); delay(1000);
  
  
}























 
 
/*
No Name Description CC254X
1 UART_RTS UART interface P1_5
2 UART_TX UART interface P1_6 
HM Bluetooth module datasheet
-------------------------------------------------------Last Version V524 2014-03-08 １４
3 UART_CTS UART interface P1_4
4 UART_RX UART interface P1_7
5 NC NC P2_1
6 NC NC P2_2
7 NC NC PIN2
8 NC NC PIN3
9 VCC V3.3 VCC
10 NC NC or VCC
11 RESETB Reset if low <100ms RESET_N
12 GND Ground GND
13 PIO3 input/output line P1_1
14 PIO2 input/output line P1_0
15 PIO1 System LED P0_7
16 PIO0 System KEY P0_6 

*/


