// กำหนดขา LED และ Sound Sensor
int pin_LED_RED = A2;  // ขาไฟ LED สีแดง
int pin_LED_GREEN = A3; // ขาไฟ LED สีเขียว
int pin_LED_BLUE = A4;  // ขาไฟ LED สีฟ้า
int pin_SOUND_SENSOR = 1; // ขา OUT ของ Sound Sensor

// กำหนดเกณฑ์ระดับเสียง (dB)
float threshold_red = 50.0;   // เสียง > 50 dB (ไฟแดง)
float threshold_green = 75.0; // เสียง > 75 dB (ไฟแดง + เขียว)
float threshold_blue = 100.0; // เสียง > 100 dB (ไฟแดง + เขียว + ฟ้า)

void setup() {
  // ตั้งค่า LED เป็น OUTPUT
  pinMode(pin_LED_RED, OUTPUT);
  pinMode(pin_LED_GREEN, OUTPUT);
  pinMode(pin_LED_BLUE, OUTPUT);

  // ตั้งค่า Sound Sensor เป็น INPUT
  pinMode(pin_SOUND_SENSOR, INPUT);

  // เริ่มต้น Serial Communication สำหรับ Debug
  Serial.begin(9600);
}

void loop() {
  // อ่านค่าจาก Sound Sensor
  int soundValue = analogRead(pin_SOUND_SENSOR);

  // แปลงค่าดิบเป็นแรงดันไฟฟ้า (0-5V)
  float voltage = (soundValue / 1023.0) * 5.0;

  // คำนวณค่าเดซิเบล (สมมติให้ 0.01V = 0 dB)
  float decibel = voltage * 100.0; // คุณอาจต้องปรับสูตรนี้ตามเซ็นเซอร์ของคุณ

  // แสดงค่าใน Serial Monitor (สำหรับ Debug)
  Serial.print("Sound Level: ");
  Serial.print(decibel);
  Serial.println(" dB");

  // ตรวจสอบระดับเสียงและเปิดไฟ LED ที่เหมาะสม
  if (decibel >= threshold_blue) {
    // เสียงดัง > 100 dB: ติดไฟทั้งสามดวง
    digitalWrite(pin_LED_RED, HIGH);
    digitalWrite(pin_LED_GREEN, HIGH);
    digitalWrite(pin_LED_BLUE, HIGH);
    Serial.println("Sound Level: High (RED + GREEN + BLUE ON)");
  } else if (decibel >= threshold_green) {
    // เสียงกลาง 75-100 dB: ติดไฟแดงและเขียว
    digitalWrite(pin_LED_RED, HIGH);
    digitalWrite(pin_LED_GREEN, HIGH);
    digitalWrite(pin_LED_BLUE, LOW);
    Serial.println("Sound Level: Medium (RED + GREEN ON)");
  } else if (decibel >= threshold_red) {
    // เสียงเบา 50-75 dB: ติดไฟแดง
    digitalWrite(pin_LED_RED, HIGH);
    digitalWrite(pin_LED_GREEN, LOW);
    digitalWrite(pin_LED_BLUE, LOW);
    Serial.println("Sound Level: Low (RED ON)");
  } else {
    // เสียงต่ำกว่า 50 dB: ดับทุกดวง
    digitalWrite(pin_LED_RED, LOW);
    digitalWrite(pin_LED_GREEN, LOW);
    digitalWrite(pin_LED_BLUE, LOW);
    Serial.println("Sound Level: Very Low (All LEDs OFF)");
  }

  // หน่วงเวลาเล็กน้อยเพื่อความเสถียร
  delay(100);
}



