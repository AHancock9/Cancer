Omap4460's internal ROM will read a file "MLO" in SD card.
This is called memory booting. When boot from a GP-device, the img need a GP head and a CH head.
This tool will do this for bare bin file.

Usage£º

python mkhead.py main.bin 0x40303080  #load main.bin at 0x40303080