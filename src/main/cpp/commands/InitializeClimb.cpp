
#include "Constants.h"
#include <iostream>
#include "commands/InitializeClimb.h"

InitializeClimb::InitializeClimb(Climb& climb) : m_climb(&climb){
    SetName("InitializeClimb");
    AddRequirements({m_climb});
}

void InitializeClimb::Initialize(){
    m_climb->SetState(ClimbingStates::busy);
    m_isFinished = false;
}

void InitializeClimb::Execute(){

    // If the limit switch reads something then continue, else, lower
    if(m_climb->GetLimitSwitch() && m_climb->CompareState(ClimbingStates::busy)){
        m_isFinished = true;
        return;
    } else {
        m_climb->LowerArm();
    }
}

bool InitializeClimb::IsFinished(){
    return m_climb->GetLimitSwitch();
}

void InitializeClimb::End(bool interrupted){
    //m_climb->ResetEncoders();
    m_climb->StopArm();
}


