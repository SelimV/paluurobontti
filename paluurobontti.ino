#include "WiFi.h"
#include "wifi_credentials.h"
#include "AsyncUDP.h"
AsyncUDP udp;

float speed = 0;
float turn = 0;

int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14;

int motor2Pin1 = 33; 
int motor2Pin2 = 32; 
int enable2Pin = 35;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
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
    Serial.println("Starting UDP listener");
    if (udp.listen(1234))
    {
      udp.onPacket([](AsyncUDPPacket packet) {
        String myString = (const char*)packet.data();
        char delimiter = '/';
        int delIndex = myString.indexOf(delimiter);
        speed = myString.substring(0, delIndex).toFloat();
        turn = myString.substring(delIndex+1, myString.length()).toFloat();
      });
    }
    Serial.println("setup complete");

    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(enable1Pin, OUTPUT);
    ledcSetup(pwmChannel, freq, resolution);
    ledcAttachPin(enable1Pin, pwmChannel);
}

void loop()
{
  Serial.println(speed);
  Serial.println(turn);
  digitalWrite(LED_BUILTIN, HIGH);

  delay(100);

  digitalWrite(LED_BUILTIN, LOW);

  delay(100);

  //Serial.println("Moving Backwards");
  //digitalWrite(motor1Pin1, HIGH);
  //digitalWrite(motor1Pin2, LOW);

  //digitalWrite(motor1Pin1, HIGH);
  //digitalWrite(motor1Pin2, LOW);

  //while (dutyCycle <= 255){
  //  ledcWrite(pwmChannel, dutyCycle);
  //  Serial.print("Forward with duty cycle: ");
  //  Serial.println(dutyCycle);
  //  dutyCycle = dutyCycle + 5;
  //  delay(500);
  ledcWrite(pwmChannel, dutyCycle);
  analogWrite(motor1Pin1, )
  analogWrite(motor1Pin2, min())
  analogWrite(motor2Pin2, max())
  analogWrite(motor2Pin2, min())
  
}