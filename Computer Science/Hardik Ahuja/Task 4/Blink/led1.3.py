import RPi.GPIO as GPIO
import time

def blink(pin):
	GPIO.output(pin,GPIO.HIGH)
	time.sleep(1)
	GPIO.output(pin,GPIO.LOW)
	time.sleep(1)

GPIO.setmode(GPIO.BOARD)
GPIO.setup(7,GPIO.OUT)
for i in range (1):
	blink(7)
print("hello")
GPIO.cleanup()
	
