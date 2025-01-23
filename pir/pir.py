import serial
import pygame  # ใช้สำหรับเล่นเสียง

# ตั้งค่าพอร์ต Serial ให้ตรงกับ Arduino
arduino = serial.Serial('COM7', 9600)  # แก้ 'COM7' ให้ตรงกับพอร์ต Arduino
pygame.mixer.init()  # เริ่มต้นระบบเสียงของ Pygame

# กำหนดไฟล์เสียงที่ต้องการเล่น
sound_file = "7-11.mp3"  # เปลี่ยนเป็นชื่อไฟล์เสียงที่คุณต้องการ
sound = pygame.mixer.Sound(sound_file)

print("ระบบพร้อมใช้งาน รอการตรวจจับการเคลื่อนไหว...")

motion_detected = False  # สถานะการเคลื่อนไหวเริ่มต้น

while True:
    if arduino.in_waiting > 0:  # ตรวจสอบว่ามีข้อมูลจาก Arduino หรือไม่
        message = arduino.readline().decode('utf-8').strip()  # อ่านข้อมูลจาก Arduino
        print(f"ข้อความที่ได้รับ: {message}")

        if message == "MOTION_DETECTED":  # ถ้าข้อความที่ได้รับคือ "MOTION_DETECTED"
            if not motion_detected:  # ตรวจสอบว่าก่อนหน้านี้ไม่มีการเคลื่อนไหว
                motion_detected = True  # เปลี่ยนสถานะเป็นมีการเคลื่อนไหว
                print("ตรวจจับการเคลื่อนไหว! กำลังเล่นเสียง...")
                sound.play()  # เล่นไฟล์เสียง
        else:
            motion_detected = False  # หากไม่มีการเคลื่อนไหว เปลี่ยนสถานะเป็นไม่มีการเคลื่อนไหว
