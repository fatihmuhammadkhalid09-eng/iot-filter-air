# IoT Filter Air Otomatis / Automatic IoT Water Filtration System

## 🇮🇩 Deskripsi
Sistem filter air berbasis IoT menggunakan Arduino Mega dan ESP8266 untuk monitoring dan kontrol kualitas air secara otomatis. Sistem ini dirancang untuk memastikan air yang dihasilkan memenuhi standar kualitas sebelum digunakan.

## 🇬🇧 Description
An IoT-based water filtration system using Arduino Mega and ESP8266 for monitoring and automatic control of water quality. The system ensures that water meets quality standards before being used.

---

## 🇮🇩 Fitur
- Monitoring sensor pH, turbidity (kekeruhan), suhu, dan TDS
- Sistem filtrasi otomatis berdasarkan kualitas air
- Kontrol pompa dan solenoid valve
- Monitoring dan kontrol melalui aplikasi Blynk
- Sistem multi-tahap (filter ulang jika belum memenuhi standar)

## 🇬🇧 Features
- Monitoring pH, turbidity, temperature, and TDS sensors
- Automatic filtration system based on water quality
- Pump and solenoid valve control
- Monitoring and control via Blynk application
- Multi-stage filtering system (re-filtering if needed)

---

## 🇮🇩 Komponen
- Arduino Mega 2560
- ESP8266 (NodeMCU)
- Sensor pH
- Sensor turbidity
- Sensor TDS
- Sensor suhu
- Relay module
- Pompa air 12V
- Solenoid valve

## 🇬🇧 Components
- Arduino Mega 2560
- ESP8266 (NodeMCU)
- pH sensor
- Turbidity sensor
- TDS sensor
- Temperature sensor
- Relay module
- 12V water pump
- Solenoid valve

---

## 🇮🇩 Cara Kerja Sistem
1. Air masuk ke bak penampungan pertama
2. Sensor membaca kualitas air (pH, turbidity, TDS, suhu)
3. Jika kualitas belum sesuai:
   - Pompa menyala terlebih dahulu
   - Setelah delay 3–5 detik, valve terbuka
4. Air difilter dan masuk ke bak kedua
5. Air dicek kembali kualitasnya
6. Jika masih belum sesuai, air difilter ulang
7. Jika sudah sesuai, air masuk ke bak penampungan akhir
8. Valve output dapat dikontrol manual melalui aplikasi

## 🇬🇧 System Workflow
1. Water enters the first tank
2. Sensors measure water quality (pH, turbidity, TDS, temperature)
3. If quality is not acceptable:
   - Pump is activated first
   - After a 3–5 second delay, the valve opens
4. Water is filtered and moves to the second tank
5. Water quality is checked again
6. If still not acceptable, filtering process repeats
7. If acceptable, water moves to the final tank
8. Output valve can be controlled manually via the application

## 🇮🇩 Struktur Project
iot-filter-air/
 ├── src/
 │    ├── arduino.ino
 │    └── esp8266.ino
 ├── docs/
 │    ├── diagram.jpg
 │    └── foto-alat.jpg
 ├── README.md

## 🇬🇧 Project Structure
iot-filter-air/
 ├── src/
 │    ├── arduino.ino
 │    └── esp8266.ino
 ├── docs/
 │    ├── diagram.jpg
 │    └── device-image.jpg
 ├── README.md

## 🇮🇩 Cara Menjalankan
1. Upload kode ke Arduino Mega
2. Upload kode ke ESP8266
3. Hubungkan semua sensor dan relay sesuai rangkaian
4. Konfigurasi WiFi dan Blynk
5. Jalankan sistem

## 🇬🇧 How to Run
1. Upload code to Arduino Mega
2. Upload code to ESP8266
3. Connect all sensors and relays according to the circuit
4. Configure WiFi and Blynk
5. Run the system

---
![Alat Filter Air](docs/nama-file-gambar.jpg)

## 🇮🇩 Catatan
Pastikan semua sensor telah dikalibrasi untuk mendapatkan hasil yang akurat.

## 🇬🇧 Notes
Make sure all sensors are calibrated properly to ensure accurate readings.

---

## Author
Fatih Muhammad Khalid

## 🇮🇩 Struktur Project
