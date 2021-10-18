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
          samp = str(card)
          n = samp[1:12]
          sql = "SELECT * FROM cart WHERE cardnumber ='%s'"%(n)
          mycursor.execute(sql)
          myresult = mycursor.fetchone()
          cdm = myresult

          if cdm == None:
              sql2 = "SELECT * FROM products WHERE cardnumber ='%s'"%(n)
              mycursor.execute(sql2)
              myresult1 = mycursor.fetchone()
              if myresult1 == None:
                  print("Card Not Registered")
                  ser.write(str.encode('4'))
                
              else:
                  cd = myresult1[0]
                  pd = myresult1[1]
                  pr = myresult1[2]

                  if len(pd) > 0:
                      sql1 = "INSERT INTO cart (cardnumber,product,price) VALUES (%s, %s,%s)"
                      val = (str(cd),str(pd),str(pr))
                      mycursor.execute(sql1, val)
                      mydb.commit()
                      print("OK")
                      ser.write(str.encode('1'))
                  
          else:
              print("Product Already Added")
              ser.write(str.encode('3'))

          
          
