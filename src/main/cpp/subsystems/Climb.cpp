// Climb subsystem

#include "subsystems/Climb.h"
#include <frc/smartdashboard/SmartDashboard.h>


Climb::Climb() {

    // this sets up a bunch of stats to display on the LiveWindow
    //
    // we probably don't want this much stuff to show up during competition
    // but for robot development and debugging, it can be very useful to see
    // specific components on the robot are actually doing
    SetName("Climb");

    // enable limit switches
//    m_upperLimitSwitch.EnableLimitSwitch(true);

    m_leftClimbController.Set(0.1);

    UpdateDashboard();
}


bool Climb::GetUpperLimitSwitch() {

//    return m_upperLimitSwitch.Get();
return true;
}


void Climb::UpdateDashboard() {

    frc::SmartDashboard::PutBoolean("Climb Upper Limit Switch: ", GetUpperLimitSwitch());
}