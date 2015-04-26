#include <SPI.h>
#include <Ethernet.h>
#include<EthernetUdp.h>


// Fill in the analog pin connected to the temperature sensor
const int pingPin = 7;
const int lightpin = A0;
int TempPin = A2;
long duration, inches, cm;
 long light_value;
 int flag_light,flag_temp,flag_ping;
// Enter a MAC address and IP address for your controller below.
byte mac[] = {0x2a, 0x11, 0x11, 0xb1, 0x41, 0xf2};
IPAddress ip(192, 168, 1, 107);

EthernetServer server(80);  // (port 80 is default for HTTP):
EthernetUDP Udp;
 char  ReplyBuffer[5];
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);// Set up serial monitor with PC
   pinMode(pingPin, INPUT);
  while(!Serial){
    ; //wait for serial port to connect. Needed for Leonardo
  }
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);// Set up the Ethernet Shield
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // listen for incoming clients
          pinMode(pingPin, OUTPUT);
          digitalWrite(pingPin, LOW);
          delayMicroseconds(5);
          digitalWrite(pingPin, HIGH);
          delayMicroseconds(5);
          digitalWrite(pingPin, LOW);
          pinMode(pingPin, INPUT);
          duration = pulseIn(pingPin, HIGH);
          //reading ligh value
          light_value=analogRead(lightpin);
          //reading temperature
          float sensorReading = analogRead(TempPin); //read temperatuyre from the sensor
          sensorReading=(((sensorReading*5000)/1024)-500)/10;
          int degreeF = ((sensorReading*9)/5)+32; //convert the value of
 
          // convert the time into a distance
           inches = duration/ 74 / 2;
          //logic to check ping
           if (inches < 25)
           {
             flag_ping=1;
             char  ReplyBuffer[]="Motion";
            }
            else
             {
             //Serial.println("Its Fine");
               flag_ping=0;
               }
 
              //logic to check temperature
             if (degreeF > 90)
             {
               flag_temp=1;
               char ReplyBuffer[] ="Fire";
             }
             else
             {
   //Serial.println("Its Fine");
             flag_temp=0;
             }
             //logic to check light
             if (light_value < 50)
             {
                flag_light=1;
                char  ReplyBuffer[]="light";
               }
             else
               {
               //Serial.println("Its Fine");
               flag_light=0;
                 }
  //delay(1);

    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
      
}
