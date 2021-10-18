import serial
import mysql.connector

mydb = mysql.connector.connect(
  host="localhost",
  user="shop",
  password="#shop1255",
  database="cars"
)

mycursor = mydb.cursor()

ser = serial.Serial('/dev/ttyACM0',9600)

while True:
       read_s = ser.readline()
       card = read_s.decode('ascii')
  
       if len(card)> 0 :
          product=input("Enter the name of the product: ")
          price = input("Enter the price of the product: ")
          samp = str(card)
          n = samp[1:12]
          print(n)
          sql = "INSERT INTO products (cardnumber,product,price) VALUES (%s, %s,%s)"
          val = (n,str(product),str(price))
          mycursor.execute(sql, val)
          mydb.commit()
          ser.write(str.encode('1'))
