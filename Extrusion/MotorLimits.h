//-- Is Motor at Low Limit?
//--
inline bool MotorGetLimitNegative( )
{
  #ifdef MotorUseLimits

    //-- Is Switched?
    //--
    if( MotorGetLimitSwitchNegative( ) ) 
      return false;

    //-- Is it Stable?
    //--
    SwitchDebounce( );

    return !MotorGetLimitSwitchNegative( );
  #else
    return false;
  #endif
}

//-- Is Motor at High Limit?
//--
inline bool MotorGetLimitPositive( )
{
  #ifdef MotorUseLimits

    //-- Is Switched?
    //--
    if( MotorGetLimitSwitchPositive( ) ) 
      return false;

    //-- Is it Stable?
    //--
    SwitchDebounce( );

    return !MotorGetLimitSwitchPositive( );
  #else
    return false;
  #endif
}

//-- Allow Motion in Direction 
//--
inline bool MotorAllowMove( )
{
  #ifdef MotorUseLimits
    if( MotorDirection > 0 )
      return !MotorGetLimitPositive( ); else
      return !MotorGetLimitNegative( );    
  #else
    return true;
  #endif
}