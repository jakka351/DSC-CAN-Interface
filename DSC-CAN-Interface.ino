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
//
//             Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
//             documentation files (the "Software"), to use, modify, and distribute the Software subject to the following conditions:
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
//            - Any modifications made to the Software must be clearly marked as such, and the modified files must carry prominent notices stating that
//              changes have been made.
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
//            
//              By using, modifying, or distributing the Software, you agree to abide by all the terms and conditions of this license.
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                             
#include <SPI.h>
#include "mcp_can.h"
#include <mcp_can.h>
#include <SPI.h>
const int SPI_CS_PIN = 17;              // CANBed V1
// const int SPI_CS_PIN = 3;            // CANBed M0
// const int SPI_CS_PIN = 9;            // CAN Bus Shield
MCP_CAN MIDSPEEDCAN(SPI_CS_PIN);       
// Define the button pins
const int buttonPins[4] = {2, 3, 4, 5};
//CAN msgs
unsigned char DEFAULT_MESSAGE[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned char DSC_BUTTON[8] = {0, 0, 0, 0x90, 0, 0, 0, 0};
unsigned char LOCK_BUTTON[8] = {0, 0, 0, 0xC0, 0, 0, 0, 0};
unsigned char UNLOCK_BUTTON[8] = {0, 0, 0, 0x84, 0, 0, 0, 0};
/*
FDIM_BUTTONS_ID = 0x307;
DSC_BUTTON = 0x90;
LOCK_BUTTON = 0xC0;
UNLOCK_BUTTON = 0x84;
DOMELGHT_BUTTON = 
HAZARD_LIGHT_BUTTON = 0x01; 
*/
void setup()
{
  Serial.begin(115200);
  while(!Serial);
  while (CAN_OK != MIDSPEEDCAN.begin(CAN_125KBPS))    // init can bus : baudrate = 500k
  {
      Serial.println("MidSpeed CANbus Error...");
      delay(100);
  }
  Serial.println("MidSpeed CANbus Connected.");
   // Set the button pins as input with internal pull-ups
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}
void loop()
{
  // Record the start time
  unsigned long startTime = millis();

  // Check each button for a press (active LOW)
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      // Simple debounce delay
      delay(50);
      // Confirm the button is still pressed before sending the message
      if (digitalRead(buttonPins[2]) == LOW) {
        CAN.sendMsgBuf(0x307, 0, 8, LOCK_BUTTON);
        // Wait until the button is released to avoid multiple sends
        while (digitalRead(buttonPins[2]) == LOW) {
          delay(10);
        }
      }
      if (digitalRead(buttonPins[3]) == LOW) {
        CAN.sendMsgBuf(0x307, 0, 8, UNLOCK_BUTTON);
        // Wait until the button is released to avoid multiple sends
        while (digitalRead(buttonPins[3]) == LOW) {
          delay(10);
        }
      }
      if (digitalRead(buttonPins[4]) == LOW) {
      // For loop that runs for exactly 4 seconds
        for (; millis() - startTime < 4000; ) {
          // Code inside the loop will run for 4 seconds
          CAN.sendMsgBuf(0x307, 0, 8, DSC_BUTTON);
          delay(10);  // Optional delay to slow down output
        }
        //Light Needs to come on here
        // Wait until the button is released to avoid multiple sends
        while (digitalRead(buttonPins[4]) == LOW) {
          delay(10);
        }
      }
    }
  }
}
// END FILE
