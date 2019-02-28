//-- Initialize State
//--
inline void StateSetup( )
{
  State  = StateIdle;
  Safety = true;
}

//-- State Machine
//--
inline void StateUpdate( )
{
  if( Safety ) 
  {
    switch( StateGetPrimary( ) )
    {
      case StateIdle: MotorIdle( ); break;  
      case StateStep: MotorStep( ); break;
      case StateGoto: MotorGoto( ); break;
      case StateFind: MotorFind( ); break;
    }
  }
}