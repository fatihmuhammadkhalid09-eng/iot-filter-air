// from bylink
#define BLYNK_TEMPLATE_ID "ID"
#define BLYNK_TEMPLATE_NAME "NAME"
#define BLYNK_AUTH_TOKEN "TOKEN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

char ssid[] = "Your SSID";
char pass[] = "your PASS";

// RX, TX (ESP)
SoftwareSerial megaSerial(D8, D7);

// Virtual Pins
#define VP_PH1 V7
#define VP_PH2 V12
#define VP_TURB1 V6
#define VP_TURB2 V11
#define VP_TDS V8
#define VP_TEMP V9
#define VP_MANUAL_POMPA V5
#define VP_MANUAL_VALVEA V10
#define VP_MANUAL_VALVEB V13

String buffer = "";

// ===== MANUAL CONTROL =====
BLYNK_WRITE(VP_MANUAL_POMPA) {
  megaSerial.println("MANUAL_POMPA:" + String(param.asInt()));
}

BLYNK_WRITE(VP_MANUAL_VALVEA) {
  megaSerial.println("MANUAL_VALVEA:" + String(param.asInt()));
}

BLYNK_WRITE(VP_MANUAL_VALVEB) {
  megaSerial.println("MANUAL_VALVEB:" + String(param.asInt()));
}

void setup() {
  Serial.begin(9600);        // Debug
  megaSerial.begin(9600);   // ke Mega
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
  bacaDariMega();
}

void bacaDariMega() {
  while (megaSerial.available()) {
    char c = megaSerial.read();
    if (c == '\n') {
      prosesData(buffer);
      buffer = "";
    } else {
      buffer += c;
    }
  }
}

void prosesData(String data) {
  float v[6];
  int idx = 0;

  for (int i = 0; i < 6; i++) {
    int p = data.indexOf(',');
    if (p == -1 && i < 5) return;
    v[i] = (i < 5) ? data.substring(0, p).toFloat()
                   : data.toFloat();
    data = data.substring(p + 1);
  }

  Blynk.virtualWrite(VP_PH1, v[0]);
  Blynk.virtualWrite(VP_PH2, v[1]);
  Blynk.virtualWrite(VP_TURB1, v[2]);
  Blynk.virtualWrite(VP_TURB2, v[3]);
  Blynk.virtualWrite(VP_TDS, v[4]);
  Blynk.virtualWrite(VP_TEMP, v[5]);
}
