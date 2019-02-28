//-- Robot     Ardbox    
//-- Bit 0 --> I0.?   |
//-- Bit 1 --> I0.?   |         > Robot Message (see RobotMessage.h)
//-- Bit 2 --> I0.4   |       / 
//-- Bit 3 --> I0.5   |  --> --> Analog Signal  (see RobotAnalog.h)
//-- Bit 4 --> I0.6   |      \ 
//-- Bit 5 --> I0.7   |       > Discrete States (see RobotDiscrete.h)
//-- Bit 6 --> I0.8   | 
//-- Bit 7 --> I0.9  --> Enable 

//-- Robot Logic Components
//--
#include "RobotState.h"
#include "RobotConfiguration.h"
#include "RobotProperties.h"
#include "RobotAnalog.h"
#include "RobotDiscrete.h"
#include "RobotMessage.h"

//-- Setup Robot
//--
inline void RobotSetup( )
{
  pinMode( RobotBit0, INPUT );  
  pinMode( RobotBit1, INPUT );  
  pinMode( RobotBit2, INPUT );  
  pinMode( RobotBit3, INPUT );  
  pinMode( RobotBit4, INPUT );  
  pinMode( RobotBit5, INPUT );  
  pinMode( RobotBit6, INPUT );  
  pinMode( RobotBit7, INPUT );  
}

//-- Process Robot Requests
//--
inline void RobotProcess( )
{
  //-- Read Robot State 
  //--
  RobotGetState( );
  if( !RobotHasChangedState( ) )
  {
    return;
  }

  //-- Ensure Enabled
  //--
  if( !RobotIsEnabled( ) )
  {
    if( MotorRunning )
      MotorSetHalt( );
    ConsolePrint( ">> Robot Disabled" );
    return;
  }

  //-- Dispatch Message
  //--
  if( RobotIsMessage( ) )
  {
    ConsolePrint( ">> Robot Message Mode" );
    RobotRespondToMessage( );
  }
  else
  {
    if( RobotIsAnalogSignal( ) )
    {
      ConsolePrint( ">> Robot Analog Mode" );
      RobotRespondToAnalogSignal( );
    }
    else
    {
      ConsolePrint( ">> Robot Discrete Mode" );
      RobotRespondToDiscreteState( );
    }
  }  
}