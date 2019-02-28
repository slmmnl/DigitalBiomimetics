//-- Get Motor Direction
//--
inline int8_t MotorGetDirection( )
{
  return MotorDirection;
}

//-- Set Motor Direction
//--
inline void MotorSetDirection( 
  int8_t direction )
{
  MotorDirection = direction;

  if( MotorDirection > 0 )
    MotorSetDirectionPositive( ); else
    MotorSetDirectionNegative( );
}

//-- Get Motor Position
//--
inline int32_t MotorGetPosition( )
{
  return MotorPosition;
}

//-- Set Motor Calibration
//--
inline void MotorSetPosition(
  int32_t position )
{
  MotorPosition = 
    position;
}

//-- Get Motor Motion Range
//--
inline int32_t MotorGetMotionRange( )
{
  return MotorMotionRange;
}

//-- Set Motor Motion Range
//--
inline void MotorSetMotionRange(
  int32_t motion_range )
{
  MotorMotionRange = 
    motion_range;
}

//-- Get Motor Pulse Value
//--
inline uint16_t MotorGetPulseValue( )
{
  return MotorPulseValue;
}

//-- Set Motor Pulse Value
//--
inline bool MotorSetPulseValue( 
  uint16_t value )
{
  #ifdef MotorUseStepper
    if( value == 0 ) 
      return false;
  #endif

  #ifdef MotorUseDC
    if( value > 0x80 )
    {
      ConsolePrint( ">> Value Limited" );
      value = 0x80;
    }

    if( MotorRunning )
    {
      analogWrite( 
        MotorPulsePin, value );
    }
  #endif

  MotorPulseValue = value;
  return true;
}

//-- Get Motor Running State
//--
inline void MotorGetRunning( )
{
  return MotorRunning;
}

//-- Set Motor Running State
//--
inline void MotorSetRunning( 
  bool state )
{
  #ifdef MotorUseStepper
    MotorRunning = state;
    if( MotorRunning )
      StateChange( StateStep ); else
      StateChange( StateIdle );
  #endif

  #ifdef MotorUseDC
    if( state && !MotorRunning )
    {
      if( MotorPulseValue == 0 )
      {
        ConsolePrint( ">> Motor Pulse Zero" );        
        analogWrite( MotorPulsePin, 0 );
        StateChange( StateIdle );
        return;
      }

      analogWrite( 
        MotorPulsePin, 
        MotorPulseValue );

      MotorRunning = true;
      StateChange( StateStep );
    } else 
    
    if( !state && MotorRunning )
    {
      analogWrite( 
        MotorPulsePin, 0 );

      MotorRunning = false;
      StateChange( StateIdle );
    }    
  #endif
}