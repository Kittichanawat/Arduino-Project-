// กำหนดขา Switch, LED, และ Motor
int pin_SWITCH = 2;    // ขา Switch
int pin_LED_RED = A1;  // ขาไฟ LED สีแดง
int pin_LED_GREEN = A3; // ขาไฟ LED สีเขียว
int pin_DC_INA = A4;   // ขาควบคุมพัดลม A
int pin_DC_INB = A5;   // ขาควบคุมพัดลม B

bool lastButtonState = LOW; // สถานะปุ่มก่อนหน้า
bool isFanOn = true; // สถานะเริ่มต้น (ไฟแดงติด, พัดลมหยุด)
bool currentButtonState = LOW;

void setup() {
  // ตั้งค่าขาเป็น INPUT และ OUTPUT
  pinMode(pin_SWITCH, INPUT_PULLUP); // ตั้ง Switch เป็น INPUT (ใช้ Pull-Up Resistor)
  pinMode(pin_LED_RED, OUTPUT);     // ตั้ง LED สีแดงเป็น OUTPUT
  pinMode(pin_LED_GREEN, OUTPUT);   // ตั้ง LED สีเขียวเป็น OUTPUT
  pinMode(pin_DC_INA, OUTPUT);      // ตั้ง Motor INA เป็น OUTPUT
  pinMode(pin_DC_INB, OUTPUT);      // ตั้ง Motor INB เป็น OUTPUT

  // กำหนดค่าเริ่มต้นให้ไฟแดงติดและพัดลมหยุดทำงาน
  digitalWrite(pin_LED_RED, HIGH);  // เปิดไฟแดง
  digitalWrite(pin_LED_GREEN, LOW); // ปิดไฟเขียว
  digitalWrite(pin_DC_INA, LOW);    // หยุดพัดลม
  digitalWrite(pin_DC_INB, LOW);

  // เริ่มต้น Serial สำหรับ Debugging
  Serial.begin(9600);
  Serial.println("System Initialized. RED LED is ON. Waiting for user action.");
}

void loop() {
  // อ่านสถานะของ Switch
  currentButtonState = digitalRead(pin_SWITCH);

  // ตรวจจับการกดปุ่ม (เปลี่ยนจาก LOW -> HIGH)
  if (currentButtonState == HIGH && lastButtonState == LOW) {
    isFanOn = !isFanOn; // สลับสถานะการทำงาน
    delay(50); // หน่วงเวลาเพื่อป้องกันการกดซ้ำ (debounce)
  }

  // การจัดการตามสถานะการทำงาน
  if (isFanOn) {
    // เปิดไฟเขียว ปิดไฟแดง พัดลมหมุน
    digitalWrite(pin_LED_RED, LOW);   // ปิดไฟแดง
    digitalWrite(pin_LED_GREEN, HIGH); // เปิดไฟเขียว
    digitalWrite(pin_DC_INA, HIGH);   // พัดลมหมุน
    digitalWrite(pin_DC_INB, LOW);
    Serial.println("GREEN LED ON, Fan Rotating");
  } else {
    // เปิดไฟแดง ปิดไฟเขียว พัดลมหยุด
    digitalWrite(pin_LED_RED, HIGH);   // เปิดไฟแดง
    digitalWrite(pin_LED_GREEN, LOW); // ปิดไฟเขียว
    digitalWrite(pin_DC_INA, LOW);    // พัดลมหยุด
    digitalWrite(pin_DC_INB, LOW);
    Serial.println("RED LED ON, Fan Stopped");
  }

  // บันทึกสถานะปุ่มปัจจุบันเป็นสถานะก่อนหน้า
  lastButtonState = currentButtonState;

  // หน่วงเวลาเล็กน้อย
  delay(50);
}
