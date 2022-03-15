// RobotContainer.h

#pragma once

#include <frc/smartdashboard/SendableChooser.h>

#include <frc2/command/Command.h>

#include "Constants.h"

#include "subsystems/Drivetrain.h"
#include "subsystems/Intake.h"
#include "subsystems/Climb.h"

#include "commands/AutonomousCommand.h"
#include "commands/LineAlignCommand.h"
#include "commands/PorterbotDrive.h"
#include "commands/MovingSolenoidBasic.h"
#include "commands/TestMagneticSwitchCommand.h"

#include <frc/XboxController.h>
#include <frc2/command/button/JoystickButton.h>


#include <frc/Encoder.h>
#include <frc/DigitalInput.h>


class RobotContainer {

public:

    frc2::Command* GetAutonomousCommand();
    static RobotContainer* GetInstance();

    // The robot's subsystems

    // 5.95 gear ratio
    // 360 PPR
    // 6 In diameter

    frc::Encoder m_encoder{Porterbots::DIOPorts::kEncoderLeftAPort, Porterbots::DIOPorts::kEncoderLeftBPort};
    
private:

    RobotContainer();

    // controllers
    frc::XboxController m_xboxDriveController{Porterbots::Controller::kDriveController};

    // subsystems
    Drivetrain   m_drivetrain;
    Intake       m_intake;
    Climb        m_climb;

    // commands
    AutonomousCommand m_autonomousCommand;
    LineAlignCommand  m_lineAlignCommand;
    MovingSolenoidBasic m_intakeLoadPositionCommand;
    MovingSolenoidBasic m_solenoidReverse;
    MovingSolenoidBasic m_solenoidStop;
    TestMagneticSwitchCommand m_testMagneticSwitchCommand;

    frc::SendableChooser<frc2::Command*> m_chooser;

    static RobotContainer* m_robotContainer;



    void ConfigureButtonBindings();
};