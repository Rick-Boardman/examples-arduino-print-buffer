/*
 *   PrintBuffer
 */

#ifndef PrintBuffer_h
#define PrintBuffer_h

#include "Arduino.h"

// inherit Print
class PrintBuffer : public Print {
    public:
        // constructor
        PrintBuffer(unsigned short flushSize = 512, unsigned short flushTime = 1000);
        // both print and println call write so we will override write
        size_t write(uint8_t);
        // enable flushing the buffer when time has passed even if buffer size isn't met
        void tick();
        // callback function in ino we will send results to
        void (*callback)(char *);
        // println uses \r\n for end of line.  we may want to send something else as eol.
        char * eol = (char *)"\r\n";
    private:
        // append chars to the buffer
        void outCharsAppend(uint8_t inChar);
        // flush the buffer
        void flush();                
        // used to track multi-char eol
        unsigned char lastChar = '\0';
        // size we want the outChars buffer to be
        unsigned short flushSize = 512;
        // time in millis we want to flush the buffer if we haven't exceeded size
        unsigned short flushTime = 1000;
        // millis of last flush
        unsigned short lastFlush = 0;
        // buffer to hold output
        unsigned char * outChars;
        // current position in buffer
        unsigned short currPos = 0;
        // last eol
        unsigned short lastEOLPos = 0;
 };

#endif
