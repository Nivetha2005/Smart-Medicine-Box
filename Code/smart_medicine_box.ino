#define BLYNK_TEMPLATE_ID "TMPL3T4dNtqXM"
#define BLYNK_TEMPLATE_NAME "medicine box node"
#define BLYNK_AUTH_TOKEN "xzWmupOKSQXzniBwTduS6Irpq_82tXxk"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <NewPing.h>
#include <Servo.h>
#include <time.h>

char ssid[] = "Ek";
char pass[] = "jhan0421";

#define TRIG_PIN 5
#define ECHO_PIN 4
#define SERVO_PIN 14
#define BUZZER_PIN 12

#define MAX_DISTANCE 200
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

Servo servo;

BlynkTimer timer;
int scheduledHour = -1, scheduledMin = -1;
bool alreadyChecked = false;

int pillCount = 5;
const int refillThreshold = 2;
bool refillAlertTriggered = false;

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 19800;
const int daylightOffset_sec = 0;

BLYNK_WRITE(V1) {
  scheduledHour = param.asInt();
  Serial.print("Hour set to: "); Serial.println(scheduledHour);
}

BLYNK_WRITE(V3) {
  scheduledMin = param.asInt();
  Serial.print("Minute set to: "); Serial.println(scheduledMin);
}

BLYNK_WRITE(V2) {
  pillCount = param.asInt();
  Serial.print("Pill count set to: ");
  Serial.println(pillCount);

  if (refillAlertTriggered && pillCount > refillThreshold) {
    pillCount = 10;
    Serial.println("Pill count auto-reset after refill.");
    refillAlertTriggered = false;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  servo.attach(SERVO_PIN);
  servo.write(0);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected.");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  timer.setInterval(1000L, checkTime);
  Serial.println("Setup complete.");
}

void loop() {
  Blynk.run();
  timer.run();
}

void checkTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) return;

  int currentHour = timeinfo.tm_hour;
  int currentMin = timeinfo.tm_min;

  if (scheduledHour == -1 || scheduledMin == -1) return;

  if (currentHour == scheduledHour && currentMin == scheduledMin && !alreadyChecked) {
    Serial.println("It's time! Checking for motion...");
    Blynk.logEvent("take_medicine", "🕒 Time to take your medicine!");
    delay(10000);

    int distance = sonar.ping_cm();
    Serial.print("Detected distance: "); Serial.println(distance);

    if (distance > 0 && distance < 15) {
      giveMedicine();
      Blynk.logEvent("took_medicine", "🎉 Yay! You took your medicine!");
    } else {
      Blynk.logEvent("missed_medicine", "⚠️ You missed your medicine!");
    }

    alreadyChecked = true;
  }

  if (!(currentHour == scheduledHour && currentMin == scheduledMin)) {
    alreadyChecked = false;
  }

  checkRefill();
}

void giveMedicine() {
  tone(BUZZER_PIN, 1000);
  delay(1000);
  noTone(BUZZER_PIN);

  servo.write(90);
  delay(3000);
  servo.write(0);

  pillCount--;
  Serial.print("Pill count: "); Serial.println(pillCount);
}

void checkRefill() {
  if (pillCount <= refillThreshold && !refillAlertTriggered) {
    Blynk.logEvent("refill_alert", "💊 Please refill your medicine!");
    refillAlertTriggered = true;
  }
}
