// Drivetrain.h

#pragma once


#include <frc2/command/SubsystemBase.h>
#include <frc/DigitalInput.h>
#include <frc/Encoder.h>

#include "Constants.h"

#include <ctre/phoenix.h>

#ifdef  ZOGBOT


/**
 *
 *
 * @author Lockport Porterbots
 */
class Spinner: public frc2::SubsystemBase {
private:

    WPI_VictorSPX   m_spinnerController{Porterbots::CAN_ID::kMotorSpinnerID};
    frc::Encoder    m_encoder{Porterbots::Ports::kEncoderAPort, Porterbots::Ports::kEncoderBPort};

public:
    Spinner();

    void    Set(double speed);

    void    ResetEncoder();
    int     GetDistEncoder();
    int     GetRawEncoder();

    int const   kSpinnerEncoderCPR    = 28;
    int const   kSpinnerWheelDiameter = 6;
};

#endif  // ZOGBOT
