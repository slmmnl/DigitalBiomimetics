//-- Motor State Variables
//--
static uint16_t MotorPulseValue;
static int8_t   MotorDirection;
static int32_t  MotorPosition;
static int32_t  MotorObjective;
static int32_t  MotorMotionRange;
static bool     MotorConfigured;
static bool     MotorRunning;

//-- Cylinder Configuration
//--
#ifdef MotorUseCylinder
  #include "MotorCylinder.h"
#endif

//-- Syringe Configuration
//--
#ifdef MotorUseSyringe
  #include "MotorSyringe.h"
#endif

//-- Peristaltic Configuration
//--
#ifdef MotorUsePeristaltic
  #include "MotorPeristaltic.h"
#endif

#include "MotorProperties.h"
#include "MotorLimits.h"
#include "MotorBasics.h"
#include "MotorAdvanced.h"
#include "MotorConfigure.h"
#include "MotorPrint.h"

//-- Setup Motor Properties
//--
inline void MotorSetup( )
{
  MotorSetupPins( );
  MotorSetDirection( 1 );  
}

