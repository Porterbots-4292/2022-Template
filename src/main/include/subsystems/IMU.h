// Drivetrain.h

#pragma once


#include <frc2/command/SubsystemBase.h>

#include "Constants.h"

#include <ctre/phoenix.h>

#ifdef  ZOGBOT


/**
 *
 *
 * @author Lockport Porterbots
 */
class IMU: public frc2::SubsystemBase {
private:

    WPI_Pigeon2 m_imu{Porterbots::CAN_ID::kPigeonID, "rio"};

    bool        m_imuReady = false;

public:
    IMU();

    void    Reset();

    int     GetHeading();

    void    UpdateDashboard();
};

#endif  // ZOGBOT
