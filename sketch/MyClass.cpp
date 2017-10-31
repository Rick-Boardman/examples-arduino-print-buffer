/*
 * MyClass
 */

#include "MyClass.h"

// constructor
MyClass::MyClass(unsigned short flushSize, unsigned short flushTime) {
    this->flushSize = flushSize;
    this->flushTime = flushTime;

    outChars = new unsigned char[flushSize];
}

// both print and println call write so we will override write
size_t MyClass::write(uint8_t inChar) {
    if (lastChar == '\r') {
        if (inChar == '\n') {
            // add eol to output
            for (int i = 0; i < strlen(eol); i++) {
                outCharsAppend(eol[i]);
            }

            lastEOLPos = currPos;
        } else {
            // add \r + inChar to output
            outCharsAppend('\r');
            outCharsAppend(inChar);
        }
    } else {
        if (inChar == '\r') {
            if (currPos + 1 == flushSize) {
                // flush first so we don't break up the eol we want to add
                flush();
            }
        }

        // add inChar to output
        outCharsAppend(inChar);
    }

    lastChar = inChar;
}

// enable flushing the buffer when time has passed even if buffer size isn't met
void MyClass::tick() {
    // if it's been more than our flush time since the last flush then flush the buffer
    if ((millis() - lastFlush) > flushTime) {
        // only if there's something to flush
        if (currPos > 0) {
            flush();
        } else {
            // set the lastFlush time even though we didn't flush so we don't just rush flush the next char that comes along
            lastFlush = millis();
        }
    }
}

// append chars to the buffer
void MyClass::outCharsAppend(uint8_t inChar) {
    // add the char and increment our position
    outChars[currPos] = inChar;
    currPos++;

    // if this char puts us at the flush size then flush the buffer
    if (currPos == flushSize) {
        flush();
    }
}

// TODO timed flush needs to add \r if it was last char since it wouldn't have added to buffer in write
// flush the buffer
void MyClass::flush() {
    // terminate the array
    outChars[currPos] = '\0';
    // send the array to the caller
    callback((char *)outChars);
    // reset
    delete [] outChars;
    outChars = new unsigned char[flushSize];
    currPos = 0;
    lastEOLPos = 0;
    // record the millis of the current flush
    lastFlush = millis();
}
