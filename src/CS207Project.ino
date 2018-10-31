#include <Arduino.h>

#include "defines.h"
#include "Controller.h"




int main()
{
  init();
  

  setup();

#if LOOP_GOTO
  loop();
#else
  while(true) loop();
#endif


  LOG("Loop ended. Oops?\n");
  
  return RETURN_SUCCESS;
}




void setup()
{
  Serial.begin(BAUD_RATE);
  
  LOG("Initializing setup...\n");

  // Notify the Windows program whether or not
  // it will be receiving debug information too
#if DEBUG
  Serial.print("debug_on:");
#else
  Serial.print("debug_off:");
#endif

/*
  LOG("Enum: ");
  LOG(Controller::JOY_LEFT);
  LOG("\nName: ");
  LOG(button_name[Controller::JOY_LEFT]);
  LOG("\nAnalog: ");
  LOG(button_analog[Controller::JOY_LEFT]);
*/

  LOG("\nSetup finished.\n\n");
}




void loop()
{
  
}
