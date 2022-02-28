// RobotContainer.h

#pragma once

#include <frc/smartdashboard/SendableChooser.h>
#include <frc2/command/Command.h>

#include "subsystems/Drivetrain.h"
#include "subsystems/Spinner.h"
#include "subsystems/IMU.h"

#include "commands/AutonomousCommand.h"
#include "commands/LineAlignCommand.h"
#include "commands/SpinnerCommand.h"
#include "commands/PorterbotDrive.h"

#include <frc/XboxController.h>
#include <frc2/command/button/JoystickButton.h>

#include "Constants.h"


class RobotContainer {

public:

    frc2::Command* GetAutonomousCommand();
    static RobotContainer* GetInstance();

    Spinner      m_spinner;

private:

    RobotContainer();

    // controllers
    frc::XboxController m_xboxDriveController{Porterbots::Controller::kDriveController};
    //frc::XboxController m_xboxMechanismController{Porterbots::Controller::kMechanismController};

    // subsystems
    Drivetrain   m_drivetrain;
    IMU          m_imu;

    // commands
    AutonomousCommand       m_autonomousCommand;
    LineAlignCommand        m_lineAlignCommand;
    SpinnerRightCommand     m_spinnerRightCommand;
    SpinnerLeftCommand      m_spinnerLeftCommand;

    frc::SendableChooser<frc2::Command*> m_chooser;

    static RobotContainer* m_robotContainer;

    void ConfigureButtonBindings();
};