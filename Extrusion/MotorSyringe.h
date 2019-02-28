//-- Arduino Leonardo Port Configuration
//--
//-- [b7][b6][b5][b4][b3][b2][b1][b0]
//-- [11][10][09][08][14][16][15][__] Port B  Note: SCK=15 MISO=14 MOSI=16
//-- [13][05][__][__][__][__][__][__] Port C
//-- [06][12][__][04][01][00][02][03] Port D
//-- [__][07][__][__][__][__][__][__] Port E
//-- [A0][A1][A2][A3][__][__][A4][A5] Port F
//--

//-- Using Stepper Motor & Limit Switches
//--
#define MotorUseStepper
#define MotorUseLimits

//-- Pin Assignments
//--
static const uint8_t MotorPulsePin         = 15; //-- PORT B1 --> SCK  --> Digital Pin 15
static const uint8_t MotorLimitNegativePin = 14; //-- PORT B3 --> MISO --> Digital Pin 14
static const uint8_t MotorLimitPositivePin = 16; //-- PORT B2 --> MOSI --> Digital Pin 16

//-- Get Negative Limit Switch
//-- digitalRead( MotorLimitNegativePin );
//--
#define MotorGetLimitSwitchNegative( ) \
  ( ( PINB >> 3 ) & 0x01 )

//-- Get Positive Limit Switch
//-- digitalRead( MotorLimitPositivePin );
//--
#define MotorGetLimitSwitchPositive( ) \
  ( ( PINB >> 2 ) & 0x01 )

//-- Toggle Pulse Pin
//-- digitalWrite( MotorPulsePin, LOW  );
//-- digitalWrite( MotorPulsePin, HIGH );
//--
#define MotorPulseToggle( ) \
  PORTB ^= 0x02

//-- Motor Direction
//--
#define MotorUseDirection

#ifdef ArdboxAnalog
  static const uint8_t MotorDirectionPin = 3; //-- PORT D0 -- SLC --

  #define MotorSetDirectionNegative( ) \
    PORTD &= 0xFE

  #define MotorSetDirectionPositive( ) \
    PORTD |= 0x01
#endif

#ifdef ArdboxRelay
  static const uint8_t MotorDirectionPin = 4; //-- PORT D4 -- RE  --

  #define MotorSetDirectionNegative( ) \
    PORTD &= 0xEF

  #define MotorSetDirectionPositive( ) \
    PORTD |= 0x10

#endif

//-- Pin Setup
//--
inline void MotorSetupPins( )
{
  //-- Variable Setup
  //--
  MotorPulseValue  = 1000;
  MotorPosition    = 0;
  MotorObjective   = 0;
  MotorMotionRange = 0;
  MotorConfigured  = false;
  MotorRunning     = false;

  //-- Pin Setup
  //--
  pinMode( MotorPulsePin,         OUTPUT       );
  pinMode( MotorDirectionPin,     OUTPUT       );
  pinMode( MotorLimitNegativePin, INPUT_PULLUP );
  pinMode( MotorLimitPositivePin, INPUT_PULLUP );      
}      

//-- Button Software Debounce
//--
#define SwitchDebounce( ) \
  delay( 5 )

//-- Map 4-bits to Analog Value
//--
inline uint16_t MotorMapValue( 
  uint8_t value )
{  
  //-- 0..15 -> 1000..100us 
  //--
  return 1000 - ( 900 * ( value > 0xF ? 0xF : value ) ) / 0xF; 
}