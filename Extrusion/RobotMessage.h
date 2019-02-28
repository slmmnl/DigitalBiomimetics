//-- Robot     Ardbox   Message
//-- Bit 0 --> I0.? --> Data 0  |
//-- Bit 1 --> I0.? --> Data 1  |  --> 4-bit Parallel per Clock
//-- Bit 2 --> I0.4 --> Data 2  |
//-- Bit 3 --> I0.5 --> Data 3  |
//-- Bit 4 --> I0.6 --> Reset      --> Reset Failsafe
//-- Bit 5 --> I0.7 --> Clock      --> Clock Pulse
//-- Bit 6 --> I0.8 --> HIGH       --> Message Type
//-- Bit 7 --> I0.9 --> HIGH       --> Robot Enabled

//-- Reset Robot Message
//--
inline void RobotReset( )
{
  RobotCount = 0;
}

//-- Robot Reset Message Request
//--
inline bool RobotIsReset( )
{
  return ( RobotState & 0x10 ) != 0;
}

//-- Robot Message is Available
//--
inline bool RobotIsAvailable( )
{
  return RobotCount != 0;
}

//-- Get Message Clock State
//--
inline bool RobotGetClock( )
{
  return ( RobotState & 0x20 ) != 0;
}

//-- Robot in Receive State
//--
inline bool RobotIsReceiving( )
{
  return RobotIsMessage( ) && 
    RobotClock == RobotGetClock( );
}

//-- Wait for Robot Nibble
//--
bool RobotWaitForNibble( )
{
  while( RobotIsReceiving( ) )
  {
    RobotGetState( );
    delay( 50 );
    if( RobotIsReset( ) )
    {
      ConsolePrint( ">> Reset Received" );
      return false;
    }
  }
  RobotClock = RobotGetClock( );
  return true;
}

//-- Receive Message from Robot
//--
void RobotRespondToMessage( )
{
  RobotCount = 0;
  RobotClock = RobotGetClock( );
  while( RobotIsMessage( ) 
     && !RobotIsReset( ) )
  {    
    //-- Load High Nibble
    //--
    #ifdef Debug
      ConsolePrintBin( ">> HiState: ", RobotState );
    #endif

    uint8_t code = RobotGetNibble( ) << 4;
    if( !RobotWaitForNibble( ) ) break;

    //-- Load Low Nibble
    //--
    #ifdef Debug
      ConsolePrintBin( ">> LoState: ", RobotState );
    #endif

    code |= RobotGetNibble( );
    if( !RobotWaitForNibble( ) ) break;

    //-- Ignore CRLF
    //--
    if( code == 13 
     || code == 10 ) continue;

    //-- Buffer Overflow FTW
    //--
    RobotBytes[RobotCount] = code;
    ++RobotCount;
  }

  if( RobotCount > 0 )
  {
    RobotBytes[RobotCount] = 0;
    ConsolePrint( ">> Robot Request ", RobotBytes );
  }
}