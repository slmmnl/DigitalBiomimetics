//-- Robot State Variables
//--
static uint8_t RobotStore;
static uint8_t RobotState;

//-- Robot Instruction Buffer
//--
static const uint8_t RobotCapacity = 32;
static char RobotBytes[RobotCapacity];
static uint8_t RobotCount;

//-- Robot Clock State
//--
static bool RobotClock;