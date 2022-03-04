// RobotContainer.h

#pragma once

#include <frc/smartdashboard/SendableChooser.h>
#include <frc2/command/Command.h>

#include "subsystems/Drivetrain.h"

#include "commands/AutonomousCommand.h"
#include "commands/LineAlignCommand.h"
#include "commands/PorterbotDrive.h"
#include "commands/MovingSolenoidBasic.h"

#include <frc/XboxController.h>
#include <frc2/command/button/JoystickButton.h>

#include "Constants.h"


class RobotContainer {

public:

    frc2::Command* GetAutonomousCommand();
    static RobotContainer* GetInstance();

    // The robot's subsystems

private:

    RobotContainer();

    // controllers
    frc::XboxController m_xboxDriveController{Porterbots::Controller::kDriveController};
    //frc::XboxController m_xboxMechanismController{Porterbots::Controller::kMechanismController};

    // subsystems
    Drivetrain   m_drivetrain;

    // commands
    AutonomousCommand m_autonomousCommand;
    LineAlignCommand  m_lineAlignCommand;
    MovingSolenoidBasic m_solenoidCommand;

    frc::SendableChooser<frc2::Command*> m_chooser;

    static RobotContainer* m_robotContainer;

    void ConfigureButtonBindings();
};