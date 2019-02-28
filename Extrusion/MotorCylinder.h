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
#define MotorUseStepper

//-- Ardbox Relay Configuration
//--
#ifdef ArdboxRelay

  //-- Pin Assignments
  //--
  static const uint8_t MotorPulsePin     = 7; //-- PORT E6 --> DE --> Pin Digital 7
  static const uint8_t MotorDirectionPin = 4; //-- PORT D4 --> RE --> Pin Digital 4 

  //-- Toggle Pulse Pin
  //-- digitalWrite( MotorPulsePin, LOW  );
  //-- digitalWrite( MotorPulsePin, HIGH );
  //--
  #define MotorPulseToggle( ) \
    PORTE ^= 0x40

  //-- Set Direction Negative --> LOW
  //-- digital Write( MotorDirectionPin, LOW );
  //--
  #define MotorSetDirectionNegative( ) \
    PORTD &= 0xEF
 
  //-- Set Direction Positive --> HIGH
  //-- digital Write( MotorDirectionPin, HIGH );
  //--
  #define MotorSetDirectionPositive( ) \
    PORTD |= 0x10

#endif

//-- Ardbox Analog Configuration
//--
#ifdef ArdboxAnalog
  #pragma GCC error "Not Implemented"
#endif

//-- Pin Setup
//--
inline void MotorSetupPins( )
{
  //-- Variable Setup
  //--
  MotorPulseValue  = 200;
  MotorPosition    = 0;
  MotorObjective   = 0;
  MotorConfigured  = false;
  MotorRunning     = false;

  //-- Pin Setup
  //--  
  pinMode( MotorPulsePin,     OUTPUT );
  pinMode( MotorDirectionPin, OUTPUT );
}

//-- Map 4-bits to Analog Value
//--
inline uint16_t MotorMapValue( 
  uint8_t value )
{  
  //-- 0..15 -> 1000..100us 
  //--
  return 1000 - ( 900 * ( value > 0xF ? 0xF : value ) ) / 0xF; 
}