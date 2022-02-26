// Spinner subsystem

#include "Constants.h"

#ifdef  ZOGBOT

#include "subsystems/IMU.h"
#include <frc/smartdashboard/SmartDashboard.h>

#include <ctre/phoenix.h>

#include <wpi/numbers>



IMU::IMU() {

    Reset();
}

void IMU::Reset() {
    m_imu.Reset();
}



int IMU::GetHeading() {
    return m_imu.GetAngle();
}

#endif // ZOGBOT