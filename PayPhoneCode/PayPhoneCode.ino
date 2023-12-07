/*
  Interactive Phone Code
  Collaboration with ChatGPT v3.5 and Eddie Farr
  ChatGPT was used to help with a few issues that 
  I couldn't resolve in the time frame I had to 
  work on this project.
*/

#include <Keypad.h> //see their documentation for help
#include <SoftwareSerial.h> //needed by dfminiplayer 
#include <DFPlayer_Mini_Mp3.h> //using an older library found here https://github.com/DFRobot/DFPlayer-Mini-mp3/tree/master

// Define the pin configurations for the keypad
const byte ROW_NUM    = 4; // four rows
const byte COLUMN_NUM = 3; // three columns


//setup keypad
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte pin_rows[ROW_NUM] = {5, 9, 3, 2};    // connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {8, 7, 6}; // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

//dfplayer needs this
SoftwareSerial mySerial(10, 11); // RX, TX

//structure for holding the phone number and audio index associated with it
struct Contact {
  char phoneNumber[8];
  int audioIndex;
};

//numbers and audio index 
Contact contacts[] = {
  {"4041257", 20},
  {"5555555", 21},
  {"1177707", 22},
  {"1173305", 23},
  {"2243577", 24}
};

//audio to play if no numbers match
const int noMatchAudioIndex = 13;

// Flag to track whether the correct code has been entered
bool codeEntered = false;

// Flag to track whether the phone is off the hook
bool phoneOffHook = false;

// Flag to track whether the dial tone is playing
bool dialTonePlaying = false;
bool wrongNumberPlaying = false;

//Flag to track wheter the keypad is enabled
bool keypadEnabled = true;

// Static declarations for the phone number and phone index
static char phoneNumber[8];
static byte phoneIndex = 0;

// Function prototypes
void resetPhoneNumber();
void playAudioMessage(int audioIndex);
void playButtonAudio(char key);
int findContact(const char* phoneNumber);

void setup() {
  //debugging
  Serial.begin(9600);
  //communication with dfPlayer
  mySerial.begin(9600);

  //Set params for dfplayer
  mp3_set_serial(mySerial);
  mp3_set_volume(8);

  //Receiver pin, used to get the state of the receiver on or off the hook
  pinMode(12, INPUT_PULLUP);
}

void loop() {
  bool currentPhoneOffHook = digitalRead(12) == HIGH;

  if (currentPhoneOffHook != phoneOffHook) {
    // Phone state has changed
    phoneOffHook = currentPhoneOffHook;

    if (phoneOffHook) {
      // Phone has been taken off the hook
      if (!dialTonePlaying) {
        // Start playing the dial tone
        mp3_play(12);
        dialTonePlaying = true;
      }
      keypadEnabled = true;
    } else {
      resetPhoneNumber();
      // Phone has been put back on the hook
      if (dialTonePlaying || wrongNumberPlaying) {
        // Stop the dial tone
        mp3_stop();
        dialTonePlaying = false;
        wrongNumberPlaying = false;
      }
      keypadEnabled = false;
    }
  }

  if (!codeEntered && phoneOffHook && keypadEnabled) {
    char key = keypad.getKey();

    if (key) {
      Serial.println(key);
      if (dialTonePlaying) {
        // Stop the dial tone when a key is pressed for the first time
        mp3_stop();
        dialTonePlaying = false;
      }
      processKeyPress(key);
    }
  }
  delay(100); // Add a small delay for stability
}

void processKeyPress(char key) {
  playButtonAudio(key);

  // Add the key to the phone number
  phoneNumber[phoneIndex++] = key;

  // If too many digits entered, reset
  if (phoneIndex > 8) {
    resetPhoneNumber();
  }

  // Check the entered phone number against the contacts
  phoneNumber[phoneIndex] = '\0'; // Null-terminate the phone number
  int audioIndex = findContact(phoneNumber);

  if (phoneIndex == 7) {
    keypadEnabled = false;
    delay(500);
    if (audioIndex != -1) {
      // Found a matching contact
      playAudioMessage(audioIndex);
      codeEntered = false;
      resetPhoneNumber();
    } else {
      playAudioMessage(noMatchAudioIndex);
      wrongNumberPlaying = true;
      resetPhoneNumber();
    }
  }
}

void resetPhoneNumber() {
  memset(phoneNumber, 0, sizeof(phoneNumber));
  phoneIndex = 0;
}

void playAudioMessage(int audioIndex) {
  mp3_play(audioIndex);
}

void playButtonAudio(char key) {
  int audioIndex; // Assuming audio files are named from 0 to 9
  if (key >= '0' && key <= '9') {
    // Play the corresponding audio file for the numeric button
    audioIndex = key - '0'; 
  } else if (key == '*') {
    audioIndex = 11; 
  } else if (key == '#') {
    audioIndex = 10; 
  } else {
    // Invalid key, do nothing
    return;
  }

  mp3_play(audioIndex);
  delay(150);
}

//compare input string to known numbers
int findContact(const char* phoneNumber) {
  for (size_t i = 0; i < sizeof(contacts) / sizeof(contacts[0]); ++i) {
    if (strcmp(contacts[i].phoneNumber, phoneNumber) == 0) {
      return contacts[i].audioIndex; // if there is a match play the audio file associated with that
    }
  }
  return -1; // Not found
}
