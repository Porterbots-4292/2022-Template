// Climb.h

#pragma once

#include <frc2/command/SubsystemBase.h>

#include <frc/SpeedController.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include "Constants.h"
#include <frc/DigitalInput.h>
#include <rev/CANSparkMax.h>

/**
 *
 *
 * @author Lockport Porterbots
 */

enum ClimbingStates{
    raised,
    lowered,
    intermediate,
    busy,
    stopped
};

class Climb: public frc2::SubsystemBase {
private:
    // Initialize the two motors that will be controlling the arms going up and down
    rev::CANSparkMax m_climbLeftArmMotor{Porterbots::CAN_ID::kClimbMotorLeft, rev::CANSparkMax::MotorType::kBrushless};
    rev::CANSparkMax m_climbRightArmMotor{Porterbots::CAN_ID::kClimbMotorRight, rev::CANSparkMax::MotorType::kBrushless};
    
    frc::MotorControllerGroup m_climbArmMotors{m_climbLeftArmMotor, m_climbRightArmMotor};

    /*
    // Encoders
    rev::SparkMaxRelativeEncoder m_climbLeftArmEncoder;
    rev::SparkMaxRelativeEncoder m_climbRightArmEncoder;
    */

    // This will be the Climb's state
    ClimbingStates m_currentState = ClimbingStates::stopped;

    ClimbingStates m_targetState = ClimbingStates::stopped;

    // WE HAVE TO CHANGE THIS ONCE WE KNOW HOW TO GET THE VALUE FROM THE LIMIT SWTICH
    frc::DigitalInput m_limitSwitch{9};

public:
    Climb();

    bool GetLimitSwitch();

    void StopArm();
    void LowerArm();
    void RaiseArm();

    void ResetEncoders();

    void Periodic() override;
    void SimulationPeriodic() override;

    void SetState(ClimbingStates _climbingState);
    bool CompareState(ClimbingStates _climbingState);
    
};
