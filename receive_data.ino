#include <SPI.h>        
#include <Ethernet.h>
#include <EthernetUdp.h>

byte mac[] = {  
  0x01, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 71);
unsigned int localPort = 8888;      // local port to listen on
EthernetUDP Udp;

char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac,ip);
  Udp.begin(localPort);
}

void loop() {
  int packetSize = Udp.parsePacket();
  if(packetSize)
  {
    //Serial.print("Received packet of size ");
    //Serial.println(packetSize);
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

    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
    Serial.println("Contents:");
    Serial.println(packetBuffer);
  }
}
