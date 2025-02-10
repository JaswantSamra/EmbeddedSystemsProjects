# EmbeddedSystemsProjects
 General Repository of my Embedded Systems adventures

## Garage Opener
Motivation: Currently working retail with mainly late night shifts and I wanted a way to open my garage door without having to wake up parents every singly time.
Project Goal: Be able to open my garage door without a dedicated remote. 

### Project Resources:
1 x Adafruit QT Py ESP32-S3 (4MB Flash, 512KB SRAM, 2MB PSRAM) - This was definitely a much higher spec than what was needed. <br/>
1 x Inland 8 Channel 5v Relay - Way too many channels (future expandability I guess) but was also the only one available in-person. <br/>
3 x M to F Dupont jumpers (I cut off the male side and soldered the cut wire to the pins I needed.) <br/>
1 x 3D printed case (STL attached.) <br/>

### Initial Attempts: 
1) Using ESP32 as the remote with a spare nRF24L01.
2) Having ESP32 host a site internally on my WiFi.
3) Using Blynk Services with my ESP32 and a 5V relay.

### Why 1 & 2 didn't work:
1) nRF24L01 works at 2.4 ghz when most garage remotes work between the range of 300 - 433.92 mhz. Garage Remotes also have oscillators/ crystals in them that are essential to creating a rolling code. Even if I could capture one of the rolling codes, I would have to constantly reprogram the remote as the codes would change after a set period of time.
2) The HTML code was written in one line and I did not want to do that to myself or anyone who tries this project out. This could've worked but for my sanity, I did not go this route. Also, family has a mixture of iOS and Android devices and I wanted to make sure that no matter what, it looked the same for both operating systems. I would also have to come home tired after work, connect to the WiFi, then go to the websites internal IP address and then finally press the button. I want something a bit easier to access.

### Why Blynk?
It was the first free service I saw that allowed me a good number of features: up to 10 devices, 10 templates, and 30000 monthly messages. It also has really good documentation and templates that help you get started. 

### Case Design: 
* [Mykorhiza's 8 Channel 5V Relay](https://www.thingiverse.com/thing:3212197)
* [Adafruit QT Py ESP32-S3 Model](https://github.com/adafruit/Adafruit_CAD_Parts/blob/main/5426%20QT%20Py%20ESP32-S3/5426%20QT%20Py%20ESP32-S3.stl)

Using these two models & TinkerCAD, I was able to combine them both with my very novice 3D modeling skills and make an area that I was happy with to store the esp32-S3. The area created is slightly ugly with its pointy corners but it works. There is also 3 total holes in the area for air flow, access for the jumper cables to pass through, and the USB-C port on the front of the ESP32. 

### Pros:
* I got to make one of my first 3D models
* Very cool to see how well everything fit together in the end.
* DIY Project for a big Quality of Life improvement.
### Cons:
* The area created specifically for the ESP32 board is way too tall. I would trim it down by 2mm-ish.
* The main sketchy part was having to trim down the pcb of the 5v relay but I made sure there were no traces near where I cut the board. I covered the cut edges with hot glue to both insulate the motherboard's now exposed layers but to also make sure the relay stuck to the case. If I did this again, I would increase the length of the case by about 1-3 mm so I didn't have to grind/cut the pcb. It was nervewracking cutting the pcb with flush cutters.

Wiring Diagrams: 
Please see the images in the folder.

Text Diagram: 

ESP32 S3 <br/>
Used Pins: <br/>
```
5V  ------------------------   
GND ------------------     |   
A0 -------------     |     |   
               |     |     |   
5V Relay       |     |     |   
IN_0 -----------     |     |   
GND ------------------     |   
VCC ------------------------   
```
5V Relay to Garage Door Button <br/>

IN_0 has: <br/>
NO <br/>
COM <br/>
NC <br/>
denoted as such on the board: <br/>
NO --------\ <br/> 
<br/>
COM -------\ <br/>
NC --------/ <br/>


Garage Door Button has 4 connections denoted by the color of the wire: White, Black, Green, Yellow. <br/>

Using a multimeter on Continuity ( V with a solid line ) mode: <br/>

Continuity exists between:
* White and Black
* White and Green

Continuity is not between:
* Black and Green
* Black and Yellow

Shorting the White and Black wire using an insulated solid core wire resulted in the door opening leading to the following assumptions: <br/>
White was COM  <br/>
Green was NC   <br/>
Black was NO   <br/>
Yellow is the Sensor input 
