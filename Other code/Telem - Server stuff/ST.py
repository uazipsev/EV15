import MySQLdb, serial, time
db = MySQLdb.connect("localhost","software","soft","FSAE_EV" )
cursor = db.cursor()

while cont == 1:
    spdFL = random.randint(100, 600)
    spdFR = random.randint(100, 600)
    spdRL = random.randint(100, 600)
    spdRR = random.randint(100, 600)
    bpp1 = random.randint(0, 100)
    bpp2 = random.randint(0, 100)
    tpp1 = random.randint(0, 100)
    tpp2 = random.randint(0, 100)
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
    cursor.execute("INSERT INTO TestDatas(Data1,Data2,Data3,Data4,Data5) VALUES(%s,%s,%s,%s,%s)",(data1,data2,data3,data4,data5))
