import serial
import speech_recognition as sr

# ตั้งค่าพอร์ต Serial ให้ตรงกับ Arduino
arduino = serial.Serial('COM7', 9600)  # ใช้ COM7 ตามที่ตรวจสอบได้ใน Device Manager
recognizer = sr.Recognizer()

print("ระบบพร้อมแล้ว กรุณาพูดคำสั่ง เช่น 'เปิดแดง', 'ปิดเขียว', 'เปิดทั้งหมด', 'หมุนซ้ายพัดลม', หรือ 'นิ่งไว้'")

while True:
    with sr.Microphone() as source:
        print("กำลังฟังคำสั่ง...")
        try:
            # ฟังเสียงจากไมโครโฟน
            audio = recognizer.listen(source)
            command = recognizer.recognize_google(audio, language='th-TH')  # ใช้ Google Speech Recognition ภาษาไทย
            print(f"คำสั่งที่ได้ยิน: {command}")

            # ตรวจสอบคำสั่งเสียงและส่งคำสั่งไปยัง Arduino
            if "เปิดไฟสีแดง" in command:
                arduino.write(b'1')  # ส่ง '1' ไปยัง Arduino เพื่อเปิดไฟสีแดง
                print("ส่งคำสั่ง: เปิดไฟสีแดง")
            elif "ปิดไฟสีแดง" in command:
                arduino.write(b'2')  # ส่ง '2' ไปยัง Arduino เพื่อปิดไฟสีแดง
                print("ส่งคำสั่ง: ปิดไฟสีแดง")
            elif "เปิดไฟสีเขียว" in command:
                arduino.write(b'3')  # ส่ง '3' ไปยัง Arduino เพื่อเปิดไฟสีเขียว
                print("ส่งคำสั่ง: เปิดไฟสีเขียว")
            elif "ปิดไฟสีเขียว" in command:
                arduino.write(b'4')  # ส่ง '4' ไปยัง Arduino เพื่อปิดไฟสีเขียว
                print("ส่งคำสั่ง: ปิดไฟสีเขียว")
            elif "เปิดไฟสีฟ้า" in command:
                arduino.write(b'5')  # ส่ง '5' ไปยัง Arduino เพื่อเปิดไฟสีฟ้า
                print("ส่งคำสั่ง: เปิดไฟสีฟ้า")
            elif "ปิดไฟสีฟ้า" in command:
                arduino.write(b'6')  # ส่ง '6' ไปยัง Arduino เพื่อปิดไฟสีฟ้า
                print("ส่งคำสั่ง: ปิดไฟสีฟ้า")
            elif "เปิดไฟทั้งหมด" in command:
                arduino.write(b'7')  # ส่ง '7' ไปยัง Arduino เพื่อเปิดไฟทุกสี
    
              
                print("ส่งคำสั่ง: เปิดไฟทั้งหมด")
            elif "ปิดไฟทั้งหมด" in command:
                arduino.write(b'8')  # ส่ง '8' ไปยัง Arduino เพื่อปิดไฟทุกสี
                print("ส่งคำสั่ง: ปิดไฟทั้งหมด")
            
            elif "หมุนซ้ายพัดลม" in command:
                arduino.write(b'9')  # ส่ง '9' ไปยัง Arduino เพื่อหมุนซ้ายพัดลม
                print("ส่งคำสั่ง: หมุนซ้ายพัดลม")
            
            elif "หมุนขวาพัดลม" in command:
                arduino.write(b'10')  # ส่ง '10' ไปยัง Arduino เพื่อหมุนขวาพัดลม
                print("ส่งคำสั่ง: หมุนขวาพัดลม")
            elif "นิ่งไว้" in command:
                arduino.write(b'11')  # ส่ง '11' ไปยัง Arduino เพื่อหยุดพัดลม
                print("ส่งคำสั่ง: นิ่งไว้")
            else:
                print("ไม่พบคำสั่งที่ตรง กรุณาลองใหม่อีกครั้ง")
        except sr.UnknownValueError:
            print("ไม่สามารถเข้าใจคำสั่งได้ กรุณาลองอีกครั้ง")
        except sr.RequestError as e:
            print(f"เกิดข้อผิดพลาดกับบริการ Google Speech Recognition: {e}")
