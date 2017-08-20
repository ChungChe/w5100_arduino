#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>
#include "DHT.h"

#define DHTPIN1 2     // what pin we're connected 
#define DHTTYPE DHT22   // DHT 22  (AM2302)

byte mac[] = {
    0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF
};

IPAddress ip(192, 168, 0, 70);
IPAddress dnServer(168, 95, 1, 1);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

EthernetServer server(80);

DHT dht1(DHTPIN1, DHTTYPE);

void setup() {
    Serial.begin(9600);
    dht1.begin();
    
    Ethernet.begin(mac, ip, dnServer, gateway, subnet);
    server.begin();
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());
}

void loop() {
    // Wait a few seconds between measurements.
    delay(2000);
    float h1 = dht1.readHumidity();
    float t1 = dht1.readTemperature();
    if (isnan(h1) || isnan(t1)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
    // listen for incoming clients
    EthernetClient client = server.available();
    if (client) {
        Serial.println("new client");
        // an http request ends with a blank line
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                Serial.write(c);
                // if you've gotten to the end of the line (received a newline
                // character) and the line is blank, the http request has ended,
                // so you can send a reply
                if (c == '\n' && currentLineIsBlank) {
                    // send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close");  // the connection will be closed after completion of the response
                    //client.println("Refresh: 5");  // refresh the page automatically every 5 sec
                    client.println();
                    client.println("<!DOCTYPE HTML>");
                    client.println("<html>");
                    // output the value of each analog input pin

                    client.print("Humidity: ");
                    client.print(h1);     
                    
                    client.print("Temperature: ");
                    client.print(t1);

                    client.println("</html>");
                    break;
                }
                if (c == '\n') {
                    // you're starting a new line
                    currentLineIsBlank = true;
                }
                else if (c != '\r') {
                    // you've gotten a character on the current line
                    currentLineIsBlank = false;
                }
            }
        }
        // give the web browser time to receive the data
        delay(1);
        // close the connection:
        client.stop();
        Serial.println("client disconnected");
    }
}

