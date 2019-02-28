//-- Get Motor Configuration
//--
inline bool MotorGetConfigured( )
{
  return MotorConfigured;
}

//-- Set Motor Configuration
//--
inline void MotorSetConfigured(
  bool configured )
{
  MotorConfigured = configured;
}

//-- Initialize Automatic Configuration
//--
inline void MotorConfigure( )
{
  #ifdef MotorUseLimits
    StateChange( StateFind );
  #else
    ConsolePrint( ">> Configuration Not Supported" );
  #endif
}

//-- Configuration Sequence
//--
inline void MotorFind( )
{
  switch( State )
  {
    //-- Begin Calibration
    //--
    case StateFindInitialize:
    {
      //-- Find Low Limit
      //--
      MotorSetConfigured( false );
      MotorSetDirection( -1 );
      MotorSetPulseValue( 200 );
      MotorSetRunning( true );
      StateChange( StateFindNegative );
    }
    break;

    //-- Low Limit Detection
    //--
    case StateFindNegative:
    {
      //-- Until Limit Switch
      //--
      if( !MotorStep( ) )
      {
        //-- Find High Limit
        //--
        ConsolePrint( ">> Negative Limit Registered" );
        MotorSetPosition( 0 );
        MotorSetDirection( 1 );
        MotorSetRunning( true );
        StateChange( StateFindPositive );
      }
    }
    break;

    //-- High Limit Detection
    //--
    case StateFindPositive:
    {
      //-- Until Limit Switch
      //--
      if( !MotorStep( ) )
      {
        //-- Complete Calibration
        //-- 
        ConsolePrint( ">> Positive Limit Registered" );
        MotorSetMotionRange( MotorGetPosition( ) );
        MotorSetConfigured( true );
        ConsolePrint( ">> Motion Range 0..", MotorGetMotionRange( ) );

        //-- Goto Middle
        //--
        MotorSetAbsolute( 
          MotorGetMotionRange( ) / 2 );
        MotorSetDirection( -1 );        
        MotorSetRunning( true );
        StateChange( StateGoto );
      }
    }
    break;
  }
}