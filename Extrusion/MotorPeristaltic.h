//-- Arduino Leonardo Port Configuration
//--
//-- [b7][b6][b5][b4][b3][b2][b1][b0]
//-- [11][10][09][08][14][16][15][__] Port B  Note: SCK=15 MISO=14 MOSI=16
//-- [13][05][__][__][__][__][__][__] Port C
//-- [06][12][__][04][01][00][02][03] Port D
//-- [__][07][__][__][__][__][__][__] Port E
//-- [A0][A1][A2][A3][__][__][A4][A5] Port F
//--

//-- Using DC Motor
//--
#define MotorUseDC

//-- Pin Assignments
//--
static const uint8_t MotorDirectionPinA = 14; //-- PORT B3 --> MISO --> Pin Digital 14
static const uint8_t MotorDirectionPinB = 16; //-- PORT B2 --> MOSI --> Pin Digital 16

//-- Set Direction Negative --> LOW
//-- digitalWrite( MotorDirectionPinA, HIGH );
//-- digitalWrite( MotorDirectionPinB, LOW  );
//--
#define MotorSetDirectionNegative( ) \
  PORTB = ( PORTB & 0xFB ) | 0x08;

//-- Set Direction Positive --> HIGH
//-- digitalWrite( MotorDirectionPinB, HIGH );
//-- digitalWrite( MotorDirectionPinA, LOW  );
//--
#define MotorSetDirectionPositive( ) \
  PORTB = ( PORTB & 0xF7 ) | 0x04

//-- Warning! Ardbox Analog Range is 0..10VDC
//--
#ifdef ArdboxAnalog
  static const uint8_t MotorPulsePin = 5;  
#endif

#ifdef ArdboxRelay
  #pragma GCC error "Not Implemented"
#endif

//-- Pin Setup
//--
inline void MotorSetupPins( )
{
  //-- Variable Setup
  //--
  MotorPulseValue = 0;
  MotorPosition   = 0;
  MotorObjective  = 0;
  MotorConfigured = false;
  MotorRunning    = false;

  //-- Pin Setup
  //--  
  pinMode( MotorPulsePin,      OUTPUT );
  pinMode( MotorDirectionPinA, OUTPUT );
  pinMode( MotorDirectionPinB, OUTPUT );
}

//-- Map 4-bits to Analog Value
//--
inline uint16_t MotorMapValue( 
  uint8_t value )
{  
  //-- 0x80 is 5VDC for Peristaltic PWM
  //-- Note: The motor will not start with
  //-- too low voltages...
  //--
  return ( 0x80 * ( value > 0xF ? 0xF : value ) ) / 0xF; 
}