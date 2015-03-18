
// Settings
#define ENABLE_DEBUG;

// Pins
const int button0 = 7;
const int button1 = 6;
const int button2 = 5;
const int button3 = 4;

const int axis0 = A0;
const int axis1 = A1;
const int axis2 = A2;
const int axis3 = A3;

// Analog to digital
const int AXIS_MIN = 550;
const int AXIS_MAX = 1023;
const int AXIS_NUL = 720;

// Joestick
JoyState_t joyStick;

// Ugly vars
int buttonState0= 0;  
int buttonState1= 0;
int buttonState2= 0;
int buttonState3= 0;
int buttonState4= 0;
int buttonState5= 0;
int buttonState6= 0;
int buttonState7= 0;

// Setup
void setup() {
  Serial.begin(9600);
  // pull up
  pinMode(button0, INPUT_PULLUP);     
  pinMode(button1, INPUT_PULLUP); 
  pinMode(button2, INPUT_PULLUP); 
  pinMode(button3, INPUT_PULLUP);   
}

void loop(){
  // read data
  buttonState0 = !digitalRead(button0);
  buttonState1 = !digitalRead(button1);
  buttonState2 = !digitalRead(button2);
  buttonState3 = !digitalRead(button3);  

  buttonState4 = analogRead(axis0);
  buttonState5 = analogRead(axis1);
  buttonState6 = analogRead(axis2);
  buttonState7 = analogRead(axis3);  


#ifdef ENABLE_DEBUG
  Serial.print(buttonState0);
  Serial.print(buttonState1);
  Serial.print(buttonState2);
  Serial.print(buttonState3); 
  Serial.print(" ");
  Serial.print(buttonState4);     
  Serial.print(" ");
  Serial.print(buttonState5); 
  Serial.print(" ");
  Serial.print(buttonState6); 
  Serial.print(" ");
  Serial.print(buttonState7);     
  Serial.println("");
#endif 

 
  float tempState = 127;
  if(buttonState4>AXIS_NUL){
    tempState = 127+(AXIS_NUL - buttonState4)/2; 
  }
  else{
    tempState =127+ (AXIS_NUL - buttonState4)/1;     
  }
  tempState = tempState<0?0:tempState;
  tempState = tempState>255?255:tempState;  
  joyStick.xAxis = tempState;

  tempState = 127;
  if(buttonState5>AXIS_NUL){
    tempState = 127+(AXIS_NUL - buttonState5)/2; 
  }
  else{
    tempState =127+ (AXIS_NUL - buttonState5)/1;     
  }
  tempState = tempState<0?0:tempState;
  tempState = tempState>255?255:tempState;  
  joyStick.yAxis = tempState;  

  tempState = buttonState6 - AXIS_MIN;
  tempState = tempState<0?0:tempState;
  tempState = (256 *tempState)/ (float)(AXIS_MAX-AXIS_MIN);
  tempState = tempState>255?255:tempState;  
  joyStick.rudder = tempState; 

  tempState = buttonState7 - AXIS_MIN;
  tempState = tempState<0?0:tempState;
  tempState = (256 *tempState)/ (float)(AXIS_MAX-AXIS_MIN);
  tempState = abs(tempState - 256);
  tempState = tempState<0?0:tempState;
  tempState = tempState>255?255:tempState;  
  joyStick.throttle = tempState;

  // all another axis set to zero position
  joyStick.zAxis = 127;
  joyStick.xRotAxis = 127;
  joyStick.yRotAxis = 127;
  joyStick.zRotAxis = 127;
  //joyStick.throttle = 127;
  //joyStick.rudder = 127;


  // hat connected to 4 key
  if(buttonState0 && buttonState1 && buttonState2 && buttonState3){
    joyStick.hatSw1 = 0; 
  }
  else if(buttonState0 && buttonState1 && !buttonState2 && buttonState3){
    joyStick.hatSw1 = 4;
  }
  else if(buttonState0 && buttonState1 && !buttonState2 && !buttonState3){
    joyStick.hatSw1 = 6;
  }
  else if(buttonState0 && buttonState1 && buttonState2 && !buttonState3){
    joyStick.hatSw1 = 2;
  }
  else{
    joyStick.hatSw1 = 8;
    // buttons connects
    joyStick.buttons = 0;
    // digital buttons to mask
    if(buttonState0){
      joyStick.buttons = joyStick.buttons | 1;  
    }

    if(buttonState1){
      joyStick.buttons = joyStick.buttons | 2;  
    }

    if(buttonState2){
      joyStick.buttons = joyStick.buttons | 4;  
    }

    if(buttonState3){
      joyStick.buttons = joyStick.buttons | 8;  
    } 

  }  

  // and hat2 to center
  joyStick.hatSw2 = 8;    

  Joystick.setState(&joyStick);

  delay(1);
}













