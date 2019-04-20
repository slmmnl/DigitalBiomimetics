//-- Command Definitions
//--
static const char CommandGetEcho         = 'e';
static const char CommandSetEcho         = 'E';
static const char CommandGetPulse        = 'p';
static const char CommandSetPulse        = 'P';
static const char CommandGetDirection    = 'd';
static const char CommandSetDirection    = 'D';
static const char CommandSetStep         = 'S';
static const char CommandSetHalt         = 'h';
static const char CommandGetPosition     = '@';
static const char CommandSetRelative     = 'R';
static const char CommandSetAbsolute     = 'A';
static const char CommandGetLimits       = 'l';
static const char CommandSetCalibrate    = 'C';
static const char CommandGetCalibrate    = 'c';
static const char CommandSetGotoNegative = '<';
static const char CommandSetGotoPositive = '>';
static const char CommandSafetyDisable   = 'x';
static const char CommandGetRobotState   = 'q';

//Communication to external Arduino for access to more Pins
static const char CommandSetFlexDemo      = 'F'; //11
static const char CommandSetCloseNoz     = 'o';  //10
static const char CommandSetOpenNoz     = 'O';  //01
static const char CommandSetNozDirection = 'V'; //00

//-- Message Processing Command
//--
void CommandProcess(
  const char* bytes, uint8_t count )
{
  if( count == 0 ) return;

  switch( bytes[0] )
  {
    #pragma region -- Robot State ---------------------------------------------

    case CommandGetRobotState:
    {
      ConsolePrintBin( ">> Robot State ", RobotGetStateFast( ) );
    }
    break;

    #pragma endregion

    #pragma region -- Safety Mode ---------------------------------------------

    case CommandSafetyDisable:
    {
      if( Safety )
        ConsolePrint( ">> Safety Off System Disabled" ); else
        ConsolePrint( ">> Safety On System Enabled"   );
      Safety = !Safety;
    }
    break;

    #pragma endregion

    #pragma region -- Echo Mode -----------------------------------------------

    case CommandGetEcho:
    {
      ConsolePrint( ">> Echo ", ConsoleGetEcho( ) );
    }
    break;

    case CommandSetEcho:
    {
      ConsolePrint( ">> Echo ", ConsoleSetEcho( !ConsoleGetEcho( ) ) );
    }
    break;

    #pragma endregion

    #pragma region -- Limit Switches ------------------------------------------

    case CommandGetLimits:
    {
      MotorPrintLimits( );
    }
    break;

    #pragma endregion

    #pragma region -- Motor Pulse Delay ---------------------------------------

    case CommandGetPulse:
    {
      MotorPrintPulseValue( );
    }
    break;

    case CommandSetPulse:
    {
      if( !MotorSetPulseValue( ParseIntU<uint16_t>(
        bytes, count, MotorGetPulseValue( ) ) ) )
      {
        ConsolePrint( ">> Motor Stopped" );
        MotorSetHalt( );
      }
      else
      {
        MotorPrintPulseValue( );
      }
    }
    break;

    #pragma endregion

    #pragma region -- Motor Direction -----------------------------------------

    case CommandGetDirection:
    {
      MotorPrintDirection( );
    }
    break;

    case CommandSetDirection:
    {
      int8_t value = ParseIntS<int8_t>(
        bytes, count, -MotorGetDirection( ) );

      MotorSetDirection(
        value < 0 ? -1 : 1 );

      MotorPrintDirection( );
    }
    break;

    #pragma endregion

    #pragma region -- Spin/Halt Motor -----------------------------------------

    case CommandSetStep:
    {
      MotorSetStep( );
    }
    break;

    case CommandSetHalt:
    {
      MotorSetHalt( );
    }
    break;

    #pragma endregion

    #pragma region -- Variable Nozzle Control -----------------------------------------

    case CommandSetFlexDemo: //F
    {
      digitalWrite(5, HIGH);
      digitalWrite(6,HIGH);
    }
    break;


    case CommandSetCloseNoz: //o
    {
      digitalWrite(5, HIGH);
      digitalWrite(6,LOW);
    }
    break;

    case CommandSetOpenNoz: // O
    {
      digitalWrite(5, LOW);
      digitalWrite(6,HIGH);
    }
    break;

    case CommandSetNozDirection: //V
    {
      digitalWrite(5, LOW);
      digitalWrite(6,LOW);
    }
    break;

    #pragma endregion

    #pragma region -- Relative Motion -----------------------------------------

    case CommandSetRelative:
    {
      MotorSetRelative( ParseIntS<int32_t>(
        bytes, count, 0 ), MotorGetPulseValue( ) );
    }
    break;

    #pragma endregion

    #pragma region -- Absolute Motion -----------------------------------------

    case CommandSetAbsolute:
    {
      MotorSetAbsolute( ParseIntS<int32_t>(
        bytes, count, 0 ), MotorGetPulseValue( ) );
    }
    break;

    #pragma endregion

    #pragma region -- Goto Low/High -------------------------------------------

    case CommandSetGotoNegative:
    {
      MotorSetAbsolute( 0, 100 );
    }
    break;

    case CommandSetGotoPositive:
    {
      MotorSetAbsolute( MotorGetMotionRange( ), 100 );
    }
    break;

    #pragma endregion

    #pragma region -- Position ------------------------------------------------

    case CommandGetPosition:
    {
      MotorPrintPosition( );
    }
    break;

    #pragma endregion

    #pragma region -- Calibration ---------------------------------------------

    case CommandSetCalibrate:
    {
      MotorConfigure( );
    }
    break;

    case CommandGetCalibrate:
    {
      ConsolePrint( ">> Configured   ", MotorGetConfigured  ( ) );
      ConsolePrint( ">> Motion Range ", MotorGetMotionRange ( ) );
    }
    break;

    #pragma endregion

    default:
    {
      ConsolePrint( ">> Unknown Instruction" );
    }
    break;
  }
}

//-- Execute Command
//--
void CommandProcess( )
{
  //-- First Check Robot
  //--
  if( RobotIsAvailable( ) )
    CommandProcess( RobotBytes, RobotCount );
  RobotReset( );

  //-- Console may override Robot
  //--
  if( ConsoleIsAvailable( ) )
    CommandProcess( ConsoleBytes, ConsoleCount );
  ConsoleReset( );
}
