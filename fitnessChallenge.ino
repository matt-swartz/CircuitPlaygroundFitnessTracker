#include <Adafruit_CircuitPlayground.h>
// left button pressed
bool leftPress = false;
// right button pressed
bool rightPress = false;
// sit-up variables
bool sitUpPosOne = false;
bool sitUpPosTwo = false;
bool sitUpPosThree = false;
int sitUpDone = 0;
// squat variables
bool squatUp = false;
bool squatDown = false;
bool squatUpTwo = false;
int squatDone = 0;
// push-up variables
bool pushUp = false;
bool pushDown = false;
bool pushUpTwo = false;
int pushUpDone = 0;
// jumping jacks variables
bool jumpDown = false;
bool jumpUp = false;
bool jumpDownTwo = false;
int jumpJackDone = 0;
// accelerometer variables
float X, Y, Z; 

// initializing everything
void initial_state() {
  // clear neopixels
  CircuitPlayground.clearPixels();
  // set the 4 exercise lights to red aka not complete
  CircuitPlayground.setPixelColor(0, 0xFF0000);
  CircuitPlayground.setPixelColor(4, 0xFF0000);
  CircuitPlayground.setPixelColor(5, 0xFF0000);
  CircuitPlayground.setPixelColor(9, 0xFF0000);
}

//our home screen with our lights to tell us an exercise is done
void homeScreen() {
  // clear neopixels
  CircuitPlayground.clearPixels();
  // reset presses
  leftPress = false;
  rightPress = false;
  // turn zeroth light green for sit-ups completed
  if(sitUpDone == 5) {
    CircuitPlayground.setPixelColor(0, 0x00FF00);
  } else {
    CircuitPlayground.setPixelColor(0, 0xFF0000);
  }
  //turn fourth light green for squats completed
  if(squatDone == 5) {
    CircuitPlayground.setPixelColor(4, 0x00FF00);
  } else {
    CircuitPlayground.setPixelColor(4, 0xFF0000);
  }
  //turn fifth light green for push-ups completed
  if(pushUpDone == 5) {
    CircuitPlayground.setPixelColor(5, 0x00FF00);
  } else {
    CircuitPlayground.setPixelColor(5, 0xFF0000);
  }
  //turn ninth light green for jumping jacks completed
  if(jumpJackDone == 5) {
    CircuitPlayground.setPixelColor(9, 0x00FF00);
  } else {
    CircuitPlayground.setPixelColor(9, 0xFF0000);
  }
}

// get accelerometer data
void accelData() {
  X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();
  Z = CircuitPlayground.motionZ();
}

void setup() {
  // put your setup code here, to run once:
  // initialize the Neopixels
  Serial.begin(9600);
  CircuitPlayground.begin();
  initial_state();
}

void loop() {
  // put your main code here, to run repeatedly:
  // double press the button you are on to get back to intial lights 
  if((CircuitPlayground.leftButton() && leftPress) || (CircuitPlayground.rightButton() && rightPress)) {
    homeScreen();
  }
  //reset the device to count more reps, switch from right to left back to right to reset
  if(CircuitPlayground.slideSwitch()) {
    // left button reset
    leftPress = false;
    // right button reset
    rightPress = false;
    // reset all exercise reps
    sitUpDone = 0;
    squatDone = 0;
    pushUpDone = 0;
    jumpJackDone = 0;
    initial_state();
  }
  // for the first time of a left button press
  if(CircuitPlayground.leftButton()) {
    // clear neopixels
    CircuitPlayground.clearPixels();
    // tell program our left button has been pressed
    leftPress = true;
    // make right press false
    rightPress = false;
  }
  // for the first time of a left button press
  if(CircuitPlayground.rightButton()) {
    // clear neopixels
    CircuitPlayground.clearPixels();
    // tell program our right button has been pressed
    rightPress = true;
    // make left press false
    leftPress = false;
  }
  //for sit-up recording
  if(leftPress && sitUpDone <= 5) {
    // sit-up lights
    switch (sitUpDone) {
      case 0:
        // set all the lights to red aka no complete reps of sit-ups
        CircuitPlayground.setPixelColor(0, 0xFF0000);
        CircuitPlayground.setPixelColor(1, 0xFF0000);
        CircuitPlayground.setPixelColor(2, 0xFF0000);
        CircuitPlayground.setPixelColor(3, 0xFF0000);
        CircuitPlayground.setPixelColor(4, 0xFF0000);
        break;
      case 1:
        // set one light to green for one rep
        CircuitPlayground.setPixelColor(0, 0x00FF00);
        CircuitPlayground.setPixelColor(1, 0xFF0000);
        CircuitPlayground.setPixelColor(2, 0xFF0000);
        CircuitPlayground.setPixelColor(3, 0xFF0000);
        CircuitPlayground.setPixelColor(4, 0xFF0000);
        break;
      case 2:
        // set two lights to green for two reps
        CircuitPlayground.setPixelColor(0, 0x00FF00);
        CircuitPlayground.setPixelColor(1, 0x00FF00);
        CircuitPlayground.setPixelColor(2, 0xFF0000);
        CircuitPlayground.setPixelColor(3, 0xFF0000);
        CircuitPlayground.setPixelColor(4, 0xFF0000);
        break;
      case 3:
        // set three lights to green for three reps
        CircuitPlayground.setPixelColor(0, 0x00FF00);
        CircuitPlayground.setPixelColor(1, 0x00FF00);
        CircuitPlayground.setPixelColor(2, 0x00FF00);
        CircuitPlayground.setPixelColor(3, 0xFF0000);
        CircuitPlayground.setPixelColor(4, 0xFF0000);
        break;
      case 4:
        // set four lights to green for four reps
        CircuitPlayground.setPixelColor(0, 0x00FF00);
        CircuitPlayground.setPixelColor(1, 0x00FF00);
        CircuitPlayground.setPixelColor(2, 0x00FF00);
        CircuitPlayground.setPixelColor(3, 0x00FF00);
        CircuitPlayground.setPixelColor(4, 0xFF0000);
        break;
      case 5:
        // set five lights to green for five reps
        CircuitPlayground.setPixelColor(0, 0x00FF00);
        CircuitPlayground.setPixelColor(1, 0x00FF00);
        CircuitPlayground.setPixelColor(2, 0x00FF00);
        CircuitPlayground.setPixelColor(3, 0x00FF00);
        CircuitPlayground.setPixelColor(4, 0x00FF00);
        break;
    }
    // accelerometer data
    accelData();
    //check laying on back position of sit-up
    if ((X > -0.5 && X < 0.5) && (Z < 10 && Z > 7)) {
      sitUpPosOne = true;
    }
    //check at top of sit-up position
    if (sitUpPosOne && (X > 7 || X < -7) && Z < 4) {
      sitUpPosTwo = true;
      sitUpPosOne = false;
    }
    //check back at bottom of sit-up position
    if (sitUpPosTwo && (X > -0.5 && X < 0.5) && (Z < 10 && Z > 7)) {
      sitUpPosThree = true;
      sitUpPosTwo = false;
    }
    //record the sit-up
    if (sitUpPosThree) {
      sitUpDone++;
      CircuitPlayground.playTone(250, 100);
      sitUpPosThree = false;
    }
  }
  // for squat reecording
  if(leftPress && squatDone <= 5) {
    // squats done
    switch (squatDone) {
      case 0:
        // set all the lights to red aka no complete reps of jumping jacks
        CircuitPlayground.setPixelColor(5, 0xFF0000);
        CircuitPlayground.setPixelColor(6, 0xFF0000);
        CircuitPlayground.setPixelColor(7, 0xFF0000);
        CircuitPlayground.setPixelColor(8, 0xFF0000);
        CircuitPlayground.setPixelColor(9, 0xFF0000);
        break;
      case 1:
        // set one light to green for one rep
        CircuitPlayground.setPixelColor(5, 0x00FF00);
        CircuitPlayground.setPixelColor(6, 0xFF0000);
        CircuitPlayground.setPixelColor(7, 0xFF0000);
        CircuitPlayground.setPixelColor(8, 0xFF0000);
        CircuitPlayground.setPixelColor(9, 0xFF0000);
        break;
      case 2:
        // set two lights to green for two reps
        CircuitPlayground.setPixelColor(5, 0x00FF00);
        CircuitPlayground.setPixelColor(6, 0x00FF00);
        CircuitPlayground.setPixelColor(7, 0xFF0000);
        CircuitPlayground.setPixelColor(8, 0xFF0000);
        CircuitPlayground.setPixelColor(9, 0xFF0000);
        break;
      case 3:
        // set three lights to green for three reps
        CircuitPlayground.setPixelColor(5, 0x00FF00);
        CircuitPlayground.setPixelColor(6, 0x00FF00);
        CircuitPlayground.setPixelColor(7, 0x00FF00);
        CircuitPlayground.setPixelColor(8, 0xFF0000);
        CircuitPlayground.setPixelColor(9, 0xFF0000);
        break;
      case 4:
        // set four lights to green for four reps
        CircuitPlayground.setPixelColor(5, 0x00FF00);
        CircuitPlayground.setPixelColor(6, 0x00FF00);
        CircuitPlayground.setPixelColor(7, 0x00FF00);
        CircuitPlayground.setPixelColor(8, 0x00FF00);
        CircuitPlayground.setPixelColor(9, 0xFF0000);
        break;
      case 5:
        // set five lights to green for five reps
        CircuitPlayground.setPixelColor(5, 0x00FF00);
        CircuitPlayground.setPixelColor(6, 0x00FF00);
        CircuitPlayground.setPixelColor(7, 0x00FF00);
        CircuitPlayground.setPixelColor(8, 0x00FF00);
        CircuitPlayground.setPixelColor(9, 0x00FF00);
        break;
    }
    // accelerometer data
    accelData();
    //check upper position of squat
    if (X < 3 && Y > -5) {
      squatUp = true;
    }
    //check down position of squat
    if (squatUp && X > 5 && Y < -9) {
      squatDown = true;
      squatUp = false;
    }
    //check back at top of squat
    if (squatDown && X < 3 && Y > -5) {
      squatUpTwo = true;
      squatDown = false;
    }
    //record the squat
    if (squatUpTwo) {
      squatDone++;
      CircuitPlayground.playTone(250, 100);
      squatUpTwo = false;
    }
  }
  //for push-up recording
  if(rightPress && pushUpDone <= 5) {
    // push-up lights
    switch (pushUpDone) {
      case 0:
        // set all the lights to red aka no complete reps of push-ups
        CircuitPlayground.setPixelColor(0, 0xFF0000);
        CircuitPlayground.setPixelColor(1, 0xFF0000);
        CircuitPlayground.setPixelColor(2, 0xFF0000);
        CircuitPlayground.setPixelColor(3, 0xFF0000);
        CircuitPlayground.setPixelColor(4, 0xFF0000);
        break;
      case 1:
        // set one light to green for one rep
        CircuitPlayground.setPixelColor(0, 0x00FF00);
        CircuitPlayground.setPixelColor(1, 0xFF0000);
        CircuitPlayground.setPixelColor(2, 0xFF0000);
        CircuitPlayground.setPixelColor(3, 0xFF0000);
        CircuitPlayground.setPixelColor(4, 0xFF0000);
        break;
      case 2:
        // set two lights to green for two reps
        CircuitPlayground.setPixelColor(0, 0x00FF00);
        CircuitPlayground.setPixelColor(1, 0x00FF00);
        CircuitPlayground.setPixelColor(2, 0xFF0000);
        CircuitPlayground.setPixelColor(3, 0xFF0000);
        CircuitPlayground.setPixelColor(4, 0xFF0000);
        break;
      case 3:
        // set three lights to green for three reps
        CircuitPlayground.setPixelColor(0, 0x00FF00);
        CircuitPlayground.setPixelColor(1, 0x00FF00);
        CircuitPlayground.setPixelColor(2, 0x00FF00);
        CircuitPlayground.setPixelColor(3, 0xFF0000);
        CircuitPlayground.setPixelColor(4, 0xFF0000);
        break;
      case 4:
        // set four lights to green for four reps
        CircuitPlayground.setPixelColor(0, 0x00FF00);
        CircuitPlayground.setPixelColor(1, 0x00FF00);
        CircuitPlayground.setPixelColor(2, 0x00FF00);
        CircuitPlayground.setPixelColor(3, 0x00FF00);
        CircuitPlayground.setPixelColor(4, 0xFF0000);
        break;
      case 5:
        // set five lights to green for five reps
        CircuitPlayground.setPixelColor(0, 0x00FF00);
        CircuitPlayground.setPixelColor(1, 0x00FF00);
        CircuitPlayground.setPixelColor(2, 0x00FF00);
        CircuitPlayground.setPixelColor(3, 0x00FF00);
        CircuitPlayground.setPixelColor(4, 0x00FF00);
        break;
    }
    // accelerometer data
    accelData();
    //check extended arms postion of a push-up
    if ((X < 8 && X > 6) && (Z > -3 && Z < -1)) {
      pushUp = true;
    }
    //check 90 degree angle of arm with downward push up position
    if (pushUp && (X < 1 && X > -3) && (Z < -8 && Z > -11)) {
      pushDown = true;
      pushUp = false;
    }
    //check back at top of push-up position with straight arms again
    if (pushDown && (X < 8 && X > 6) && (Z > -3 && Z < -1)) {
      pushUpTwo = true;
      pushDown = false;
    }
    //record the push-up
    if (pushUpTwo) {
      pushUpDone++;
      CircuitPlayground.playTone(250, 100);
      pushUpTwo = false;
    }
  }
  //for jumping jack recording
  if(rightPress && jumpJackDone <= 5) {
    // jumping jack lights
    switch (jumpJackDone) {
      case 0:
        // set all the lights to red aka no complete reps of jumping jacks
        CircuitPlayground.setPixelColor(5, 0xFF0000);
        CircuitPlayground.setPixelColor(6, 0xFF0000);
        CircuitPlayground.setPixelColor(7, 0xFF0000);
        CircuitPlayground.setPixelColor(8, 0xFF0000);
        CircuitPlayground.setPixelColor(9, 0xFF0000);
        break;
      case 1:
        // set one light to green for one rep
        CircuitPlayground.setPixelColor(5, 0x00FF00);
        CircuitPlayground.setPixelColor(6, 0xFF0000);
        CircuitPlayground.setPixelColor(7, 0xFF0000);
        CircuitPlayground.setPixelColor(8, 0xFF0000);
        CircuitPlayground.setPixelColor(9, 0xFF0000);
        break;
      case 2:
        // set two lights to green for two reps
        CircuitPlayground.setPixelColor(5, 0x00FF00);
        CircuitPlayground.setPixelColor(6, 0x00FF00);
        CircuitPlayground.setPixelColor(7, 0xFF0000);
        CircuitPlayground.setPixelColor(8, 0xFF0000);
        CircuitPlayground.setPixelColor(9, 0xFF0000);
        break;
      case 3:
        // set three lights to green for three reps
        CircuitPlayground.setPixelColor(5, 0x00FF00);
        CircuitPlayground.setPixelColor(6, 0x00FF00);
        CircuitPlayground.setPixelColor(7, 0x00FF00);
        CircuitPlayground.setPixelColor(8, 0xFF0000);
        CircuitPlayground.setPixelColor(9, 0xFF0000);
        break;
      case 4:
        // set four lights to green for four reps
        CircuitPlayground.setPixelColor(5, 0x00FF00);
        CircuitPlayground.setPixelColor(6, 0x00FF00);
        CircuitPlayground.setPixelColor(7, 0x00FF00);
        CircuitPlayground.setPixelColor(8, 0x00FF00);
        CircuitPlayground.setPixelColor(9, 0xFF0000);
        break;
      case 5:
        // set five lights to green for five reps
        CircuitPlayground.setPixelColor(5, 0x00FF00);
        CircuitPlayground.setPixelColor(6, 0x00FF00);
        CircuitPlayground.setPixelColor(7, 0x00FF00);
        CircuitPlayground.setPixelColor(8, 0x00FF00);
        CircuitPlayground.setPixelColor(9, 0x00FF00);
        break;
    }
    // accelerometer data
    accelData();
    //check downward arms and closed legs position
    if (X > 10) {
      jumpDown = true;
    }
    //check arms up and legs open position
    if (jumpDown && X < -10) {
      jumpUp = true;
      jumpDown = false;
    }
    //check back on downward arms and closed legs position
    if (jumpUp && X > 10) {
      jumpDownTwo = true;
      jumpUp = false;
    }
    //record the jumping jack
    if (jumpDownTwo) {
      jumpJackDone++;
      CircuitPlayground.playTone(250, 100);
      jumpDownTwo = false;
    }
  }
}
