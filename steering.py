import RPi.GPIO as GPIO
from time import sleep

GPIO.setmode(GPIO.BOARD)


Motor2A = 15
Motor2B = 16
Motor2E = 22



GPIO.setup(Motor2A,GPIO.OUT)
GPIO.setup(Motor2B,GPIO.OUT)
GPIO.setup(Motor2E,GPIO.OUT)


print "Turning motor2 on"

print "A: right"
GPIO.output(Motor2B,GPIO.LOW)
GPIO.output(Motor2A,GPIO.HIGH)
GPIO.output(Motor2E,GPIO.HIGH)
sleep(2)

GPIO.output(Motor2A,GPIO.LOW)
sleep(2)

print "B: left"

GPIO.output(Motor2B,GPIO.HIGH)

sleep(1)

print "Stopping motor2"
GPIO.output(Motor2E,GPIO.LOW)


GPIO.cleanup()


