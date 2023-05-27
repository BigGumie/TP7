import datetime
import serial

serial_port = 'COM6'

with serial.Serial(serial_port, 9600, timeout=1) as ser:
    with open('data.txt', 'a') as file:
        while True:
            line = ser.readline().decode().strip()
            if line:
                file.write(f"{line},{datetime.datetime.now()}\n")
                file.flush()
