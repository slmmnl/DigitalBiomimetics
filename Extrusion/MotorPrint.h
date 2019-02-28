//-- Print Motor Pulse Value
//--
inline void MotorPrintPulseValue( )
{
  ConsolePrint( ">> Motor Pulse Value ", 
    MotorPulseValue );
}

inline void MotorPrintDirection( )
{
  ConsolePrint( ">> Motor Direction ", 
    MotorDirection < 0 ? '-' : '+' );
}

inline void MotorPrintLimits( )
{
  #ifdef MotorUseLimits
    ConsolePrint( ">> Motor Limits Positive ", MotorGetLimitPositive( ) );
    ConsolePrint( ">> Motor Limits Negative ", MotorGetLimitNegative( ) );
  #else
    ConsolePrint( ">> Motor Limits Not Supported" );
  #endif
}

inline void MotorPrintPosition( )
{
  ConsolePrint( ">> Position  ", MotorPosition  );
  ConsolePrint( ">> Objective ", MotorObjective );
}