// RobotContainer.cpp

#include "RobotContainer.h"
#include <frc2/command/ParallelRaceGroup.h>
#include <frc/smartdashboard/SmartDashboard.h>



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

    m_drivetrain.SetDefaultCommand(PorterbotDrive([this] { return -(m_xboxDriveController.GetLeftY()); },
                                         [this] { return m_xboxDriveController.GetRightX(); },
                                         m_drivetrain));
}

RobotContainer* RobotContainer::GetInstance() {
    if (m_robotContainer == NULL) {
        m_robotContainer = new RobotContainer();
    }
    return(m_robotContainer);
}

void RobotContainer::ConfigureButtonBindings() {

    std::cout << "ConfigureButton Settings - button " << (int)frc::XboxController::Button::kA << std::endl;
    
    frc2::JoystickButton(&m_xboxDriveController, (int)frc::XboxController::Button::kA).WhenPressed(
                                                 LineAlignCommand(m_drivetrain));
    //frc2::JoystickButton(&m_xboxDriveController, (int)frc::XboxController::Button::kX).WhenPressed(LineAlignCommand(m_drivetrain));
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // The selected command will be run in autonomous
  return m_chooser.GetSelected();
}