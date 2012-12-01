#recive ASIC ID first
#img load at 0x40300000
#return 0xf003 0002
#send img


import serial
import struct
import sys

if len(sys.argv) != 3:
       print "usage: python serial_downloader <comnum> <filename>"
com_num = sys.argv[1]
file_name = sys.argv[2]
mlo_img = open(file_name, "rb")
img = ""
while True:
    img_temp = mlo_img.read(256)
    img = img + img_temp
    if len(img_temp) == 0:
        break
print "read img done, size is "+str(len(img))+" bytes"
mlo_img.close()
img_size = len(img)
ser = serial.Serial(com_num,115200)

#asic id size is 81bytes
while True:
       print "check device..."
       asic_id = ser.read(81)
       print "read 81 bytes"
       result = struct.unpack("<81B",asic_id)
       items = result[0:8]
       print "read items: " + hex(items[0])
       print "read dev : " + hex(items[4])
       if hex(items[4]) == "0x44" or hex(items[4]) =="0x45":
              print "found Omap4460"
              print "check all right..."
              print "ROM revision: "+hex(items[6])
#continue booting with UART
              ser.write(0xf0030002)
              break
       else:
              print "wrong asic id format... try again"
              ser.flushInput()
              ser.write(0xf0030003)
              continue

print "transfer start..."
ser.write(img_size)
print "transfer img.... "
ser.write(img)
print "transfer done..."

print "try to interrupt auto boot"
ser.write("\n")
ser.write("\n")
ser.close()
              

              


