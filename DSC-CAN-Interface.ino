////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                             
//                             ___________              __                 __________                                      __                         
//                             \__    ___/___   _______/  |_  ___________  \______   \_______   ____   ______ ____   _____/  |_                       
//                               |    |_/ __ \ /  ___/\   __\/ __ \_  __ \  |     ___/\_  __ \_/ __ \ /  ___// __ \ /    \   __\                      
//                               |    |\  ___/ \___ \  |  | \  ___/|  | \/  |    |     |  | \/\  ___/ \___ \\  ___/|   |  \  |                        
//                               |____| \___  >____  > |__|  \___  >__|     |____|     |__|    \___  >____  >\___  >___|  /__|                        
//                                          \/     \/            \/                                \/     \/     \/     \/                            
//                               _________                    .__       .__  .__          __                                                          
//                              /   _____/_____   ____   ____ |__|____  |  | |__| _______/  |_                                                        
//                              \_____  \\____ \_/ __ \_/ ___\|  \__  \ |  | |  |/  ___/\   __\                                                       
//                              /        \  |_> >  ___/\  \___|  |/ __ \|  |_|  |\___ \  |  |                                                         
//                             /_______  /   __/ \___  >\___  >__(____  /____/__/____  > |__|                                                         
//                                     \/|__|        \/     \/        \/             \/                                                               
//                                _____          __                         __  .__                                                                   
//                               /  _  \  __ ___/  |_  ____   _____   _____/  |_|__|__  __ ____                                                       
//                              /  /_\  \|  |  \   __\/  _ \ /     \ /  _ \   __\  \  \/ // __ \                                                      
//                             /    |    \  |  /|  | (  <_> )  Y Y  (  <_> )  | |  |\   /\  ___/                                                      
//                             \____|__  /____/ |__|  \____/|__|_|  /\____/|__| |__| \_/  \___  >                                                     
//                                     \/                         \/                          \/                                                      
//                               _________      .__          __  .__                                                                                  
//                              /   _____/ ____ |  |  __ ___/  |_|__| ____   ____   ______                                                            
//                              \_____  \ /  _ \|  | |  |  \   __\  |/  _ \ /    \ /  ___/                                                            
//                              /        (  <_> )  |_|  |  /|  | |  (  <_> )   |  \\___ \                                                              
//                             /_______  /\____/|____/____/ |__| |__|\____/|___|  /____  >                                                           
//                                     \/                                       \/     \/                                                             
//
//
//
//                              Tester Present Specialist Automotive Solutions Open Source License (TPSAS-OSL)
//                              Version 1.0, 2025
//
//                              Copyright (c) 2025 Tester Present Specialist Automotive Solutions
//
//                              Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
//                              documentation files (the "Software"), to use, modify, and distribute the Software subject to the following conditions:
//
//          1. Attribution.
//            - The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//            - Credit must be given to "Tester Present Specialist Automotive Solutions" in any documentation, public notices, or product materials 
//              that acknowledge the use of the Software.//
//
//          2. Open Source Use Only.
//            - The Software, including any modifications or derivative works (collectively, “Derivatives”), must be distributed only as open source software.
//            - Derivatives or distributions of the Software must be licensed under this license or another license approved by the Open Source Initiative 
//              (OSI) that maintains equivalent open source freedoms.
//            - The Software and any Derivatives may not be used as a component in any closed source or proprietary software product.
//
//          3. Redistribution.
//            - Redistributions of the Software, in source or binary form, must reproduce the above attribution, this license, and the disclaimer below 
//              in the documentation and/or other materials provided with the distribution.
//            - Any modifications made to the Software must be clearly marked as such, and the modified files must carry prominent notices stating that changes have been made.
//
//          4. No Warranty.
//            - THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//              FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT.
//            - IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
//              TORT, OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//          5. Termination.
//            - This license and the rights granted hereunder will terminate automatically upon any breach of the above conditions.
//            - Upon termination, you must cease all use and distribution of the Software and any Derivatives.
//
//          6. Entire Agreement.
//            - This license constitutes the entire agreement between you and Tester Present Specialist Automotive Solutions regarding the Software 
//              and supersedes any prior understandings or agreements, whether written or oral, regarding the subject matter herein.
//
//          By using, modifying, or distributing the Software, you agree to abide by all the terms and conditions of this license.
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                             
#include <Wire.h>
#include <stdio.h>
#include "canbed_dual.h"
//////////////////////////////////////////////////////
CANBedDual MIDSPEEDCAN(0);
CANBedDual HIGHSPEEDCAN(1);
//CAN msgs
unsigned char DEFAULT_MESSAGE[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char DSC_BUTTON[8] = {0, 0, 0, 0x90, 0, 0, 0, 0};
unsigned char LOCK_BUTTON[8] = {0, 0, 0, 0xC0, 0, 0, 0, 0};
unsigned char UNLOCK_BUTTON[8] = {0, 0, 0, 0x84, 0, 0, 0, 0};
unsigned char HVAC_ON_BUTTON[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char HVAC_OFF_BUTTON[8] = {0, 0, 0, 0, 0, 0, 0, 0};
//RESTRAINTS CONTROL MODULE MSGS FOR CLUSTER ALARMS
unsigned char ID341[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char ID340[8] = {0, 0x18, 0, 0, 0, 0, 0, 0};
unsigned char ID350[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int rcm = 0;
//////////////////////////////////////////////////////
void setup()
{
    Serial.begin(115200);
    pinMode(18, OUTPUT);  
    pinMode(19, INPUT_PULLUP);
    pinMode(20, INPUT_PULLUP);
    pinMode(21, INPUT_PULLUP);
    pinMode(22, INPUT_PULLUP);
    pinMode(23, INPUT_PULLUP);
    Serial.print("pins set \r\n");
    Wire1.setSDA(6);
    Wire1.setSCL(7);
    Wire1.begin();
    Serial.print("1 wire init \r\n");
    //SETUP CANBUS PCMCAN and ABSCAN // ABS CAN  NEEDS A TERMINATING RESISTOR 120 OHM
    MIDSPEEDCAN.init(125000);          // CAN0 baudrate: 500kb/s
    HIGHSPEEDCAN.init(500000);          // CAN1 baudrate: 500kb/s
    Serial.print("can0 & can1 init \r\n");
}
//////////////////////////////////////////////////////
void loop()
{
  unsigned long id = 0;
  int ext = 0;
  int rtr = 0;
  int fd = 0;
  int len = 0;    
  //READ PCM CAN BUS
  bool dscState = true; //DSC State false = off, true = on
  bool hvacSate = false; //HVAC ON = true, off = false
  // Record the start time
  unsigned long startTime = millis();
  // Check each button for a press (active LOW) 
  if (rcm = 0) {
   HIGHSPEEDCAN.send(0x340, 0, 0, 0, 8, ID340);
   HIGHSPEEDCAN.send(0x340, 0, 0, 0, 8, ID350);
   delay(50);
   rcm = 1;
  }
  if (rcm = 1) {
   HIGHSPEEDCAN.send(0x340, 0, 0, 0, 8, ID341);
   HIGHSPEEDCAN.send(0x340, 0, 0, 0, 8, ID350);
   delay(50);
   rcm = 0;
  }
  Serial.print("Restraints Control Module Signal Sent. \r\n");
  // Confirm the button is still pressed before sending the message
  if (digitalRead(19) == LOW) {
    MIDSPEEDCAN.send(0x307, 0, 0, 0, 8, LOCK_BUTTON);
    Serial.print("LOCK_BUTTON \r\n");
    // Wait until the button is released to avoid multiple sends
    while (digitalRead(19) == LOW) {
      delay(10);
    }
  }
  if (digitalRead(20) == LOW) {
    MIDSPEEDCAN.send(0x307, 0, 0, 0, 8, UNLOCK_BUTTON);
    Serial.print("UNLOCK_BUTTON \r\n");
    // Wait until the button is released to avoid multiple sends
    while (digitalRead(20) == LOW) {
      delay(10);
    }
  }
  if (digitalRead(21) == LOW) {
  // For loop that runs for exactly 4 seconds
    if(dscState) {
      for (; millis() - startTime < 4000; ) {
        // Code inside the loop will run for 4 seconds
        MIDSPEEDCAN.send(0x307, 0, 0, 0, 8, DSC_BUTTON);
        Serial.print("DSC_BUTTON_ON\r\n");
        delay(10);  // Optional delay to slow down output
      }          
      dscState = false; //DSC NOW OFF
    }
    else {
      MIDSPEEDCAN.send(0x307, 0, 0, 0, 8, DSC_BUTTON);
      Serial.print("DSC_BUTTON_OFF\r\n");
      delay(10);  // Optional delay to slow down output  
      dscState = true; //DSC ON 
    }
    //Light Needs to come on here
    // Wait until the button is released to avoid multiple sends
    while (digitalRead(21) == LOW) {
      delay(10);
    }
  }
  if (digitalRead(22) == LOW) {
    MIDSPEEDCAN.send(0x307, 0, 0, 0, 8, HVAC_ON_BUTTON);
    Serial.print("HVAC_ON_BUTTON\r\n");
    // Wait until the button is released to avoid multiple sends
    while (digitalRead(22) == LOW) {
      delay(10);
    }
  }
  if (digitalRead(23) == LOW) {
    MIDSPEEDCAN.send(0x307, 0, 0, 0, 8, HVAC_OFF_BUTTON);
    Serial.print("HVAC_OFF_BUTTON\r\n");
    // Wait until the button is released to avoid multiple sends
    while (digitalRead(23) == LOW) {
      delay(10);
    }
  }
}
////////////////////////////////////////////////////// 

// ENDIF
////////////////////////////////////////////////////////////////////////////
