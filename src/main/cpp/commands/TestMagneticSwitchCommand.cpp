
#include "commands/TestMagneticSwitchCommand.h"

#include "Robot.h"
#include <iostream>


TestMagneticSwitchCommand::TestMagneticSwitchCommand(Drivetrain& drivetrain, Climb& climb) : m_climb(climb), m_driveTrain(driveTrain){
    SetName("TestMagneticSwitch");
    AddRequirements({m_climb, m_driveTrain});
}

void TestMagneticSwitchCommand::Initialize(){}

void TestMagneticSwitchCommand::Execute(){
    if(m_climb->GetLimitSwitch()){
        m_driveTrain->ArcadeDrive(0.25, 0, false);
    } else {
        m_driveTrain->ArcadeDrive(0,0,false);
    }
}

void TestMagneticSwitchCommand::IsFinished(){
    return false;
}

void TestMagneticSwitchCommand::End(){
    m_driveTrain->ArcadeDrive(0,0,false);
}


