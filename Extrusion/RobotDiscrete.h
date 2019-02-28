//-- Robot     Ardbox   FSM
//-- Bit 0 --> I0.? --> Case Bit 0   \
//-- Bit 1 --> I0.? --> Case Bit 1    \
//-- Bit 2 --> I0.4 --> Case Bit 2      --> 64 Cases
//-- Bit 3 --> I0.5 --> Case Bit 3    /
//-- Bit 4 --> I0.6 --> Case Bit 4  /
//-- Bit 5 --> I0.7 --> LOW         --> Discrete States
//-- Bit 6 --> I0.8 --> LOW         --> Not a Message
//-- Bit 7 --> I0.9 --> HIGH        --> Robot Enabled


//-- Predefined State Examples
//--
static const uint8_t RobotMessageReturnToIdle = B00000000;
static const uint8_t RobotMessageSlowPositive = B00000001;
static const uint8_t RobotMessageSlowNegative = B00000010;
static const uint8_t RobotMessageFastPositive = B00000011;
static const uint8_t RobotMessageFastNegative = B00000100;

//-- State Message Processing
//--
void RobotRespondToDiscreteState( )
{
  switch( RobotState & 0x3F )
  {
    case RobotMessageReturnToIdle:
    {
      ConsolePrint( ">> Robot Idle" );
      ConsoleSetTalk( false );
      MotorSetHalt( );
      ConsoleSetTalk( true );
    }
    break;

    case RobotMessageSlowPositive:
    {
      ConsolePrint( ">> Robot Pulse +500" );
      MotorSetStep( +500 );
    }
    break;

    case RobotMessageSlowNegative:
    {
      ConsolePrint( ">> Robot Pulse -500" );
      MotorSetStep( -500 );
    }
    break; 

    case RobotMessageFastPositive:
    {
      ConsolePrint( ">> Robot Pulse +100" );
      MotorSetStep( +100 );
    }
    break;

    case RobotMessageFastNegative:
    {
      ConsolePrint( ">> Robot Pulse -100" );
      MotorSetStep( -100 );
    }
    break;     

    //-- etc other states

    default:
    {      
      //-- Turn Motor Off for Safety
      //--
      ConsolePrint( ">> Robot Defaulted ", 
        RobotState & 0x3F );
      MotorSetHalt( );
    }
    break;
  }  
}
