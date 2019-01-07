/*  
    Authur:         MyStickersArePeeling
    Contact:        
    Start Date:     04.JAN.2019
    Last modified:  07.JAN.2019
    
    Goal:           Make a face on an 8x8 LED matrix using an Arduino
*/

#include <Arduino.h>

// Number of rows/columns in use
#define N_ROW 7
#define N_COL 7

// Connecting pin on arduino to row/column on LED matrix
// Top left is (0, 0)
// Ommiting row and column 8: Not enough pins on Arduino
int row[N_ROW] = {0, 1, 2, 3, 4, 5, 6};
int col[N_COL] = {7, 8, 9, 10, 11, 12, 13};

// Default wait time (ms)
int wait = 1.75;

// Insure all LEDs are off at startup
void setup() {
  for (int i = 0; i < N_ROW + N_COL; i++) {
    pinMode(i, OUTPUT);
    if (i < N_ROW) {
      digitalWrite(i, LOW);
    } else {
      digitalWrite(i, HIGH);
    }
  }
}

// Patterns for differnt faceial expressions
/*
   |0123456
  -+-------
  0|.......
  1|.00.00.
  2|.00.00.
  3|......
  4|.0...0.
  5|..000..
  6|.......
*/
#define HAPPY_LEN 14
int happy[HAPPY_LEN][2] =     {
                                {1, 1}, {2, 1}, {5, 1}, {6, 1},
                                {1, 2}, {2, 2}, {5, 2}, {6, 2},
                                {1, 4}, {6, 4},
                                {2, 5}, {3, 5}, {4, 5}, {5, 5}
                              };

#define NEUTRAL_LEN 14
int neutral[NEUTRAL_LEN][2] = {
                                {1, 1}, {2, 1}, {5, 1}, {6, 1},
                                {1, 2}, {2, 2}, {5, 2}, {6, 2},
                                {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5}
                              };

#define SAD_LEN 14
int sad[SAD_LEN][2] =         {
                                {1, 1}, {2, 1}, {5, 1}, {6, 1},
                                {1, 2}, {2, 2}, {5, 2}, {6, 2},
                                {2, 5}, {3, 5}, {4, 5}, {5, 5},
                                {1, 6}, {6, 6}
                              };

#define CONFUSE_LEN 14
int confuse_down[CONFUSE_LEN][2] = {
                                {1, 1}, {2, 1}, {5, 1}, {6, 1},
                                {1, 2}, {2, 2}, {5, 2}, {6, 2},
                                {2, 5}, {4, 5}, {6, 5},
                                {1, 6}, {3, 6}, {5, 6}
                              };

int confuse_up[CONFUSE_LEN][2] = {
                                {1, 1}, {2, 1}, {5, 1}, {6, 1},
                                {1, 2}, {2, 2}, {5, 2}, {6, 2},
                                {1, 5}, {3, 5}, {5, 5},
                                {2, 6}, {4, 6}, {6, 6}
                              };


void loop() {
  happy_loop(50);
  delay(5);
  neutral_loop(50);
  delay(5);
  sad_loop(50);
  delay(5);
  confuse_down_loop(50);
  delay(5);
  confuse_up_loop(50);
  delay(5);
}

// Display the happy face 
// Flash each LED in face briefly 
// Turn all off at end
void happy_loop(int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < HAPPY_LEN; j++) {
      pos(happy[j][0], happy[j][1]);
      delay(wait);
    }
  }
  pos(-1, -1);
}

// Display the neutral face 
void neutral_loop(int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < NEUTRAL_LEN; j++) {
      pos(neutral[j][0], neutral[j][1]);
      delay(wait);
    }
  }
  pos(-1, -1);
}

// Display the sad face 
void sad_loop(int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < SAD_LEN; j++) {
      pos(sad[j][0], sad[j][1]);
      delay(wait);
    }
  }
  pos(-1, -1);
}

// Display the confuse face 
// Left most lip LED down
void confuse_down_loop(int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < CONFUSE_LEN; j++) {
      pos(confuse_down[j][0], confuse_down[j][1]);
      delay(wait);
    }
  }
  pos(-1, -1);
}

// Display the confuse face
// Left most lip LED up
void confuse_up_loop(int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < CONFUSE_LEN; j++) {
      pos(confuse_up[j][0], confuse_up[j][1]);
      delay(wait);
    }
  }
  pos(-1, -1);
}


/* 
    Turn on only the LED at position (c, r)
    
    LED will on turn on if its row is high and column is low
    To turn on only LED at (c, r):
      - Column c must be low
      - All other columns must be high
      - Row r must be high
      - All other rows must be low
*/
void pos(int c, int r) {
  for (int i = 0; i < N_ROW; i++) {
    if (i == r) {
      digitalWrite(row[i], HIGH);
    } else {
      digitalWrite(row[i], LOW);
    }
  }
  for (int i = 0; i < N_COL; i++) {
    if (i == c) {
      digitalWrite(col[i], LOW);
    } else {
      digitalWrite(col[i], HIGH);
    }
  }
}
