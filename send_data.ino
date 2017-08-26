#include <SPI.h>        
#include <Ethernet.h>
#include <EthernetUdp.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 70);
unsigned int localPort = 8888;      // local port to listen on
EthernetUDP Udp;

void setup() {
  // start the Ethernet and UDP:
  Ethernet.begin(mac,ip);
  Udp.begin(localPort);
}

void send(char* addr, int port, char *str)
{
  Udp.beginPacket(addr, port);
  Udp.write(str);
  Udp.endPacket();
}

void loop() {
  char buf[16] = "192.168.0.71";
  char data[64] = "hello ~";
  send("192.168.0.71", 8888, data);
  
  delay(2000);
}
