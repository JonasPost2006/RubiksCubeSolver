  // Code for the first prototype with buttons to solve the Rubik's cube

  // Open the machine with motors that turn the screws
  // Mount the cube into the machine and close it again
  // Use buttons to allocate colours to the pieces on the cube by calling a function and using 'while' loops to wait for a button to be pressed
  // Solve the cube one piece at a time by establishing the position of each piece and calling functions to turn the sides so that the pieces move to their correct positions
  // Allow the Arduino to keep track of the moving positions by calling a function which re-organises the piece positions after each turn

// Define every position on the cube
int wrW;
int wrR;

int wbW;
int wbB;

int woW;
int woO;

int wgW;
int wgG;

int rbR;
int rbB;

int boB;
int boO;

int ogO;
int ogG;

int grG;
int grR;

int ryR;
int ryY;

int byB;
int byY;

int oyO;
int oyY;

int gyG;
int gyY;

int wrbW;
int wrbR;
int wrbB;

int wboW;
int wboB;
int wboO;

int wogW;
int wogO;
int wogG;

int wgrW;
int wgrG;
int wgrR;

int rbyR;
int rbyB;
int rbyY;

int boyB;
int boyO;
int boyY;

int ogyO;
int ogyG;
int ogyY;

int gryG;
int gryR;
int gryY;

int const motorSpeed = 750;

// Attach the coloured buttons to arduino pins
const int openButton = 42;
const int closeButton = 48;

const int whiteButton = 38;
const int redButton = 40;
const int greenButton = 44;
const int blueButton = 46;
const int yellowButton = 50;
const int orangeButton = 52;

const int stepPinWhite = 13;
const int dirPinWhite = 12;
const int stepPinRed = 3;
const int dirPinRed = 2;
const int stepPinGreen = 5;
const int dirPinGreen = 4;
const int stepPinBlue = 20;
const int dirPinBlue = 21;
const int stepPinYellow = 18;
const int dirPinYellow = 19;
const int stepPinOrange = 11;
const int dirPinOrange = 10;

#include <Stepper.h>
const float stepsPerRev = 2048;
const float internalStepCount = 32;
Stepper SM(internalStepCount, 37, 41, 39, 43);

void setup() {
    // Define the pin modes of the buttons
    pinMode(openButton, INPUT_PULLUP);
    pinMode(closeButton, INPUT_PULLUP);
    
    pinMode(whiteButton, INPUT_PULLUP);
    pinMode(redButton, INPUT_PULLUP);
    pinMode(greenButton, INPUT_PULLUP);
    pinMode(blueButton, INPUT_PULLUP);
    pinMode(yellowButton, INPUT_PULLUP);
    pinMode(orangeButton, INPUT_PULLUP);
    Serial.begin(9600);

    pinMode(stepPinWhite, OUTPUT);
    pinMode(dirPinWhite, OUTPUT);
    pinMode(stepPinRed, OUTPUT);
    pinMode(dirPinRed, OUTPUT);
    pinMode(stepPinGreen, OUTPUT);
    pinMode(dirPinGreen, OUTPUT);
    pinMode(stepPinBlue, OUTPUT);
    pinMode(dirPinBlue, OUTPUT);
    pinMode(stepPinYellow, OUTPUT);
    pinMode(dirPinYellow, OUTPUT);
    pinMode(stepPinOrange, OUTPUT);
    pinMode(dirPinOrange, OUTPUT);
}

void loop() {

    int openButtonCond = digitalRead(openButton);
    int closeButtonCond = digitalRead(closeButton);

    if(openButtonCond == LOW){
        SM.setSpeed(1000);
        SM.step(stepsPerRev*10);
        delay(1000);
    }

    if(closeButtonCond == LOW){
        SM.setSpeed(1000);
        SM.step(-stepsPerRev*10);
        delay(1000);
    }
    
    int whiteButtonCond = digitalRead(whiteButton);
    int redButtonCond = digitalRead(redButton);
    int greenButtonCond = digitalRead(greenButton);
    int blueButtonCond = digitalRead(blueButton);
    int yellowButtonCond = digitalRead(yellowButton);
    int orangeButtonCond = digitalRead(orangeButton);
 
    if(whiteButtonCond == LOW || redButtonCond == LOW || greenButtonCond == LOW || blueButtonCond == LOW || yellowButtonCond == LOW || orangeButtonCond == LOW){
      
      buttonColourAllocation();
      for(int y = 0; y < 5; y++){
      wrPiece();
      wbPiece();
      woPiece();
      wgPiece();
      wrbPiece();
      wboPiece();
      wogPiece();
      wgrPiece();
      // Serial.println("+");

      rbPiece();
      boPiece();
      ogPiece();
      grPiece();

      yellowCross();
      yellowMiddles();
      cornerPieces();
      cornerRotation();

      }
    }

}

int wrPiece(){
    if(wrW == 1 && wrR == 2){
      Serial.println("-");
    }
    else if(wrW == 2 && wrR == 1){
      // Rotate the red side clockwise by 90 degrees
      // Rotate the blue side clockwise by 90 degrees
      // Rotate the white side clockwise by 90 degrees
      redRotate90();
      blueRotate90();
      whiteRotate90();
      Serial.println("rc, bc, wc");
    }
    else if(wbW == 1 && wbB == 2){
      // Rotate the white side clockwise by 90 degrees
      whiteRotate90();
      Serial.println("wc");
    }
    else if(wbW == 2 && wbB == 1){
      // Rotate the blue side anticlockwise by 90 degrees
      // Rotate the red side anticlockwise by 90 degrees
      blueRotateInvert90();
      redRotateInvert90();
      Serial.println("ba, ra");
    }
    else if(woW == 1 && woO == 2){
      // Rotate the white side by 180 degrees in either direction
      whiteRotate90();
      whiteRotate90();
      Serial.println("wc, wc");
    }
    else if(woW == 2 && woO == 1){
      // Rotate the white side clockwise by 90 degrees
      // Rotate the blue side anticlockwise by 90 degrees
      // Rotate the red side anticlockwise by 90 degrees
      whiteRotate90();
      blueRotateInvert90();
      redRotateInvert90();
      Serial.println("wc, ba, ra");
    }
    else if(wgW == 1 && wgG == 2){
      // Rotate the white side anticlockwise by 90 degrees
      whiteRotateInvert90();
      Serial.println("wa");
    }
    else if(wgW == 2 && wgG == 1){
      // Rotate the green side clockwise by 90 degrees
      // Rotate the red side clockwise by 90 degrees
      greenRotate90();
      redRotate90();
      Serial.println("gc, rc");
    }
    else if(rbR == 1 && rbB == 2){
      // Rotate the red face anticlockwise by 90 degrees << this is a mistake, find the correction below
      // ba, ya, r180
      blueRotateInvert90();
      yellowRotateInvert90();
      redRotate90();
      redRotate90();
      Serial.println("ba, ya, r180");
    }
    else if(rbR == 2 && rbB == 1){
      // Rotate the blue side clockwise by 90 degrees
      // Rotate the white side clockwise by 90 degrees <<<<< mistake

      // ra
      redRotateInvert90();
      Serial.println("ra");
    }
    else if(boB == 1 && boO == 2){
      // Rotate the orange side clockwise by 90 degrees
      // Rotate the white side by 180 degrees
      orangeRotate90();
      whiteRotate90();
      whiteRotate90();
      Serial.println("oc, wc, wc");
    }
    else if(boB == 2 && boO == 1){
      // Rotate the blue side anticlockwise by 90 degrees
      // Rotate the white side clockwise by 90 degrees
      blueRotateInvert90();
      whiteRotate90();
      Serial.println("ba, wc");
    }
    else if(ogO == 1 && ogG == 2){
      // Rotate the green side clockwise by 90 degrees
      // Rotate the white side anticlockwise by 90 degrees
      greenRotate90();
      whiteRotateInvert90();
      Serial.println("gc, wa");
    }
    else if(ogO == 2 && ogG == 1){
      // Rotate the orange side anticlockwise by 90 degrees
      // Rotate the white side by 180 degrees
      orangeRotateInvert90();
      whiteRotate90();
      whiteRotate90();
      Serial.println("oa, wc, wc");
    }
    else if(grG == 1 && grR == 2){
      // Rotate the red side clockwise by 90 degrees
      redRotate90();
      Serial.println("rc");
    }
    else if(grG == 2 && grR == 1){
      // Rotate the green side anticlockwise by 90 degrees
      // Rotate the white side anticlockwise by 90 degrees
      greenRotateInvert90();
      whiteRotateInvert90();
      Serial.println("ga, wa");
    }
    else if(ryR == 1 && ryY == 2){
      // Rotate the red side anticlockwise by 90 degrees
      // Rotate the blue side clockwise by 90 degrees
      // Rotate the white side clockwise by 90 degrees
      redRotateInvert90();
      blueRotate90();
      whiteRotate90();
      Serial.println("ra, bc, wc");
    }
    else if(ryR == 2 && ryY == 1){
      // Rotate the red side by 180 degrees
      redRotate90();
      redRotate90();
      Serial.println("rc, rc");
    }
    else if(byB == 1 && byY == 2){
      // Rotate the blue side clockwise by 90 degrees
      // Rotate the red side anticlockside by 90 degrees
      // Rotate the white side anticlockwise by 90 degrees
      blueRotate90();
      redRotateInvert90();
      whiteRotateInvert90();
      Serial.println("bc, ra, wa");
    }
    else if(byB == 2 && byY == 1){
      // Rotate the blue side by 180 degrees
      // Rotate the white side anticlockwise by 90 degrees
      blueRotate90();
      blueRotate90();
      whiteRotateInvert90();
      Serial.println("bc, bc, wa");
    }
    else if(oyO == 1 && oyY == 2){
      // Rotate the orange side clockwise by 90 degrees
      // Rotate the blue side anticlockside by 90 degrees
      // Rotate the white side clockwise by 90 degrees
      orangeRotate90();
      blueRotateInvert90();
      whiteRotate90();
      Serial.println("oc, ba, wc");
    }
    else if(oyO == 2 && oyY == 1){
      // Rotate the orange side by 180 degrees
      // Rotate the white side by 180 degrees
      orangeRotate90();
      orangeRotate90();
      whiteRotate90();
      whiteRotate90();
      Serial.println("oc, oc, wc, wc");
    }
    else if(gyG == 1 && gyY == 2){
      // Rotate the green side clockwise by 90 degrees
      // Rotate the orange side anticlockside by 90 degrees
      // Rotate the white side by 180 degrees
      greenRotate90();
      orangeRotateInvert90();
      whiteRotate90();
      whiteRotate90();
      Serial.println("gc, oa, wc, wc");
    }
    else{
      // Rotate the green side by 180 degrees
      // Rotate the white side anticlockwise by 90 degrees
      greenRotate90();
      greenRotate90();
      whiteRotateInvert90();
      Serial.println("gc, gc, wa");
    }
}

int wbPiece(){
    if(wbW == 1 && wbB == 4){
      Serial.println("-");
    }
    else if(wbW == 4 && wbB == 1){
      // ba, ra, wa, rc
      blueRotateInvert90();
      redRotateInvert90();
      whiteRotateInvert90();
      redRotate90();
      Serial.println("ba, ra, wa, rc");
    }
    else if(woW == 1 && woO == 4){
      // ra, wc, rc
      redRotateInvert90();
      whiteRotate90();
      redRotate90();
      Serial.println("ra, wc, rc");
    }
    else if(woW == 4 && woO == 1){
      // oa, ba
      orangeRotateInvert90();
      blueRotateInvert90();
      Serial.println("oa, ba");
    }
    else if(wgW == 1 && wgG == 4){
      // ra, w180, rc
      redRotateInvert90();
      whiteRotate90();
      whiteRotate90();
      redRotate90();
      Serial.println("ra, w180, rc");
    }
    else if(wgW == 4 && wgG == 1){
      // ga, wa, ra, wc, rc
      greenRotateInvert90();
      whiteRotateInvert90();
      redRotateInvert90();
      whiteRotate90();
      redRotate90();
      Serial.println("ga, wa, ra, wc, rc");
    }
    else if(rbR == 1 && rbB == 4){
      // bc
      blueRotate90();
      Serial.println("bc");
    }
    else if(rbR == 4 && rbB == 1){
      // ra, wa, rc
      redRotateInvert90();
      whiteRotateInvert90();
      redRotate90();
      Serial.println("ra, wa, rc");
    }
    else if(boB == 1 && boO == 4){
      // oc, ra, wc, rc
      orangeRotate90();
      redRotateInvert90();
      whiteRotate90();
      redRotate90();
      Serial.println("oc, ra, wc, rc");
    }
    else if(boB == 4 && boO == 1){
      // ba
      blueRotateInvert90();
      Serial.println("wc");
    }
    else if(ogO == 1 && ogG == 4){
      // gc, ra, w180, rc
      greenRotate90();
      redRotateInvert90();
      whiteRotate90();
      whiteRotate90();
      redRotate90();
      Serial.println("gc, ra, w180, rc");
    }
    else if(ogO == 4 && ogG == 1){
      // oa, ra, wc, rc
      orangeRotateInvert90();
      redRotateInvert90();
      whiteRotate90();
      redRotate90();
      Serial.println("oa, ra, wc, rc");
    }
    else if(grG == 1 && grR == 4){
      // rc, wa, ra
      redRotate90();
      whiteRotateInvert90();
      redRotateInvert90();
      Serial.println("rc, wa, ra");
    }
    else if(grG == 4 && grR == 1){
      // ga, ra, w180, rc
      greenRotateInvert90();
      redRotateInvert90();
      whiteRotate90();
      whiteRotate90();
      redRotate90();
      Serial.println("ga, ra, w180, rc");
    }
  
    else if(ryR == 1 && ryY == 4){
      // ra, bc, rc
      redRotateInvert90();
      blueRotate90();
      redRotate90();
      Serial.println("ra, bc, rc");
    }
    else if(ryR == 4 && ryY == 1){
      // yc, b180
      yellowRotate90();
      blueRotate90();
      blueRotate90();
      Serial.println("yc, b180");
    }
    else if(byB == 1 && byY == 4){
      // bc, ra, wa, rc
      blueRotate90();
      redRotateInvert90();
      whiteRotateInvert90();
      redRotate90();
      Serial.println("bc, ra, wa, rc");
    }
    else if(byB == 4 && byY == 1){
      // b180
      blueRotate90();
      blueRotate90();
      Serial.println("b180");
    }
    else if(oyO == 1 && oyY == 4){
      // oc, ba
      orangeRotate90();
      blueRotateInvert90();
      Serial.println("oc, ba");
    }
    else if(oyO == 4 && oyY == 1){
      // ya, b180
      yellowRotateInvert90();
      blueRotate90();
      blueRotate90();
      Serial.println("ya, b180");
    }
    else if(gyG == 1 && gyY == 4){
      // ga, rc, wa, ra
      greenRotateInvert90();
      redRotate90();
      whiteRotateInvert90();
      redRotateInvert90();
      Serial.println("ga, rc, wa, ra");
    }
    else{
      // g180, ra, w180, rc
      greenRotate90();
      greenRotate90();
      redRotateInvert90();
      whiteRotate90();
      whiteRotate90();
      redRotate90();
      Serial.println("g180, ra, w180, rc");
    }
}

int woPiece(){
    if(woW == 1 && woO == 6){
      Serial.println("-"); 
    }
    else if(woW == 6 && woO == 1){
      // o180, ya, ba, oc, bc
        orangeRotate90();
        orangeRotate90();
        yellowRotateInvert90();
        blueRotateInvert90();
        orangeRotate90();
        blueRotate90();
      Serial.println("o180, ya, ba, oc, bc");
    }
    else if(wgW == 1 && wgG == 6){
      // g180, ya, o180
        greenRotate90();
        greenRotate90();
        yellowRotateInvert90();
        orangeRotate90();
        orangeRotate90();
      Serial.println("g180, ya, o180");
    }
    else if(wgW == 6 && wgG == 1){
      // ga, oa
        greenRotateInvert90();
        orangeRotateInvert90();
      Serial.println("ga, oa");
    }
    else if(rbR == 1 && rbB == 6){
      // ba, yc, bc, o180
        blueRotateInvert90();
        yellowRotate90();
        blueRotate90();
        orangeRotate90();
        orangeRotate90();
      Serial.println("ba, yc, bc, o180");
    }
    else if(rbR == 6 && rbB == 1){
      // rc, y180, ra, o180
        redRotate90();
        yellowRotate90();
        yellowRotate90();
        redRotateInvert90();
        orangeRotate90();
        orangeRotate90();
      Serial.println("rc, y180, ra, o180");
    }
    else if(boB == 1 && boO == 6){
      // oc
        orangeRotate90();
      Serial.println("oc");
    }
    else if(boB == 6 && boO == 1){
      // ra, ba, wa, bc, rc
        redRotateInvert90();
        blueRotateInvert90();
        whiteRotateInvert90();
        blueRotate90();
        redRotate90();
      Serial.println("ra, ba, wa, bc, rc");
    }
    else if(ogO == 1 && ogG == 6){
      // ga, ya, o180
        greenRotateInvert90();
        yellowRotateInvert90();
        orangeRotate90();
        orangeRotate90();
      Serial.println("ga, ya, o180");
    }
    else if(ogO == 6 && ogG == 1){
      // oa
        orangeRotateInvert90();
      Serial.println("oa");
    }
    else if(grG == 1 && grR == 6){
      // ra, y180, o180
        redRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        orangeRotate90();
        orangeRotate90();
      Serial.println("ra, y180, o180");
    }
    else if(grG == 6 && grR == 1){
      // gc, ya, o180
        greenRotate90();
        yellowRotateInvert90();
        orangeRotate90();
        orangeRotate90();
      Serial.println("gc, ya, o180");
    }
  
    else if(ryR == 1 && ryY == 6){
      // ya, gc, oa
        yellowRotateInvert90();
        greenRotate90();
        orangeRotateInvert90();
      Serial.println("ya, gc, oa");
    }
    else if(ryR == 6 && ryY == 1){
      // y180, o180
        yellowRotate90();
        yellowRotate90();
        orangeRotate90();
        orangeRotate90();
      Serial.println("y180, o180");
    }
    else if(byB == 1 && byY == 6){
      // ba, oc, bc
        blueRotateInvert90();
        orangeRotate90();
        blueRotate90();
      Serial.println("ba, oc, bc");
    }
    else if(byB == 6 && byY == 1){
      // yc, o180
        yellowRotate90();
        orangeRotate90();
        orangeRotate90();
      Serial.println("yc, o180");
    }
    else if(oyO == 1 && oyY == 6){
      // yc, gc, oa
        yellowRotate90();
        greenRotate90();
        orangeRotateInvert90();
      Serial.println("yc, gc, oa");
    }
    else if(oyO == 6 && oyY == 1){
      // o180
        orangeRotate90();
        orangeRotate90();
      Serial.println("o180");
    }
    else if(gyG == 1 && gyY == 6){
      // gc, oa
        greenRotate90();
        orangeRotateInvert90();
      Serial.println("gc, oa");
    }
    else{
      // ya, o180
        yellowRotateInvert90();
        orangeRotate90();
        orangeRotate90();
      Serial.println("ya, o180");
    }
}

int wgPiece(){
    if(wgW == 1 && wgG == 3){
      Serial.println("-"); 
    }
    else if(wgW == 3 && wgG == 1){
      // g180, ya, oa, gc, oc
        greenRotate90();
        greenRotate90();
        yellowRotateInvert90();
        orangeRotateInvert90();
        greenRotate90();
        orangeRotate90();
      Serial.println("g180, ya, oa, gc, oc");
    }
    else if(rbR == 1 && rbB == 3){
      // ba, y180, bc, g180
        blueRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        blueRotate90();
        greenRotate90();
        greenRotate90();
      Serial.println("ba, y180, bc, g180");
    }
    else if(rbR == 3 && rbB == 1){
      // ba, ya, bc, rc, ga, ra
        blueRotateInvert90();
        yellowRotateInvert90();
        blueRotate90();
        redRotate90();
        greenRotateInvert90();
        redRotateInvert90();
      Serial.println("ba, ya, bc, rc, ga, ra");
    }
    else if(boB == 1 && boO == 3){
      // oa, yc, oc, g180
        orangeRotateInvert90();
        yellowRotate90();
        orangeRotate90();
        greenRotate90();
        greenRotate90();
      Serial.println("oa, yc, oc, g180");
    }
    else if(boB == 3 && boO == 1){
      // o180, gc, o180
        orangeRotate90();
        orangeRotate90();
        greenRotate90();
        orangeRotate90();
        orangeRotate90();
      Serial.println("o180, gc, o180");
    }
    else if(ogO == 1 && ogG == 3){
      // gc
        greenRotate90();
      Serial.println("gc");
    }
    else if(ogO == 3 && ogG == 1){
      // oc, yc, oa, g180
        orangeRotate90();
        yellowRotate90();
        orangeRotateInvert90();
        greenRotate90();
        greenRotate90();
      Serial.println("oc, yc, oa, g180");
    }
    else if(grG == 1 && grR == 3){
      // ra, ya, rc, g180
        redRotateInvert90();
        yellowRotateInvert90();
        redRotate90();
        greenRotate90();
        greenRotate90();
      Serial.println("ra, ya, rc, g180");
    }
    else if(grG == 3 && grR == 1){
      // ga
        greenRotateInvert90();
      Serial.println("ga");
    }
    else if(ryR == 1 && ryY == 3){
      // rc, ga, ra
        redRotate90();
        greenRotateInvert90();
        redRotateInvert90();
      Serial.println("rc, ga, ra");
    }
    else if(ryR == 3 && ryY == 1){
      // ya, g180
        yellowRotateInvert90();
        greenRotate90();
        greenRotate90();
      Serial.println("ya, g180");
    }
    else if(byB == 1 && byY == 3){
      // yc, oa, gc, oc
        yellowRotate90();
        orangeRotateInvert90();
        greenRotate90();
        orangeRotate90();
      Serial.println("yc, oa, gc, oc");
    }
    else if(byB == 3 && byY == 1){
      // y180, g180
        yellowRotate90();
        yellowRotate90();
        greenRotate90();
        greenRotate90();
      Serial.println("y180, g180");
    }
    else if(oyO == 1 && oyY == 3){
      // oa, gc, oc
        orangeRotateInvert90();
        greenRotate90();
        orangeRotate90();
      Serial.println("oa, gc, oc");
    }
    else if(oyO == 3 && oyY == 1){
      // yc, g180
        yellowRotate90();
        greenRotate90();
        greenRotate90();
      Serial.println("yc, g180");
    }
    else if(gyG == 1 && gyY == 3){
      // ya, oa, gc, oc
        yellowRotateInvert90();
        orangeRotateInvert90();
        greenRotate90();
        orangeRotate90();
      Serial.println("ya, oa, gc, oc");
    }
    else{
      // g180
        greenRotate90();
        greenRotate90();
      Serial.println("g180");
    }
}

int wrbPiece(){
    if(wrbW == 1 && wrbR == 2 && wrbB == 4){
      Serial.println("-");
    }
    else if(wrbW == 4 && wrbR == 1 && wrbB == 2){
      // ba, yc, bc, ya, ba, yc, bc
        blueRotateInvert90();
        yellowRotate90();
        blueRotate90();
        yellowRotateInvert90();
        blueRotateInvert90();
        yellowRotate90();
        blueRotate90();
      Serial.println("ba, yc, bc, ya, ba, yc, bc");
    }
    else if(wrbW == 2 && wrbR == 4 && wrbB == 1){
      // ba, ya, bc, yc, ba, ya, bc
        blueRotateInvert90();
        yellowRotateInvert90();
        blueRotate90();
        yellowRotate90();
        blueRotateInvert90();
        yellowRotateInvert90();
        blueRotate90();
      Serial.println("ba, ya, bc, yc, ba, ya, bc");
    }
  
    
    else if(wboW == 1 && wboB == 2 && wboO == 4){
      // oa, ya, oc, ya, ba, yc, bc
        orangeRotateInvert90();
        yellowRotateInvert90();
        orangeRotate90();
        yellowRotateInvert90();
        blueRotateInvert90();
        yellowRotate90();
        blueRotate90();
      Serial.println("oa, ya, oc, ya, ba, yc, bc");
    }
    else if(wboW == 4 && wboB == 1 && wboO == 2){
      // oa, ya, oc, ba, y180, bc, yc, ba, ya, bc
        orangeRotateInvert90();
        yellowRotateInvert90();
        orangeRotate90();
        blueRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        blueRotate90();
        yellowRotate90();
        blueRotateInvert90();
        yellowRotateInvert90();
        blueRotate90();
      Serial.println("oa, ya, oc, ba, y180, bc, yc, ba, ya, bc");
    }
    else if(wboW == 2 && wboB == 4 && wboO == 1){
      // oa, ya, oc, ba, ya, bc
        orangeRotateInvert90();
        yellowRotateInvert90();
        orangeRotate90();
        blueRotateInvert90();
        yellowRotateInvert90();
        blueRotate90();
      Serial.println("oa, ya, oc, ba, ya, bc");
    }
  
    
    else if(wogW == 1 && wogO == 2 && wogG == 4){
      // ga, ya, gc, y180, ba, yc, bc
        greenRotateInvert90();
        yellowRotateInvert90();
        greenRotate90();
        yellowRotate90();
        yellowRotate90();
        blueRotateInvert90();
        yellowRotate90();
        blueRotate90();
      Serial.println("ga, ya, gc, y180, ba, yc, bc");
    }
    else if(wogW == 4 && wogO == 1 && wogG == 2){
      // ga, ya, gc, ya, ba, y180, bc, yc, ba, ya, bc
        greenRotateInvert90();
        yellowRotateInvert90();
        greenRotate90();
        yellowRotateInvert90();
        blueRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        blueRotate90();
        yellowRotate90();
        blueRotateInvert90();
        yellowRotateInvert90();
        blueRotate90();
      Serial.println("ga, ya, gc, ya, ba, y180, bc, yc, ba, ya, bc");
    }
    else if(wogW == 2 && wogO == 4 && wogG == 1){
      // ga, ya, gc, ya, ba, ya, bc
        greenRotateInvert90();
        yellowRotateInvert90();
        greenRotate90();
        yellowRotateInvert90();
        blueRotateInvert90();
        yellowRotateInvert90();
        blueRotate90();
      Serial.println("ga, ya, gc, ya, ba, ya, bc");
    }
  
    
    else if(wgrW == 1 && wgrG == 2 && wgrR == 4){
      // ra, ya, rc, yc, ba, yc, bc
        redRotateInvert90();
        yellowRotateInvert90();
        redRotate90();
        yellowRotate90();
        blueRotateInvert90();
        yellowRotate90();
        blueRotate90();
      Serial.println("ra, ya, rc, yc, ba, yc, bc");
    }
    else if(wgrW == 4 && wgrG == 1 && wgrR == 2){
      // gc, yc, ga, ya, ba, yc, bc
        greenRotate90();
        yellowRotate90();
        greenRotateInvert90();
        yellowRotateInvert90();
        blueRotateInvert90();
        yellowRotate90();
        blueRotate90();
      Serial.println("gc, yc, ga, ya, ba, yc, bc");
    }
    else if(wgrW == 2 && wgrG == 4 && wgrR == 1){
      // ra, ya, rc, y180, ba, ya, bc
        redRotateInvert90();
        yellowRotateInvert90();
        redRotate90();
        yellowRotate90();
        yellowRotate90();
        blueRotateInvert90();
        yellowRotateInvert90();
        blueRotate90();
      Serial.println("ra, ya, rc, y180, ba, ya, bc");
    }
  
    
    else if(rbyR == 1 && rbyB == 4 && rbyY == 2){
      // ya, ba, yc, bc
        yellowRotateInvert90();
        blueRotateInvert90();
        yellowRotate90();
        blueRotate90();
      Serial.println("ya, ba, yc, bc");
    }
    else if(rbyR == 4 && rbyB == 2 && rbyY == 1){
      // ba, y180, bc, yc, ba, ya, bc
        blueRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        blueRotate90();
        yellowRotate90();
        blueRotateInvert90();
        yellowRotateInvert90();
        blueRotate90();
      Serial.println("ba, y180, bc, yc, ba, ya, bc");
    }
    else if(rbyR == 2 && rbyB == 1 && rbyY == 4){
      // yc, rc, ya, ra
        yellowRotate90();
        redRotate90();
        yellowRotateInvert90();
        redRotateInvert90();
      Serial.println("yc, rc, ya, ra");
    }
  
  
    else if(boyB == 1 && boyO == 4 && boyY == 2){
      // y180, ba, yc, bc
        yellowRotate90();
        yellowRotate90();
        blueRotateInvert90();
        yellowRotate90();
        blueRotate90();
      Serial.println("y180, ba, yc, bc");
    }
    else if(boyB == 4 && boyO == 2 && boyY == 1){
      // ya, ba, y180, bc, yc, ba, ya, bc
        yellowRotateInvert90();
        blueRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        blueRotate90();
        yellowRotate90();
        blueRotateInvert90();
        yellowRotateInvert90();
        blueRotate90();
      Serial.println("ya, ba, y180, bc, yc, ba, ya, bc");
    }
    else if(boyB == 2 && boyO == 1 && boyY == 4){
      // ya, ba, ya, bc
        yellowRotateInvert90();
        blueRotateInvert90();
        yellowRotateInvert90();
        blueRotate90();
      Serial.println("ya, ba, ya, bc");
    }
  
    
    else if(ogyO == 1 && ogyG == 4 && ogyY == 2){
      // yc, ba, yc, bc
        yellowRotate90();
        blueRotateInvert90();
        yellowRotate90();
        blueRotate90();
      Serial.println("yc, ba, yc, bc");
    }
    else if(ogyO == 4 && ogyG == 2 && ogyY == 1){
      // y180, ba, y180, bc, yc, ba, ya, bc
        yellowRotate90();
        yellowRotate90();
        blueRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        blueRotate90();
        yellowRotate90();
        blueRotateInvert90();
        yellowRotateInvert90();
        blueRotate90();
      Serial.println("y180, ba, y180, bc, yc, ba, ya, bc");
    }
    else if(ogyO == 2 && ogyG == 1 && ogyY == 4){
      // y180, ba, ya, bc
        yellowRotate90();
        yellowRotate90();
        blueRotateInvert90();
        yellowRotateInvert90();
        blueRotate90();
      Serial.println("y180, ba, ya, bc");
    }
  
    
    else if(gryG == 1 && gryR == 4 && gryY == 2){
      // ba, yc, bc
        blueRotateInvert90();
        yellowRotate90();
        blueRotate90();
      Serial.println("ba, yc, bc");
    }
    else if(gryG == 4 && gryR == 2 && gryY == 1){
      // yc, ba, y180, bc, yc, ba, ya, bc
        yellowRotate90();
        blueRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        blueRotate90();
        yellowRotate90();
        blueRotateInvert90();
        yellowRotateInvert90();
        blueRotate90();
      Serial.println("yc, ba, y180, bc, yc, ba, ya, bc");
    }
    else{
      // yc, ba, ya, bc
        yellowRotate90();
        blueRotateInvert90();
        yellowRotateInvert90();
        blueRotate90();
      Serial.println("yc, ba, ya, bc");
    }
}

int wboPiece(){
    if(wboW == 1 && wboB == 4 && wboO == 6){
      Serial.println("-"); 
    }
    else if(wboW == 6 && wboB == 1 && wboO == 4){
      // oa, yc, oc, ya, oa, yc, oc
        orangeRotateInvert90();
        yellowRotate90();
        orangeRotate90();
        yellowRotateInvert90();
        orangeRotateInvert90();
        yellowRotate90();
        orangeRotate90();
      Serial.println("oa, yc, oc, ya, oa, yc, oc");
    }
    else if(wboW == 4 && wboB == 6 && wboO == 1){
      // oa, ya, oc, yc, oa, ya, oc
        orangeRotateInvert90();
        yellowRotateInvert90();
        orangeRotate90();
        yellowRotate90();
        orangeRotateInvert90();
        yellowRotateInvert90();
        orangeRotate90();
      Serial.println("oa, ya, oc, yc, oa, ya, oc");
    }
  
    
    else if(wogW == 1 && wogO == 4 && wogG == 6){
      // ga, ya, gc, ya, oa, yc, oc
        greenRotateInvert90();
        yellowRotateInvert90();
        greenRotate90();
        yellowRotateInvert90();
        orangeRotateInvert90();
        yellowRotate90();
        orangeRotate90();
      Serial.println("ga, ya, gc, ya, oa, yc, oc");
    }
    else if(wogW == 6 && wogO == 1 && wogG == 4){
      // ga, ya, gc, oa, y180, oc, yc, oa, ya, oc
        greenRotateInvert90();
        yellowRotateInvert90();
        greenRotate90();
        orangeRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        orangeRotate90();
        yellowRotate90();
        orangeRotateInvert90();
        yellowRotateInvert90();
        orangeRotate90();
      Serial.println("ga, ya, gc, oa, y180, oc, yc, oa, ya, oc");
    }
    else if(wogW == 4 && wogO == 6 && wogG == 1){
      // ga, ya, gc, oa, ya, oc
        greenRotateInvert90();
        yellowRotateInvert90();
        greenRotate90();
        orangeRotateInvert90();
        yellowRotateInvert90();
        orangeRotate90();
      Serial.println("ga, ya, gc, oa, ya, oc");
    }
  
    
    else if(wgrW == 1 && wgrG == 4 && wgrR == 6){
      // gc, y180, ga, oa, ya, oc
        greenRotate90();
        yellowRotate90();
        yellowRotate90();
        greenRotateInvert90();
        orangeRotateInvert90();
        yellowRotateInvert90();
        orangeRotate90();
      Serial.println("gc, y180, ga, oa, ya, oc");
    }
    else if(wgrW == 6 && wgrG == 1 && wgrR == 4){
      // ra, ya, rc, ya, oa, y180, oc, yc, oa, ya, oc
        redRotateInvert90();
        yellowRotateInvert90();
        redRotate90();
        yellowRotateInvert90();
        orangeRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        orangeRotate90();
        yellowRotate90();
        orangeRotateInvert90();
        yellowRotateInvert90();
        orangeRotate90();
      Serial.println("ra, ya, rc, ya, oa, y180, oc, yc, oa, ya, oc");
    }
    else if(wgrW == 4 && wgrG == 6 && wgrR == 1){
      // ra, y180, rc, oa, ya, oc
        redRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        redRotate90();
        orangeRotateInvert90();
        yellowRotateInvert90();
        orangeRotate90();
      Serial.println("ra, y180, rc, oa, ya, oc");
    }
  
    
    else if(rbyR == 1 && rbyB == 6 && rbyY == 4){
      // oa, yc, oc
        orangeRotateInvert90();
        yellowRotate90();
        orangeRotate90();
      Serial.println("oa, yc, oc");
    }
    else if(rbyR == 6 && rbyB == 4 && rbyY == 1){
      // yc, oa, y180, oc, yc, oa, ya, oc
        yellowRotate90();
        orangeRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        orangeRotate90();
        yellowRotate90();
        orangeRotateInvert90();
        yellowRotateInvert90();
        orangeRotate90();
      Serial.println("yc, oa, y180, oc, yc, oa, ya, oc");
    }
    else if(rbyR == 4 && rbyB == 1 && rbyY == 6){
      // yc, oa, ya, oc
        yellowRotate90();
        orangeRotateInvert90();
        yellowRotateInvert90();
        orangeRotate90();
      Serial.println("yc, oa, ya, oc");
    }
  
  
    else if(boyB == 1 && boyO == 6 && boyY == 4){
      // ya, oa, yc, oc
        yellowRotateInvert90();
        orangeRotateInvert90();
        yellowRotate90();
        orangeRotate90();
      Serial.println("ya, oa, yc, oc");
    }
    else if(boyB == 6 && boyO == 4 && boyY == 1){
      // oa, y180, oc, yc, oa, ya, oc
        orangeRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        orangeRotate90();
        yellowRotate90();
        orangeRotateInvert90();
        yellowRotateInvert90();
        orangeRotate90();
      Serial.println("oa, y180, oc, yc, oa, ya, oc");
    }
    else if(boyB == 4 && boyO == 1 && boyY == 6){
      // oa, ya, oc
        orangeRotateInvert90();
        yellowRotateInvert90();
        orangeRotate90();
      Serial.println("oa, ya, oc");
    }
  
    
    else if(ogyO == 1 && ogyG == 6 && ogyY == 4){
      // y180, oa, yc, oc
        yellowRotate90();
        yellowRotate90();
        orangeRotateInvert90();
        yellowRotate90();
        orangeRotate90();
      Serial.println("y180, oa, yc, oc");
    }
    else if(ogyO == 6 && ogyG == 4 && ogyY == 1){
      // ya, oa, y180, oc, yc, oa, ya, oc
        yellowRotateInvert90();
        orangeRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        orangeRotate90();
        yellowRotate90();
        orangeRotateInvert90();
        yellowRotateInvert90();
        orangeRotate90();
      Serial.println("ya, oa, y180, oc, yc, oa, ya, oc");
    }
    else if(ogyO == 4 && ogyG == 1 && ogyY == 6){
      // ya, oa, ya, oc
        yellowRotateInvert90();
        orangeRotateInvert90();
        yellowRotateInvert90();
        orangeRotate90();
      Serial.println("ya, oa, ya, oc");
    }
  
    
    else if(gryG == 1 && gryR == 6 && gryY == 4){
      // oa, y180, oc
        orangeRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        orangeRotate90();
      Serial.println("oa, y180, oc");
    }
    else if(gryG == 6 && gryR == 4 && gryY == 1){
      // y180, oa, y180, oc, yc, oa, ya, oc
        yellowRotate90();
        yellowRotate90();
        orangeRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        orangeRotate90();
        yellowRotate90();
        orangeRotateInvert90();
        yellowRotateInvert90();
        orangeRotate90();
      Serial.println("y180, oa, y180, oc, yc, oa, ya, oc");
    }
    else{
      // y180, oa, ya, oc
        yellowRotate90();
        yellowRotate90();
        orangeRotateInvert90();
        yellowRotateInvert90();
        orangeRotate90();
      Serial.println("y180, oa, ya, oc");
    }
}

int wogPiece(){
    if(wogW == 1 && wogO == 6 && wogG == 3){
      Serial.println("-"); 
    }
    else if(wogW == 3 && wogO == 1 && wogG == 6){
      // ga, yc, gc, ya, ga, yc, gc
        greenRotateInvert90();
        yellowRotate90();
        greenRotate90();
        yellowRotateInvert90();
        greenRotateInvert90();
        yellowRotate90();
        greenRotate90();
      Serial.println("ga, yc, gc, ya, ga, yc, gc");
    }
    else if(wogW == 6 && wogO == 3 && wogG == 1){
      // ga, ya, gc, yc, ga, ya, gc
        greenRotateInvert90();
        yellowRotateInvert90();
        greenRotate90();
        yellowRotate90();
        greenRotateInvert90();
        yellowRotateInvert90();
        greenRotate90();
      Serial.println("ga, ya, gc, yc, ga, ya, gc");
    }
  
    
    else if(wgrW == 1 && wgrG == 6 && wgrR == 3){
      // ra, ya, rc, ya, ga, yc, gc
        redRotateInvert90();
        yellowRotateInvert90();
        redRotate90();
        yellowRotateInvert90();
        greenRotateInvert90();
        yellowRotate90();
        greenRotate90();
      Serial.println("ra, ya, rc, ya, ga, yc, gc");
    }
    else if(wgrW == 3 && wgrG == 1 && wgrR == 6){
      // ra, ya, rc, ga, y180, gc, yc, ga, ya, gc
        redRotateInvert90();
        yellowRotateInvert90();
        redRotate90();
        greenRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        greenRotate90();
        yellowRotate90();
        greenRotateInvert90();
        yellowRotateInvert90();
        greenRotate90();
      Serial.println("ra, ya, rc, ga, y180, gc, yc, ga, ya, gc");
    }
    else if(wgrW == 6 && wgrG == 3 && wgrR == 1){
      // ra, ya, rc, ga, ya, gc
        redRotateInvert90();
        yellowRotateInvert90();
        redRotate90();
        greenRotateInvert90();
        yellowRotateInvert90();
        greenRotate90();
      Serial.println("ra, ya, rc, ga, ya, gc");
    }
  
    
    else if(rbyR == 1 && rbyB == 3 && rbyY == 6){
      // yc, ga, yc, gc
        yellowRotate90();
        greenRotateInvert90();
        yellowRotate90();
        greenRotate90();
      Serial.println("yc, ga, yc, gc");
    }
    else if(rbyR == 3 && rbyB == 6 && rbyY == 1){
      // y180, ga, y180, gc, yc, ga, ya, gc
        yellowRotate90();
        yellowRotate90();
        greenRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        greenRotate90();
        yellowRotate90();
        greenRotateInvert90();
        yellowRotateInvert90();
        greenRotate90();
      Serial.println("y180, ga, y180, gc, yc, ga, ya, gc");
    }
    else if(rbyR == 6 && rbyB == 1 && rbyY == 3){
      // y180, ga, ya, gc
        yellowRotate90();
        yellowRotate90();
        greenRotateInvert90();
        yellowRotateInvert90();
        greenRotate90();
      Serial.println("y180, ga, ya, gc");
    }
  
  
    else if(boyB == 1 && boyO == 3 && boyY == 6){
      // ga, yc, gc
        greenRotateInvert90();
        yellowRotate90();
        greenRotate90();
      Serial.println("ga, yc, gc");
    }
    else if(boyB == 3 && boyO == 6 && boyY == 1){
      // yc, ga, y180, gc, yc, ga, ya, gc
        yellowRotate90();
        greenRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        greenRotate90();
        yellowRotate90();
        greenRotateInvert90();
        yellowRotateInvert90();
        greenRotate90();
      Serial.println("yc, ga, y180, gc, yc, ga, ya, gc");
    }
    else if(boyB == 6 && boyO == 1 && boyY == 3){
      // yc, ga, ya, gc
        yellowRotate90();
        greenRotateInvert90();
        yellowRotateInvert90();
        greenRotate90();
      Serial.println("yc, ga, ya, gc");
    }
  
    
    else if(ogyO == 1 && ogyG == 3 && ogyY == 6){
      // ya, ga, yc, gc
        yellowRotateInvert90();
        greenRotateInvert90();
        yellowRotate90();
        greenRotate90();
      Serial.println("ya, ga, yc, gc");
    }
    else if(ogyO == 3 && ogyG == 6 && ogyY == 1){
      // yc, ga, y180, gc, yc, ga, ya, gc
        yellowRotate90();
        greenRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        greenRotate90();
        yellowRotate90();
        greenRotateInvert90();
        yellowRotateInvert90();
        greenRotate90();
      Serial.println("yc, ga, y180, gc, yc, ga, ya, gc");
    }
    else if(ogyO == 6 && ogyG == 1 && ogyY == 3){
      // yc, ga, ya, gc
        yellowRotate90();
        greenRotateInvert90();
        yellowRotateInvert90();
        greenRotate90();
      Serial.println("yc, ga, ya, gc");
    }
  
    
    else if(gryG == 1 && gryR == 3 && gryY == 6){
      // y180, ga, yc, gc
        yellowRotate90();
        yellowRotate90();
        greenRotateInvert90();
        yellowRotate90();
        greenRotate90();
      Serial.println("y180, ga, yc, gc");
    }
    else if(gryG == 3 && gryR == 6 && gryY == 1){
      // ya, ga, y180, gc, yc, ga, ya, gc
        yellowRotateInvert90();
        greenRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        greenRotate90();
        yellowRotate90();
        greenRotateInvert90();
        yellowRotateInvert90();
        greenRotate90();
      Serial.println("ya, ga, y180, gc, yc, ga, ya, gc");
    }
    else{
      // ya, ga, ya, gc
        yellowRotateInvert90();
        greenRotateInvert90();
        yellowRotateInvert90();
        greenRotate90();
      Serial.println("ya, ga, ya, gc");
    }
}

int wgrPiece(){
    if(wgrW == 1 && wgrG == 3 && wgrR == 2){
      Serial.println("-"); 
    }
    else if(wgrW == 2 && wgrG == 1 && wgrR == 3){
      // ra, yc, rc, ya, ra, yc, rc 
        redRotateInvert90();
        yellowRotate90();
        redRotate90();
        yellowRotateInvert90();
        redRotateInvert90();
        yellowRotate90();
        redRotate90();
      Serial.println("ra, yc, rc, ya, ra, yc, rc ");
    }
    else if(wgrW == 3 && wgrG == 2 && wgrR == 1){
      // ra, ya, rc, yc, ra, ya, rc
        redRotateInvert90();
        yellowRotateInvert90();
        redRotate90();
        yellowRotate90();
        redRotateInvert90();
        yellowRotateInvert90();
        redRotate90();
      Serial.println("ra, ya, rc, yc, ra, ya, rc");
    }
  
    
    else if(rbyR == 1 && rbyB == 2 && rbyY == 3){
      // y180, ra, yc, rc
        yellowRotate90();
        yellowRotate90();
        redRotateInvert90();
        yellowRotate90();
        redRotate90();
      Serial.println("y180, ra, yc, rc");
    }
    else if(rbyR == 2 && rbyB == 3 && rbyY == 1){
      // ya, ra, y180, rc, yc, ra, ya, rc
        yellowRotateInvert90();
        redRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        redRotate90();
        yellowRotate90();
        redRotateInvert90();
        yellowRotateInvert90();
        redRotate90();
      Serial.println("ya, ra, y180, rc, yc, ra, ya, rc");
    }
    else if(rbyR == 3 && rbyB == 1 && rbyY == 2){
      // ya, ra, y180, rc, yc, ra, ya, rc  << mistake, corrected below
      // ya, ra, ya, rc
        yellowRotateInvert90();
        redRotateInvert90();
        yellowRotateInvert90();
        redRotate90();
      Serial.println("ya, ra, ya, rc");
    }
  
  
    else if(boyB == 1 && boyO == 2 && boyY == 3){
      // yc, ra, yc, rc
        yellowRotate90();
        redRotateInvert90();
        yellowRotate90();
        redRotate90();
      Serial.println("yc, ra, yc, rc");
    }
    else if(boyB == 2 && boyO == 3 && boyY == 1){
      // y180, ra, y180, rc, yc, ra, yc, rc << mistake, corrected below
      // y180, ra, y180, rc, yc, ra, ya, rc
        yellowRotate90();
        yellowRotate90();
        redRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        redRotate90();
        yellowRotate90();
        redRotateInvert90();
        yellowRotateInvert90();
        redRotate90();
      Serial.println("y180, ra, y180, rc, yc, ra, ya, rc");
    }
    else if(boyB == 3 && boyO == 1 && boyY == 2){
      // y180, ra, ya, rc
        yellowRotate90();
        yellowRotate90();
        redRotateInvert90();
        yellowRotateInvert90();
        redRotate90();
      Serial.println("y180, ra, ya, rc");
    }
  
    
    else if(ogyO == 1 && ogyG == 2 && ogyY == 3){
      // ra, yc, rc
        redRotateInvert90();
        yellowRotate90();
        redRotate90();
      Serial.println("ra, yc, rc");
    }
    else if(ogyO == 2 && ogyG == 3 && ogyY == 1){
      // yc, ra, y180, rc, yc, ra, ya, rc
        yellowRotate90();
        redRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        redRotate90();
        yellowRotate90();
        redRotateInvert90();
        yellowRotateInvert90();
        redRotate90();
      Serial.println("yc, ra, y180, rc, yc, ra, ya, rc");
    }
    else if(ogyO == 3 && ogyG == 1 && ogyY == 2){
      // yc, ra, ya, rc
        yellowRotate90();
        redRotateInvert90();
        yellowRotateInvert90();
        redRotate90();
      Serial.println("yc, ra, ya, rc");
    }
  
    
    else if(gryG == 1 && gryR == 2 && gryY == 3){
      // ya, ra, yc, rc
        yellowRotateInvert90();
        redRotateInvert90();
        yellowRotate90();
        redRotate90();
      Serial.println("ya, ra, yc, rc");
    }
    else if(gryG == 2 && gryR == 3 && gryY == 1){
      // ra, y180, rc, yc, ra, ya, rc
        redRotateInvert90();
        yellowRotate90();
        yellowRotate90();
        redRotate90();
        yellowRotate90();
        redRotateInvert90();
        yellowRotateInvert90();
        redRotate90();
      Serial.println("ra, y180, rc, yc, ra, ya, rc");
    }
    else{
      // ra, ya, rc
        redRotateInvert90();
        yellowRotateInvert90();
        redRotate90();
      Serial.println("ra, ya, rc");
    }
}

int rbPiece(){
    if(rbR == 2 && rbB == 4){
  }
  else if(rbR == 4 && rbB == 2){
    middleLayerAlgorithmRight(4);
    yellowRotate90();
    yellowRotate90();
    middleLayerAlgorithmRight(4);
  }
  else if(boB == 2 && boO == 4){
    middleLayerAlgorithmRight(6);
    middleLayerAlgorithmLeft(4);
  }
  else if(boB == 4 && boO == 2){
    middleLayerAlgorithmRight(6);
    yellowRotate90();    
    middleLayerAlgorithmRight(4);
  }
  else if(ogO == 2 && ogG == 4){
    middleLayerAlgorithmRight(3);
    yellowRotateInvert90();
    middleLayerAlgorithmLeft(4);
  }
  else if(ogO == 4 && ogG == 2){
    middleLayerAlgorithmRight(3);
    middleLayerAlgorithmRight(4);
  }
  else if(grG == 2 && grR == 4){
    middleLayerAlgorithmRight(2);
    yellowRotate90();
    yellowRotate90();
    middleLayerAlgorithmLeft(4);
  }
  else if(grG == 4 && grR == 2){
    middleLayerAlgorithmRight(2);
    yellowRotateInvert90();
    middleLayerAlgorithmRight(4);
  }
  else if(ryR == 2 && ryY == 4){
    middleLayerAlgorithmLeft(4);
  }
  else if(ryR == 4 && ryY == 2){
    yellowRotate90();
    middleLayerAlgorithmRight(4);
  }
  else if(byB == 2 && byY == 4){
    yellowRotateInvert90();
    middleLayerAlgorithmLeft(4);
  }
  else if(byB == 4 && byY == 2){
    middleLayerAlgorithmRight(4);
  }
  else if(oyO == 2 && oyY == 4){
    yellowRotate90();
    yellowRotate90();
    middleLayerAlgorithmLeft(4);
  }
  else if(oyO == 4 && oyY == 2){
    yellowRotateInvert90();
    middleLayerAlgorithmRight(4);
  }
  else if(gyG == 2 && gyY == 4){
    yellowRotate90();
    middleLayerAlgorithmLeft(4);
  }
  else{
    yellowRotate90();
    yellowRotate90();
    middleLayerAlgorithmRight(4);
  }
}

int boPiece(){
    if(boB == 4 && boO == 6){
  }
  else if(boB == 6 && boO == 4){
    middleLayerAlgorithmRight(6);
    yellowRotate90();
    yellowRotate90();
    middleLayerAlgorithmRight(6);
  }
  else if(ogO == 4 && ogG == 6){
    middleLayerAlgorithmRight(3);
    middleLayerAlgorithmLeft(6);
  }
  else if(ogO == 6 && ogG == 4){
    middleLayerAlgorithmRight(3);
    yellowRotate90();
    middleLayerAlgorithmRight(6);
  }
  else if(grG == 4 && grR == 6){
    middleLayerAlgorithmRight(6);
    yellowRotateInvert90();
    middleLayerAlgorithmLeft(6);
  }
  else if(grG == 6 && grR == 4){
    middleLayerAlgorithmRight(2);
    middleLayerAlgorithmRight(6);
  }
  else if(ryR == 4 && ryY == 6){
    yellowRotate90();
    middleLayerAlgorithmLeft(6);
  }
  else if(ryR == 6 && ryY == 4){
    yellowRotate90();
    yellowRotate90();
    middleLayerAlgorithmRight(6);
  }
  else if(byB == 4 && byY == 6){
    middleLayerAlgorithmLeft(6);
  }
  else if(byB == 6 && byY == 4){
    yellowRotate90();
    middleLayerAlgorithmRight(6);
  }
  else if(oyO == 4 && oyY == 6){
    yellowRotateInvert90();
    middleLayerAlgorithmLeft(6);
  }
  else if(oyO == 6 && oyY == 4){
    middleLayerAlgorithmRight(6);
  }
  else if(gyG == 4 && gyY == 6){
    yellowRotate90();
    yellowRotate90();
    middleLayerAlgorithmLeft(6);
  }
  else{
    yellowRotateInvert90();
    middleLayerAlgorithmRight(6);
  }
}

int ogPiece(){
  if(ogO == 6 && ogG == 3){
  }
  else if(ogO == 3 && ogG == 6){
    middleLayerAlgorithmRight(3);
    yellowRotate90();
    yellowRotate90();
    middleLayerAlgorithmRight(3);
  }
  else if(grG == 6 && grR == 3){
    middleLayerAlgorithmRight(2);
    middleLayerAlgorithmLeft(3);
  }
  else if(grG == 3 && grR == 6){
    middleLayerAlgorithmRight(2);
    yellowRotate90();
    middleLayerAlgorithmRight(3);
  }
  else if(ryR == 6 && ryY == 3){
    yellowRotate90();
    yellowRotate90();
    middleLayerAlgorithmLeft(3);
  }
  else if(ryR == 3 && ryY == 6){
    yellowRotateInvert90();
    middleLayerAlgorithmRight(3);
  }
  else if(byB == 6 && byY == 3){
    yellowRotate90();
    middleLayerAlgorithmLeft(3);
  }
  else if(byB == 3 && byY == 6){
    yellowRotate90();
    yellowRotate90();
    middleLayerAlgorithmRight(3);
  }
  else if(oyO == 6 && oyY == 3){
    middleLayerAlgorithmLeft(3);
  }
  else if(oyO == 3 && oyY == 6){
    yellowRotate90();
    middleLayerAlgorithmRight(3);
  }
  else if(gyG == 6 && gyY == 3){
    yellowRotateInvert90();
    middleLayerAlgorithmLeft(3);
  }
  else{
    middleLayerAlgorithmRight(3);
  }
}

int grPiece(){
    if(grG == 3 && grR == 2){
  }
  else if(grG == 2 && grR == 3){
    middleLayerAlgorithmRight(2);
    yellowRotate90();
    yellowRotate90();
    middleLayerAlgorithmRight(2);
  }
  else if(ryR == 3 && ryY == 2){
    yellowRotateInvert90();
    middleLayerAlgorithmLeft(2);
  }
  else if(ryR == 2 && ryY == 3){
    middleLayerAlgorithmRight(2);
  }
  else if(byB == 3 && byY == 2){
    yellowRotate90();
    yellowRotate90();
    middleLayerAlgorithmLeft(2);
  }
  else if(byB == 2 && byY == 3){
    yellowRotateInvert90();
    middleLayerAlgorithmRight(2);
  }
  else if(oyO == 3 && oyY == 2){
    yellowRotate90();
    middleLayerAlgorithmLeft(2);
  }
  else if(oyO == 2 && oyY == 3){
    yellowRotate90();
    yellowRotate90();
    middleLayerAlgorithmRight(2);
  }
  else if(gyG == 3 && gyY == 2){
    middleLayerAlgorithmLeft(2);
  }
  else{
    yellowRotate90();
    middleLayerAlgorithmRight(2);
  }
}

int middleLayerAlgorithmRight(int x){
  // u, r, ui, ri, ui, fi, u, f
  if(x == 2){
    // yc, gc, ya, ga, ya, ra, yc, rc
      yellowRotate90();
      greenRotate90();
      yellowRotateInvert90();
      greenRotateInvert90();
      yellowRotateInvert90();
      redRotateInvert90();
      yellowRotate90();
      redRotate90();
  }
  else if(x == 3){
    // yc, oc, ya, oa, ya, ga, yc, gc
      yellowRotate90();
      orangeRotate90();
      yellowRotateInvert90();
      orangeRotateInvert90();
      yellowRotateInvert90();
      greenRotateInvert90();
      yellowRotate90();
      greenRotate90();
  }
  else if(x == 4){
    // yc, rc, ya, ra, ya, ba, yc, bc
      yellowRotate90();
      redRotate90();
      yellowRotateInvert90();
      redRotateInvert90();
      yellowRotateInvert90();
      blueRotateInvert90();
      yellowRotate90();
      blueRotate90();
  }
  else if(x == 6){
    // yc, bc, ya, ba, ya, oa, yc, oc
      yellowRotate90();
      blueRotate90();
      yellowRotateInvert90();
      blueRotateInvert90();
      yellowRotateInvert90();
      orangeRotateInvert90();
      yellowRotate90();
      orangeRotate90();
  }
}

int middleLayerAlgorithmLeft(int x){
  // ui, fi, u, f, u, r, ui, ri
  if(x == 2){
    // ya, ra, yc, rc, yc, gc, ya, ga
      yellowRotateInvert90();
      redRotateInvert90();
      yellowRotate90();
      redRotate90();
      yellowRotate90();
      greenRotate90();
      yellowRotateInvert90();
      greenRotateInvert90();
  }
  else if(x == 3){
    // ya, ga, yc, gc, yc, oc, ya, oa
      yellowRotateInvert90();
      greenRotateInvert90();
      yellowRotate90();
      greenRotate90();
      yellowRotate90();
      orangeRotate90();
      yellowRotateInvert90();
      orangeRotateInvert90();
  }
  else if(x == 4){
    // ya, ba, yc, bc, yc, rc, ya, ra
      yellowRotateInvert90();
      blueRotateInvert90();
      yellowRotate90();
      blueRotate90();
      yellowRotate90();
      redRotate90();
      yellowRotateInvert90();
      redRotateInvert90();
  }
  else if(x == 6){
    // ya, oa, yc, oc, yc, bc, ya, ba
      yellowRotateInvert90();
      orangeRotateInvert90();
      yellowRotate90();
      orangeRotate90();
      yellowRotate90();
      blueRotate90();
      yellowRotateInvert90();
      blueRotateInvert90();
  }
}

int yellowCross(){
    if(ryY == 5 && byY == 5 && oyY == 5 && gyY == 5){
  }
  else if(ryY == 5 && byY == 5 && oyY != 5 && gyY != 5){
    yellowCrossAlgorithm(3);
    yellowCrossAlgorithm(3);
  }
  else if(ryY != 5 && byY == 5 && oyY == 5 && gyY != 5){
    yellowCrossAlgorithm(2);
    yellowCrossAlgorithm(2);
  }
  else if(ryY != 5 && byY != 5 && oyY == 5 && gyY == 5){
    yellowCrossAlgorithm(4);
    yellowCrossAlgorithm(4);
  }
  else if(ryY == 5 && byY != 5 && oyY != 5 && gyY == 5){
    yellowCrossAlgorithm(6);
    yellowCrossAlgorithm(6);
  }

  
  else if(ryY == 5 && byY != 5 && oyY == 5 && gyY != 5){
    yellowCrossAlgorithm(4);
  }
  else if(ryY != 5 && byY == 5 && oyY != 5 && gyY == 5){
    yellowCrossAlgorithm(2);
  }

  
  else if(ryY != 5 && byY != 5 && oyY != 5 && gyY != 5){
    yellowCrossAlgorithm(2);
    yellowCrossAlgorithm(6);
    yellowCrossAlgorithm(6);
  }
}

int yellowCrossAlgorithm(int x){
  // f, r, u, ri, ui, fi

  if(x == 2){
    // rc, gc, yc, ga, ya, ra
      redRotate90();
      greenRotate90();
      yellowRotate90();
      greenRotateInvert90();
      yellowRotateInvert90();
      redRotateInvert90();
  }
  if(x == 4){
    // bc, rc, yc, ra, ya, ba
      blueRotate90();
      redRotate90();
      yellowRotate90();
      redRotateInvert90();
      yellowRotateInvert90();
      blueRotateInvert90();
  }
  if(x == 6){
    // oc, bc, yc, ba, ya, oa
      orangeRotate90();
      blueRotate90();
      yellowRotate90();
      blueRotateInvert90();
      yellowRotateInvert90();
      orangeRotateInvert90();
  }
  if(x == 3){
    // gc, oc, yc, oa, ya, ga
      greenRotate90();
      orangeRotate90();
      yellowRotate90();
      orangeRotateInvert90();
      yellowRotateInvert90();
      greenRotateInvert90();
  }
}

int yellowMiddles(){
    if(ryR == 2 && byB == 4 && oyO == 6 && gyG == 3){
    }
  else if(ryR == 2 && byB == 4 && oyO == 3 && gyG == 6){
    yellowMiddlesAlgorithm(6);
    yellowRotate90();
    Serial.print("yc");
  }
  else if(ryR == 6 && byB == 2 && oyO == 4 && gyG == 3){
    yellowRotateInvert90();
    Serial.println("ya");
    yellowMiddlesAlgorithm(6);
    yellowRotate90();
    Serial.print("yc");
  }
  else if(ryR == 3 && byB == 6 && oyO == 2 && gyG == 4){
    yellowRotate90();
    yellowRotate90();
    Serial.println("y180");
    yellowMiddlesAlgorithm(6);
    yellowRotate90();
    Serial.print("yc");
  }  
  else if(ryR == 4 && byB == 3 && oyO == 6 && gyG == 2){
    yellowRotate90();
    Serial.println("yc");
    yellowMiddlesAlgorithm(6);
    yellowRotate90();
    Serial.print("yc");
  }


  else if(ryR == 3 && byB == 4 && oyO == 6 && gyG == 2){
    yellowMiddlesAlgorithm(3);
    yellowRotate90();
    Serial.print("yc");
  }
  else if(ryR == 2 && byB == 3 && oyO == 4 && gyG == 6){
    yellowRotateInvert90();
    Serial.println("ya");
    yellowMiddlesAlgorithm(3);
    yellowRotate90();
    Serial.print("yc");
  }
  else if(ryR == 6 && byB == 2 && oyO == 3 && gyG == 4){
    yellowRotate90();
    yellowRotate90();
    Serial.println("y180");
    yellowMiddlesAlgorithm(3);
    yellowRotate90();
    Serial.print("yc");
  }
  else if(ryR == 4 && byB == 6 && oyO == 2 && gyG == 3){
    yellowRotate90();
    Serial.println("yc");
    yellowMiddlesAlgorithm(3);
    yellowRotate90();
    Serial.print("yc");
  }


  
  else if(ryR == 4 && byB == 2 && oyO == 6 && gyG == 3){
    yellowMiddlesAlgorithm(2);
    yellowRotate90();
    Serial.print("yc");
  }
  else if(ryR == 3 && byB == 4 && oyO == 2 && gyG == 6){
    yellowRotateInvert90();
    Serial.println("ya");
    yellowMiddlesAlgorithm(2);
    yellowRotate90();
    Serial.print("yc");
  }
  else if(ryR == 6 && byB == 3 && oyO == 4 && gyG == 2){
    yellowRotate90();
    yellowRotate90();
    Serial.print("y180");
    yellowMiddlesAlgorithm(2);
    yellowRotate90();
    Serial.print("yc");
  }
  else if(ryR == 2 && byB == 6 && oyO == 3 && gyG == 4){
    yellowRotate90();
    Serial.println("yc");
    yellowMiddlesAlgorithm(2);
    yellowRotate90();
    Serial.print("yc");
  }


  
  else if(ryR == 2 && byB == 6 && oyO == 4 && gyG == 3){
    yellowMiddlesAlgorithm(4);
    yellowRotate90();
    Serial.print("yc");
  }
  else if(ryR == 3 && byB == 2 && oyO == 6 && gyG == 4){
    yellowRotateInvert90();
    Serial.println("ya");
    yellowMiddlesAlgorithm(4);
    yellowRotate90();
    Serial.print("yc");
  }
  else if(ryR == 4 && byB == 3 && oyO == 2 && gyG == 6){
    yellowRotate90();
    yellowRotate90();
    Serial.println("y180");
    yellowMiddlesAlgorithm(4);
    yellowRotate90();
    Serial.print("yc");
  }
  else if(ryR == 6 && byB == 4 && oyO == 3 && gyG == 2){
    yellowRotate90();
    Serial.println("yc");
    yellowMiddlesAlgorithm(4);
    yellowRotate90();
    Serial.print("yc");
  }


  else if(ryR == 2 && byB == 3 && oyO == 6 && gyG == 4){
    yellowMiddlesAlgorithm(2);
    yellowMiddlesAlgorithm(4);
    yellowRotate90();
    Serial.println("yc");
  }
  else if(ryR == 4 && byB == 2 && oyO == 3 && gyG == 6){
    yellowRotateInvert90();
    Serial.println("ya");
    yellowMiddlesAlgorithm(2);
    yellowMiddlesAlgorithm(4);
    yellowRotate90();
    Serial.print("yc");
  }
  else if(ryR == 6 && byB == 4 && oyO == 2 && gyG == 3){
    yellowRotate90();
    yellowRotate90();
    Serial.println("y180");
    yellowMiddlesAlgorithm(2);
    yellowMiddlesAlgorithm(4);
    yellowRotate90();
    Serial.print("yc");
  }
  else if(ryR == 3 && byB == 6 && oyO == 4 && gyG == 2){
    yellowRotate90();
    Serial.println("yc");
    yellowMiddlesAlgorithm(2);
    yellowMiddlesAlgorithm(4);
    yellowRotate90();
    Serial.print("yc");
  }
}

int yellowMiddlesAlgorithm(int x){
    // r, u, ri, u, r, u, u, ri
    if(x == 2){
      // gc, yc, ga, yc, gc, y180, ga
      greenRotate90();
      yellowRotate90();
      greenRotateInvert90();
      yellowRotate90();
      greenRotate90();
      yellowRotate90();
      yellowRotate90();
      greenRotateInvert90();
      Serial.print("gc, yc, ga, yc, gc, y180, ga");
    }
    else if(x == 4){
      // rc, yc, ra, yc, rc, y180, ra
      redRotate90();
      yellowRotate90();
      redRotateInvert90();
      yellowRotate90();
      redRotate90();
      yellowRotate90();
      yellowRotate90();
      redRotateInvert90();
      Serial.print("rc, yc, ra, yc, rc, y180, ra");
    }
    else if(x == 6){
      // bc, yc, ba, yc, bc, y180, ba
      blueRotate90();
      yellowRotate90();
      blueRotateInvert90();
      yellowRotate90();
      blueRotate90();
      yellowRotate90();
      yellowRotate90();
      blueRotateInvert90();
      Serial.print("bc, yc, ba, yc, bc, y180, ba");
    }
    else if(x == 3){
      // oc, yc, oa, yc, oc, y180, oa
      orangeRotate90();
      yellowRotate90();
      orangeRotateInvert90();
      yellowRotate90();
      orangeRotate90();
      yellowRotate90();
      yellowRotate90();
      orangeRotateInvert90();
      Serial.print("oc, yc, oa, yc, oc, y180, oa");
    }
}

int cornerPieces(){
    for(int z = 0; z < 3; z++){
      if( ((rbyR != 6 && rbyR != 3) && (rbyB != 6 && rbyB != 3) && (rbyY != 6 && rbyY != 3)) 
      &&  ((boyB != 2 && boyB != 3) && (boyO != 2 && boyO != 3) && (boyY != 2 && boyY != 3)) ){
        // Nothing happens
      }
    else if( ((rbyR != 6 && rbyR != 3) && (rbyB != 6 && rbyB != 3) && (rbyY != 6 && rbyY != 3)) 
      &&  ((boyB == 2 || boyB == 3) || (boyO != 2 || boyO != 3) || (boyY != 2 || boyY != 3)) ){
        cornerAlgorithm(4);
      }
    else if( ((boyB != 2 && boyB != 3) && (boyO != 2 && boyO != 3) && (boyY != 2 && boyY != 3)) 
      &&  ((rbyR == 6 || rbyR == 3) || (rbyB == 6 || rbyB == 3) || (rbyY == 6 || rbyY == 3)) ){
        cornerAlgorithm(6);
      }
    else if( ((ogyO != 2 && ogyO != 4) && (ogyG != 2 && ogyG != 4) && (ogyY != 2 && ogyY != 4)) 
      &&  ((rbyR == 6 || rbyR == 3) || (rbyB == 6 || rbyB == 3) || (rbyY == 6 || rbyY == 3)) ){
        cornerAlgorithm(3);
      }
    else if( ((gryG != 6 && gryG != 4) && (gryR != 6 && gryR != 4) && (gryY != 6 && gryY != 4)) 
      &&  ((rbyR == 6 || rbyR == 3) || (rbyB == 6 || rbyB == 3) || (rbyY == 6 || rbyY == 3)) ){
        cornerAlgorithm(2);
      }
    else{
      cornerAlgorithm(2);
      }
      Serial.println("+");
  }
}

int cornerAlgorithm(int x){
    // u, r, ui, li, u, ri, ui, l
  if(x == 2){
    // yc, gc, ya, ba, yc, ga, ya, bc
      yellowRotate90();
      greenRotate90();
      yellowRotateInvert90();
      blueRotateInvert90();
      yellowRotate90();
      greenRotateInvert90();
      yellowRotateInvert90();
      blueRotate90();
    Serial.println("yc, gc, ya, ba, yc, ga, ya, bc");
  }
  else if(x == 4){
    // yc, rc, ya, oa, yc, ra, ya, oc
      yellowRotate90();
      redRotate90();
      yellowRotateInvert90();
      orangeRotateInvert90();
      yellowRotate90();
      redRotateInvert90();
      yellowRotateInvert90();
      orangeRotate90();
      Serial.println("yc, rc, ya, oa, yc, ra, ya, oc");
  }
  else if(x == 6){
    // yc, bc, ya, ga, yc, ba, ya, gc
      yellowRotate90();
      blueRotate90();
      yellowRotateInvert90();
      greenRotateInvert90();
      yellowRotate90();
      blueRotateInvert90();
      yellowRotateInvert90();
      greenRotate90();
      Serial.println("yc, bc, ya, ga, yc, ba, ya, gc");
  }
  else if(x == 3){
    // yc, oc, ya, ra, yc, oa, ya, rc
      yellowRotate90();
      orangeRotate90();
      yellowRotateInvert90();
      redRotateInvert90();
      yellowRotate90();
      orangeRotateInvert90();
      yellowRotateInvert90();
      redRotate90();
      Serial.println("yc, oc, ya, ra, yc, oa, ya, rc");
  }
}

int cornerRotation(){
  for(int a = 0; a < 6; a++){
    if(rbyY == 5 && boyY == 5 && ogyY == 5 && gryY == 5){
    // Nothing
  }
  else if(rbyY != 5){
    cornerRotateAlgorithm();
    cornerRotateAlgorithm();
    Serial.println("ga, wa, gc, wc, ga, wa, gc, wc");
  }
  else if(boyY != 5){
    yellowRotateInvert90();
    cornerRotateAlgorithm();
    cornerRotateAlgorithm();
    yellowRotate90();
    Serial.println("ya, ga, wa, gc, wc, ga, wa, gc, wc, yc");
  }
  else if(ogyY != 5){
    yellowRotate90();
    yellowRotate90();
    cornerRotateAlgorithm();
    cornerRotateAlgorithm();
    yellowRotate90();
    yellowRotate90();
    Serial.println("y180, ga, wa, gc, wc, ga, wa, gc, wc, y180");
  }
  else if(gryY != 5){
    yellowRotate90();
    cornerRotateAlgorithm();
    cornerRotateAlgorithm();
    yellowRotateInvert90();
    Serial.println("yc, ga, wa, gc, wc, ga, wa, gc, wc, ya");
  }
      Serial.println("+");
}
}

int cornerRotateAlgorithm(){
  // ri, di, r, d
    // ra, wa, rc, wc
      redRotateInvert90();
      whiteRotateInvert90();
      redRotate90();
      whiteRotate90();
}

int whiteRotate90(){
    digitalWrite(dirPinWhite, LOW);
    for(int x = 0; x < 200/4; x++){
      digitalWrite(stepPinWhite, HIGH);
      delayMicroseconds(motorSpeed);
      digitalWrite(stepPinWhite, LOW);
      delayMicroseconds(motorSpeed);
    }
    white90ColourReshuffle();
    delay(50);
}

int whiteRotateInvert90(){
    digitalWrite(dirPinWhite, HIGH);
    for(int x = 0; x < 200/4; x++){
      digitalWrite(stepPinWhite, HIGH);
      delayMicroseconds(motorSpeed);
      digitalWrite(stepPinWhite, LOW);
      delayMicroseconds(motorSpeed);
    }
    whiteInvert90ColourReshuffle();
    delay(50);
}

int redRotate90(){
    digitalWrite(dirPinRed, LOW);
    for(int x = 0; x < 200/4; x++){
      digitalWrite(stepPinRed, HIGH);
      delayMicroseconds(motorSpeed);
      digitalWrite(stepPinRed, LOW);
        delayMicroseconds(motorSpeed);
    }
    red90ColourReshuffle();
    delay(50);
}

int redRotateInvert90(){
    digitalWrite(dirPinRed, HIGH);
    for(int x = 0; x < 200/4; x++){
      digitalWrite(stepPinRed, HIGH);
      delayMicroseconds(motorSpeed);
      digitalWrite(stepPinRed, LOW);
      delayMicroseconds(motorSpeed);
    }
    redInvert90ColourReshuffle();
    delay(50);
}

int greenRotate90(){
    digitalWrite(dirPinGreen, LOW);
    for(int x = 0; x < 200/4; x++){
      digitalWrite(stepPinGreen, HIGH);
      delayMicroseconds(motorSpeed);
      digitalWrite(stepPinGreen, LOW);
      delayMicroseconds(motorSpeed);
    }
    green90ColourReshuffle();
    delay(50);
}

int greenRotateInvert90(){
    digitalWrite(dirPinGreen, HIGH);
    for(int x = 0; x < 200/4; x++){
      digitalWrite(stepPinGreen, HIGH);
      delayMicroseconds(motorSpeed);
      digitalWrite(stepPinGreen, LOW);
      delayMicroseconds(motorSpeed);
    }
    greenInvert90ColourReshuffle();
    delay(50);
}

int blueRotate90(){
    digitalWrite(dirPinBlue, LOW);
    for(int x = 0; x < 200/4; x++){
      digitalWrite(stepPinBlue, HIGH);
      delayMicroseconds(motorSpeed);
      digitalWrite(stepPinBlue, LOW);
      delayMicroseconds(motorSpeed);
    }
    blue90ColourReshuffle();
    delay(50);
}

int blueRotateInvert90(){
    digitalWrite(dirPinBlue, HIGH);
    for(int x = 0; x < 200/4; x++){
      digitalWrite(stepPinBlue, HIGH);
      delayMicroseconds(motorSpeed);
      digitalWrite(stepPinBlue, LOW);
      delayMicroseconds(motorSpeed);
    }
    blueInvert90ColourReshuffle();
    delay(50);
}

int yellowRotate90(){
    digitalWrite(dirPinYellow, LOW);
    for(int x = 0; x < 200/4; x++){
      digitalWrite(stepPinYellow, HIGH);
      delayMicroseconds(motorSpeed);
      digitalWrite(stepPinYellow, LOW);
      delayMicroseconds(motorSpeed);
    }
    yellow90ColourReshuffle();
    delay(50);
}

int yellowRotateInvert90(){
    digitalWrite(dirPinYellow, HIGH);
    for(int x = 0; x < 200/4; x++){
      digitalWrite(stepPinYellow, HIGH);
      delayMicroseconds(motorSpeed);
      digitalWrite(stepPinYellow, LOW);
      delayMicroseconds(motorSpeed);
    }
    yellowInvert90ColourReshuffle();
    delay(50);
    
}

int orangeRotate90(){
    digitalWrite(dirPinOrange, LOW);
    for(int x = 0; x < 200/4; x++){
      digitalWrite(stepPinOrange, HIGH);
      delayMicroseconds(motorSpeed);
      digitalWrite(stepPinOrange, LOW);
      delayMicroseconds(motorSpeed);
    }
    orange90ColourReshuffle();
    delay(50);
}

int orangeRotateInvert90(){
    digitalWrite(dirPinOrange, HIGH);
    for(int x = 0; x < 200/4; x++){
      digitalWrite(stepPinOrange, HIGH);
      delayMicroseconds(motorSpeed);
      digitalWrite(stepPinOrange, LOW);
      delayMicroseconds(motorSpeed);
    }
    orangeInvert90ColourReshuffle();
    delay(50);
}


int buttonColourAssignment(){

    int whiteButtonCond = digitalRead(whiteButton);
    int redButtonCond = digitalRead(redButton);
    int greenButtonCond = digitalRead(greenButton);
    int blueButtonCond = digitalRead(blueButton);
    int yellowButtonCond = digitalRead(yellowButton);
    int orangeButtonCond = digitalRead(orangeButton);
    int colour;
    
    while(whiteButtonCond == HIGH && redButtonCond == HIGH && greenButtonCond == HIGH && blueButtonCond == HIGH && yellowButtonCond == HIGH && orangeButtonCond == HIGH){
      
    whiteButtonCond = digitalRead(whiteButton);
    redButtonCond = digitalRead(redButton);
    greenButtonCond = digitalRead(greenButton);
    blueButtonCond = digitalRead(blueButton);
    yellowButtonCond = digitalRead(yellowButton);
    orangeButtonCond = digitalRead(orangeButton);
    }

    // Using white = 1, red = 2, green = 3, blue = 4, yellow = 5, orange = 6
    
    if(whiteButtonCond == LOW){
      colour = 1;
    }
    if(redButtonCond == LOW){
      colour = 2;
    }
    if(greenButtonCond == LOW){
      colour = 3;
    }
    if(blueButtonCond == LOW){
      colour = 4;
    }
    if(yellowButtonCond == LOW){
      colour = 5;
    }
    if(orangeButtonCond == LOW){
      colour = 6;
    }
    delay(300);
    return colour;
}

int white90ColourReshuffle(){
  int val = wogW;
  wogW = wgrW;
  wgrW = wrbW;
  wrbW = wboW;
  wboW = val;

  int val2 = wogO;
  wogO = wgrG;
  wgrG = wrbR;
  wrbR = wboB;
  wboB = val2;

  int val3 = wogG;
  wogG = wgrR;
  wgrR = wrbB;
  wrbB = wboO;
  wboO = val3;

  int val4 = woW;
  woW = wgW;
  wgW = wrW;
  wrW = wbW;
  wbW = val4;

  int val5 = woO;
  woO = wgG;
  wgG = wrR;
  wrR = wbB;
  wbB = val5;
}

int whiteInvert90ColourReshuffle(){
  int val = wgrW;
  wgrW = wogW;
  wogW = wboW;
  wboW = wrbW;
  wrbW = val;

  int val2 = wgrG;
  wgrG = wogO;
  wogO = wboB;
  wboB = wrbR;
  wrbR = val2;

  int val3 = wgrR;
  wgrR = wogG;
  wogG = wboO;
  wboO = wrbB;
  wrbB = val3;

  int val4 = woW;
  woW = wbW;
  wbW = wrW;
  wrW = wgW;
  wgW = val4;

  int val5 = woO;
  woO = wbB;
  wbB = wrR;
  wrR = wgG;
  wgG = val5;
}

int red90ColourReshuffle(){
  int val = wgrR;
  wgrR = gryR;
  gryR = rbyR;
  rbyR = wrbR;
  wrbR = val;

  int val2 = wgrW;
  wgrW = gryG;
  gryG = rbyY;
  rbyY = wrbB;
  wrbB = val2;  

  int val3 = wgrG;
  wgrG = gryY;
  gryY = rbyB;
  rbyB = wrbW;
  wrbW = val3;

  int val4 = wrR;
  wrR = grR;
  grR = ryR;
  ryR = rbR;
  rbR = val4;

  int val5 = wrW;
  wrW = grG;
  grG = ryY;
  ryY = rbB;
  rbB = val5;
}

int redInvert90ColourReshuffle(){
  int val = wgrR;
  wgrR = wrbR;
  wrbR = rbyR;
  rbyR = gryR;
  gryR = val;

  int val2 = wgrW;
  wgrW = wrbB;
  wrbB = rbyY;
  rbyY = gryG;
  gryG = val2;

  int val3 = wgrG;
  wgrG = wrbW;
  wrbW = rbyB;
  rbyB = gryY;
  gryY = val3;

  int val4 = wrR;
  wrR = rbR;
  rbR = ryR;
  ryR = grR;
  grR = val4;

  int val5 = wrW;
  wrW = rbB;
  rbB = ryY;
  ryY = grG;
  grG = val5;
}

int green90ColourReshuffle(){
  int val = wogG;
  wogG = ogyG;
  ogyG = gryG;
  gryG = wgrG;
  wgrG = val;

  int val2 = wogW;
  wogW = ogyO;
  ogyO = gryY;
  gryY = wgrR;
  wgrR = val2;

  int val3 = wogO;
  wogO = ogyY;
  ogyY = gryR;
  gryR = wgrW;
  wgrW = val3;

  int val4 = wgG;
  wgG = ogG;
  ogG = gyG;
  gyG = grG;
  grG = val4;

  int val5 = wgW;
  wgW = ogO;
  ogO = gyY;
  gyY = grR;
  grR = val5;
}

int greenInvert90ColourReshuffle(){
  int val = wogG;
  wogG = wgrG;
  wgrG = gryG;
  gryG = ogyG;
  ogyG = val;

  int val2 = wogW;
  wogW = wgrR;
  wgrR = gryY;
  gryY = ogyO;
  ogyO = val2;

  int val3 = wogO;
  wogO = wgrW;
  wgrW = gryR;
  gryR = ogyY;
  ogyY = val3;

  int val4 = wgG;
  wgG = grG;
  grG = gyG;
  gyG = ogG;
  ogG = val4;

  int val5 = wgW;
  wgW = grR;
  grR = gyY;
  gyY = ogO;
  ogO = val5;
}

int blue90ColourReshuffle(){
  int val = wrbB;
  wrbB = rbyB;
  rbyB = boyB;
  boyB = wboB;
  wboB = val;

  int val2 = wrbW;
  wrbW = rbyR;
  rbyR = boyY;
  boyY = wboO;
  wboO = val2;

  int val3 = wrbR;
  wrbR = rbyY;
  rbyY = boyO;
  boyO = wboW;
  wboW = val3;

  int val4 = wbB;
  wbB = rbB;
  rbB = byB;
  byB = boB;
  boB = val4;

  int val5 = wbW;
  wbW = rbR;
  rbR = byY;
  byY = boO;
  boO = val5;
}

int blueInvert90ColourReshuffle(){
  int val = wrbB;
  wrbB = wboB;
  wboB = boyB;
  boyB = rbyB;
  rbyB = val;

  int val2 = wrbW;
  wrbW = wboO;
  wboO = boyY;
  boyY = rbyR;
  rbyR = val2;

  int val3 = wrbR;
  wrbR = wboW;
  wboW = boyO;
  boyO = rbyY;
  rbyY = val3;

  int val4 = wbB;
  wbB = boB;
  boB = byB;
  byB = rbB;
  rbB = val4;

  int val5 = wbW;
  wbW = boO;
  boO = byY;
  byY = rbR;
  rbR = val5;
}

int yellow90ColourReshuffle(){
  int val = gryY;
  gryY = ogyY;
  ogyY = boyY;
  boyY = rbyY;
  rbyY = val;

  int val2 = gryR;
  gryR = ogyG;
  ogyG = boyO;
  boyO = rbyB;
  rbyB = val2;

  int val3 = gryG;
  gryG = ogyO;
  ogyO = boyB;
  boyB = rbyR;
  rbyR = val3;

  int val4 = ryY;
  ryY = gyY;
  gyY = oyY;
  oyY = byY;
  byY = val4;

  int val5 = ryR;
  ryR = gyG;
  gyG = oyO;
  oyO = byB;
  byB = val5;
}

int yellowInvert90ColourReshuffle(){
  int val = gryY;
  gryY = rbyY;
  rbyY = boyY;
  boyY = ogyY;
  ogyY = val;

  int val2 = gryR;
  gryR = rbyB;
  rbyB = boyO;
  boyO = ogyG;
  ogyG = val2;

  int val3 = gryG;
  gryG = rbyR;
  rbyR = boyB;
  boyB = ogyO;
  ogyO = val3;

  int val4 = ryY;
  ryY = byY;
  byY = oyY;
  oyY = gyY;
  gyY = val4;

  int val5 = ryR;
  ryR = byB;
  byB = oyO;
  oyO = gyG;
  gyG = val5;
}

int orange90ColourReshuffle(){
  int val = wboO;
  wboO = boyO;
  boyO = ogyO;
  ogyO = wogO;
  wogO = val;

  int val2 = wboW;
  wboW = boyB;
  boyB = ogyY;
  ogyY = wogG;
  wogG = val2;

  int val3 = wboB;
  wboB = boyY;
  boyY = ogyG;
  ogyG = wogW;
  wogW = val3;

  int val4 = woO;
  woO = boO;
  boO = oyO;
  oyO = ogO;
  ogO = val4;

  int val5 = woW;
  woW = boB;
  boB = oyY;
  oyY = ogG;
  ogG = val5;
}

int orangeInvert90ColourReshuffle(){
  int val = wboO;
  wboO = wogO;
  wogO = ogyO;
  ogyO = boyO;
  boyO = val;

  int val2 = wboW;
  wboW = wogG;
  wogG = ogyY;
  ogyY = boyB;
  boyB = val2;

  int val3 = wboB;
  wboB = wogW;
  wogW = ogyG;
  ogyG = boyY;
  boyY = val3;

  int val4 = woO;
  woO = ogO;
  ogO = oyO;
  oyO = boO;
  boO = val4;

  int val5 = woW;
  woW = ogG;
  ogG = oyY;
  oyY = boB;
  boB = val5;
}

int buttonColourAllocation(){
      // Allocate colours to all the squares with the buttons
    wogW = buttonColourAssignment();
    Serial.print("wogW = ");
    Serial.println(wogW);
    woW = buttonColourAssignment();
    Serial.print("woW = ");
    Serial.println(woW);
    wboW = buttonColourAssignment();
    Serial.print("wboW = ");
    Serial.println(wboW);
    wgW = buttonColourAssignment();
    Serial.print("wgW = ");
    Serial.println(wgW);
    wbW = buttonColourAssignment();
    Serial.print("wbW = ");
    Serial.println(wbW);
    wgrW = buttonColourAssignment();
    Serial.print("wgrW = ");
    Serial.println(wgrW);
    wrW = buttonColourAssignment();
    Serial.print("wrW = ");
    Serial.println(wrW);
    wrbW = buttonColourAssignment();
    Serial.print("wrbW = ");
    Serial.println(wrbW);
    wgrR = buttonColourAssignment();
    Serial.print("wgrR = ");
    Serial.println(wgrR);
    wrR = buttonColourAssignment();
    Serial.print("wrR = ");
    Serial.println(wrR);
    wrbR = buttonColourAssignment();
    Serial.print("wrbR = ");
    Serial.println(wrbR);
    grR = buttonColourAssignment();
    Serial.print("grR = ");
    Serial.println(grR);
    rbR = buttonColourAssignment();
    Serial.print("rbR = ");
    Serial.println(rbR);
    gryR = buttonColourAssignment();
    Serial.print("gryR = ");
    Serial.println(gryR);
    ryR = buttonColourAssignment();
    Serial.print("ryR = ");
    Serial.println(ryR);
    rbyR = buttonColourAssignment();
    Serial.print("rbyR = ");
    Serial.println(rbyR);
    wrbB = buttonColourAssignment();
    Serial.print("wrbB = ");
    Serial.println(wrbB);
    wbB = buttonColourAssignment();
    Serial.print("wbB = ");
    Serial.println(wbB);
    wboB = buttonColourAssignment();
    Serial.print("wboB = ");
    Serial.println(wboB);
    rbB = buttonColourAssignment();
    Serial.print("rbB = ");
    Serial.println(rbB);
    boB = buttonColourAssignment();
    Serial.print("boB = ");
    Serial.println(boB);
    rbyB = buttonColourAssignment();
    Serial.print("rbyB = ");
    Serial.println(rbyB);
    byB = buttonColourAssignment();
    Serial.print("byB = ");
    Serial.println(byB);
    boyB = buttonColourAssignment();
    Serial.print("boyB = ");
    Serial.println(boyB);
    wboO = buttonColourAssignment();
    Serial.print("wboO = ");
    Serial.println(wboO);
    woO = buttonColourAssignment();
    Serial.print("woO = ");
    Serial.println(woO);
    wogO = buttonColourAssignment();
    Serial.print("wogO = ");
    Serial.println(wogO);
    boO = buttonColourAssignment();
    Serial.print("boO = ");
    Serial.println(boO);
    ogO = buttonColourAssignment();
    Serial.print("ogO = ");
    Serial.println(ogO);
    boyO = buttonColourAssignment();
    Serial.print("boyO = ");
    Serial.println(boyO);
    oyO = buttonColourAssignment();
    Serial.print("oyO = ");
    Serial.println(oyO);
    ogyO = buttonColourAssignment();
    Serial.print("ogyO = ");
    Serial.println(ogyO);
    wogG = buttonColourAssignment();
    Serial.print("wogG = ");
    Serial.println(wogG);
    wgG = buttonColourAssignment();
    Serial.print("wgG = ");
    Serial.println(wgG);
    wgrG = buttonColourAssignment();
    Serial.print("wgrG = ");
    Serial.println(wgrG);
    ogG = buttonColourAssignment();
    Serial.print("ogG = ");
    Serial.println(ogG);
    grG = buttonColourAssignment();
    Serial.print("grG = ");
    Serial.println(grG);
    ogyG = buttonColourAssignment();
    Serial.print("ogyG = ");
    Serial.println(ogyG);
    gyG = buttonColourAssignment();
    Serial.print("gyG = ");
    Serial.println(gyG);
    gryG = buttonColourAssignment();
    Serial.print("gryG = ");
    Serial.println(gryG);
    gryY = buttonColourAssignment();
    Serial.print("gryY = ");
    Serial.println(gryY);
    ryY = buttonColourAssignment();
    Serial.print("ryY = ");
    Serial.println(ryY);
    rbyY = buttonColourAssignment();
    Serial.print("rbyY = ");
    Serial.println(rbyY);
    gyY = buttonColourAssignment();
    Serial.print("gyY = ");
    Serial.println(gyY);
    byY = buttonColourAssignment();
    Serial.print("byY = ");
    Serial.println(byY);
    ogyY = buttonColourAssignment();
    Serial.print("ogyY = ");
    Serial.println(ogyY);
    oyY = buttonColourAssignment();
    Serial.print("oyY = ");
    Serial.println(oyY);
    boyY = buttonColourAssignment();
    Serial.print("boyY = ");
    Serial.println(boyY);
}