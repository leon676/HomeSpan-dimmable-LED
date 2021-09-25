
////////////////////////////////////
//   DEVICE-SPECIFIC LED SERVICES //
////////////////////////////////////

// library of various PWM functions
#include "extras/PwmPin.h"                          

////////////////////////////////////

// Dimmable LED
struct DEV_DimmableLED : Service::LightBulb {       

  // reference to Led Pin
  LedPin *ledPin;                                   
  // reference to the On Characteristic
  SpanCharacteristic *power;                        
  // reference to the Brightness Characteristic
  SpanCharacteristic *level;                        

  // constructor() method  
  DEV_DimmableLED(int pin) : Service::LightBulb(){       

    power=new Characteristic::On();     

    // Brightness Characteristic with an initial value of 50%                
    level=new Characteristic::Brightness(50);       
    // sets the range of the Brightness to be from a min of 5%, to a max of 100%, in steps of 1%
    level->setRange(5,100,1);                       

    // configures a PWM LED for output to the specified pin
    this->ledPin=new LedPin(pin);                   

    // initialization message
    Serial.print("Configuring Dimmable LED: Pin="); 
    Serial.print(ledPin->getPin());
    Serial.print("\n");
    
  } // end constructor
  
  // update() method
  boolean update(){
                                  
    // displays information about what is updated
    LOG1("Updating Dimmable LED on pin=");       
    LOG1(ledPin->getPin());
    LOG1(":  Current Power=");
    LOG1(power->getVal()?"true":"false");
    LOG1("  Current Brightness=");
    LOG1(level->getVal());
 
    if(power->updated()){
      LOG1("  New Power=");
      LOG1(power->getNewVal()?"true":"false");
    }

    if(level->updated()){
      LOG1("  New Brightness=");
      LOG1(level->getNewVal());
    } 

    LOG1("\n");

    // updates the actual PWM Pin
    ledPin->set(power->getNewVal()*level->getNewVal());    
   
    return(true);
  
  } // update
};

////////////////////////////////////
