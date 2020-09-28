import spidev

spi=spidev.SpiDev()
spi.open(0,0)
spi.max_speed_hz=500000

def send_data(input):
 tx_msb=input>>8
 tx_lsb=input & 0xFF
 spi.xfer([tx_msb,tx_lsb])
 print(input)


send_data(0x0100) # Send a reset

send_data(0x1000) #MSB
send_data(0x4001) #Freq 0 reg = 2300hz

send_data(0x0000) #LSB
send_data(0x60f0) #Freq 0 reg = 2300hz

send_data(0x0028) # Blockwave output


