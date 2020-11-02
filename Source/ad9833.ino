{\rtf1\ansi\ansicpg1252\cocoartf2513
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fmodern\fcharset0 Courier;\f1\fmodern\fcharset0 Courier-Oblique;\f2\fmodern\fcharset0 Courier-Bold;
\f3\fnil\fcharset0 Calibri;}
{\colortbl;\red255\green255\blue255;\red0\green0\blue128;\red0\green128\blue0;\red187\green94\blue0;
\red0\green128\blue128;\red128\green0\blue255;\red128\green0\blue0;}
{\*\expandedcolortbl;;\csgenericrgb\c0\c0\c50196;\csgenericrgb\c0\c50196\c0;\csgenericrgb\c73333\c36863\c0;
\csgenericrgb\c0\c50196\c50196;\csgenericrgb\c50196\c0\c100000;\csgenericrgb\c50196\c0\c0;}
\paperw11900\paperh16840\margl1440\margr1440\vieww10800\viewh8400\viewkind0
\deftab720
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0

\f0\fs20 \cf2 #include <SPI.h>\
#include <MD_AD9833.h>\
\
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0

\f1\i \cf3 // Pins for SPI comm with the AD9833 IC\
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0

\f0\i0 \cf2 #define DATA  11	   
\f1\i \cf3 ///< SPI Data pin number\

\f0\i0 \cf2 #define CLK   13	   
\f1\i \cf3 ///< SPI Clock pin number\

\f0\i0 \cf2 #define FSYNC 10	   
\f1\i \cf3 ///< SPI Load pin number (FSYNC in AD9833 usage)\

\f0\i0 \cf2 #define CS_DIGIPOT 9 
\f1\i \cf3 // MCP41010 chip select - digital potentiometer.\
\
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0

\f0\i0 \cf4 MD_AD9833\cf5 	\cf4 AD\cf2 (\cf4 FSYNC\cf2 );\cf5  
\f1\i \cf3 // Hardware SPI\
//MD_AD9833	AD(DATA, CLK, FSYNC); // Arbitrary SPI pins\
\
// Character constants for commands\
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0

\f2\i0\b \cf6 const
\f0\b0 \cf5  
\f2\b \cf6 char
\f0\b0 \cf5  \cf4 CMD_HELP\cf5  \cf2 =\cf5  \cf2 '?';\

\f2\b \cf6 const
\f0\b0 \cf5  
\f2\b \cf6 char
\f0\b0 \cf5  \cf4 BLANK\cf5  \cf2 =\cf5  \cf2 ' ';\

\f2\b \cf6 const
\f0\b0 \cf5  
\f2\b \cf6 char
\f0\b0 \cf5  \cf4 PACKET_START\cf5  \cf2 =\cf5  \cf2 ':';\

\f2\b \cf6 const
\f0\b0 \cf5  
\f2\b \cf6 char
\f0\b0 \cf5  \cf4 PACKET_END\cf5  \cf2 =\cf5  \cf2 ';';\

\f2\b \cf6 const
\f0\b0 \cf5  
\f2\b \cf6 char
\f0\b0 \cf5  \cf4 CMD_FREQ\cf5  \cf2 =\cf5  \cf2 'F';\

\f2\b \cf6 const
\f0\b0 \cf5  
\f2\b \cf6 char
\f0\b0 \cf5  \cf4 CMD_PHASE\cf5  \cf2 =\cf5  \cf2 'P';\

\f2\b \cf6 const
\f0\b0 \cf5  
\f2\b \cf6 char
\f0\b0 \cf5  \cf4 CMD_OUTPUT\cf5  \cf2 =\cf5  \cf2 'O';\

\f2\b \cf6 const
\f0\b0 \cf5  
\f2\b \cf6 char
\f0\b0 \cf5  \cf4 OPT_FREQ\cf5  \cf2 =\cf5  \cf2 'F';\

\f2\b \cf6 const
\f0\b0 \cf5  
\f2\b \cf6 char
\f0\b0 \cf5  \cf4 OPT_PHASE\cf5  \cf2 =\cf5  \cf2 'P';\

\f2\b \cf6 const
\f0\b0 \cf5  
\f2\b \cf6 char
\f0\b0 \cf5  \cf4 OPT_SIGNAL\cf5  \cf2 =\cf5  \cf2 'S';\

\f2\b \cf6 const
\f0\b0 \cf5  
\f2\b \cf6 char
\f0\b0 \cf5  \cf4 OPT_1\cf5  \cf2 =\cf5  \cf2 '1';\

\f2\b \cf6 const
\f0\b0 \cf5  
\f2\b \cf6 char
\f0\b0 \cf5  \cf4 OPT_2\cf5  \cf2 =\cf5  \cf2 '2';\

\f2\b \cf6 const
\f0\b0 \cf5  
\f2\b \cf6 char
\f0\b0 \cf5  \cf4 OPT_MODULATE\cf5  \cf2 =\cf5  \cf2 'M';\

\f2\b \cf6 const
\f0\b0 \cf5  \cf4 uint8_t\cf5  \cf4 PACKET_SIZE\cf5  \cf2 =\cf5  \cf0 20\cf2 ;\
\

\f2\b \cf6 void
\f0\b0 \cf5  \cf4 setup\cf2 ()\
\{\
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0
\cf5   \cf4 pinMode\cf2 (\cf4 CS_DIGIPOT\cf2 ,\cf4 OUTPUT\cf2 );\
\
\cf5   \cf4 Serial\cf2 .\cf4 begin\cf2 (\cf0 57600\cf2 );\
\cf5   \cf4 AD\cf2 .\cf4 begin\cf2 ();\
\cf5   \cf4 usage\cf2 ();\
\
  
\f1\i \cf3 // 
\f0\i0 \cf2 Set to high first\
\cf5   \cf4 digitalWrite\cf2 (\cf4 CS_DIGIPOT\cf2 ,\cf4 HIGH\cf2 );\
\cf5   
\f1\i \cf3 // take the CS pin low to select the chip:\

\f0\i0 \cf5   \cf4 digitalWrite\cf2 (\cf4 CS_DIGIPOT\cf2 ,\cf4 LOW\cf2 );\
\cf5   
\f1\i \cf3 //  send in the address and value via SPI:\
  // 
\f3\i0\fs24 \cf0 Code 0 = PW0 connected to PB0\
\pard\pardeftab720\ri-340\partightenfactor0
\cf0     
\f1\i\fs20 \cf3 // 
\f3\i0\fs24 \cf0  Code B11111111 = 0xff = PW0 = PA0
\f1\i\fs20 \cf3 \
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0

\f0\i0 \cf5   \cf4 SPI\cf2 .\cf4 transfer\cf2 (\cf4 B00010001\cf2 );\
\cf5   
\f1\i \cf3 // write out the value for the resistor: 0-255, 255 most amplification\

\f0\i0 \cf5   \cf4 SPI\cf2 .\cf4 transfer\cf2 (\cf0 255\cf2 );\
\cf5   
\f1\i \cf3 // take the CS pin high to de-select the chip:\

\f0\i0 \cf5   \cf4 digitalWrite\cf2 (\cf4 CS_DIGIPOT\cf2 ,\cf4 HIGH\cf2 );\
\}\
\
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0

\f2\b \cf6 void
\f0\b0 \cf5  \cf4 usage\cf2 (
\f2\b \cf6 void
\f0\b0 \cf2 )\
\{\
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0
\cf5   \cf4 Serial\cf2 .\cf4 print\cf2 (\cf4 F\cf2 (\cf7 "\\n\\n[MD_AD9833_Tester]"\cf2 ));\
\cf5   \cf4 Serial\cf2 .\cf4 print\cf2 (\cf4 F\cf2 (\cf7 "\\n?\\thelp - this message"\cf2 ));\
\cf5   \cf4 Serial\cf2 .\cf4 print\cf2 (\cf4 F\cf2 (\cf7 "\\n\\n:<cmd><opt> <param>;"\cf2 ));\
\cf5   \cf4 Serial\cf2 .\cf4 print\cf2 (\cf4 F\cf2 (\cf7 "\\n:f1n;\\tset frequency 1 to n Hz"\cf2 ));\
\cf5   \cf4 Serial\cf2 .\cf4 print\cf2 (\cf4 F\cf2 (\cf7 "\\n:f2n;\\tset frequency 2 to n Hz"\cf2 ));\
\cf5   \cf4 Serial\cf2 .\cf4 print\cf2 (\cf4 F\cf2 (\cf7 "\\n:fmn;\\tset frequency modulation to n Hz"\cf2 ));\
\cf5   \cf4 Serial\cf2 .\cf4 print\cf2 (\cf4 F\cf2 (\cf7 "\\n:p1n;\\tset phase 1 to n in tenths of a degree (1201 is 120.1 deg)"\cf2 ));\
\cf5   \cf4 Serial\cf2 .\cf4 print\cf2 (\cf4 F\cf2 (\cf7 "\\n:p2n;\\tset phase 2 to n in tenths of a degree (1201 is 120.1 deg)"\cf2 ));\
\cf5   \cf4 Serial\cf2 .\cf4 print\cf2 (\cf4 F\cf2 (\cf7 "\\n:ofn;\\toutput frequency n or modulation [n=1/2/m]"\cf2 ));\
\cf5   \cf4 Serial\cf2 .\cf4 print\cf2 (\cf4 F\cf2 (\cf7 "\\n:opn;\\toutput phase n or modulation [n=1/2/m]"\cf2 ));\
\cf5   \cf4 Serial\cf2 .\cf4 print\cf2 (\cf4 F\cf2 (\cf7 "\\n:osn;\\toutput signal type n [n=(o)ff/(s)ine/(t)riangle/s(q)uare]"\cf2 ));\
\}\
\
\cf4 uint8_t\cf5  \cf4 htoi\cf2 (
\f2\b \cf6 char
\f0\b0 \cf5  \cf4 c\cf2 )\
\{\
\cf5   \cf4 c\cf5  \cf2 =\cf5  \cf4 toupper\cf2 (\cf4 c\cf2 );\
\
\cf5   
\f2\b \cf6 if
\f0\b0 \cf5  \cf2 (\cf4 c\cf5  \cf2 >=\cf5  \cf2 '0'\cf5  \cf2 &&\cf5  \cf4 c\cf5  \cf2 <=\cf5  \cf2 '9')\
\cf5       
\f2\b \cf6 return
\f0\b0 \cf2 (\cf4 c\cf5  \cf2 -\cf5  \cf2 '0');\
\cf5   
\f2\b \cf6 else
\f0\b0 \cf5  
\f2\b \cf6 if
\f0\b0 \cf5  \cf2 (\cf4 c\cf5  \cf2 >=\cf5  \cf2 'A'\cf5  \cf2 &&\cf5  \cf4 c\cf5  \cf2 <=\cf5  \cf2 'F')\
\cf5       
\f2\b \cf6 return
\f0\b0 \cf2 (\cf4 c\cf5  \cf2 -\cf5  \cf2 'A'\cf5  \cf2 +\cf5  \cf0 10\cf2 );\
\cf5   
\f2\b \cf6 else\

\f0\b0 \cf5       
\f2\b \cf6 return
\f0\b0 \cf2 (\cf0 0\cf2 );\
\}\
\
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0

\f2\b \cf6 char
\f0\b0 \cf5  \cf4 nextChar\cf2 (
\f2\b \cf6 void
\f0\b0 \cf2 )\
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0

\f1\i \cf3 // Read the next character from the serial input stream\
// Blocking wait\
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0

\f0\i0 \cf2 \{\
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0
\cf5   
\f2\b \cf6 while
\f0\b0 \cf5  \cf2 (!\cf4 Serial\cf2 .\cf4 available\cf2 ())\
\cf5     \cf2 ;\cf5  
\f1\i \cf3 /* do nothing */\

\f0\i0 \cf5   
\f2\b \cf6 return
\f0\b0 \cf2 (\cf4 toupper\cf2 (\cf4 Serial\cf2 .\cf4 read\cf2 ()));\
\}\
\
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0

\f2\b \cf6 char
\f0\b0 \cf5  \cf2 *\cf4 readPacket\cf2 (
\f2\b \cf6 void
\f0\b0 \cf2 )\
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0

\f1\i \cf3 // read a packet and return the\
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0

\f0\i0 \cf2 \{\
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0
\cf5   
\f2\b \cf6 static
\f0\b0 \cf5  
\f2\b \cf6 enum
\f0\b0 \cf5  \cf2 \{\cf5  \cf4 S_IDLE\cf2 ,\cf5  \cf4 S_READ_CMD\cf2 ,\cf5  \cf4 S_READ_MOD\cf2 ,\cf5  \cf4 S_READ_PKT\cf5  \cf2 \}\cf5  \cf4 state\cf5  \cf2 =\cf5  \cf4 S_IDLE\cf2 ;\
\cf5   
\f2\b \cf6 static
\f0\b0 \cf5  
\f2\b \cf6 char
\f0\b0 \cf5  \cf4 cBuf\cf2 [\cf4 PACKET_SIZE\cf5  \cf2 +\cf5  \cf0 1\cf2 ];\
\cf5   
\f2\b \cf6 static
\f0\b0 \cf5  
\f2\b \cf6 char
\f0\b0 \cf5  \cf2 *\cf4 cp\cf2 ;\
\cf5   
\f2\b \cf6 char
\f0\b0 \cf5  \cf4 c\cf2 ;\
\
\cf5   
\f2\b \cf6 switch
\f0\b0 \cf5  \cf2 (\cf4 state\cf2 )\
\cf5   \cf2 \{\
\cf5   
\f2\b \cf6 case
\f0\b0 \cf5  \cf4 S_IDLE\cf2 :\cf5    
\f1\i \cf3 // waiting for packet start\

\f0\i0 \cf5     \cf4 c\cf5  \cf2 =\cf5  \cf4 nextChar\cf2 ();\
\cf5     
\f2\b \cf6 if
\f0\b0 \cf5  \cf2 (\cf4 c\cf5  \cf2 ==\cf5  \cf4 CMD_HELP\cf2 )\
\cf5     \cf2 \{\
\cf5       \cf4 usage\cf2 ();\
\cf5       
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\cf5     \cf2 \}\
\cf5     
\f2\b \cf6 if
\f0\b0 \cf5  \cf2 (\cf4 c\cf5  \cf2 ==\cf5  \cf4 PACKET_START\cf2 )\
\cf5     \cf2 \{\
\cf5       \cf4 cp\cf5  \cf2 =\cf5  \cf4 cBuf\cf2 ;\
\cf5       \cf4 state\cf5  \cf2 =\cf5  \cf4 S_READ_CMD\cf2 ;\
\cf5     \cf2 \}\
\cf5     
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\
\cf5   
\f2\b \cf6 case
\f0\b0 \cf5  \cf4 S_READ_CMD\cf2 :\cf5    
\f1\i \cf3 // waiting for command char\

\f0\i0 \cf5     \cf4 c\cf5  \cf2 =\cf5  \cf4 nextChar\cf2 ();\
\cf5     
\f2\b \cf6 if
\f0\b0 \cf5  \cf2 (\cf4 c\cf5  \cf2 ==\cf5  \cf4 CMD_FREQ\cf5  \cf2 ||\cf5  \cf4 c\cf5  \cf2 ==\cf5  \cf4 CMD_PHASE\cf5  \cf2 ||\cf5  \cf4 c\cf5  \cf2 ==\cf5  \cf4 CMD_OUTPUT\cf2 )\
\cf5     \cf2 \{\
\cf5       \cf2 *\cf4 cp\cf2 ++\cf5  \cf2 =\cf5  \cf4 c\cf2 ;\
\cf5       \cf4 state\cf5  \cf2 =\cf5  \cf4 S_READ_MOD\cf2 ;\
\cf5     \cf2 \}\
\cf5     
\f2\b \cf6 else\

\f0\b0 \cf5       \cf4 state\cf5  \cf2 =\cf5  \cf4 S_IDLE\cf2 ;\
\cf5     
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\
\cf5   
\f2\b \cf6 case
\f0\b0 \cf5  \cf4 S_READ_MOD\cf2 :\cf5  
\f1\i \cf3 // Waiting for command modifier\

\f0\i0 \cf5     \cf4 c\cf5  \cf2 =\cf5  \cf4 nextChar\cf2 ();\
\cf5     
\f2\b \cf6 if
\f0\b0 \cf5  \cf2 (\cf4 c\cf5  \cf2 ==\cf5  \cf4 OPT_FREQ\cf5  \cf2 ||\cf5  \cf4 c\cf5  \cf2 ==\cf5  \cf4 OPT_PHASE\cf5  \cf2 ||\cf5  \cf4 c\cf5  \cf2 ==\cf5  \cf4 OPT_SIGNAL\cf5  \cf2 ||\
\cf5       \cf4 c\cf5  \cf2 ==\cf5  \cf4 OPT_1\cf5  \cf2 ||\cf5  \cf4 c\cf5  \cf2 ==\cf5  \cf4 OPT_2\cf5  \cf2 ||\cf5  \cf4 c\cf5  \cf2 ==\cf5  \cf4 OPT_MODULATE\cf2 )\
\cf5     \cf2 \{\
\cf5       \cf2 *\cf4 cp\cf2 ++\cf5  \cf2 =\cf5  \cf4 c\cf2 ;\
\cf5       \cf4 state\cf5  \cf2 =\cf5  \cf4 S_READ_PKT\cf2 ;\
\cf5     \cf2 \}\
\cf5     
\f2\b \cf6 else\

\f0\b0 \cf5       \cf4 state\cf5  \cf2 =\cf5  \cf4 S_IDLE\cf2 ;\
\cf5     
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\
\cf5   
\f2\b \cf6 case
\f0\b0 \cf5  \cf4 S_READ_PKT\cf2 :\cf5  
\f1\i \cf3 // Reading parameter until packet end\

\f0\i0 \cf5     \cf4 c\cf5  \cf2 =\cf5  \cf4 nextChar\cf2 ();\
\cf5     
\f2\b \cf6 if
\f0\b0 \cf5  \cf2 (\cf4 c\cf5  \cf2 ==\cf5  \cf4 PACKET_END\cf2 )\
\cf5     \cf2 \{\
\cf5       \cf2 *\cf4 cp\cf5  \cf2 =\cf5  \cf2 '\\0';\
\cf5       \cf4 state\cf5  \cf2 =\cf5  \cf4 S_IDLE\cf2 ;\
\cf5       
\f2\b \cf6 return
\f0\b0 \cf2 (\cf4 cBuf\cf2 );\
\cf5     \cf2 \}\
\cf5     \cf2 *\cf4 cp\cf2 ++\cf5  \cf2 =\cf5  \cf4 c\cf2 ;\
\cf5     
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\
\cf5   
\f2\b \cf6 default
\f0\b0 \cf2 :\
\cf5     \cf4 state\cf5  \cf2 =\cf5  \cf4 S_IDLE\cf2 ;\
\cf5     
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\cf5   \cf2 \}\
\
\cf5   
\f2\b \cf6 return
\f0\b0 \cf2 (\cf4 NULL\cf2 );\
\}\
\
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0

\f2\b \cf6 void
\f0\b0 \cf5  \cf4 processPacket\cf2 (
\f2\b \cf6 char
\f0\b0 \cf5  \cf2 *\cf4 cp\cf2 )\
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0

\f1\i \cf3 // Assume we have a correctly formed packet from the parsing in readPacket()\
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0

\f0\i0 \cf2 \{\
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0
\cf5   \cf4 uint32_t\cf5   \cf4 ul\cf2 ;\
\cf5   \cf4 MD_AD9833\cf2 ::\cf4 channel_t\cf5  \cf4 chan\cf2 ;\
\cf5   \cf4 MD_AD9833\cf2 ::\cf4 mode_t\cf5  \cf4 mode\cf2 ;\
\
\cf5   
\f2\b \cf6 switch
\f0\b0 \cf5  \cf2 (*\cf4 cp\cf2 ++)\
\cf5   \cf2 \{\
\cf5   
\f2\b \cf6 case
\f0\b0 \cf5  \cf4 CMD_FREQ\cf2 :\
\cf5     
\f2\b \cf6 switch
\f0\b0 \cf5  \cf2 (*\cf4 cp\cf2 ++)\
\cf5     \cf2 \{\
\cf5     
\f2\b \cf6 case
\f0\b0 \cf5  \cf4 OPT_1\cf2 :\cf5  \cf4 chan\cf5  \cf2 =\cf5  \cf4 MD_AD9833\cf2 ::\cf4 CHAN_0\cf2 ;\cf5  
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\cf5     
\f2\b \cf6 case
\f0\b0 \cf5  \cf4 OPT_2\cf2 :\cf5  \cf4 chan\cf5  \cf2 =\cf5  \cf4 MD_AD9833\cf2 ::\cf4 CHAN_1\cf2 ;\cf5  
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\cf5     
\f2\b \cf6 case
\f0\b0 \cf5  \cf4 OPT_MODULATE\cf2 :\cf5  
\f1\i \cf3 /* do something in future */
\f0\i0 \cf5  
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\cf5     \cf2 \}\
\
\cf5     \cf4 ul\cf5  \cf2 =\cf5  \cf4 strtoul\cf2 (\cf4 cp\cf2 ,\cf5  \cf4 NULL\cf2 ,\cf5  \cf0 10\cf2 );\
\cf5     \cf4 AD\cf2 .\cf4 setFrequency\cf2 (\cf4 chan\cf2 ,\cf5  \cf4 ul\cf2 );\
\cf5     
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\
\cf5   
\f2\b \cf6 case
\f0\b0 \cf5  \cf4 CMD_PHASE\cf2 :\
\cf5     
\f2\b \cf6 switch
\f0\b0 \cf5  \cf2 (*\cf4 cp\cf2 ++)\
\cf5     \cf2 \{\
\cf5     
\f2\b \cf6 case
\f0\b0 \cf5  \cf4 OPT_1\cf2 :\cf5  \cf4 chan\cf5  \cf2 =\cf5  \cf4 MD_AD9833\cf2 ::\cf4 CHAN_0\cf2 ;\cf5  
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\cf5     
\f2\b \cf6 case
\f0\b0 \cf5  \cf4 OPT_2\cf2 :\cf5  \cf4 chan\cf5  \cf2 =\cf5  \cf4 MD_AD9833\cf2 ::\cf4 CHAN_1\cf2 ;\cf5  
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\cf5     \cf2 \}\
\
\cf5     \cf4 ul\cf5  \cf2 =\cf5  \cf4 strtoul\cf2 (\cf4 cp\cf2 ,\cf5  \cf4 NULL\cf2 ,\cf5  \cf0 10\cf2 );\
\cf5     \cf4 AD\cf2 .\cf4 setPhase\cf2 (\cf4 chan\cf2 ,\cf5  \cf2 (\cf4 uint16_t\cf2 )\cf4 ul\cf2 );\
\cf5     
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\
\cf5   
\f2\b \cf6 case
\f0\b0 \cf5  \cf4 CMD_OUTPUT\cf2 :\
\cf5     
\f2\b \cf6 switch
\f0\b0 \cf5  \cf2 (*\cf4 cp\cf2 ++)\
\cf5     \cf2 \{\
\cf5     
\f2\b \cf6 case
\f0\b0 \cf5  \cf4 OPT_FREQ\cf2 :\
\cf5       
\f2\b \cf6 switch
\f0\b0 \cf5  \cf2 (*\cf4 cp\cf2 )\
\cf5       \cf2 \{\
\cf5       
\f2\b \cf6 case
\f0\b0 \cf5  \cf4 OPT_1\cf2 :\cf5  \cf4 chan\cf5  \cf2 =\cf5  \cf4 MD_AD9833\cf2 ::\cf4 CHAN_0\cf2 ;\cf5  
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\cf5       
\f2\b \cf6 case
\f0\b0 \cf5  \cf4 OPT_2\cf2 :\cf5  \cf4 chan\cf5  \cf2 =\cf5  \cf4 MD_AD9833\cf2 ::\cf4 CHAN_1\cf2 ;\cf5  
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\cf5       
\f2\b \cf6 case
\f0\b0 \cf5  \cf4 OPT_MODULATE\cf2 :\cf5  
\f1\i \cf3 /* do something in future */
\f0\i0 \cf5  
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\cf5       \cf2 \}\
\cf5       \cf4 AD\cf2 .\cf4 setActiveFrequency\cf2 (\cf4 chan\cf2 );\
\cf5       
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\
\cf5     
\f2\b \cf6 case
\f0\b0 \cf5  \cf4 OPT_PHASE\cf2 :\
\cf5       
\f2\b \cf6 switch
\f0\b0 \cf5  \cf2 (*\cf4 cp\cf2 )\
\cf5       \cf2 \{\
\cf5       
\f2\b \cf6 case
\f0\b0 \cf5  \cf4 OPT_1\cf2 :\cf5  \cf4 chan\cf5  \cf2 =\cf5  \cf4 MD_AD9833\cf2 ::\cf4 CHAN_0\cf2 ;\cf5  
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\cf5       
\f2\b \cf6 case
\f0\b0 \cf5  \cf4 OPT_2\cf2 :\cf5  \cf4 chan\cf5  \cf2 =\cf5  \cf4 MD_AD9833\cf2 ::\cf4 CHAN_1\cf2 ;\cf5  
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\cf5       
\f2\b \cf6 case
\f0\b0 \cf5  \cf4 OPT_MODULATE\cf2 :\cf5  
\f1\i \cf3 /* do something in future */
\f0\i0 \cf5  
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\cf5       \cf2 \}\
\cf5       \cf4 AD\cf2 .\cf4 setActivePhase\cf2 (\cf4 chan\cf2 );\
\cf5       
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\
\cf5     
\f2\b \cf6 case
\f0\b0 \cf5  \cf4 OPT_SIGNAL\cf2 :\
\cf5       
\f2\b \cf6 switch
\f0\b0 \cf5  \cf2 (*\cf4 cp\cf2 )\
\cf5       \cf2 \{\
\cf5       
\f2\b \cf6 case
\f0\b0 \cf5  \cf2 'O':\cf5  \cf4 mode\cf5  \cf2 =\cf5  \cf4 MD_AD9833\cf2 ::\cf4 MODE_OFF\cf2 ;\cf5     
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\cf5       
\f2\b \cf6 case
\f0\b0 \cf5  \cf2 'S':\cf5  \cf4 mode\cf5  \cf2 =\cf5  \cf4 MD_AD9833\cf2 ::\cf4 MODE_SINE\cf2 ;\cf5    
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\cf5       
\f2\b \cf6 case
\f0\b0 \cf5  \cf2 'T':\cf5  \cf4 mode\cf5  \cf2 =\cf5  \cf4 MD_AD9833\cf2 ::\cf4 MODE_TRIANGLE\cf2 ;\cf5   
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\cf5       
\f2\b \cf6 case
\f0\b0 \cf5  \cf2 'Q':\cf5  \cf4 mode\cf5  \cf2 =\cf5  \cf4 MD_AD9833\cf2 ::\cf4 MODE_SQUARE1\cf2 ;\cf5   
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\cf5       \cf2 \}\
\cf5       \cf4 AD\cf2 .\cf4 setMode\cf2 (\cf4 mode\cf2 );\
\cf5       
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\cf5     \cf2 \}\
\cf5     
\f2\b \cf6 break
\f0\b0 \cf2 ;\
\cf5   \cf2 \}\
\
\cf5   
\f2\b \cf6 return
\f0\b0 \cf2 ;\
\}\
\
\
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0

\f2\b \cf6 void
\f0\b0 \cf5  \cf4 loop\cf2 ()\
\{\
\pard\tx916\tx1832\tx2748\tx3664\tx4580\tx5496\tx6412\tx7328\tx8244\tx9160\tx10076\tx10992\tx11908\tx12824\tx13740\tx14656\pardeftab720\ri-340\partightenfactor0
\cf5   
\f2\b \cf6 char
\f0\b0 \cf5   \cf2 *\cf4 cp\cf2 ;\
\
\cf5   
\f2\b \cf6 if
\f0\b0 \cf5  \cf2 ((\cf4 cp\cf5  \cf2 =\cf5  \cf4 readPacket\cf2 ())\cf5  \cf2 !=\cf5  \cf4 NULL\cf2 )\
\cf5     \cf4 processPacket\cf2 (\cf4 cp\cf2 );\
\}\
}