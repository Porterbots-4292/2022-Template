// RobotContainer.cpp

#include "RobotContainer.h"
#include <frc2/command/ParallelRaceGroup.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Compressor.h>
#include <frc2/command/button/POVButton.h>



RobotContainer* RobotContainer::m_robotContainer = NULL;

RobotContainer::RobotContainer()
    : m_autonomousCommand(m_drivetrain), m_lineAlignCommand(m_drivetrain),
      m_spinnerRightCommand(m_spinner), m_spinnerLeftCommand(m_spinner) {

    // Smartdashboard Subsystems
    frc::SmartDashboard::PutData("DriveTrain:  ", &m_drivetrain);
    frc::SmartDashboard::PutData("Spinner:     ", &m_spinner);
    frc::SmartDashboard::PutData("IMU:         ", &m_imu);

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
            m_drivetrain.SetDefaultCommand(PorterbotDrive([this] { return -(m_xboxDriveController.GetLeftY()); },
                                           [this] { return -(m_xboxDriveController.GetRightY()); },
                                           Porterbots::Drivetrain::kDriveModeTank, m_drivetrain));
            break;

        default:
            std::cout << "RobotContainer: Invalid drive mode - defaulting to Arcade-style" << std::endl;

            // FALLS THROUGH!!!

        case Porterbots::Drivetrain::kDriveModeArcade:
        
            m_drivetrain.SetDefaultCommand(PorterbotDrive([this] { return -(m_xboxDriveController.GetLeftY()); },
                                           [this] { return m_xboxDriveController.GetRightX(); },
                                           Porterbots::Drivetrain::kDriveModeArcade, m_drivetrain));
            break;
    }

    m_solenoid.Set(true);

    frc::Compressor compressor(Porterbots::CAN_ID::kPcmID, frc::PneumaticsModuleType::REVPH);

    compressor.EnableAnalog(0_psi, 120_psi);

    frc::SmartDashboard::PutNumber("Compressor PSI: ", compressor.GetPressureSwitchValue());


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
#ifdef ZOGBOT
    frc2::POVButton leftPOVButton(&m_xboxDriveController, 270);
    frc2::POVButton rightPovButton(&m_xboxDriveController, 90);
    
    leftPOVButton.WhenPressed(&m_spinnerLeftCommand);
    rightPovButton.WhenPressed(&m_spinnerRightCommand);
    frc2::JoystickButton(&m_xboxDriveController, (int)frc::XboxController::Button::kX).CancelWhenPressed(&m_spinnerLeftCommand)
                                                                                      .CancelWhenPressed(&m_spinnerRightCommand);
#endif // ZOGBOT
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
  // The selected command will be run in autonomous
  return m_chooser.GetSelected();
}

void RobotContainer::UpdateDashboard() {
    m_drivetrain.UpdateDashboard();
    m_imu.UpdateDashboard();
    m_climb.UpdateDashboard();
}