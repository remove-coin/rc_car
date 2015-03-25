import RPi.GPIO as GPIO
from time import sleep
 
GPIO.setmode(GPIO.BOARD)
 
# Pin 7 (GPIO 4) 
Motor1A = 7
Motor1B = 12
Motor1E = 11

 
GPIO.setup(Motor1A,GPIO.OUT)
GPIO.setup(Motor1B,GPIO.OUT)
GPIO.setup(Motor1E,GPIO.OUT)

 
print "Turning motor1 on"
print "Forward"
GPIO.output(Motor1A,GPIO.LOW)
GPIO.output(Motor1B,GPIO.HIGH)
GPIO.output(Motor1E,GPIO.HIGH)

sleep(1)


print "Backward"
GPIO.output(Motor1B,GPIO.LOW)
GPIO.output(Motor1A,GPIO.HIGH)
 
sleep(1)
 
print "Stopping motor1"
GPIO.output(Motor1E,GPIO.LOW)


GPIO.cleanup()
