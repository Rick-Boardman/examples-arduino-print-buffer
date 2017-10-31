/*
 * sketch
 */

#include "MyClass.h"

// instantiate MyClass
MyClass myClass;

void setup() {
    /*
    * SETUP DEVICES AND CLASSES
    */

    // setup MyClass to call back to our callback_function when flushing it's buffer
    myClass.callback = callback_function;

    // initiate serial
    Serial.begin(250000);
    while (!Serial) { ; } // wait for serial port

    // notify device setup complete
    Serial.print("Device Setup Complete - ");
    Serial.println(millis());

    firstLoop();
};

void firstLoop() {
    /*
    * DO FIRST LOOP TYPE WORK
    * (without having to have a boolean firstLoop variable checked every loop!)
    */

    // just slowing comm down a little so it's not all in the same milli
    delay(1);
    
    // try out println in MyClass
    myClass.print("hello world (this will be delayed) - ");
    myClass.println(millis());

    // just slowing comm down a little so it's not all in the same milli
    delay(1);
    
    // notify first loop setup complete
    Serial.print("Setup Complete - ");
    Serial.println(millis());
};

void loop() {
    // let myClass have some cpu time if needed
    myClass.tick();
};

// myClass calls back to here when it flushes the buffer
void callback_function(char * inChars) {
    Serial.print(inChars);
};
