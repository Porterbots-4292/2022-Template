// Climb.h

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/DigitalInput.h>

#include "Constants.h"


#include <rev/CANSparkMax.h>



/**
 *
 *
 * @author Lockport Porterbots
 */
class Climb: public frc2::SubsystemBase {
private:

    rev::CANSparkMax m_leftClimbController{Porterbots::CAN_ID::kMotorLeftClimb, rev::CANSparkMax::MotorType::kBrushless};
#ifndef ZOGBOT
    rev::CANSparkMax m_rightClimbController{Porterbots::CAN_ID::kMotorRightClimb, rev::CANSparkMax::MotorType::kBrushless};
#endif  // ZOGBOT

    rev::SparkMaxLimitSwitch m_upperLimitSwitch = m_leftClimbController.GetForwardLimitSwitch(Porterbots::Climb::kClimbUpperSwitchMode);
    
public:
    Climb();

    bool GetUpperLimitSwitch();

    void UpdateDashboard();
};
