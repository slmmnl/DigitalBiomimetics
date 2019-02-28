//-- State Definitions
//--
static const uint8_t StateIdle            = 0x00;
static const uint8_t StateStep            = 0x10;
static const uint8_t StateGoto            = 0x20;
static const uint8_t StateFind            = 0x30;
static const uint8_t StateFindInitialize  = 0x30;
static const uint8_t StateFindPositive    = 0x31;
static const uint8_t StateFindNegative    = 0x32;

//-- State Variable
//--
static uint8_t State;
static uint8_t Safety;

//-- Change State
//--
inline void StateChange( 
  uint8_t state )
{
  #ifdef Debug
    ConsolePrint( ">> State Change ", state );
  #endif

  State = state;
}

//-- Primary State
//--
inline uint8_t StateGetPrimary( )
{
  return State & 0xF0;
}

//-- Secondary State
//--
inline uint8_t StateGetSecondary( )
{
  return State & 0x0F;
}
