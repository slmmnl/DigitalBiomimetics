//-- Ardbox Analog Configuration
//--
#ifdef ArdboxAnalog  
                                       //-- Robot    Ardbox
  static const uint8_t RobotBit0 =  8; //-- DO00 --> I0.2
  static const uint8_t RobotBit1 =  4; //-- DO01 --> I0.3
  static const uint8_t RobotBit2 = A5; //-- DO02 --> I0.4
  static const uint8_t RobotBit3 = A4; //-- DO03 --> I0.5
  static const uint8_t RobotBit4 = A3; //-- DO04 --> I0.6
  static const uint8_t RobotBit5 = A2; //-- DO05 --> I0.7
  static const uint8_t RobotBit6 = A1; //-- DO06 --> I0.8
  static const uint8_t RobotBit7 = A0; //-- DO07 --> I0.9

  //-- Assemble State from Ports
  //-- Faster than digitalRead( )
  //--
  #define RobotGetStateFast( ) \
      ( ( PINF & 0xF0 ) << 0 ) \
    | ( ( PINF & 0x03 ) << 2 ) \
    | ( ( PIND >> 3 ) & 0x02 ) \
    | ( ( PINB >> 4 ) & 0x01 ) 

#endif

//-- Ardbox Relay Configuration
//--
#ifdef ArdboxRelay
                                       //-- Robot    Ardbox
  static const uint8_t RobotBit0 =  2; //-- DO00 --> I0.0  -- !!! I2C Pins
  static const uint8_t RobotBit1 =  3; //-- DO01 --> I0.1  -- !!!
  static const uint8_t RobotBit2 = A0; //-- DO02 --> I0.4
  static const uint8_t RobotBit3 = A1; //-- DO03 --> I0.5
  static const uint8_t RobotBit4 = A2; //-- DO04 --> I0.6
  static const uint8_t RobotBit5 = A3; //-- DO05 --> I0.7
  static const uint8_t RobotBit6 = A4; //-- DO06 --> I0.8
  static const uint8_t RobotBit7 = A5; //-- DO07 --> I0.9

  //-- Assemble State from Ports
  //-- Faster than digitalRead( )
  //--
  #define RobotGetStateFast( ) \
      ( ( PINF << 7 ) & 0x80 ) \
    | ( ( PINF << 5 ) & 0x40 ) \
    | ( ( PINF << 1 ) & 0x20 ) \
    | ( ( PINF >> 1 ) & 0x10 ) \
    | ( ( PINF >> 3 ) & 0x08 ) \
    | ( ( PINF >> 5 ) & 0x04 ) \
    | ( ( PIND << 1 ) & 0x02 ) \
    | ( ( PIND >> 1 ) & 0x01 )
#endif
