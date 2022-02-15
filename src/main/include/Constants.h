//  Constants.h
//
// robot-wide constant values

#include <units/time.h>

#pragma once


// enable this define to build for the REV Robotics SparkMAX motor controllers
//
// if SPARKMAX is not defined, the code will build for
// Cross the Road Electronics VictorSPX motor controllers
//
// this is because mr herzog doesn't have any VictorSpx controllers on hand but has some
// SparkMAX conttrollers and it'd be nice to be able to test some things remotely
//
// be sure comment out the next line for a normal Porterbots build (that should be the default)
#define     SPARKMAX


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

        // see Drivetrain code for more details on this constant
        double const       kDriveInputSquareValue = 2.0;   

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
        //
        // want to be careful here - we don't want to go so fast that we overshoot things and
        // have to re-align for that reason but we don't want to take forever to line up either
        // so we'll probably end up working up some emperical value that works OK based on our testing
        double const    kLineAlignSpeed = 0.2;
}


}
