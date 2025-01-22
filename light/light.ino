int pin_DC_A = 10;     // ขาเชื่อมต่อกับ DC Motor A
int pin_DC_B = 11;     // ขาเชื่อมต่อกับ DC Motor B
int pin_LightSensor = A15; // ขาเชื่อมต่อกับ Light Sensor (LDR)
int lightThreshold = 500;  // ค่าระดับแสงที่กำหนด (ปรับตามต้องการ)

void setup() {
  pinMode(pin_DC_A, OUTPUT);      // ตั้งค่า pin_DC_A เป็น OUTPUT
  pinMode(pin_DC_B, OUTPUT);      // ตั้งค่า pin_DC_B เป็น OUTPUT
  pinMode(pin_LightSensor, INPUT); // ตั้งค่า Light Sensor เป็น INPUT
  Serial.begin(9600);             // เริ่มต้น Serial Communication ที่ 9600
}

void Motor_CW(unsigned char Speed) {
  digitalWrite(pin_DC_A, LOW);    // หมุนตามเข็มนาฬิกา
  analogWrite(pin_DC_B, Speed);  // ควบคุมความเร็ว
}

void Stop(void) {
  digitalWrite(pin_DC_A, LOW);    // หยุดการหมุน
  digitalWrite(pin_DC_B, LOW);
}

void loop() {
  int lightValue = analogRead(pin_LightSensor); // อ่านค่าจาก Light Sensor
  Serial.print("Light Sensor Value: ");
  Serial.println(lightValue);

  if (lightValue < lightThreshold) { // ถ้าค่าแสงต่ำกว่าเกณฑ์ (มืด)
    Serial.println("It's dark. Fan is running...");
    Motor_CW(200); // พัดลมหมุนด้วยความเร็ว 200
  } else { // ถ้าค่าแสงสูงกว่าเกณฑ์ (สว่าง)
    Serial.println("It's bright. Fan is stopped.");
    Stop(); // หยุดพัดลม
  }

  delay(1000); // หน่วงเวลา 1 วินาที
}
