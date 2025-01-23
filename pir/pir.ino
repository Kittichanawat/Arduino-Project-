int pin_PIR_OUT = A2; // ขา OUT ของ PIR Sensor

void setup() {
  pinMode(pin_PIR_OUT, INPUT); // ตั้งค่า PIR Sensor เป็น INPUT
  Serial.begin(9600); // เริ่มต้น Serial Communication
  Serial.println("Arduino is ready to detect motion.");
}

void loop() {
  int motionDetected = digitalRead(pin_PIR_OUT); // อ่านค่าจาก PIR Sensor

  if (motionDetected == HIGH) { // ถ้ามีการตรวจจับการเคลื่อนไหว
    Serial.println("MOTION_DETECTED"); // ส่งข้อความไปยัง Python
    delay(500); // ป้องกันการส่งซ้ำในช่วงเวลาสั้น ๆ
  } else {
    Serial.println("NO_MOTION"); // ส่งข้อความไปยัง Python เมื่อไม่มีการเคลื่อนไหว
    delay(500); // ป้องกันการส่งซ้ำในช่วงเวลาสั้น ๆ
  }
}
