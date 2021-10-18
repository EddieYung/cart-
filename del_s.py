import serial
import mysql.connector

mydb = mysql.connector.connect(
  host="localhost",
  user="shop",
  password="#shop1255",
  database="cars"
)

mycursor = mydb.cursor()

ser = serial.Serial('/dev/ttyACM1',9600)

while True:
       print("Swipe Card to delete")
       read_s = ser.readline()
       card = read_s.decode('ascii')
  
       if len(card)> 0 :
          samp = str(card)
          n = samp[1:12]
          sql5 = "SELECT * FROM cart WHERE cardnumber ='%s'"%(n)
          mycursor.execute(sql5)
          myresult = mycursor.fetchone()
          cdm = myresult
          if cdm == None:
              print("Item is not cart")
              ser.write(str.encode('5'))
              
          else:
              pd = myresult[1]
              if len(pd) > 0:
                  sql6 = "DELETE FROM cart WHERE cardnumber ='%s'"%(n)
                  mycursor.execute(sql6)
                  myresult = mycursor.fetchone()
                  cdm = myresult
                  print("Card Delete!")
                  mydb.commit()
                  ser.write(str.encode('2'))
                   
