// Drivetrain.h

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/DigitalInput.h>
#include <frc/DoubleSolenoid.h>

#include <ctre/phoenix.h>


#include "Constants.h"

#ifndef ZOGBOT
#include <ctre/phoenix.h>
#else   // ZOGBOT
#include <rev/CANSparkMax.h>
#endif  // ZOGBOT


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

    frc::DoubleSolenoid m_intakeCylinder{Porterbots::CAN_ID::kPcmID, frc::PneumaticsModuleType::CTREPCM,
                                         Porterbots::Solenoids::kSolenoidPort1, Porterbots::Solenoids::kSolenoidPort2};
                                         
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
