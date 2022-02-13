// RobotBuilder Version: 4.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// ROBOTBUILDER TYPE: RobotContainer.

#include "RobotContainer.h"
#include <frc2/command/ParallelRaceGroup.h>
#include <frc/smartdashboard/SmartDashboard.h>



RobotContainer* RobotContainer::m_robotContainer = NULL;

RobotContainer::RobotContainer() : m_autonomousCommand() {

    // Smartdashboard Subsystems


    // SmartDashboard Buttons
    frc::SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());
    frc::SmartDashboard::PutData("Line Align Command", new LineAlignCommand(&m_drivetrain));

    ConfigureButtonBindings();

    m_chooser.SetDefaultOption("Autonomous Command", new AutonomousCommand());

    frc::SmartDashboard::PutData("Auto Mode", &m_chooser);

}

RobotContainer* RobotContainer::GetInstance() {
    if (m_robotContainer == NULL) {
        m_robotContainer = new RobotContainer();
    }
    return(m_robotContainer);
}

void RobotContainer::ConfigureButtonBindings() {

    frc::XboxController* driveController     = getXboxDriveController();
    
    // mechanismController is commented out for now but when you need it to reference buttons on it,
    // it's here and all you have to do is uncomment it to reference it - just got tired of the unused
    // warnings from every build - zog
    //frc::XboxController* mechanismController = getXboxMechanismController();

    frc2::JoystickButton m_xboxButton_A{driveController, (int)frc::XboxController::Button::kA};
    frc2::JoystickButton m_xboxButton_X{driveController, (int)frc::XboxController::Button::kX};

    m_xboxButton_A.WhenPressed(LineAlignCommand( &m_drivetrain), true);
    //m_xboxButton_X.WhenPressed(m_drivetrain.m_lineAlignCommand->Cancel(), true);
}

frc::XboxController* RobotContainer::getXboxDriveController() {
   return &m_xboxDriveController;
}

frc::XboxController* RobotContainer::getXboxMechanismController() {
   return &m_xboxMechanismController;
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // The selected command will be run in autonomous
  return m_chooser.GetSelected();
}