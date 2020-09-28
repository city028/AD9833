# Using the AD9833 with a Raspberry Pi

<sorry for the mess, I am learning how formatting works>

## Introduction

In this project I will be using an AD9833 module you can buy e.g. at Amazon or eBay and use it with Python(3) on a Raspberry Pi. In my research I found a lot of references about using these modules with an Arduino but the examples for using these modules with a Raspberry Pi did not work for me so I did my own research and came-up with something which works for me and I hope for you to.

In the chapters below I’ll discuss the hardware, how to hook the modules up to the Raspberry Pi and I’ll discuss in the software section how to programme the modules using Python. 

## Hardware

The AD9833 module below on the left, as you can see from the schematic below it just holds the AD9833 chip, a crystal for the clock and some R’s and C’s to make it all work.

The Module on the right expands upon this design by introducing and amplifier to the output of the AD9833 with a digital resistor (also programmable via SPI) so that you can change the amplification setting.


AD9833 Module|AD9833 with Amplification Module
---------------------|---------------------
<img src="https://github.com/city028/AD9833/blob/master/Source/pics/IMG_2763.jpeg" width="200"> | <img src="https://github.com/city028/AD9833/blob/master/Source/pics/IMG_2760.jpeg" width="200">
<img src="https://github.com/city028/AD9833/blob/master/Source/pics/IMG_0416.jpeg" width="200">|<img src="https://github.com/city028/AD9833/blob/master/Source/pics/IMG_0414.jpeg" width="200">
	 


## Raspberry Pi Header Pin-out

Let us first take a look at the raspberry Pi GPIO Header Pin-out below from element14.com

 

## SPI Bus

The Raspberry Pi is provided with an SPI bus which can be used for a serial connection between the Raspberry Pi and other devices.

The AD9833 modules are using an SPI bus as well to receive data from the SPI master so that they can be configured to create e.g. a sinewave at 1Khz. So, if we identify the SPI pins on the Raspberry Pi header we get the following table:

PIN	GPIO	Description
19	GPIO10	SPI_MOSI
21	GPIO09	SPI_MISO
23	GPIO11	SPI_CLK
24	GPIO08	SPI_CE0_N
26	GPIO07	SPI_CE1_N

The below diagram explains how the SPI bus needs to be wired up:

 
Assume that in our case the SPI Master is the Raspberry PI and that the AD9833 modules are connected to the Master as depicted for the Slaves.

As we will be using the AD9833 modules which only receive data and will not send data back to the master, the MISO connectivity between Master and slaves can be omitted. If you however are working with an AD converter you will need the MISO link to read the data from your ADC.

So, for the regular AD9833 module we’ll get the following connection table

Raspberry Pi	AD9833 Module
PIN	GPIO	Description	PIN	Remarks
19	GPIO10	SPI_MOSI	DAT	MOSI = Data = Receive data from Master
23	GPIO11	SPI_CLK	CLK	Clock
24	GPIO08	SPI_CE0_N 	FNC	FNC = Chip select = FSYNC0 = SSO = Device 0
05	+5v	VCC	VCC	VCC
06	GND	Ground	GND	Ground

Note: The Raspberry PI has two pins which are used for selecting the chip (Chip Select, SS) to where to send the data to or to receive from, these are: 

PIN	GPIO	Description
24	GPIO08	SPI_CE0_N 
26	GPIO07	SPI_CE1_N 

So, with the Raspberry Pi we can drive 2 different SPI slaves using the same SPI bus (e.g. Slave 1 and slave 2 above)

For the AD9833 module with amplification we get to the following connection table:

Raspberry Pi	AD9833 with Amplification Module
PIN	GPIO	Description	PIN	Remarks
19	GPIO10	SPI_MOSI	DAT	MOSI = Data = Receive data from Master
23	GPIO11	SPI_CLK	CLK	Clock
24	GPIO08	SPI_CE0_N 	FSY	FNC = Chip select = FSYNC0 = SSO = Device 0
26	GPIO07	SPI_CE1_N 	CS	Used to programme the digital resistor
SS1 = Device 1
05	+5v	VCC	VCC	VCC
06	GND	Ground	GND	Ground
<Test this out>

## AD9833 Module wire diagram

<Insert Fritzing diagrams>

## AD9833 Amplification Module wire diagram

<Insert Fritzing diagrams>

## Software Installation

Now that we have hooked up the hardware we can have a look at the software to make things work.

In this section I will guide you through how I made things work and what software I have used, probably you’ll be able to make it work with other OS’s as well for the Raspberry Pi but for this example I have used Raspberry PI OS (32-bit) Lite (at the time of writing the August 2020 version).

From here onwards, I will assume that you have a Raspberry Pi up and running with the OS version I have mentioned above and that you are able to SSH to the Raspberry Pi. For more information on the OS Installation, enabling SSH and flashing the OS to the SD card please look at the links table mentioned below.

Note: for security reasons you should change the default password

The below table shows a step by step approach to install the required software

Commands	Output
Update the OS with:

$sudo apt update	 
$sudo apt upgrade

Type: Y	 
After this is done (can take a couple of minutes) we need to enable the SPI interface on the Raspberry, to do this we type in the following command:

$sudo raspi-config

Select: 5 (use arrow keys). Interfacing options” hit enter
	 
Select P4 SPI and hit enter

	 
Use Tab to select <Yes> and hit enter	 
The PSI interface is now enabled, hit OK	 
Use Tab to select <Finish> and exit raspi-config	 

Now that the Raspberry Pi has been “Updated” and “Upgraded” and the SPI interface is now enabled we can focus on installing Python3, PIP3 and SPIDEV (the library I use to use the SPI interface in Python).

Command	Output
$sudo apt install python3 idle3

Type: Y and enter	 
When done we need to install PIP3 with the following command

$sudo apt install python3-pip

Hit: Y and Enter

PIP3 is required to install SPIDEV, you probably get some warnings on Locale but they can be ignored	 

 
Now install SPIDEV using PIP3

$ sudo pip3 install spidev	 

Ok, everything we need is now enabled and installed so let’s start programming!

Well, hold on, first some background on how the AD9833 works….

# Programming the AD9833

This part took me quite a while before I figured it out as the examples I found on the Internet did not work for me for some reason.

As mentioned above the AD9833 uses a SPI bus (serial) to communicate with the master (in this case the Raspberry), when the chip is selected (SPI_CE0_N or SPI_CE1_N) data can be written to the chip to programme it for a certain frequency and set the output to sine, sawtooth or block (and in case of the AD9833 with amplification also the peak to peak value of the output using the amplifier chip).

Link #1 in the table below in this document, the datasheet of the AD9833 can be downloaded which gives us a lot of information.

## The AD9833 Control register

The control register is used to “programme” the AD9833 the way we would like it, so from the raspberry Pi we send a number of commands and the chip starts outputting the signal and the Raspberry can do other things (this is the main reason why I chose the AD9833 to offload creating a signal to another device). The AD9833 uses a 16-bit register as a control register, each bit in that register has a purpose (please check-out table 2, page 10 of the datasheet).

The way I got this to work is to first write a command to the AD9833 to execute a reset (Bit D8). This means that Bit D8 should be set to 1.

 

This corresponds to the Hex value of: 0x0100

Note: I am using the calculator on the mac which has a programme view but, in the table, below you will find a link to a converter (Link #10).

Now we can send bytes to the frequency registers of which the AD9833 has 2 (see table 3, page 11 of the data sheet).

We are only going to use FREQ0 in this example which means that D15 and D14 should be set to 01 (for FRQ1 this will be: 10).

The FREQ0 register is 28 bits and has 2 registers, one for the Most Significant Byte (MSB) and one for the Least Significant Byte (LSB), both 14 bits. See table 6 and 7 on page 11 of the AD9833 datasheet.

We will first write to the MSB by sending a word with bit D12 set

 

This corresponds to Hex: 0x1000

The command is followed by the value we want to set plus ensuring that we write it in the proper FREQ register, as we are using FREQ0 we need to ensure that D15 and D14 are set to 01.

 

I will get back to the MSB value as there is some Math involved….

Now that we have set the MSB we can set the LSB, for this D12 needs to be 0 so we’ll write all zeros to the register.

 

Which is hex :0x0000

Now we write the LSB to FREQ0:

 

We will close off by setting the signal to a square wave (will get back on that later).

To get a Square wave we need to set D5 (OPBITEN) to be 1 the DAC will be disabled and you will have a direct square wave output (although this defies the purpose of using a DAC, for me with my sheep oscilloscope it was the best way to measure a proper signal, we’ll get back to getting a sine wave out of the module later).

D5 = OPBITEN = No DAC = 1

The next thing I stumbled on was my output frequency was 2 x what I thought it would be, by setting DIV2, D3 to 1 we get the expected frequency.

D3 = DIV2 = 1 = No MSB/2

 

Which corresponds to hex: 0x0028

## Calculating the frequency word

Ok, brace you selves, here is the math part.

We need to calculate a frequency word (28 bits) which we need to write to the MSB and LSB registers using the below formula:

 
 
The information can be found in the application notes which can be find in link #11 in the table below.

Here is an example for creating a 400Hz frequency:

 

The 25Mhz (F mclk) is the frequency of the crystal providing the clock to the AD9833. F out is the frequency we want to get out of the AD9833, in this case 400Hz and lastly the 2^28 is above my paygrade but what it states in the documentation is: 

“The phase accumulator in the AD9833 is implemented in 28 bits, Therefore, in the AD9833, 2(pi) = 2^28”

Ok, now you know, I still don’t, but it does not matter for what we are doing.

The outcome of the above calculation for a required 400hz signal is: 0x10C7 (I noticed this is not exact, you might need to tweak this value to get closer to the desired output)

After tinkering with the values and watching it on my scope I got to a value of: 0x1100 so slightly higher than the calculation (maybe the AD9833 is not accurate or my scope…probably the latter).

 

Now that we have this value we can make the MSB and LSB.

Before we proceed we need to be reminded that the LSB and MSB registers are 14 bit registers so we need to ensure that whatever frequency word we get we need to ensure it fits into 2 14bit registers and not 2 16bit registers as D15 and D14 are used to designate FREQ0 or FREQ1. 

For 400hz this is not a big deal as the last bit set is D12 but for higher frequencies we need to split the frequency word at 14 bits (D00 – D13).

Let’s first finish up the 400Hz calculation (using 0x1100) and then we’ll look at a higher frequency.

First of all, we’ll do a logical AND with 0x3ff where bits D00 – D13 are set to 1, above this they are 0 so this would give is the LSB 14 bits.

 

Now let’s set D15=0 and D14=1 to select FREQ0 

 

So our LSB = 0x5100 when writing it to FREQ0.

In the case of 400Hz we have no bits set higher than D12 so the MSB would be 0x00 but we need to set D15=0 and D14 =1.

 


Based upon the previous information we now know what values to write to the AD9833 for 400Hz.

Value	Remarks
0x0100	Send a reset to the AD9833 
0x1000	Select the MSB Register
0x4000	Write 0x0000 to FREQ0
0x0000	Select the LSB Register
0x5100	Write 0x1100 to FREQ0
0x0028	Select Block wave and ensure we don’t use DIV/2

Please look in the Source directory on Github to check out the 400hz.py source file which sets a block wave of 400hz (below I will explain the code in more detail).

## Higher Frequencies MSB and LSB calculations

Now that we know what values we need for 400Hz lets take a look at a bit higher frequency such as 2300Hz. 

Using the same calculation as mentioned above I came to the follow frequency work:

0x6189 = 0110 0001 1000 1001  

 

We now have a challenge, bit D14 is set in this value so we need to do something to determine the MSB but first but first let’s determine the LSB

 

So yeah, we are back at 0x6189 but we know now that D15 = 0 and D14 =1 which selects FREQ0.

After some tinkering with the values I got to a LSB value of 0x60f0

Now we need to do something with the MSB by moving bits to the right 14x, AND to make sure D15 and D14 are not set and then OR by 0x4000 to set bits D15,D14 correctly for FREQ0.

 

So, when the dust settles…the MSB is 0x4001.

Based upon the previous information we now know what values to write to the AD9833 for 2300hz.

Value	Remarks
0x0100	Send a reset to the AD9833 
0x1000	Select the MSB Register
0x4001	Write MSB = 0x0001 to FREQ0
0x0000	Select the LSB Register
0x6189	Write LSB = 0x20F0 to FREQ0
0x0028	Select Block wave and ensure we don’t use DIV/2

Please look in the Source directory on Github to check out the 2300hz.py source file which sets a block wave of 2300hz (below I will explain the code in more detail).

# Finally, some programming

Let’s keep it simple before we let loose our programming skills and focus on what is required to get some output and we’ll use the normal AD9833 module for this example.

First off create a file e.g. 2300hz.py and add the following

import spidev

This will import the spidev library we installed earlier above, now lets create the SPI object

spi=spidev.SpiDev()

And open up communications

spi.open(0,0)

SPIDEV supports 2 SPI busses and each with 2 devices (as far as I know)

The syntax for the command is:

spi.open(bus,device)

We only have one bus on the Raspberry, so BUS = 0

We can connect two devices:
Device = 0 = SPI_CE0_N = PIN 24 = GPIO08
Device = 1 = SPI_CE1_N = PIN 26 = GPIO07

So, with the command above we’ll select Bus 0 and Device 0

spi.max_speed_hz=500000

The command above sets the clock speed which is used between the Raspberry PI and the SPI slave devices, I have not played with this, please let me know your thoughts.

def send_data(input):
    tx_msb=input>>8
    tx_lsb=input & 0xFF
    spi.xfer([tx_msb,tx_lsb])
    print(input)

The only bit of “fancy” programming here is to break up the word we want to write to the AD9833 into to bytes being the MSB (Byte this case, 8 bits) and LSB (8 bits), you can see that a bit shift of 8 bits is used to determine the MSB and an AND against 0xff is used to determine the LSB.

After this the spidev procedure “spi.xfer()” is used to send the two bytes, MSB first followed by LSB) and finally the input is printed so that you at least see some output on your screen.

Now we can start sending some information to the FREQ0 registers

send_data(0x0100) # Send a reset

send_data(0x1000) # Select the MSB Register
send_data(0x4001) # Write MSB = 0x0001 to FREQ0

send_data(0x0000) # Select the LSB Register
send_data(0x60f0)  # Write LSB = 0x20F0 to FREQ0

send_data(0x0028) # Blockwave output


Bringing it together we get:
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

send_data(0x1000) # Select the MSB Register
send_data(0x4001) # Write MSB = 0x0001 to FREQ0

send_data(0x0000) # Select the LSB Register
send_data(0x60f0)  # Write LSB = 0x20F0 to FREQ0

send_data(0x0028) # Blockwave output


Now, let execute this code

$ python3 2300hz.py

If all goes well you would see a 2300hz sinewave on your oscilloscope.

 

Please check out the Source directory for more examples.

# Testing

Although the picture above looks OK one of the big issues I had was testing the output with my cheepo OWON USB oscilloscope, If I were to take a video the signal would be bouncing up and down, I am sure this has nothing to do with the AD9833 but more with my test environment and kit. 

I had the scope on an USB port of a laptop and the Raspberry Pi (and thus the AD9833 module) was connected via a separate USB charger plugged into a separate socket and I could net get a proper signal, it looked like I had a 50Hz signal of 230Volts AC messing up my measurements. Once I powered the raspberry of an USB port on the Laptop things got better so I definitely have a challenge with grounding in my workshop.

I need to do some further testing with creating a sine wave as this totally messed up the measured signal, the voltage drop seems to be significant when switching from a block wave to a sine wave (using the DAC) hence I bought the ad9833 with amplifier, once I figured that out I’ll update this page and the source code files.

# Summary

So, in summary, although some math is required to calculate the frequency word to be programmed in the AD9833 registers (I am sure we can resolve this by a simple procedure which does that for you, I’ll post that into the source directory when I am done) It is pretty straightforward to use the AD9833 with a Raspberry Pi when you figure out which bits of the control register do what and I hope the above description helped.

# Up next

* Create a procedure which does all the math for you to set the frequency
* Create a procedure to get a sinewave and sawtooth out of the AD9833 besides the frequency
* Test the AD9833 with amplification
* Create a procedure to use the AD9833 with amplifier module
* Add the Fritzing diagrams on how everything is hooked up

# Links

#|Description|Link
---------|----------|-------------
1|AD9833 Data sheet|https://datasheet.lcsc.com/szlcsc/Analog-Devices-ADI-AD9833BRMZ_C9652.pdf
2|Raspberry Pi Header pin out|https://www.element14.com/community/docs/DOC-88824/l/raspberry-pi-3-model-b-gpio-40-pin-block-poe-header-pinout
3|Raspberry Pi OS downloads|https://www.raspberrypi.org/downloads/raspberry-pi-os/
4|Enabling SSH|https://www.raspberrypi-spy.co.uk/2012/05/enable-secure-shell-ssh-on-your-raspberry-pi/
5|Using Ether to flash SD cards for the Raspberry Pi|https://www.balena.io/etcher/
6|Raspberry Pi and the SPI interface|https://raspberrypi-aa.github.io/session3/spi.html
7|Installing Python3|https://projects.raspberrypi.org/en/projects/generic-python-install-python3#linux
8|The SPIDEV website|https://pypi.org/project/spidev/
9|Install PIP|https://www.raspberrypi.org/documentation/linux/software/python.md
10|Binary to hex converter|https://www.rapidtables.com/convert/number/binary-to-hex.html
11|AD9833 application notes|https://www.analog.com/media/en/technical-documentation/application-notes/AN-1070.pdf



