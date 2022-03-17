#include "Constants.h"

#include "subsystems/Climb.h"

Climb::Climb(){

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
}

void Climb::RaiseArm(){
    // This will move the motor up
}

void Climb::StopArm(){
    // This will stop the motor
}

void Climb::Periodic(){

}

void Climb::SimulationPeriodic(){

}
