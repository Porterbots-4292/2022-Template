//  Constants.h
//
// robot-wide constant values

#include <units/time.h>

#include <iostream>             // mostly for cout-style debugging

#include <rev/CANSparkMax.h>

#pragma once


// enable this define to vary the build for mr herzog's test rig
// that uses a slightly different hardware configuration including fewer drive motors
// as well as the REV Robotics SparkMax motor controllers with NEO brushless motors
//
// if ZOGBOT is not defined, the code will build for the Porterbots' configuration
// using four Cross the Road Electronics VictorSPX motor controllers and a pair of motors on each side
//
// be sure to comment out the next line for a normal Porterbots build (that should be the default)
//
// this also impacts some other robot aspects like turning down the max speed and the speed
// the line alignment code uses to prevent potentially loose motors on the test rig from
// twisting around all over the place 
//
// this is a good example of how we can have a single code base with a few variations in it
// to accomodate different testing environments
//
// the bulk of the code base is totally the same with just a few small differences in the hardware being
// used - we can accomodate the hardware differences and since these differences get wrapped by the higher
// level WPILib functions, the higher level code is unchanged
#define     ZOGBOT


namespace   Porterbots {
// All CAN IDs are captured here
//
// Note that the actual devices need to be configured to USE these IDs so that
// they respond at this address

    namespace CAN_ID {

        int const       kMotorRightFrontID = 10;
        int const       kMotorRightRearID  = 11;
        int const       kMotorLeftFrontID  = 12;
        int const       kMotorLeftRearID   = 13;
        int const       kMotorLeftClimb    = 15;
        int const       kMotorRightClimb   = 16;
        int const       kPcmID             = 21;

#ifdef  ZOGBOT
        int const       kMotorSpinnerID    = 20;
        int const       kPigeonID          = 50;
#endif  // ZOGBOT
    }

    namespace Drivetrain {

        int const       kDriveModeArcade   = 0;
        int const       kDriveModeTank     = 1;
        int const       kDriveModeDefault  = kDriveModeTank;

#ifndef ZOGBOT
        double const    kMaxOutput      = 1.0;
#else   // ZOGBOT
        double const    kMaxOutput      = 0.1;
#endif   // ZOGBOT

        bool const      kSafetyEnabled  = true;
        constexpr auto  kExpirationTime = 0.1_s;

        // reduce the low speed sensitivity
        bool const      kDriveSquareInputs = true;   

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
#ifndef ZOGBOT
        double const    kLineAlignSpeed = 0.2;
#else // ZOGBOT
        double const    kLineAlignSpeed = 0.4;
#endif  // ZOGBOT
        // side moving "forward"
        double const    kLineAlignPivotFastSideSpeed  = kLineAlignSpeed;
        // side moving "backward"
        double const    kLineAlignPivotSlowSideSpeed = -kLineAlignSpeed;
    }

#ifdef ZOGBOT
    namespace DIOPorts {
        int const       kEncoderAPort = 8;
        int const       kEncoderBPort = 9;
    }

    namespace Spinner {
        double const    kSpinnerSpeed = 0.20;

        int const       kTargetDistance = 6 * 12;         // distance in inches
    }

    namespace Climb {
        rev::SparkMaxLimitSwitch::Type const x = rev::SparkMaxLimitSwitch::LimitSwitchPolarity::kNormallyOpen;
        
        rev::CANDigitalInput::LimitSwitchPolarity const       kClimbUpperSwitchMode = rev::SparkMaxLimitSwitch::LimitSwitchPolarity::kNormallyOpen;
    }
    
#endif      // ZOGBOT
}
