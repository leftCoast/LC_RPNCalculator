#include <calculator.h>
#include <serialStr.h>
#include <strTools.h>

//
// You will have to read calculator.cpp to see what the buttons need to send.
// https://github.com/leftCoast/LC_RPNCalculator/blob/main/calculator.cpp
//

calculator  myCalculator;  // There you have one.
serialStr   serialMgr;     // This one read the serial port.
char*       btnTxt;        // Our global that holds the incoming button text.

void setup() {
   
   Serial.begin(9600);              // Start the serial port.
   btnTxt = NULL;                   // Defualt the button text string to NULL. **IMPORTANT**
   serialMgr.setCallback(gotClk);   // Set the call back that accepts the incoming text string.
}


// Callback that accepts the incoming string.
void gotClk(char* inTxt) { heapStr(&btnTxt,inTxt); }



void loop(void) {
   
   float result;

   idle();                                // Runs all the magic for the serial port.
   if (btnTxt) {                          // Got non NULL text?
      myCalculator.buttonClick(btnTxt);   // Stuff it into the calcualator.
      result = myCalculator.getX();       // Read the calcualtion result.
      Serial.println(btnTxt);             // Print the keystroke text.
      Serial.println(result,2);           // Print the result, 2 decimal places.
      freeStr(&btnTxt);                   // Recycle the string. Sets it back to NULL.
   }        
}