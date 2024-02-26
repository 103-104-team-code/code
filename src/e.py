# Imports go at the top
from microbit import *


# Code in a 'while True:' loop repeats forever

def parser():
    operations = ['+', '-']
    input1 = ''
    input2 = ''
    input3 = ''
    if button_a.was_pressed():
        input1+='0'
    if button_b.was_pressed():
        input1+='1'
    if button_a.is_pressed() and button_b.is_pressed():
         display.scroll('ok')
         sleep(200)
    if button_a.was_pressed():
        input2+='0'
    if button_b.was_pressed():
        input2+='1'
    if button_a.is_pressed() and button_b.is_pressed():
        display.scroll('ok')
    if button_a.was_pressed():
        input3+='0'
    if button_b.was_pressed():
        input3+='1'
    if button_a.is_pressed() and button_b.is_pressed():
        display.scroll('ok')
    
    num1 = int(input1, 2)
    num2 = int(input1, 2)
    operation = int(input3, 2)
    if operation == '0':
        display.scroll(num1+num2)
    if operation == '1':
        display.scroll(num1-num2)
    
    
# def toBinary(string1):
#     string1 = str(string1)
#     string1 = int(string1, 2)
#     return string1
while True:
    parser()