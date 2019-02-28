//-- Console Data
//--
static const uint8_t ConsoleCapacity = 32;
static char ConsoleBytes[ConsoleCapacity]; 
static uint8_t ConsoleCount;

//-- Communication States
//--
static bool ConsoleEcho;
static bool ConsoleTalk;

//-- Setup Communications
//--
inline void ConsoleSetup( )
{
  ConsoleEcho  = false;
  ConsoleTalk  = true;
  ConsoleCount = 0;

  Serial.begin( 9600 );
  delay( 1000 );
}

//-- Process Incoming Messages
//--
void ConsoleProcess( )
{
  //-- Read Bytes
  //--
  ConsoleCount = 0;
  while( Serial.available( ) > 0 )
  {
    ConsoleBytes[ConsoleCount] = Serial.read( );

    //-- Skip CRLF
    //--
    if( ConsoleBytes[ConsoleCount] == 13 
     || ConsoleBytes[ConsoleCount] == 10 ) 
     continue;
    
    //-- Buffer Overflow FTW
    //--
    ++ConsoleCount;
  }
  
  //-- Null Terminate
  //--
  ConsoleBytes[ConsoleCount] = 0;

  if( ConsoleCount > 0 )
  {
    //-- Echo
    //--
    if( ConsoleEcho )
    {
      Serial.print( "<< " );
      Serial.println( ConsoleBytes );
    }
  }
}

//-- Available Message Data?
//--
inline bool ConsoleIsAvailable( )
{
  return ConsoleCount != 0;
}

//-- Reset Communications Buffer
//--
inline void ConsoleReset( )
{
  ConsoleCount = 0;
}

//-- Get Echo Mode
//--
inline bool ConsoleGetEcho( )
{
  return ConsoleEcho;
}

//-- Set Echo Mode
//--
inline bool ConsoleSetEcho( 
  bool echo )
{
  return ConsoleEcho = echo;
}

//-- Get Talk Mode
//--
inline bool ConsoleGetTalk( )
{
  return ConsoleTalk;
}

//-- Set Talk Mode
//--
inline bool ConsoleSetTalk( 
  bool talk )
{
  return ConsoleTalk = talk;
}

//-- Print Simple Text Message
//--
inline void ConsolePrint( 
  const char* text )
{
  if( ConsoleTalk ) 
  {
    Serial.println( text );  
  }
}

//-- Print Text and Suffix
//--
template<typename Type>
inline void ConsolePrint( 
  const char* text, Type number )
{
  if( ConsoleTalk ) 
  {
    Serial.print( text );  
    Serial.println( number );  
  }
}

//-- Print Text and Suffix
//--
template<typename Type>
inline void ConsolePrintHex( 
  const char* text, Type value )
{
  if( ConsoleTalk ) 
  {
    Serial.print( text );  
    Serial.println( value, HEX );  
  }
}

//-- Print Text and Suffix
//--
template<typename Type>
inline void ConsolePrintBin( 
  const char* text, Type value )
{
  if( ConsoleTalk ) 
  {
    Serial.print( text );  
    Serial.println( value, BIN );  
  }
}