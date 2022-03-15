// Climb.h

#pragma once

#include <frc2/command/SubsystemBase.h>

#include "Constants.h"
#include <frc/DigitalInput.h>

/**
 *
 *
 * @author Lockport Porterbots
 */
class Climb: public frc2::SubsystemBase {
private:
    frc::DigitalInput m_magneticLimitSwitch{9};
public:
    Climb();

    bool GetLimitSwitch();

    void Periodic() override;
    void SimulationPeriodic() override;
    
};
