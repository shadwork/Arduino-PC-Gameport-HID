
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
const int AXIS_MAX = 1000;
const int AXIS_NUL = 32;

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

  if(buttonState4<AXIS_MIN && buttonState4>AXIS_NUL){
    joyStick.xAxis = 255;  
  }
  else if(buttonState4>AXIS_MAX){
    joyStick.xAxis = 0; 
  }
  else{
    joyStick.xAxis = 127;     
  }

  if(buttonState5<AXIS_MIN && buttonState5>AXIS_NUL){
    joyStick.yAxis = 255; 
  }
  else if(buttonState5>AXIS_MAX){
    joyStick.yAxis = 0; 
  }
  else{
    joyStick.yAxis = 127;    
  }   

  // all another axis set to zero position
  joyStick.zAxis = 127;
  joyStick.xRotAxis = 127;
  joyStick.yRotAxis = 127;
  joyStick.zRotAxis = 127;
  joyStick.throttle = 127;
  joyStick.rudder = 127;
  // and hats to center
  joyStick.hatSw1 = 8;
  joyStick.hatSw2 = 8;    

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

  // analog buttons

  if(buttonState6>AXIS_MAX){
    joyStick.buttons = joyStick.buttons | 16;   
  }

  if(buttonState7>AXIS_MAX){
    joyStick.buttons = joyStick.buttons | 32;   
  }
  Joystick.setState(&joyStick);

  delay(1);

}









