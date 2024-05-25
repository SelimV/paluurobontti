#include "WiFi.h"
#include "wifi_credentials.h"
#include "AsyncUDP.h"
AsyncUDP udp;

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    if (udp.listen(1234))
    {
        udp.onPacket([](AsyncUDPPacket packet)
                     {
        String myString = (const char*)packet.data();
        Serial.println(myString); });
    }
}

void loop()
{

    digitalWrite(LED_BUILTIN, HIGH);

    delay(500);

    digitalWrite(LED_BUILTIN, LOW);

    delay(1000);
}