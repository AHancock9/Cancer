#recive ASIC ID first
#img load at 0x40300000
#return 0xf003 0002
#send img


import serial
import struct

if len(sys.argv) != 3:
       print "usage: python serial_downloader <comnum> <filename>"
com_num = sys.argv[1]
file_name = sys.argv[2]
mlo_img = open(filename, "rb")
img = ""
while True:
    img_temp = mlo_img.read(256)
    img = img + img_temp
    if len(img_temp) == 0:
        break
print "read img done, size is "+str(img)+" bytes"
mlo_img.close()
img_size = len(img)
ser = serial.Serial(com_num,115200)

#asic id size is 81bytes
while True:
       asic_id = ser.read(81)
       items,id_subblock,no_use0,no_use1,no_use2,crc = struct.unpack("=1B7B4B23B35B11B",asic_id)
       print "read items: "+hex(items)
       id_block = struct.unpack("=BBBSBBB",id_subblock)
       if hex(id_block[3]) == "0x44" or hex(id_block[3]) =="0x40":
              print "found Omap4460"
              print "check all right..."
              print "ROM revision: "+hex(id_block[5])
#continue booting with UART
              ser.write(0xf0030002)
              break
       else:
              print "wrong asic id format... try again"
              ser.write(0xf0030003)
              continue

print "transfer start..."
ser.write(img_size)
print "transfer img.... "
ser.write(img)
print "transfer done..."
ser.close()
              


