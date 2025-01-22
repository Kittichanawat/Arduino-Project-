// กำหนดขาเซ็นเซอร์อัลตราโซนิก, buzzer และไฟ LED
int pin_UL_TRIG = A2; // ขาส่งสัญญาณของ Ultrasonic
int pin_UL_OUT = A3;  // ขารับสัญญาณของ Ultrasonic
int pin_BUZZER = A4;  // ขา buzzer
int pin_LED_RED = A5; // ขาไฟ LED สีแดง

void setup() {
  pinMode(pin_UL_TRIG, OUTPUT);
  pinMode(pin_UL_OUT, INPUT);
  pinMode(pin_BUZZER, OUTPUT);
  pinMode(pin_LED_RED, OUTPUT); // กำหนดขา LED สีแดงเป็น OUTPUT
  Serial.begin(9600); // ใช้สำหรับ Debug
}

void loop() {
  long duration, distance;

  // ส่งสัญญาณ Trigger
  digitalWrite(pin_UL_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(pin_UL_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_UL_TRIG, LOW);

  // วัดระยะเวลา Echo
  duration = pulseIn(pin_UL_OUT, HIGH);

  // คำนวณระยะทาง (ในเซนติเมตร)
  distance = duration * 0.034 / 2;

  // แสดงค่าระยะทางใน Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // ตรวจสอบระยะทาง ถ้าวัตถุเข้าใกล้ (เช่น น้อยกว่า 10 ซม.)
  if (distance > 0 && distance < 10) {
    digitalWrite(pin_BUZZER, HIGH); // buzzer ดัง
    digitalWrite(pin_LED_RED, HIGH); // ไฟแดงติด
  } else {
    digitalWrite(pin_BUZZER, LOW);  // buzzer หยุด
    digitalWrite(pin_LED_RED, LOW); // ไฟแดงดับ
  }

  delay(100); // หน่วงเวลาเล็กน้อยเพื่อความเสถียร
}
