int pin_LED_RED = A5;  // ขาไฟ LED สีแดง
int pin_LED_GREEN = A6; // ขาไฟ LED สีเขียว
int pin_LED_BLUE = A7;  // ขาไฟ LED สีฟ้า
int pin_DC_INA = 10;    // ขามอเตอร์ INA
int pin_DC_INB = 11;    // ขามอเตอร์ INB
int motorSpeed = 200;   // ความเร็วเริ่มต้นของมอเตอร์ (0-255)

void setup() {
  pinMode(pin_LED_RED, OUTPUT);  // ตั้งค่า LED สีแดงเป็น OUTPUT
  pinMode(pin_LED_GREEN, OUTPUT); // ตั้งค่า LED สีเขียวเป็น OUTPUT
  pinMode(pin_LED_BLUE, OUTPUT);  // ตั้งค่า LED สีฟ้าเป็น OUTPUT
  pinMode(pin_DC_INA, OUTPUT);   // ตั้งค่า DC INA เป็น OUTPUT
  pinMode(pin_DC_INB, OUTPUT);   // ตั้งค่า DC INB เป็น OUTPUT
  Serial.begin(9600);  // เริ่มต้น Serial Communication
  Serial.println("Arduino is ready to receive commands.");  // แจ้งเตือนใน Serial Monitor
}

void Motor_CW(unsigned char Speed) {
  analogWrite(pin_DC_INA, Speed);  // ตั้งค่าความเร็ว INA
  digitalWrite(pin_DC_INB, LOW);   // INB LOW หมุนตามเข็มนาฬิกา
}

void Motor_CCW(unsigned char Speed) {
  analogWrite(pin_DC_INB, Speed);  // ตั้งค่าความเร็ว INB
  digitalWrite(pin_DC_INA, LOW);   // INA LOW หมุนทวนเข็มนาฬิกา
}

void StopMotor() {
  digitalWrite(pin_DC_INA, LOW);   // หยุดมอเตอร์ INA
  digitalWrite(pin_DC_INB, LOW);   // หยุดมอเตอร์ INB
}

void loop() {
  if (Serial.available()) {  // ถ้ามีข้อมูลจาก Serial
    String command = Serial.readStringUntil('\n');  // อ่านคำสั่งจาก Serial จนกว่าจะเจอ '\n'

    // ตรวจสอบคำสั่งและควบคุมไฟ LED
    if (command == "1") {
      digitalWrite(pin_LED_RED, HIGH);  // เปิดไฟสีแดง
      Serial.println("RED LED is ON.");
    } else if (command == "2") {
      digitalWrite(pin_LED_RED, LOW);  // ปิดไฟสีแดง
      Serial.println("RED LED is OFF.");
    } else if (command == "3") {
      digitalWrite(pin_LED_GREEN, HIGH);  // เปิดไฟสีเขียว
      Serial.println("GREEN LED is ON.");
    } else if (command == "4") {
      digitalWrite(pin_LED_GREEN, LOW);  // ปิดไฟสีเขียว
      Serial.println("GREEN LED is OFF.");
    } else if (command == "5") {
      digitalWrite(pin_LED_BLUE, HIGH);  // เปิดไฟสีฟ้า
      Serial.println("BLUE LED is ON.");
    } else if (command == "6") {
      digitalWrite(pin_LED_BLUE, LOW);  // ปิดไฟสีฟ้า
      Serial.println("BLUE LED is OFF.");
    } else if (command == "7") {
      digitalWrite(pin_LED_RED, HIGH);  // เปิดไฟทั้งหมด
      digitalWrite(pin_LED_GREEN, HIGH);
      digitalWrite(pin_LED_BLUE, HIGH);
      Serial.println("All LEDs are ON.");
    } else if (command == "8") {
      digitalWrite(pin_LED_RED, LOW);  // ปิดไฟทั้งหมด
      digitalWrite(pin_LED_GREEN, LOW);
      digitalWrite(pin_LED_BLUE, LOW);
      Serial.println("All LEDs are OFF.");
    } else if (command == "9") {
      Motor_CW(motorSpeed);  // หมุนตามเข็มนาฬิกา
      Serial.println("Motor is rotating CW.");
    } else if (command == "10") {
      Motor_CCW(motorSpeed);  // หมุนทวนเข็มนาฬิกา
      Serial.println("Motor is rotating CCW.");
    } else if (command == "11") {
      StopMotor();   // หยุดมอเตอร์
      Serial.println("Motor is OFF.");
    } else {
      Serial.println("Invalid command.");  // กรณีคำสั่งไม่ถูกต้อง
    }
  }
}
