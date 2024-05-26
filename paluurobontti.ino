#include "WiFi.h"
#include "wifi_credentials.h"
#include "AsyncUDP.h"
AsyncUDP udp;

float speed = 0;
float turn = 0;

int motor1Pin1 = 33;
int motor1Pin2 = 27;
int enable1Pin = 12;

int motor2Pin1 = 15;
int motor2Pin2 = 32;
int enable2Pin = 14;

int buzzerPin = 16;

int resolution = 8;
int freq = 30000;

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
  Serial.println("Starting UDP listener");
  if (udp.listen(1234))
  {
    udp.onPacket([](AsyncUDPPacket packet)
                 {
        String myString = (const char*)packet.data();
        char delimiter = '/';
        int delIndex = myString.indexOf(delimiter);
        speed = myString.substring(0, delIndex).toFloat();
        turn = myString.substring(delIndex+1, myString.length()).toFloat(); });
  }
  Serial.println("setup complete");

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);

  pinMode(buzzerPin, OUTPUT);

  ledcSetup(0, freq, resolution);
  ledcSetup(1, freq, resolution);
  ledcAttachPin(enable1Pin, 0);
  ledcAttachPin(enable2Pin, 1);
}

void loop()
{
  int speed_right = (int)(255.0 * (speed - turn));
  int value_right = min(255, abs(speed_right));
  analogWrite(enable1Pin, value_right);
  if (speed_right > 0)
  {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
  }
  else
  {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
  }

  int speed_left = (int)(255.0 * (speed + turn));
  int value_left = min(255, abs(speed_left));
  analogWrite(enable2Pin, value_left);
  if (speed_left > 0)
  {
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
  }
  else
  {
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
  }

  if (speed > 0)
  {
    tone(buzzerPin, 1000);
  }
  else
  {
    noTone(buzzerPin);
  }

  Serial.println(speed);
  Serial.println(turn);

  delay(100);
}