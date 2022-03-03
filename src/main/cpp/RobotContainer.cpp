// RobotContainer.cpp

#include "RobotContainer.h"
#include <frc2/command/ParallelRaceGroup.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <Constants.h>
#include <frc/DoubleSolenoid.h>


RobotContainer* RobotContainer::m_robotContainer = NULL;

RobotContainer::RobotContainer()
    : m_autonomousCommand(m_drivetrain), m_lineAlignCommand(m_drivetrain) {

    // Smartdashboard Subsystems
    frc::SmartDashboard::PutData(&m_drivetrain);

    // SmartDashboard Buttons
    frc::SmartDashboard::PutData("Autonomous Command", new AutonomousCommand(m_drivetrain));
    frc::SmartDashboard::PutData("Line Align Command", new LineAlignCommand(m_drivetrain));

    ConfigureButtonBindings();

    m_chooser.SetDefaultOption("Autonomous Command", new AutonomousCommand(m_drivetrain));

    frc::SmartDashboard::PutData("Auto Mode", &m_chooser);

    // set the default drivetrain subsystem command
    //
    // this runs when nothing else is using the subsystem - the default command is
    // to take input from the controller and manually drive the robot
    //
    // as soon as any command needs the drivetrain subssytem, this will "take over" the
    // drivetrain - this is how command sequences that need to "drive" the robot do the
    // actual driving without the driver interfering with the command

    switch (Porterbots::Drivetrain::kDriveModeDefault) {

        case Porterbots::Drivetrain::kDriveModeTank:
            m_drivetrain.SetDefaultCommand(PorterbotDrive([this] { return -(m_xboxDriveController.GetLeftY()) * Porterbots::Drivetrain::kControlScaleFactor; },
                                           [this] { return -(m_xboxDriveController.GetRightY()) * Porterbots::Drivetrain::kControlScaleFactor; },
                                           Porterbots::Drivetrain::kDriveModeTank, m_drivetrain));
            //m_drivetrain.SetDefaultCommand(AutonomousCommand(m_drivetrain));
            break;

        default:
            std::cout << "RobotContainer: Invalid drive mode - defaulting to Arcade-style" << std::endl;
            // FALLS THROUGH!!!
        case Porterbots::Drivetrain::kDriveModeArcade:
        
            m_drivetrain.SetDefaultCommand(PorterbotDrive([this] { return -(m_xboxDriveController.GetLeftY()) * Porterbots::Drivetrain::kControlScaleFactor; },
                                           [this] { return m_xboxDriveController.GetRightX() * Porterbots::Drivetrain::kControlScaleFactor; },
                                           Porterbots::Drivetrain::kDriveModeArcade, m_drivetrain));
            break;
    }

    // Adds the solenoid for testing
}

RobotContainer* RobotContainer::GetInstance() {
    if (m_robotContainer == NULL) {
        m_robotContainer = new RobotContainer();
    }
    return(m_robotContainer);
}

void RobotContainer::ConfigureButtonBindings() {  
    // while the "A" button is held, run the line alignment command
    //
    // it will stop when the button is released or when it completes (after aligning hopefully)
    frc2::JoystickButton(&m_xboxDriveController, (int)frc::XboxController::Button::kA).WhenHeld(&m_lineAlignCommand);
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // The selected command will be run in autonomous
  return m_chooser.GetSelected();
}