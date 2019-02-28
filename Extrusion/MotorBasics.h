//-- Idle Motor
//--
inline void MotorIdle( )
{  
}

//-- Spin Motor
//--
inline void MotorSetStep( )
{
  ConsolePrint( ">> Motor Step" );
  MotorSetRunning( true );
}

//-- Spin Motor Shortcut
//--
inline void MotorSetStep( 
  int32_t pulse )
{
  if( MotorSetPulseValue( abs( pulse ) ) )
  {
    ConsolePrint( ">> Motor Step" );
    MotorSetDirection( pulse < 0 ? -1 : 1 );
    MotorSetRunning( true );
  }
}

//-- Halt Motor
//--
inline void MotorSetHalt( )
{
  ConsolePrint( ">> Motor Halt" );
  MotorSetRunning( false );
}

//-- Step Motor
//--
inline bool MotorStep( )
{
  //-- Check Limits 
  //--
  #ifdef MotorUseLimits
    if( !MotorAllowMove( ) )
    {
      MotorSetHalt( );
      ConsolePrint( ">> Limit Reached" ); 
      return false;
    }
  #endif

  //-- Issue Step Pulse
  //--
  #ifdef MotorUseStepper
    MotorPulseToggle( );  
    delayMicroseconds( 
      MotorPulseValue );
  #endif

  //-- Count Steps
  //--
  MotorPosition += MotorDirection;
  return true;
}