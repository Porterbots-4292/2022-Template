#include "Constants.h"

#include "subsystems/Climb.h"

Climb::Climb(){
    //m_climbLeftArmEncoder = m_climbLeftArmMotor.GetEncoder();
    //m_climbRightArmEncoder = m_climbRightArmMotor.GetEncoder();
}

bool Climb::GetLimitSwitch(){
    return !(m_limitSwitch.Get());
}

void Climb::SetState(ClimbingStates _climbingState){
    // This will be made better later
    m_currentState = _climbingState;
}

bool Climb::CompareState(ClimbingStates _climbingState){
    return m_currentState == _climbingState;
}

void Climb::LowerArm(){
    // This will move the motor down
    m_climbLeftArmMotor.Set(Porterbots::Climb::kLowerSpeed);
}

void Climb::RaiseArm(){
    // This will move the motor up
    m_climbLeftArmMotor.Set(Porterbots::Climb::kRaiseSpeed);
}

void Climb::StopArm(){
    // This will stop the motor
    m_climbLeftArmMotor.Set(0);
}

void Climb::Periodic(){

}

/*
void Climb::ResetEncoders(){
    m_climbLeftArmEncoder.SetPosition(0);
    m_climbRightArmEncoder.SetPosition(0);
}
*/
void Climb::SimulationPeriodic(){

}
