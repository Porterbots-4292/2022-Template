// MoveXDistance
#include "Constants.h"
#include <iostream>
#include "commands/MoveXDistance.h"

MoveXDistance::MoveXDistance(double x, Drivetrain& drivetrain) : m_drivetrain(&drivetrain) {
    AddRequirements({m_drivetrain});
    SetName("MoveXDistance");
    m_x = x;
}

void MoveXDistance::Initialize() {
    m_drivetrain->ResetEncoders();
    m_encoderGood = false;
}

void MoveXDistance::Execute() {
    double encoderDistance = m_drivetrain->GetEncoderDistance();
    double scaleValue = 1;

    // Right here we change the scale value so that when we are closer to the target position, we slow down
    if(abs(m_x - encoderDistance) < m_tolerance){
        scaleValue = ((m_x - encoderDistance) / m_tolerance);
        scaleValue *= scaleValue * 1.5;
    }
    
    // We move robot and when we exceed our target we stop
    if (encoderDistance >= m_x) {
        m_drivetrain->ArcadeDrive(-Porterbots::MoveXDistance::kWheelSpeed,0,false);
        m_encoderGood = true;
    } else if (encoderDistance < m_x) {
        m_drivetrain->ArcadeDrive(Porterbots::MoveXDistance::kWheelSpeed * scaleValue,0,false);
    } 

}
/*
void MoveXDistance::Execute() {
    double encoderDistance = m_drivetrain->GetEncoderDistance();
    if (abs(encoderDistance - m_x) < m_tolerance) {
        m_drivetrain->ArcadeDrive(0,0,false);
        m_encoderGood = true;
    } else if (encoderDistance < m_x) {
        m_drivetrain->ArcadeDrive(Porterbots::MoveXDistance::kWheelSpeed,0,false);
    } else if (encoderDistance > m_x) {
        m_drivetrain->ArcadeDrive(-Porterbots::MoveXDistance::kWheelSpeed,0,false);
    }
}
*/

bool MoveXDistance::IsFinished() {
    return m_encoderGood;
}

void MoveXDistance::End(bool interrupted) {
    m_drivetrain->ArcadeDrive(0,0,false);
    if (interrupted) {
        m_drivetrain->ArcadeDrive(0,0,false);
    }
}