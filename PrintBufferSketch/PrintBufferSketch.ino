/*
 * PrintBufferSketch
 * 
 * This example shows how to delay sending messages to Serial
 * This allows faster loops until the loop where the buffer flushes
 */

#include "PrintBuffer.h"

// instantiate PrintBuffer
PrintBuffer pb;

// setup reference to Serial
// if Serial needs changed to Serial1 for example change it here and in setup Serial.begin
Stream &serCom = Serial;

void setup() {
    /*
    * SETUP DEVICES AND CLASSES
    */

    // setup PrintBuffer to call back to our callback_function when flushing it's buffer
    pb.callback = callback_function;

    // I keep the baud rate as high as possible.
    // 9600 can really slow things down.  It's only 960 bytes per second.  About 1 ms per character.
    // at those speeds a single character serial com each loop could slow down an Uno by 16,000 loops per second

    // initiate serial.
    // This has to be to Serial itself
    Serial.begin(250000);
    // but from here on we can operate on the Stream that Serial inherits
    while (!&serCom) { ; } // wait for serial port

    // notify device setup complete
    serCom.print("Device Setup Complete - ");
    serCom.println(millis());

    firstLoop();
};

void firstLoop() {
    /*
    * DO FIRST LOOP TYPE WORK
    * (without having to have a boolean firstLoop variable checked every loop!)
    */

    // just slowing comm down a little so it's not all in the same milli
    delay(1);
    
    // try out println in PrintBuffer
    pb.print("hello world (this will be delayed) - ");
    pb.println(millis());

    // just slowing comm down a little so it's not all in the same milli
    delay(1);
    
    // notify first loop setup complete
    serCom.print("Setup Complete - ");
    serCom.println(millis());
};

void loop() {
    /*
    * DO LOOP WORK
    * This can loop very fast when it's not bogged down by time expesive tasks like Serial print or logging
    * I've seen this at 80,000 times per second on a mega with digital pin reads / writes and some math
    * A good example is here: https://learn.sparkfun.com/blog/1687
    * Suggesting an unloaded loop could happen at max 16Mhz (16 million times a second) on an Uno
    * and a simple digital toggle loop drops that to 117kHz (117,000 times a second)
    */

    // let PrintBuffer have some cpu time if needed
    pb.tick();
};

// PrintBuffer calls back to here when it flushes the buffer
void callback_function(char * inChars) {
    serCom.print(inChars);
};
