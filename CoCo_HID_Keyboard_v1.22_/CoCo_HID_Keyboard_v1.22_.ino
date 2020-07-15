/* 
    CoCo Keys2USB v1.22
    by: Paul Fiscarelli
    
    Copyright (c) 2020, Paul Fiscarelli
    
    Adapted from keyPadHiduino Example Code, by: Jim Lindblom

    MIT License

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
      
   CoCo Keyboard Map:
   ==================
     CoCo Keyboard rows and columns:
     ---------------------------------  Row
     | @ | A | B | C | D | E | F | G | - 1
     | H | I | J | K | L | M | N | O | - 2
     | P | Q | R | S | T | U | V | W | - 4
     | X | Y | Z | UA| DA| LA| RA|SPC| - 5
     | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | - 6
     | 8 | 9 | : | ; | , | - | . | / | - 7
     |ENT|CLR|BRK|ALT|CTL| F1| F2|SFT| - 8
     ---------------------------------
       |   |   |   |   |   |   |   |
   Col 9  10  11  12  13  14  15  16 
     
   CoCo Keyboard to Pro Micro connections:
   =======================================
      CoCo Keyboard  ------- Pro Micro
           Pin                  Pin        
            1 ------------------ 2
            2 ------------------ 3
          N/C ------------------ N/C
            4 ------------------ 4
            5 ------------------ 5
            6 ------------------ 6
            7 ------------------ 7
            8 ------------------ 8
            9 ------------------ 9
           10 ------------------ 10
           11 ------------------ 16
           12 ------------------ 14
           13 ------------------ 15
           14 ------------------ 18 (A0)
           15 ------------------ 19 (A1)
           16 ------------------ 20 (A2)
*/

#include <Keyboard.h>
#include "cocoKeyMaps.h"

// 15-Pins of the Color Computer keyboard connected to the Pro Micro
//  *note - Pin-3 of keyboard is no-connection
int keyboardPins[15] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 14, 15, 18, 19, 20};

uint8_t *keyOutputs;                      // initialize keyMap outputs
int keyboardTypeCount = 3;                // different types of keyboard emulator outputs
int currentKeyboard = 1;                  // current keyboard output
                      
// set bit values if column strobe (in row-6) contains a modifier key
bool modifierCols[8] = {false, false, false, true, true, true, true, true};

bool keyDown = false;                     // monitor if key is held down
int keyboardStatus;                       // check which key is pressed
int specialKeys;                          // check for special key combinations
int modifierKeys = 0;                     // check which modifier keys are pressed


// Setup inputs and keyMaps
void setup()
{
  keyOutputs = keyMapVCC;   
  for (int i=0; i<15; i++)
  {
    pinMode(keyboardPins[i], INPUT);      // set all keyboard pins as inputs
    digitalWrite(keyboardPins[i], HIGH);  // pull all keyboard pins high
  }
  Keyboard.releaseAll();                  // release all key presses
}


// Main loop
void loop()
{
  // Go scan keyboard
  keyboardStatus = getKeyboardStatus();                                          

  // Check for presence of keystroke
  if ((keyboardStatus != -1) | modifierKeys != 0) {
    // Handle keystroke  
    if ((getKeyboardStatus() == keyboardStatus) && (keyboardStatus != -1)) {
      specialKeys = checkSpecialKeys();
      if(specialKeys == -1) {
        sendKeyPress(keyboardStatus);
        keyDown = true;
      }
    }
    else {
      Keyboard.releaseAll();
      keyDown = false;
    }

    // Check if keystroke is held
    while ((getKeyboardStatus() == keyboardStatus) && (keyboardStatus != -1)) {
      delayMicroseconds(1);
    }

    // Handle keystroke modifiers
    if (getModifierStatus() != 0) {
      sendModifiers();
      keyDown = true;
    }
    else {
      Keyboard.releaseAll();
      keyDown = false;
    }

    // Check if modifier keys are held
    while ((getModifierStatus() == modifierKeys) && (modifierKeys != 0) && (getKeyboardStatus() == -1)) {
      // Handle keystroke release while modifier key is held
      if (getKeyboardStatus() != keyboardStatus) {
        Keyboard.release(keyOutputs[keyboardStatus]);
        keyboardStatus = getKeyboardStatus();
      }
      delay(50);
    }
    
  }
  // Check if keystroke was down and now released
  else if(keyDown) {
    Keyboard.releaseAll();
    keyDown = false;
  }
}


/* sendKeyPress(int key): This function sends a single keystroke over USB
    It requires an int to be passed, which is used as a lookup in the keyOutputs
    lookup table.
 */
void sendKeyPress(int key)
{
  int pressedKey = keyOutputs[key];
  Keyboard.press(pressedKey);
  delay(75);
}


/* checkSpecialKeys(): This function is for handling special keystroke cases.
 *  Based on the current value of what modifierKeys are currently pressed,
 *  a special keystroke will emulate a keystroke based on that modifierKeys buffer.
 *  The keyboardStatus value is checked based on the row/column index of a key press.
 */
int checkSpecialKeys()
{
  switch(modifierKeys)
  {
    case(16):                               // Ctrl Key Pressed
      if(keyboardStatus == 0){              // '@' key pressed
        Keyboard.release(KEY_LEFT_CTRL);    // release Ctrl Key
        delay(25);
        Keyboard.press(KEY_SHIFT);          // emulate '@' Key
        Keyboard.press(KEY_2);
        delay(50);
        specialKeys = 0;
        Keyboard.releaseAll();
      }
      else if(keyboardStatus == 20){        // 'T' key pressed
        Keyboard.release(KEY_LEFT_CTRL);    // release Ctrl Key
        delay(25);
        Keyboard.press(KEY_TAB);            // emulate TAB Key
        delay(50);
        specialKeys = 0;
        Keyboard.releaseAll();
      }
      else if(keyboardStatus == 29){        // 'Left-Arrow' key pressed
        Keyboard.release(KEY_LEFT_CTRL);    // release Ctrl Key
        delay(25);
        Keyboard.press(KEY_BACKSPACE);      // emulate Backspace Key
        delay(50);
        specialKeys = 0;
        Keyboard.releaseAll();
      }
      else {
        specialKeys = -1;                   // reset special keys
      }
      break;
    case(128):
      //Keyboard.press(KEY_SHIFT);          // Shift Key
      if(keyboardStatus == 48){             // 'Enter' key pressed
        cycleKeyMap();                      // go cycle Key Map
        specialKeys = 0;
        Keyboard.releaseAll();
      }
      else {
        specialKeys = -1;
      }
      break;
    default:                                // no special key pressed
      specialKeys = -1;
      break;             
  }
  return specialKeys;
}


/* cycleKeyMap(): This function is used for cycling through predefined keyMaps.
 *  This is used to handle the different keymaps of the various CoCo emulators.
 *  Keymaps are defined in the cocoKeyMaps.h file.
 */
void cycleKeyMap()
{
  int selectedEmulator = 0;
  
  ++currentKeyboard;
  
  if(currentKeyboard > keyboardTypeCount)
  {
    currentKeyboard = 1;
  }

  switch(currentKeyboard)
  {
    case(1):
      keyOutputs = keyMapVCC;               // set emulator keyMap for VCC
      selectedEmulator = KEY_V;
      break;
    case(2):
      keyOutputs = keyMapXRoar;             // set emulator keyMap for XRoar
      selectedEmulator = KEY_X;
      break;
    case(3):
      keyOutputs = keyMapMAME;              // set emulator keyMap for MAME
      selectedEmulator = KEY_M;
      break;
    default:
      keyOutputs = keyMapMAME;              // default emulator keyMap as MAME
      selectedEmulator = KEY_M;
      break;
  }
  Keyboard.press(selectedEmulator);
  delay(250);
  Keyboard.releaseAll();
}


/* sendModifiers(): takes a single byte-value modifierKeys and converts to keystrokes
 *  Each bit of modifierKeys byte-value represents a specific modifier key
 *  Masking of each bit value will determine which modifier key is pressed
 *  Multi-keystroke modifiers are possible by combining individual bit values
 *  
 *  The bit representation is as follows:
 *  
 *     bit    key     hex
 * -------------------------
 *      0     n/a     0x01
 *      1     n/a     0x02
 *      2     n/a     0x04
 *      3     Alt     0x08
 *      4     Ctrl    0x10
 *      5     F1      0x20
 *      6     F2      0x40
 *      7     Shift   0x80
 *      
 */
void sendModifiers()
{
  switch(modifierKeys)
  {
    case(192):                              // Shift+F2
      cycleKeyMap();
      break;
    case(128):
      Keyboard.press(KEY_SHIFT);            // Shift Key
      break;
    case(72):
      Keyboard.press(KEY_LEFT_ALT);         // ALT+F2 Keys
      delay(75);
      Keyboard.press(KEY_F2);      
      break;
    case(64):
      Keyboard.press(KEY_F2);               // F2 Key
      break;
    case(40):
      Keyboard.press(KEY_LEFT_ALT);         // ALT+F1 Keys
      delay(75);
      Keyboard.press(KEY_F1);      
      break;
    case(32):
      Keyboard.press(KEY_F1);               // F1 Key
      break;  
    case(24):
      Keyboard.press(KEY_LEFT_CTRL);        // CTRL+ALT Keys
      delay(75);
      Keyboard.press(KEY_LEFT_ALT);
      break;  
    case(16):
      Keyboard.press(KEY_LEFT_CTRL);        // Control Key
      break;
    case(8):
      Keyboard.press(KEY_LEFT_ALT);         // Alt Key
      break;
    default:
      //Keyboard.println(modifierKeys);
      break;
  }
}


/* getModifierStatus(): This function returns an int that represents
 *  the status of which modifier keys are pressed on the CoCo keyboard.
 *  This value is calculated based on which column pins are pressed in
 *  row-6 of the keyboard. Each of the 8-columns are represented as a 
 *  single bit raised to the power of two, to represent an 8-bit integer
 *  value
 */
int getModifierStatus()
{
  // row pins are 1, 2, 4, 5, 6, 7, and 8 of CoCo keyboard
  int rowPins[7] = {keyboardPins[0], keyboardPins[1], keyboardPins[2], keyboardPins[3], keyboardPins[4], keyboardPins[5], keyboardPins[6]};
  // column pins are pins 9, 10, 11, 12, 13, 14, 15, and 16 of CoCo keyboard
  int columnPins[8] = {keyboardPins[7], keyboardPins[8], keyboardPins[9], keyboardPins[10], keyboardPins[11], keyboardPins[12], keyboardPins[13], keyboardPins[14]};
  
  int modifierStatus = 0;                   // reset modifier status
  
  // initialize all pins, inputs w/ pull-ups
  for (int i=0; i<15; i++)
  {
    pinMode(keyboardPins[i], INPUT);
    digitalWrite(keyboardPins[i], HIGH);
  }
  
  int row = 6;                              // set row to modifier key row
  pinMode(rowPins[row], OUTPUT);            // set row pins as an output
  digitalWrite(rowPins[row], LOW);          // pull row pins low

  // check all 8 columns in modifier key row
  for (int col=0; col<8; col++)             
  { 
    if (!digitalRead(columnPins[col])) {
       if (modifierCols[col]) {
          bitSet(modifierStatus, col);
       }
       else {
          bitClear(modifierStatus, col);
       }
    }
  }
  pinMode(rowPins[row], INPUT);             // reset row pins as an input
  digitalWrite(rowPins[row], HIGH);         // pull row pins high

  return modifierStatus;
}


/* getKeyboardStatus(): This function returns an int that represents
 *  the status of which key is pressed on the CoCo keyboard.
 *  This value is calculated based on the 7-rows and 8-columns of the
 *  CoCo keyboard (row*8 + column). The return values is then used in
 *  the keymap lookup table.
 */
int getKeyboardStatus()
{
  // row pins are 1, 2, 4, 5, 6, 7, and 8 of CoCo keyboard
  int rowPins[7] = {keyboardPins[0], keyboardPins[1], keyboardPins[2], keyboardPins[3], keyboardPins[4], keyboardPins[5], keyboardPins[6]};
  // column pins are pins 9, 10, 11, 12, 13, 14, 15, and 16 of CoCo keyboard
  int columnPins[8] = {keyboardPins[7], keyboardPins[8], keyboardPins[9], keyboardPins[10], keyboardPins[11], keyboardPins[12], keyboardPins[13], keyboardPins[14]};
  
  int keyboardStatus = -1;                  // initialize keystroke return value
  modifierKeys = 0;                         // reset modifier keys

  // initialize all pins, inputs w/ pull-ups
  for (int i=0; i<15; i++)
  {
    pinMode(keyboardPins[i], INPUT);
    digitalWrite(keyboardPins[i], HIGH);
  }

  // check all 7 rows
  for (int row=0; row<7; row++)
  {
    pinMode(rowPins[row], OUTPUT);          // set row pins as an output
    digitalWrite(rowPins[row], LOW);        // pull row pins low
    
    // check all 8 columns of each row
    for (int col=0; col<8; col++)
    {
       if (!digitalRead(columnPins[col])) {
         switch(row)
         {
           case 6:
             if (modifierCols[col]) {
                bitSet(modifierKeys, col);
             }
             else {
                bitClear(modifierKeys, col);
                keyboardStatus = (row)*8 + (col);
             }
             break;
           default:
             keyboardStatus = (row)*8 + (col);
             break; 
         }
      }
      
    }
    pinMode(rowPins[row], INPUT);           // reset row pins as an input
    digitalWrite(rowPins[row], HIGH);       // pull row pins high
  }
  return keyboardStatus;
}
