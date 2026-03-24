#include <OneWire.h>
#include <DallasTemperature.h>

#define SensorPin A0     // pH
#define TdsPin A2        // TDS
#define TurbidityPin A1  // NTU
#define TempPin 7        // DS18B20
#define FloatPin 2       // Pelampung
#define RelayPin 10      // Pompa
#define ValvePin 8       // Valve

OneWire oneWire(TempPin);
DallasTemperature sensors(&oneWire);

unsigned long lastSample = 0;
const unsigned long interval = 1000;

bool manualPompa = false;
bool manualValve = false;

void setup() {
  Serial.begin(9600);     // for debugging
  Serial1.begin(9600);    // for communication to ESP8266

  pinMode(RelayPin, OUTPUT);
  pinMode(ValvePin, OUTPUT);
  pinMode(FloatPin, INPUT_PULLUP);

  digitalWrite(RelayPin, HIGH);  // Pompa OFF
  digitalWrite(ValvePin, LOW);   // Valve Close

  sensors.begin();
}

void loop() {
  bacaPerintahDariESP(); // ← proces intruction form ESP

  bool tankFull = digitalRead(FloatPin) == HIGH;

  if (millis() - lastSample > interval) {
    lastSample = millis();

    // write sensor pH
    int sensorPH = analogRead(SensorPin);
    float voltagePH = sensorPH * (5.0 / 1023.0);
    float pHValue = -5.324 * voltagePH + 24.841;

    // wrrite sensor TDS
    int sensorTDS = analogRead(TdsPin);
    float voltageTDS = sensorTDS * (5.0 / 1023.0);
    float tdsValue = (133.42 * voltageTDS * voltageTDS * voltageTDS
                      - 255.86 * voltageTDS * voltageTDS
                      + 857.39 * voltageTDS) * 0.313;

    // write sensor suhu
    sensors.requestTemperatures();
    float temperatureC = sensors.getTempCByIndex(0);

    // wwrite sensor turbidity
    int sensorNTU = analogRead(TurbidityPin);
    float voltageNTU = sensorNTU * (5.0 / 1023.0);
    float ntuValue = (3000 / voltageNTU) - 300;  // Rumus bisa disesuaikan

    //write Nilai
     Serial.print("pH: "); Serial.print(pHValue, 2);
      //Serial.print(" | Turbidity: "); Serial.print(turbidityValue, 2); Serial.print(" NTU");
      Serial.print(" | TDS: "); Serial.print(tdsValue, 0); Serial.print(" ppm");
      Serial.print(" | Temp: "); Serial.print(temperatureC, 1); Serial.println(" C");

    // logic if water is clean
    String status = (pHValue >= 6.0 && pHValue <= 8.0 && tdsValue <= 500) ? "BERSIH" : "KOTOR";

    // send data to ESP8266
    Serial1.print(pHValue, 2); Serial1.print(",");
    Serial1.print(tdsValue, 0); Serial1.print(",");
    Serial1.print(temperatureC, 1); Serial1.print(",");
    Serial1.print(status); Serial1.print(",");
    Serial1.print(tankFull ? "1" : "0"); Serial1.print(",");
    Serial1.print(ntuValue, 1); Serial1.println(",");

    // Kontrol pompa & valve
    if (manualPompa) {
      digitalWrite(RelayPin, LOW);  // Manual  pump
    } else {
      digitalWrite(RelayPin, status == "BERSIH" ? HIGH : LOW);  // Otomatis
    }

    if (manualValve) {
      digitalWrite(ValvePin, HIGH); // Manual open valve
    } else {
      digitalWrite(ValvePin, status == "BERSIH" ? HIGH : LOW);  // Otomatis
    }
  }
}

// fuction to write intruction from ESP8266
void bacaPerintahDariESP() {
  while (Serial1.available()) {
    String perintah = Serial1.readStringUntil('\n');

    if (perintah.startsWith("MANUAL_POMPA:")) {
      manualPompa = perintah.endsWith("1");
    }
    if (perintah.startsWith("MANUAL_VALVE:")) {
      manualValve = perintah.endsWith("1");
    }
  }
}
