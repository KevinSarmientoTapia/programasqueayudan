#include "segment.h"
  int a=2;
  int b=3;
  int c=4;
  int d=5;
  int e=6;
  int f=7;
  int g=8;
  // Arrays for the programs
  int Zero[7]={1, 1, 1, 1, 1, 1, 0}; // To make the number 0.
  int One[7]={0, 1, 1, 0, 0, 0, 0}; // To make the number 1.
  int Two[7]={1, 1, 0, 1, 1, 0, 1}; // To make the number 2.
  int Three[7]={1, 1, 1, 1, 0, 0, 1}; // To make the number 3.
  int Four[7]={0, 1, 1, 0, 0, 1, 1}; // To make the number 4.
  int Five[7]={1, 0, 1, 1, 0, 1, 1}; // To make the number 5.
  int Six[7]={1, 0, 1, 1, 1, 1, 1}; // To make the number 6.
  int Seven[7]={1, 1, 1, 0, 0, 0, 0}; // To make the number 7.
  int Eight[7]={1, 1, 1, 1, 1, 1, 1}; // To make the number 8.
  int Nine[7]={1, 1, 1, 0, 0, 1, 1}; // To make the number 9. 
 segment::segment(int a, int b, int c, int d, int e, int f, int g){
    Pins[0]=a;
    Pins[1]=b;
    Pins[2]=c;
    Pins[3]=d;
    Pins[4]=e;
    Pins[5]=f;
    Pins[6]=g;
  }
 void segment::beging(){
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  }

  void segment::zero(){
  for (int x=0; x<7; x++) {
  digitalWrite(Pins[x], Zero[x]);
  }
}

void segment::one(){
  for (int x=0; x<7; x++) {
  digitalWrite(Pins[x], One[x]);
  }
}

void segment::two(){
  for (int x=0; x<7; x++) {
  digitalWrite(Pins[x], Two[x]);
  }
}

void segment::three(){
  for (int x=0; x<7; x++) {
  digitalWrite(Pins[x], Three[x]);
  }
}

void segment::four(){
  for (int x=0; x<7; x++) {
  digitalWrite(Pins[x], Four[x]);
  }
}

void segment::five(){
  for (int x=0; x<7; x++) {
  digitalWrite(Pins[x], Five[x]);
  }
}

void segment::six(){
  for (int x=0; x<7; x++) {
  digitalWrite(Pins[x], Six[x]);
  }
}

void segment::seven(){
  for (int x=0; x<7; x++) {
  digitalWrite(Pins[x], Seven[x]);
  }
}

void segment::eight(){
  for (int x=0; x<7; x++) {
  digitalWrite(Pins[x], Eight[x]);
  }
}

void segment::nine(){
  for (int x=0; x<7; x++) {
  digitalWrite(Pins[x], Nine[x]);
  }
}