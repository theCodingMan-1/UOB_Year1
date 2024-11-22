// Basic program skeleton for a Sketch File (.sk) Viewer
#include "displayfull.h"
#include "sketch.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Allocate memory for a drawing state and initialise it
state *newState() {
  state *p = malloc(sizeof(state));
  p->x = 0;
  p->y = 0;
  p ->tx = 0;
  p->ty = 0;
  p->tool = LINE;
  p->start = 0;
  p->data = 0;
  p->end = 0;
  return p;
}

// Release all memory associated with the drawing state
void freeState(state *s) {
  free(s);
}

// Extract an opcode from a byte (two most significant bits).
int getOpcode(byte b) {


  //0000 0000 - 0011 1111 -> DX
  //0100 0000 - 0111 1111 -> DY
  //1000 0000 - 1011 1111 -> TOOL
  //1100 0000 - 1111 1111 -> DATA

  if (b <= 0b00111111) return DX;
  else if (b >= 0b01000000 && b <= 0b01111111) return DY;
  else if (b >= 0b10000000 && b <= 0b10111111) return TOOL;

  else if (b >= 0b11000000) return DATA; //In



}

// Extract an operand (-32..31) from the rightmost 6 bits of a byte.
int getOperand(byte b) {

  if (b >= 0b01000000) b -= 0b01000000;
  else if (b >= 0b11000000) b -= 0b11000000;

  int num = b;

  if (b <= 0b00011111) {
    return num;
  }
  else {
    num -= 64;
    return num;
  }

  

  // 0001 1111 -> 31
  //0010 0000 -> 32 : -32
  //0010 0001 -> 33 : -31

}

// Execute the next byte of the command sequence.
void obey(display *d, state *s, byte op) {
  int opcode = getOpcode(op);
  int operand = getOperand(op);





  if (opcode == DX) {
    s->tx = s->tx + operand;

  }
  else if (opcode == DY) {
    s->ty = s->ty + operand;
    if (s->tool == LINE) line(d, s->x, s->y, s->tx, s->ty);
    if (s->tool == BLOCK) block(d, s->x, s->y, abs(s->tx - s->x), abs(s->ty - s->y));

    s->x = s-> tx;
    s->y = s-> ty;

  }

  else if (opcode == TOOL) {
    if (operand == COLOUR) {
      colour(d, s->data);
    }
    else if (operand == TARGETX) s->tx = s->data;
    else if (operand == TARGETY) s->ty = s->data;
    else s->tool = operand;
    
    // xxxx xxxx  xxxx xxxx  xxxx xxxx  xxxx xxxx
    //Hex
    //a -> 1010
    //b -> 1011
    //c -> 1100
    //d -> 1101
    //e -> 1110
    //f -> 1111

    s->data = 0; //In
  }

  //In
  else if (opcode == DATA) {
    s->data *= 64; //0b1000000
    if (operand >= 64) operand -= 64;
    s->data += operand;


  }

  //TO DO
  // 0001 1110 -> DX : 30
  // 0101 1110 -> DY : 30
  // 1000 0000 -> TOOL : NONE
  // 0111 1111 -> DY : -1

}

// Draw a frame of the sketch file. For basic and intermediate sketch files
// this means drawing the full sketch whenever this function is called.
// For advanced sketch files this means drawing the current frame whenever
// this function is called.
bool processSketch(display *d, const char pressedKey, void *data) {
  if (data == NULL) return (pressedKey == 27);
  const int max = sizeof(byte);

  state *s = (state*) data;
  char *filename = getName(d);
  FILE *file = fopen(filename, "rb");
  char line[max], name[100];
  // int n;
  byte *b = malloc(max);

  b = fgetc(file);
  while (! feof(file)) {
    obey(d, s, b);
    b = fgetc(file);
    
  }


  fclose(file);

  show(d);
  s->x = 0;
  s->y = 0;
  s->tx = 0;
  s->ty = 0;
  s->tool = LINE;
  s->data = 0;
  s->end = 0;

  return (pressedKey == 27);

    //TO DO: OPEN, PROCESS/DRAW A SKETCH FILE BYTE BY BYTE, THEN CLOSE IT
    //NOTE: CHECK DATA HAS BEEN INITIALISED... if (data == NULL) return (pressedKey == 27);
    //NOTE: TO GET ACCESS TO THE DRAWING STATE USE... state *s = (state*) data;
    //NOTE: TO GET THE FILENAME... char *filename = getName(d);
    //NOTE: DO NOT FORGET TO CALL show(d); AND TO RESET THE DRAWING STATE APART FROM
    //      THE 'START' FIELD AFTER CLOSING THE FILE
}

// View a sketch file in a 200x200 pixel window given the filename
void view(char *filename) {
  display *d = newDisplay(filename, 200, 200);
  state *s = newState();
  run(d, s, processSketch);
  freeState(s);
  freeDisplay(d);
}

// Include a main function only if we are not testing (make sketch),
// otherwise use the main function of the test.c file (make test).
#ifndef TESTING
int main(int n, char *args[n]) {
  if (n != 2) { // return usage hint if not exactly one argument
    printf("Use ./sketch file\n");
    exit(1);
  } else view(args[1]); // otherwise view sketch file in argument
  return 0;
}
#endif
