#ifndef SEGMENT_H
#define SEGMENT_H
#include <Arduino.h>
class segment{

private:
int Pins[7];

public:
segment(){}; //Default Constructor
segment(int a, int b, int c, int d, int e, int f, int g); //Constructor and pins
void beging(); // Set pins as outputs
void zero(); //print number 0 in 7 segment.
void one(); //print number 1 in 7 segment.
void two(); //print number 2 in 7 segment.
void three(); //print number 3 in 7 segment.
void four(); //print number 4 in 7 segment.
void five(); //print number 5 in 7 segment.
void six(); //print number 6 in 7 segment.
void seven(); //print number 7 in 7 segment.
void eight(); //print number 8 in 7 segment.
void nine(); //print number 9 in 7 segment.

};
#endif
