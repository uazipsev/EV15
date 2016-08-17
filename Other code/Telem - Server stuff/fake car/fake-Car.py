import serial, time, random

ser = serial.Serial('COM6', 115200, timeout=1)
done = 0
while done == 1:
    data = ser.readline()
    print data
    if data == 'DD/n':
            ser.write('ok/n')
            print "conneted!!!!!"
            done = 0


time.sleep(2)
data = 1
while data == 1:
    #send data for daz
    spd = random.randint(100, 600)
    bpp = random.randint(0, 100)
    tpp = random.randint(0, 100)
    b1 = random.randint(200, 400)
    b2 = random.randint(200, 400)
    b3 = random.randint(200, 400)
    b4 = random.randint(200, 400)
    b5 = random.randint(200, 400)
    b6 = random.randint(200, 400)
    b7 = random.randint(200, 400)
    b8 = random.randint(200, 400)
    b9 = random.randint(200, 400)
    b10 = random.randint(200, 400)
    b11 = random.randint(200, 400)
    b12 = random.randint(200, 400)
    b13 = random.randint(200, 400)
    b14 = random.randint(200, 400)
    b15 = random.randint(200, 400)
    b16 = random.randint(200, 400)
    b17 = random.randint(200, 400)
    b18 = random.randint(200, 400)
    b19 = random.randint(200, 400)
    b20 = random.randint(200, 400)
    b21 = random.randint(200, 400)
    b22 = random.randint(200, 400)
    b23 = random.randint(200, 400)
    b24 = random.randint(200, 400)
    b25 = random.randint(200, 400)
    b26 = random.randint(200, 400)
    b27 = random.randint(200, 400)
    b28 = random.randint(200, 400)
    b29 = random.randint(200, 400)
    b30 = random.randint(200, 400)
    b31 = random.randint(200, 400)
    b32 = random.randint(200, 400)
    b33 = random.randint(200, 400)
    cnt = random.randint(0, 266)
    n=1
    ser.write('$')
    ser.write(bytes(n))
    ser.write('\r')
    ser.write(bytes(n+1))
    ser.write('\r')
    ser.write(bytes(n+2))
    ser.write('\r')
    ser.write(bytes(n+4))
    ser.write('\r')
    ser.write(bytes(n+5))
    ser.write('\r\n')
    time.sleep(0.01)
    
ser.close()
