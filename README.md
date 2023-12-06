# Prop Payphone

![](/media/finished.jpg)

### Overview 

Here are some issues I ran into while converting an old pay phone into a prop for a local store.  The client wanted customers to be able to type in a seven-digit number and hear a pre-recorded message play if they typed in the correct number. In the spirit of the project, I also added a dial tone sound that plays before a number is typed as well as the touch-tone audio for each key that is pressed.  Finally, there is a wrong number audio file that is played if the customer types in a number that isn't recognized.

### Parts

The pay phone was ordered from     <a href="https://www.payphone.com">Payphone.com</a>
 I think any would work off the site since we're not using it as intended.  The only pieces that we are going to be dealing with are the keypad itself, the receiver switch, and the speaker of the receiver. 

### Payphone Keypad

How a keypad works is outside the scope of this document but <a href="https://www.jameco.com/Jameco/workshop/JamecoBuilds/working-with-matrix-keypads.html">here</a> is a link to a good explanation.  

![](/media/keypad.jpg)
</br>
This is the keypad from the pay phone.  To access the row/columns matrix we need to remove the PCB from the enclosure.
</br>
![](/media/keypad_apart.jpg)
</br>
Here is the keypad broken down into the metal numbers, the membrane, and the PCB.  

### Receiver Switch

![](/media/receiver_switch.jpg)

This is the switch after being modified to communicate with the Arduino.  To figure out which wires to use from the switch place a multimeter in continuity mode and test pairs until you find two that beep when the receiver is depressed.  I used this switch to let me know when to start playing the dial tone sound and when to accept input on the keypad.  

### Receiver Speaker

![](/media/receiver.jpg)

This is the actual receiver for the phone.  It's a little tricky to remove because of the security measures that keep it attached to the phone but once you get it out you're left with four wires.  Two go to the speaker in the receiver and two go to the microphone.  My two wires happened to be yellow and black although yours might be different.  To test play audio and swap wires around until you find the two the send audio to the receiver speaker. 

### Arduino 

![](/media/arduino.jpg)
</br>





