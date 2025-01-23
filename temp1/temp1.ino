#include <DHT.h>  // นำเข้าไลบรารี DHT สำหรับเซ็นเซอร์ DHT11

#define DHTPIN A3       // ขา pin ที่เชื่อมต่อกับเซ็นเซอร์ DHT11
#define DHTTYPE DHT11   // ประเภทของเซ็นเซอร์ DHT11

DHT dht(DHTPIN, DHTTYPE);  // สร้างออบเจกต์ dht สำหรับเซ็นเซอร์ DHT11

int pin_led_R = A1;  // LED สีแดง
int pin_led_G = A2;  // LED สีเขียว

void setup() {
  Serial.begin(9600);        // เริ่มต้นการสื่อสาร Serial ที่ความเร็ว 9600 bps
  dht.begin();               // เริ่มต้นการใช้งานเซ็นเซอร์ DHT11
  pinMode(pin_led_R, OUTPUT); // ตั้งค่าพอร์ต LED สีแดงเป็น OUTPUT
  pinMode(pin_led_G, OUTPUT); // ตั้งค่าพอร์ต LED สีเขียวเป็น OUTPUT
}

void loop() {
  // อ่านค่าความชื้นและอุณหภูมิจากเซ็นเซอร์ DHT11
  float humidity = dht.readHumidity();      // ค่าความชื้น
  float temperature = dht.readTemperature(); // ค่าอุณหภูมิ

  // ตรวจสอบว่าเซ็นเซอร์อ่านค่าผิดหรือไม่
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT11 sensor!"));
    return;  // ถ้าอ่านค่าไม่ได้ให้หยุดการทำงานใน loop นี้
  }

  // แสดงผลค่าความชื้นและอุณหภูมิจากเซ็นเซอร์ DHT11
  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperature);
  Serial.println(F("°C"));

  // ควบคุมไฟ LED ตามค่าอุณหภูมิที่ได้
  if (temperature >= 27) {
    // ถ้าอุณหภูมิ 40 องศาขึ้นไป ให้เปิดไฟแดง
    digitalWrite(pin_led_R, HIGH);
    digitalWrite(pin_led_G, LOW); // ปิดไฟเขียว
  } else if (temperature <= 26) {
    // ถ้าอุณหภูมิ 25 องศาลงไป ให้เปิดไฟเขียว
    digitalWrite(pin_led_R, LOW); // ปิดไฟแดง
    digitalWrite(pin_led_G, HIGH); // เปิดไฟเขียว
  } else {
    // ถ้าอุณหภูมิอยู่ระหว่าง 25 ถึง 40 องศา ให้ปิดทั้งสองไฟ
    digitalWrite(pin_led_R, LOW);
    digitalWrite(pin_led_G, LOW);
  }

  delay(2000); // หน่วงเวลา 2 วินาทีก่อนเริ่มอ่านค่าครั้งถัดไป
}