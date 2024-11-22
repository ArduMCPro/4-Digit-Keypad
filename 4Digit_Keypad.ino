#include <Adafruit_Keypad.h>

// define your specific keypad here via PID
#define KEYPAD_PID1332

// define your pins here
#define ROW1 2
#define COLUMN1 8
#define COLUMN2 9
#define COLUMN3 10
#define COLUMN4 11

//define pins for the leds
#define OKLED 13
#define ERRORLED 12

const byte ROWS = 1;  // rows
const byte COLS = 4;  // columns

// define the symbols on the buttons of the keypads
char keys[ROWS][COLS] = {
  { '1', '2', '3', '4' },
};

byte rowPins[ROWS] = { ROW1 };                                // connect to the row pinouts of the keypad
byte colPins[COLS] = { COLUMN1, COLUMN2, COLUMN3, COLUMN4 };  // connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Adafruit_Keypad customKeypad = Adafruit_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//define the passcode
String passcode = "1234";

//currently entered passcode buffer
String enteredPasscode = "";

void setup() {
  //initialize the keypad and leds
  customKeypad.begin();
  pinMode(OKLED, OUTPUT);
  pinMode(ERRORLED, OUTPUT);
}

void loop() {
  //poll the keypad
  customKeypad.tick();

  //read the keypad
  while (customKeypad.available()) {
    keypadEvent e = customKeypad.read();
    if (e.bit.EVENT == KEY_JUST_PRESSED) {
      enteredPasscode = enteredPasscode + (char)e.bit.KEY;
    }
  }

  //check if the entered passcode is the same length as the target passcode
  if (enteredPasscode.length() == passcode.length()) {
    //check if passcodes match
    if (enteredPasscode == passcode) {
      enteredPasscode = "";
      digitalWrite(OKLED, HIGH);
      digitalWrite(ERRORLED, LOW);
    } else {
      enteredPasscode = "";
      digitalWrite(OKLED, LOW);
      digitalWrite(ERRORLED, HIGH);
    }
  }

  delay(10);
}
