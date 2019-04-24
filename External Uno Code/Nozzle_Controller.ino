//Include the Arduino Stepper Library
#include <Stepper.h>
 
// Define Constants
 
// Number of steps per internal motor revolution 
const float STEPS_PER_REV = 32; 
 
//  Amount of Gear Reduction
const float GEAR_RED = 64;
 
// Number of steps per geared output rotation
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;
 
// Define Variables
 
// Create Instance of Stepper Class
// Specify Pins used for motor coils
// The pins used are 9,10,11,12
// Connected to ULN2003 Motor Driver In1, In2, In3, In4 
// Pins entered in sequence 1-3-2-4 for proper step sequencing

#define CPIN1 2
#define CPIN2 3

#define IN1 9
#define IN2 10
#define IN3 11
#define IN4 12
 
Stepper steppermotor(STEPS_PER_REV, IN1, IN3, IN2, IN4);

int currentPos = 0;
int stepsMove;

//Preset absolute position values with reference to the fully open position at 0.
int presetX = 600;
int presetY = 800;

int shutVal = 1000;
boolean dir = false;

char rx_byte = 0;
String rx_str = "";

void setup()
{
  Serial.begin(9600);

  Serial.println("Enter a number to set the steps and run the motor");
  Serial.println("Fully open position at 0");
  Serial.println("Fully closed position at 900");
  Serial.println("'F' to run flex demo from fully open position");
  
  Serial.print("'C' to close at position ");
  Serial.println(shutVal);
  Serial.println("'O' to open position at 0");
  Serial.println("'D' to change direction");
  
  Serial.print("'X' to run preset X which is set to ");
  Serial.println(presetX);
  Serial.print("'Y' to run preset Y which is set to ");
  Serial.println(presetY);

  Serial.println("'S' for status");   
  Serial.println("Close Direction");

  pinMode(CPIN1, INPUT);
  pinMode(CPIN2, INPUT);
}
 
void loop(){
  if ( (digitalRead(CPIN1)==LOW) && (digitalRead(CPIN2)==LOW) ){
    Serial.println("CPIN reads 00");
    if (Serial.available() > 0) {    // is a character available?
      rx_byte = Serial.read();       // get the character
    
      // check if a number was received
      if (isDigit(rx_byte)){
        //Serial.println(rx_byte);
        rx_str += rx_byte;
      }
      else if (rx_byte == 'D'){
        dir = !dir;
        showStatus();
      }
      
      else if (rx_byte == 'C'){
        steppermotor.setSpeed(600);   
        goToClose();
        showStatus();
        turnOffMotor();
      }
      
      else if (rx_byte == 'R'){   //Reset to 0. Change currentPos to 0
        currentPos = 0;
        Serial.println("Current postion is now set to 0");
      }
  
      else if (rx_byte == 'S'){   //Show Status
        showStatus();
      }
      
      else if (rx_byte == 'O'){ //Go to Open Position at 0
        steppermotor.setSpeed(600);
        goToOpen();
        showStatus();
        turnOffMotor();
      }
  
      else if (rx_byte == 'X'){ //Go to X Position
        steppermotor.setSpeed(600);
        goToX();
        showStatus();
        turnOffMotor();
      }
  
      else if (rx_byte == 'x'){ //Go to X Position
        presetX = currentPos;
        Serial.print("X is now set to ");
        Serial.println(presetX);
      }
  
      else if (rx_byte == 'Y'){ //Go to Y Position
        steppermotor.setSpeed(600);
        goToY();
        showStatus();
        turnOffMotor();
      }
  
      else if (rx_byte == 'y'){ //Set presetY to currentPos
        presetY = currentPos;
        Serial.print("Y is now set to ");
        Serial.println(presetY);
      }
      
      else if (rx_byte == '\n') {
        Serial.println("Newline");
        Serial.println(rx_str);
        stepsMove = rx_str.toInt();
        if (dir){
          //Serial.println("Open Direction");
        }
        else{
          //Serial.println("Close Direction");
          stepsMove = (-1)*stepsMove;
        }
        rx_str = "";
      }
      else {
        Serial.println("Invalid character/command");
        rx_str = "";
      }
    }
    if (stepsMove!=0){   
      steppermotor.setSpeed(700);   
      steppermotor.step(stepsMove);
      currentPos += stepsMove;
      stepsMove = 0;
      showStatus();
      turnOffMotor();
    }
  }
  else if ( (digitalRead(CPIN1)==LOW) && (digitalRead(CPIN2)==HIGH) ){
    //Serial.println("CPIN reads 01");
    //State 2. Open to X position.
    steppermotor.setSpeed(600);
    goToX();
    showStatus();
    turnOffMotor();
  }
  else if ( (digitalRead(CPIN1)==HIGH) && (digitalRead(CPIN2)==LOW) ){
    steppermotor.setSpeed(600);   
    goToClose();
    showStatus();
    turnOffMotor();
  }
  else if ( (digitalRead(CPIN1)==HIGH) && (digitalRead(CPIN2)==HIGH) ){
    //Serial.println("CPIN reads 11");
    //Go to Open position
    steppermotor.setSpeed(600);
    goToOpen();
    showStatus();
    turnOffMotor();
  }
}

void showStatus(){
  Serial.print("currentPos: ");
  Serial.println(currentPos);

  Serial.print("X position at ");
  Serial.println(presetX);

  Serial.print("Y postion at ");
  Serial.println(presetY);

  if(dir){
    Serial.println("Close Direction");
  }
  else{
    Serial.println("Open Direction");
  }
}

void turnOffMotor(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void goToOpen(){
  if(currentPos>0){
        //Open Direction to reach 0
        Serial.println("Opening up to 0 position!");
        steppermotor.step(-1*currentPos);
        currentPos-=currentPos;
      }
      else if(currentPos<0){
        //Close Direction to reach 0
        Serial.println("Closing in to 0 position!");
        steppermotor.step(currentPos);
        currentPos+=currentPos;
      }
      else{
        Serial.println("Already at 0!");
      }
}

void goToClose(){
  if(currentPos>shutVal){
    //Open Direction to reach 0
    Serial.print("Opening up to shut position at ");\
    Serial.println(shutVal);
    steppermotor.step(shutVal-currentPos);
    currentPos=shutVal;
  }
  else if(currentPos<shutVal){
    //Close Direction to reach 0
    Serial.println("Closing in to 0 position!");
    steppermotor.step(shutVal-currentPos);
    currentPos=shutVal;
  }
  else{
    Serial.print("Already at shut position at ");
    Serial.println(shutVal);
  }
}

void goToX(){
  if(currentPos > presetX){
    //Open Direction to reach X
    Serial.println("Opening up to X position!");
    steppermotor.step(presetX-currentPos);
    currentPos = presetX;
  }
  else if(currentPos < presetX){
    //Close Direction to reach X
    Serial.println("Closing in to X position!");
    steppermotor.step(presetX-currentPos);
    currentPos = presetX;
  }
  else{
    Serial.println("Already at position X!");
  }
}

void goToY(){
  if(currentPos > presetY){
    //Open Direction to reach Y
    Serial.println("Opening up to Y position!");
    steppermotor.step(presetY-currentPos);
    currentPos = presetY;
  }
  else if(currentPos < presetY){
    //Close Direction to reach Y
    Serial.println("Closing in to Y position!");
    steppermotor.step(presetY-currentPos);
    currentPos = presetY;
  }
  else{
    Serial.println("Already at position Y!");
  }
}

