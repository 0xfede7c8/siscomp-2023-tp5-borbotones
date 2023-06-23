#!/bin/env python3

# Leemos GPIO con python para probar...

import RPi.GPIO as GPIO
import time

# GPIO pin definitions
dist_bit0 = 2
dist_bit1 = 3
dist_bit2 = 4
dist_bit3 = 17
dist_bit4 = 27
dist_bit5 = 22
dist_bit6 = 10
dist_bit7 = 9

pote_bit0 = 14
pote_bit1 = 15
pote_bit2 = 18
pote_bit3 = 23
pote_bit4 = 24
pote_bit5 = 25
pote_bit6 = 8
pote_bit7 = 7

# Set up GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup([dist_bit0, dist_bit1, dist_bit2, dist_bit3, dist_bit4, dist_bit5, dist_bit6, dist_bit7], GPIO.IN)
GPIO.setup([pote_bit0, pote_bit1, pote_bit2, pote_bit3, pote_bit4, pote_bit5, pote_bit6, pote_bit7], GPIO.IN)

def read_distance():
    return  GPIO.input(dist_bit7) << 7 | GPIO.input(dist_bit6) << 6 | GPIO.input(dist_bit5) << 5 | GPIO.input(dist_bit4) << 4 | \
            GPIO.input(dist_bit3) << 3 | GPIO.input(dist_bit2) << 2 | GPIO.input(dist_bit1) << 1 | GPIO.input(dist_bit0)

def read_pote():
    return GPIO.input(pote_bit7) << 7 | GPIO.input(pote_bit6) << 6 | GPIO.input(pote_bit5) << 5 | GPIO.input(pote_bit4) << 4 | \
            GPIO.input(pote_bit3) << 3 | GPIO.input(pote_bit2) << 2 | GPIO.input(pote_bit1) << 1 | GPIO.input(pote_bit0)

try:
    while True:
        print("Distance: ", read_distance())
        print("Pote: ", read_pote())

        # Delay before next reading
        time.sleep(0.05)

except KeyboardInterrupt:
    GPIO.cleanup()