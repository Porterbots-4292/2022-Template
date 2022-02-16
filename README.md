# zogbot
 Template Command-based Robot to start off the 2022 robot code with - it's not the robot but a place to put the code to operate the robot.
 
 ## Subsystems
 Defines a single subsystem:
 
 * Drivetrain
 
 ## Commands
 Defines three commands:
 
 * Autonomous (which does nothing right now)
 * LineAlign
   * For right now, it just moves the robot until either of the line sensors detect a line and then the robot stops and the command sequence ends
     * This is where the real line alignment code will go - turn and move the robot appropriately using the pair of line sensors to detect the line and align the robot with the line
     * It is active so long as the "A" button on the driver's controller (controller 0) is active
     * When the button is released, the command will end
     * This allows the operator to abort the line alignment operation if for some reason it does not operate correctly
   * While the command is in operation, the robot cannot be driven manually - the normal driving controls will have no effect
   * When the command ends, either by successfully aligning to the line or by releasing the "A" button, manual driving control of the robot will be restored
 * PorterbotDrive
   * This the default command to drive the robot
   * It reads the appropriate joystick inputs from the drivers controller and calls the Drive method in the Drivetrain class using those values
     * The Drive method can pointed at either the Arcade or Tank drive methods which are part of the frc::DifferentialDrive class to suport either driving style and allow the robot's driving style to be switched very quickly
     * Currently, it is setup to support Arcade-style driving
      * Left joystick forward and back for speed
      * Right joystick left and right for turning
    * The Drive method also provides a place for specifying optional input squaring for better low speed control (currently on by default as defined in "Constants.h")

## Constants.h
The "Constants.h" file defines the various addresses, constants, and other key parameters for the robot code to use.  It is included by most of the headers files in use so you'll typically not need to explicitly include it in a .cpp file.  This file is located in the src/main/include directory (same level as Robot.h and RobotContainer.h) and can be included by any file needing it like this:

```cpp
#include "Constants.h"
```

There are several important constants defined here:

All of the constants are in the "Porterbots" namespace with other namespaces located inside of it
```cpp
namespace   Porterbots
```
To use the constants, reference the Porterbots namespace, the speciic namespace for the constant, and then the constant itself.

For example, to get the CAN ID of the left front motor, use:
```cpp
Porterbots::CAN_ID::KMotorLeftFrontID
```

CAN bus IDs are defined in the "CAN_ID" namespace - note that this defines them for the software to access but the actual CAN devices will need to have their IDs configured using whatever method is appropriate (using the CTRE Phoenix Tuner tool to configure the VictorSPX motor controllers for example)
```cpp
    namespace CAN_ID {
        int const     kMotorRightFrontID = 10;
        int const     kMotorRightRearID  = 11;
        int const     kMotorLeftFrontID  = 12;
        int const     kMotorLeftRearID   = 13;
    }
```
There are several drivetrain-related constants including setting the maximum motor output, enabling subsystem safety, and setting the safety timeout - you probably won't need to mess with these.

There is also a flag to enable or disable "input squaring" - when true this can give substantially better low-speed control (it's a boolean constant).
```cpp
    namespace Drivetrain {
        double const    kMaxOutput      = 1.0;

        bool const      kSafetyEnabled  = true;
        constexpr auto  kExpirationTime = 0.1_s;

        // reduce the low speed sensitivity
        bool const       kDriveSquareInputs = true;   
    }
```

Controller constants are defined in the Controller namespace - these should correspond to controller slots on the Driver Station and you can see and set them there by clicking on the USB symbol on the left edge of the Driver Station window.  Right now, there are two controllers defined - one to "drive" the robot and the other to operate "mechanisms". At this time, only the drive controller is used by the template code.

Note that you don't need to define controller buttons here - these are already defined in the FRC header files and should be used when you want to access any specific button on a controller.
```cpp
    namespace Controller {
        int const       kDriveController     = 0;
        int const       kMechanismController = 1;    
    }
```

There are several constants which impact the LineDetection system.  This includes identifying the ports the left and right line sensors are connected to on the roboRIO as well as the speed the robot should move at when searching for the line - that speed will probably need to be adjusted depending on how well and how reliably the line alignment code works.  We probably want to move as quickly as we can and still be reliable with maybe slowing things down a little for competition in hopes of getting a little more reliability in a slightly different environment.
```cpp
    namespace LineDetection {
        int const       kLeftLineSensor      = 0;
        int const       kRightLineSensor     = 1;
        
        double const    kLineAlignSpeed = 0.2;
    }
```

There is also a single line near the top of the "Constants.h" file that controls how the software builds and what motor controllers are used for the drivetrain:
```cpp
//#define ZOGBOT
```

If this line is commented out, the robot code will build to use only two REV Robotics SparkMAX motor controllers and their associated NEO brushless motors for the drivetrain. This reflects Mr. Herzog's test rig and allows the sharing of code for development and testing between the school robot and Mr. Herzog's test rig.

For normal Porterbot robot builds, this line should be commented out.
