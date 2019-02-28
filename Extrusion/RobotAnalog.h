//-- Robot     Ardbox    Analog
//-- Bit 0 --> I0.? -->  Data 0     |
//-- Bit 1 --> I0.? -->  Data 1     | 
//-- Bit 2 --> I0.4 -->  Data 2     | --> 5-bit DAC
//-- Bit 3 --> I0.5 -->  Data 3     |
//-- Bit 4 --> I0.6 -->  Direction  |
//-- Bit 5 --> I0.7 -->  HIGH         --> Analog Signal
//-- Bit 6 --> I0.8 -->  LOW          --> Not a Message
//-- Bit 7 --> I0.9 -->  HIGH         --> Robot Enabled

//-- Get Robot Direction
//--
inline int8_t RobotGetDirection( )
{
  return ( RobotState & 0x10 ) != 0 ? -1 : 1;
}

//-- Get Robot Digital to Analog 
//--
inline uint16_t RobotGetAnalogValue( )
{
  return MotorMapValue( RobotGetNibble( ) );
}

//-- Respond to Analog Signal
//--
inline void RobotRespondToAnalogSignal( )
{
  ConsolePrint( ">> Robot Analog ", 
    (int32_t)RobotGetDirection( ) * 
    RobotGetAnalogValue( ) );
  
  MotorSetDirection( 
    RobotGetDirection( ) );

  if( MotorSetPulseValue( 
    RobotGetAnalogValue( ) ) )
    MotorSetStep( );
}