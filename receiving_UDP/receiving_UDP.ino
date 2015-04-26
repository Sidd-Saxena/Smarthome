#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>


// Replace "**" in the mac and ip array with assigned digits
byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };
IPAddress ip(192, 168, 1, 105);


int pin=9;
// -------- Do not change the section below -----------------
const unsigned int localPort = 1025;  // Process ID port
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet, // Buffer for incoming data
IPAddress remoteIP(192, 168, 1, 101);        // Holds source IP address from incoming data
unsigned int remotePort;  // Holds source port # from incoming data
//LiquidCrystal lcd(8, 6, 7, 5, 3, 4); // Set up LCD screen on open pins
      // ------------------------------------------------------------
//unsigned int localPort = 8888;      // local port to listen on
 EthernetUDP Udp;
void setup()
{
    Ethernet.begin(mac,ip);    // Set up the Ethernet Shield
    Udp.begin(localPort);      // Open a socket for this port
    Serial.begin(9600);        // Set up serial monitor with PC
}

void loop()
{    
  int packetSize = Udp.parsePacket();
  if(packetSize)
  {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remote = Udp.remoteIP();
    for (int i =0; i < 4; i++)
    {
      Serial.print(remote[i], DEC);
      if (i < 3)
      {
        Serial.print(".");
      }
    }
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
    Serial.println("Contents:");
    Serial.println(packetBuffer);
    digitalWrite(pin,HIGH);
      
    }
}

