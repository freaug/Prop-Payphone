# Prop Payphone
</br></br>
![](/media/finished.jpg)
</br></br>
### Overview 
</br></br>
The client wanted customers to be able to type in a seven-digit number and hear a pre-recorded message play if they typed in the correct number. In the spirit of the project, I also added a dial tone sound that plays before a number is typed as well as the touch-tone audio for each key that is pressed.  Finally, there is a wrong number audio file that is played if the customer types in a number that isn't recognized.
</br></br>
### Parts
</br></br>
The pay phone was ordered from     <a href="https://www.payphone.com">Payphone.com</a>
 I think any would work off the site since we're not using it as intended.  The only pieces that we are going to be dealing with are the keypad itself, the receiver switch, and the speaker of the receiver.  I also used an <a href="https://www.amazon.com/ELEGOO-Board-ATmega328P-ATMEGA16U2-Compliant/dp/B01EWOE0UU/ref=sr_1_1_sspa">Arduino Uno</a> with an <a href="https://www.amazon.com/Electronics-Salon-Arduino-Terminal-Breakout-Module/dp/B07HF2DD7T/ref=sr_1_7_sspa">Electronics Salon Shield</a> and <a href="https://www.dfrobot.com/product-1121.html">DFPlayer</a> audio player. You'd also need some extra wire, 22awg should be fine, for connecting the keypad, receiver switch, and receiver speaker to the Arduino. Also a 1kΩ resistor for the DFPlayer and Arduino RX line.  
</br></br>
### Payphone Keypad
</br></br>
How a keypad works is outside the scope of this document but <a href="https://www.jameco.com/Jameco/workshop/JamecoBuilds/working-with-matrix-keypads.html">here</a> is a link to a good explanation.  
</br></br>
![](/media/keypad.jpg)
</br></br>
This is the keypad from the pay phone.  To access the row/columns matrix we need to remove the PCB from the enclosure.
</br></br>
![](/media/keypad_apart.jpg)
</br></br>
Here is the keypad broken down into the metal numbers, the membrane, and the PCB.  
</br></br>
### Issues
</br></br>
The only out of the normal issue I ran into was getting the keypad to work with the <a href="https://www.arduino.cc/reference/en/libraries/keypad/">Keypad</a> library for Arduino.  This kay pad had circuitry integrated on the back side of the PCB so it wasn't possible to use the output pins shown at the bottom to get the row/column data.  To get around this I had to cut the traces from the row/column matrix that went to the IC on the back of the board.  I then had to solder jumper wires to each column and row.  Not the worst problem but I was scratching my head for a few hours.
</br></br>
### Receiver Switch
</br></br>
![](/media/receiver_switch.jpg)
</br></br>
This is the switch after being modified to communicate with the Arduino.  To figure out which wires to use from the switch place a multimeter in continuity mode and test pairs until you find two that beep when the receiver is depressed.  I used this switch to let me know when to start playing the dial tone sound and when to accept input on the keypad.  
</br></br>
### Receiver Speaker
</br></br>
![](/media/receiver.jpg)
</br></br>
This is the actual receiver for the phone.  It's a little tricky to remove because of the security measures that keep it attached to the phone but once you get it out you're left with four wires.  Two go to the speaker in the receiver and two go to the microphone.  My two wires happened to be yellow and black although yours might be different.  To test play audio and swap wires around until you find the two the send audio to the receiver speaker. 
</br></br>
### Arduino 
</br></br>
![](/media/arduino.jpg)
</br></br>
Here is the Arduino Uno with the Electronics-Salon Shield and a homemade audio hat with a DFPlayer audio player on top. Ihop tall stack. 
### Schematic 
</br></br>
![](/media/Schematic.pdf)
</br></br>
