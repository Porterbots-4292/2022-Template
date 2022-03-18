//  Constants.h
//
// robot-wide constant values

#include <units/time.h>

#include <iostream>             // mostly for cout-style debugging

#pragma once


// enable this define to build vary the build for mr herzog's
// test righ that uses soem slightly different hardware including fewer drive motors
// as well as the REV Robotics ZOGBOT motor controllers
//
// if ZOGBOT is not defined, the code will build for the Porterbots' configuration
// using Cross the Road Electronics VictorSPX motor controllers and a pair of motors on each side
//
// be sure comment out the next line for a normal Porterbots build (that should be the default)
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
//#define     ZOGBOT


namespace   Porterbots {
// All CAN IDs are captured here
//
// Note that the actual devices need to be configured to USE these IDs so that
// they respond at this address

    namespace CAN_ID {
        // drive motors
        int const       kMotorRightFrontID = 10;
        int const       kMotorRightRearID  = 11;
        int const       kMotorLeftFrontID  = 12;
        int const       kMotorLeftRearID   = 13;

        int const       kMotorIntake       = 15;

        int const       kPcmID             = 21;


        // Climb motors
        int const       kClimbMotorLeft    =   16;
        int const       kClimbMotorRight   =   17;

    }

    namespace DIOPorts {
            int const   kEncoderLeftAPort = 4;
            int const   kEncoderLeftBPort = 5;
            int const   kEncoderRightAPort = 2;
            int const   kEncoderRightBPort = 3;
            

    }

    namespace Drivetrain {

        int const       kDriveModeArcade   = 0;
        int const       kDriveModeTank     = 1;
        int const       kDriveModeDefault  = kDriveModeArcade;
        
        double const    kControlScaleFactor = 0.5;
#ifndef ZOGBOT
        double const    kMaxOutput      = 0.5;
#else   // ZOGBOT
        double const    kMaxOutput      = 0.1;
#endif   // ZOGBOT
        // for safety
        bool const      kSafetyEnabled  = true;
        constexpr auto  kExpirationTime = 0.1_s;

        // reduce the low speed sensitivity
        bool const      kDriveSquareInputs = true;   

    }

    namespace Intake {
        int const       kIntakeLoadSpeed     = 0.5;
        int const       kIntakeScoreSpeed    = 1.0;
    }

    namespace Pneumatics{
            // The compressor will activate when the pressure drops below the min, and it will
            // continue to stay on until the pressure hits the max
            int const kMinPressure = 50;
            int const kMaxPressure = 100;
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

        double const kRotateSpeed = 0.4;

#ifndef ZOGBOT
        double const    kLineAlignSpeed = 0.4;
#else // ZOGBOT
        double const    kLineAlignSpeed = 0.5;
#endif  // ZOGBOT
    }

    namespace Solenoids {
            int const   kSolenoidPort1 = 0;
            int const   kSolenoidPort2 = 1;
    }

    namespace RobotSpecs {
            double const kWheelDiameter = 6;
            double const kGearRatio = 1;
            double const kPulsesPerRevolution = 360;
    }

    namespace MoveXDistance {
            double const kWheelSpeed = 0.3;
    }

    namespace Climb {
            double const kLowerSpeed = -0.1;
            double const kRaiseSpeed = 0.1;
    }

}

