#include <SPI.h>        
#include <Ethernet.h>
#include <EthernetUdp.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 70);
unsigned int localPort = 8888;      // local port to listen on
EthernetUDP udp;

void setup() {
    Ethernet.begin(mac,ip);
    udp.begin(localPort);
}

void send(const String addr, int port, const String str)
{
    udp.beginPacket(addr.c_str(), port);
    udp.write(str.c_str());
    udp.endPacket();
}

void loop() {
    String remote_ip("192.168.0.101");
    String data("hello ~");
    send(remote_ip, 15000, data);
  
    delay(2000);
}
