// Drivetrain subsystem

#include "subsystems/Drivetrain.h"
#include <frc/smartdashboard/SmartDashboard.h>


Drivetrain::Drivetrain() {

    // this sets up a bunch of stats to display on the LiveWindow
    //
    // we probably don't want this much stuff to show up during competition
    // but for robot development and debugging, it can be very useful to see
    // specific components on the robot are actually doing
    SetName("Drivetrain");

    // FIGURE OUT WHAT ADDCHLD DOES
#ifndef ZOGBOT
    AddChild("Front_Left Motor", &m_leftFrontController);
    AddChild("Rear Left Motor", &m_leftRearController);
    AddChild("Front Right Motor", &m_rightFrontController);
    AddChild("Rear Right Motor", &m_rightRearController);
#endif // ! ZOGBOT

    SetSubsystem("Diff Drive");
    AddChild("Diff Drive", &m_robotDrive);

    SetSubsystem("Line Sensors");
    AddChild("Left", &m_leftLineSensor);
    AddChild("Right", &m_rightLineSensor);

    // these are parameters that apply to the differential drive (overall)
    m_robotDrive.SetSafetyEnabled(Porterbots::Drivetrain::kSafetyEnabled);
    m_robotDrive.SetExpiration(Porterbots::Drivetrain::kExpirationTime);
    m_robotDrive.SetMaxOutput(Porterbots::Drivetrain::kMaxOutput);
 
    // SetInverted to true reverses the "normal" rotation direction of the associated motor
    // controller or controller group - typicaly this is because motors on different sides
    // of the robot are mounted in different direions but we all want them to spin the
    // appropriate direction for them to all move the robot forward
    //
    // if the robot runs "backwards" after using the SetInverted() settings, just flip the
    // true and false values and the robot will switch it's primary direction of travel
    //
    // many times they properties can be pre-configured in the motor controller as part of
    // its offline configuration but it's best to set any parameters important for the robot
    // in software so that if a controller is replaced, any special settings get configured
    // before it gets used and we don't have to count on someone configuring something at
    // the time the component was replaced - they'll still need to set the CAD ID of the
    // replacement controller but all they need to do is get the address right and we can
    // handle the rest
    //
    // some folks go as far as doing a factory reset in the code and then changing *ONLY* what
    // needs changing - this isn't a bad idea either
    //m_leftSideMotors.SetInverted(false);
    //m_rightSideMotors.SetInverted(true);

    
    
#ifdef ZOGBOT
    // seems the SparkMAX controllers don't inherit SetInverted() from the
    // motorcontroller group so we set them individually here - this seems to work
    m_leftFrontController.SetInverted(false);
    m_rightFrontController.SetInverted(true); 
#else
    m_leftFrontController.SetInverted(false);
    m_leftRearController.SetInverted(false);
    m_rightFrontController.SetInverted(true);
    m_rightRearController.SetInverted(true);

#endif// ZOGBOT
}

void Drivetrain::Drive(double input1, double input2, bool square) {
    
    // our default "Drive" routine is Arcade for now but we can change it here if we like
    //
    // this is where the human driver input should go through
    //
    // we can also call the explicit routines to intermingle Arcade and Tank when we want one or
    // the other - could be handy for some command sequences to think about it in one of those ways
    // over the other
    //
    // as to why we're squaring the drive input, it's for smoother control at slow speeds
    //
    // the library squares the input to implement an exponential curve
    // to the joystick response - this gives us a lot more fine low end control because using
    // squaring means that .5 (half joystick) is treated as .25 while a full value of 1.0
    // is still 1.0 (full speed)
    //
    // we can disable "input squaring" by specifying a value of false for kDriveSquareInput
    // in Constants.h    

    m_robotDrive.ArcadeDrive(input1, input2, square);
}

void Drivetrain::TankDrive(double leftSpeed, double rightSpeed, bool square) {

    m_robotDrive.TankDrive(leftSpeed, rightSpeed, square);
}

void Drivetrain::ArcadeDrive(double speed, double turn, bool square) {

    m_robotDrive.ArcadeDrive(speed, turn, square);
}

void Drivetrain::Periodic() {
    // Put code here to be run every loop

}

void Drivetrain::SimulationPeriodic() {
    // This method will be called once per scheduler run when in simulation

}


// Put methods for controlling this subsystem
// here. Call these from Commands.

bool Drivetrain::IsLineDetected(int sensor) {

    // defaulting this to true actually means a line is *NOT* detected
    // since the sensor is seeing the IR being reflected from the carpet
    //
    // the black alignment tape actually does not reflect so the sensor
    // returns false to indicate the line has been found
    //
    // this ensure that if a bad sensor identifier is passed, it will return
    // no line - this seems like the safest bet

    bool sensorReading = true;

    switch (sensor) {

        case Porterbots::LineDetection::kLeftLineSensor:

            sensorReading = m_leftLineSensor.Get();
            break;

        case Porterbots::LineDetection::kRightLineSensor:

            sensorReading = m_rightLineSensor.Get();
            break;
    }

    // we invert the return from the sensor because for us, a "true" indicates
    // the line was found
    return (sensorReading);
}