
#include "Constants.h"
#include <iostream>
#include "commands/InitializeClimb.h"

InitializeClimb::InitializeClimb(Climb& climb) : m_climb(&climb){
    SetName("InitializeClimb");
    AddRequirements({m_climb});
}

void InitializeClimb::Initialize(){

}

void InitializeClimb::Execute(){

    // If the limit switch reads something then continue, else, lower
    if(m_climb->GetLimitSwitch()){
        m_climb->SetState(ClimbingStates::lowered);
        return;
    }
    m_climb->LowerArm();
    
}

bool InitializeClimb::IsFinished(){
    return m_climb->CompareState(ClimbingStates::lowered);
}

void InitializeClimb::End(bool interrupted){
    m_climb->StopArm();
}


