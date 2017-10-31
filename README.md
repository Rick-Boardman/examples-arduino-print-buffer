# PrintBuffer

This c++ arduino sketch shows how to delay sending messages to Serial  
This allows faster loops until the loop where the buffer flushes

The sketch has examples of the following:  
How to inherit serial print and println functions in your class to take advantage of their pass any type behavior.  
How to add a class to a sketch.  
How to use a callback function.  
How to add loop cpu time to a class by calling the class tick function.  
How to use an unsigned char buffer.  
How to change end of line characters for output.  
The concept of a first loop setup for things you want separate from Setup.  
How to reference a serial device by it's stream.

Operation:  
At the end of Setup() Device Setup Complete is print to Serial.  
It then calls a function and in that function hello world is print to the PrintBuffer.  
At the end of that function Setup Complete is print to Serial.

Output:  
Device Setup Complete - 0  
Setup Complete - 2  
hello world (this will be delayed) - 1  
