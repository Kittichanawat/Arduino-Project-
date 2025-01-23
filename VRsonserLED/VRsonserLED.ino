int pin_VR = A4;     // พอร์ต Analog สำหรับ VR Sensor
int pin_led_R = A1;  // LED สีแดง
int pin_led_G = A2;  // LED สีเขียว
int pin_led_B = A3;  // LED สีฟ้า

bool reverseOrder = false; // ตัวแปรสำหรับสลับลำดับ

void setup() {
  pinMode(pin_led_R, OUTPUT);
  pinMode(pin_led_G, OUTPUT);
  pinMode(pin_led_B, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int vrValue = analogRead(pin_VR);

  int vrMapped = map(vrValue, 0, 1023, 0, 10);

  Serial.print("VR Value: ");
  Serial.print(vrValue);
  Serial.print(" | Mapped Value: ");
  Serial.println(vrMapped);

  if (vrMapped == 3) {
    // เลข 3 -> ไฟสีแดงติด
    digitalWrite(pin_led_R, HIGH);
    digitalWrite(pin_led_G, LOW);
    digitalWrite(pin_led_B, LOW);
  } else if (vrMapped == 5) {
    // เลข 5 -> ไฟสีเขียวติด
    digitalWrite(pin_led_R, LOW);
    digitalWrite(pin_led_G, HIGH);
    digitalWrite(pin_led_B, LOW);
  } else if (vrMapped == 7) {
    // เลข 7 -> ไฟสีฟ้าติด
    digitalWrite(pin_led_R, LOW);
    digitalWrite(pin_led_G, LOW);
    digitalWrite(pin_led_B, HIGH);
  } else if (vrMapped == 10) {
    if (!reverseOrder) {
      // รอบแรก: สีแดง → สีเขียว → สีฟ้า
      digitalWrite(pin_led_R, HIGH); // ไฟแดงเปิด
      delay(200);
      digitalWrite(pin_led_R, LOW);  // ไฟแดงปิด

      digitalWrite(pin_led_G, HIGH); // ไฟเขียวเปิด
      delay(200);
      digitalWrite(pin_led_G, LOW);  // ไฟเขียวปิด

      digitalWrite(pin_led_B, HIGH); // ไฟฟ้าเปิด
      delay(200);
      digitalWrite(pin_led_B, LOW);  // ไฟฟ้าปิด
    } else {
      // รอบที่สอง: สีฟ้า → สีเขียว → สีแดง
      digitalWrite(pin_led_B, HIGH); // ไฟฟ้าเปิด
      delay(200);
      digitalWrite(pin_led_B, LOW);  // ไฟฟ้าปิด

      digitalWrite(pin_led_G, HIGH); // ไฟเขียวเปิด
      delay(200);
      digitalWrite(pin_led_G, LOW);  // ไฟเขียวปิด

      digitalWrite(pin_led_R, HIGH); // ไฟแดงเปิด
      delay(200);
      digitalWrite(pin_led_R, LOW);  // ไฟแดงปิด
    }

    // สลับลำดับรอบถัดไป
    reverseOrder = !reverseOrder;
  } else {
    // ค่าอื่น ๆ -> ไฟดับทั้งหมด
    digitalWrite(pin_led_R, LOW);
    digitalWrite(pin_led_G, LOW);
    digitalWrite(pin_led_B, LOW);
  }

  delay(100); // หน่วงเวลาเล็กน้อย
}
