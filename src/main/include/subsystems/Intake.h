// Intake.h

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/DoubleSolenoid.h>

#include <ctre/phoenix.h>

#include <frc/PneumaticHub.h>
#include "Constants.h"

// enumeration for various high level intake positions - the intake code will handle the actual solenoid positions
enum    eIntakePosition { IntakePosLoad, IntakePosScore, IntakePosTravel, IntakePosStop };

/**
 *
 *
 * @author Lockport Porterbots
 */
class Intake: public frc2::SubsystemBase {
private:
    // It's desirable that everything possible is private except
    // for methods that implement subsystem capabilities

    WPI_VictorSPX m_intakeMotor{Porterbots::CAN_ID::kMotorIntake};

    frc::DoubleSolenoid m_intakeCylinder{Porterbots::CAN_ID::kPcmID, frc::PneumaticsModuleType::REVPH,
                                         Porterbots::Solenoids::kSolenoidPort1, Porterbots::Solenoids::kSolenoidPort2};

    frc::PneumaticHub m_hub{Porterbots::CAN_ID::kPcmID};

public:
    Intake();

    void SetIntakeLoadPosition();
    void SetIntakeScorePosition();
    void SetIntakeTravelPosition();     // might just be the score position with the motors running to keep the balls in??

    void RunIntakeLoad();
    void RunIntakeScore();

    void StopIntake();
    void StopPneumatics();

    void Periodic() override;
    void SimulationPeriodic() override;
};
