//-- Get Robot State from IRC5 Controller
//--
inline uint8_t RobotGetState( )
{
  RobotStore = RobotState;
  RobotState = RobotGetStateFast( );

  #ifdef Debug
    ConsolePrintBin( ">> Robot Safe ", RobotState );                
  #endif

  return RobotState;
}

//-- Has Robot State Changed?
//--
inline bool RobotHasChangedState( )
{
  return RobotState != RobotStore;
}

//-- Robot is Enabled?
//--
inline bool RobotIsEnabled( )
{
  return ( RobotState & 0x80 ) != 0;
}

//-- Robot in Message Mode?
//--
inline bool RobotIsMessage( )
{
  return ( RobotState & 0x40 ) != 0;
}

//-- Robot in Analog Signal Mode
//--
inline bool RobotIsAnalogSignal( )
{
  return ( RobotState & 0x20 ) != 0;
}

//-- Get Robot Data Bits
//--
inline uint8_t RobotGetNibble( )
{
  return RobotState & 0xF;
}
