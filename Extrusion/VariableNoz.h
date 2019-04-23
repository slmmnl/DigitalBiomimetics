//-- Arduino Leonardo Port Configuration
//--
//-- [b7][b6][b5][b4][b3][b2][b1][b0]
//-- [11][10][09][08][14][16][15][__] Port B  Note: SCK=15 MISO=14 MOSI=16
//-- [13][05][__][__][__][__][__][__] Port C
//-- [06][12][__][04][01][00][02][03] Port D
//-- [__][07][__][__][__][__][__][__] Port E
//-- [A0][A1][A2][A3][__][__][A4][A5] Port F
//--

//-- Using Stepper Motor
//--
#include <Stepper.h>
#define MotorUseVariableNoz

//-- Ardbox Relay Configuration
//--
#ifdef ArdboxRelay

  //-- Pin Assignments
  //--
  static const int In1 = 2;
  static const int In2 = 3;
  static const int In3 = 5;
  static const int In4 = 6;

  // Number of steps per internal motor revolution
  const float STEPS_PER_REV = 32;

  //  Amount of Gear Reduction
  const float GEAR_RED = 64;

  // Number of steps per geared output rotation
  const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;

#endif

//-- Ardbox Analog Configuration
//--
#ifdef ArdboxAnalog
  #pragma GCC error "Not Implemented"
#endif

//-- Pin Setup
//--
inline void NozSetupPins( )
{
  //-- Variable Setup
  //--
  int currentPos = 0;
  int stepsMove;
  int moveVal = 1400;
  boolean dir = false;

  // Number of Steps Required
  int StepsRequired;

  // Create Instance of Stepper Class
  // Specify Pins used for motor coils
  // The pins used are 9,10,11,12
  // Connected to ULN2003 Motor Driver In1, In2, In3, In4
  // Pins entered in sequence 1-3-2-4 for proper step sequencing
  // IN1: Pin 2 IN2: Pin 3 IN3: Pin 5 IN4: Pin 6
  Stepper steppermotor(STEPS_PER_REV, In1, In3, In2, In4);

}
