//-- Has Reached Objective
//--
inline bool MotorHasCompleted( )
{
  #ifdef MotorUseStepper
    return MotorPosition 
        == MotorObjective;
  #else
    return true;
  #endif
}

//-- Goto Position Relative/Absolute
//-- 
inline void MotorGoto( )
{
  if( !MotorHasCompleted( ) )
  {
    if( !MotorStep( ) )
    {
      MotorSetHalt( );
      ConsolePrint( ">> Limit Reached" );
    }
  }
  else
  {    
    MotorSetHalt( );
    ConsolePrint( ">> Objective Reached" );
  }
}

//-- Select Direction Based on objective
//--
inline void MotorSelectDirection( )
{
  MotorSetDirection( 
    MotorPosition < MotorObjective ? 1 : -1 );  
}

//-- Relative Motion
//--
inline void MotorSetRelative( 
  int32_t steps, uint16_t pulse )
{
  ConsolePrint( ">> Relative ", steps );  
  MotorObjective = MotorPosition + steps;
  MotorSetPulseValue( pulse );
  MotorSelectDirection( );
  MotorSetRunning( true );
  StateChange( StateGoto );
}

//-- Absolute Motion
//--
inline void MotorSetAbsolute( 
  int32_t objective, uint16_t pulse = 0xFFFF )
{
  #ifdef MotorUseLimits
    if( !MotorConfigured )
    {
      ConsolePrint( ">> Limits Not Configured" );    
      return;
    }

    ConsolePrint( ">> Absolute ", objective );  
    if( objective > MotorMotionRange 
     || objective < 0 )
    {
      ConsolePrint( ">> Beyond Limit ", MotorMotionRange );    
      return;
    }

    MotorObjective = objective;
    if( pulse != 0xFFFF )
      MotorSetPulseValue( pulse );
    MotorSelectDirection( );
    StateChange( StateGoto );
  #else
    ConsolePrint( ">> Absolute Motion Not Supported" );    
  #endif
}