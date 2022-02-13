//  Constants.h
//
// robot-wide constant values

#include <units/time.h>

#pragma once


namespace   Porterbots {
// All CAN IDs are captured here
//
// Note that the actual devices need to be configured to USE these IDs so that
// they respond at this address

    namespace CAN_ID {

        int const     kMotorRightFrontID = 10;
        int const     kMotorRightRearID  = 11;
        int const     kMotorLeftFrontID  = 12;
        int const     kMotorLeftRearID   = 13;

    }

    namespace Drivetrain {

        double const    kMaxOutput      = 1.0;

        bool const      kSafetyEnabled  = true;
        constexpr auto  kExpirationTime = 0.1_s;
    
        bool const      kOperatorCommand = false;               // used to distinguish operator from automated control
        bool const      kAutoCommand     = true;                // when we start autonomous command sequences (whenever they start)
                                                                // we want to suppress any operator robot movement commands
    }

    namespace Controller {

        int const       kDriveController     = 0;
        int const       kMechanismController = 1;    
    }

    namespace LineDetection {

        // these are the digital I/O ports where the line sensors are connected
        int const       kLeftLineSensor      = 0;
        int const       kRightLineSensor     = 1;

        // speed used for line detection and alignment moves
        double const    kLineAlignSpeed = 0.2;
}


}
