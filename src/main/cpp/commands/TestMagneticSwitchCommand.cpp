
#include "commands/TestMagneticSwitchCommand.h"

#include "Robot.h"
#include <iostream>


TestMagneticSwitchCommand::TestMagneticSwitchCommand(Drivetrain& drivetrain, Climb& climb) : m_climb(&climb), m_drivetrain(&drivetrain){
    SetName("TestMagneticSwitch");
    AddRequirements({m_climb, m_drivetrain});
}

void TestMagneticSwitchCommand::Initialize(){}

void TestMagneticSwitchCommand::Execute(){
    /* if(m_climb->GetLimitSwitch()){
        m_drivetrain->ArcadeDrive(0.25, 0, false);
    } else {
        m_drivetrain->ArcadeDrive(0,0,false);
    } */
    
    if((m_climb->GetLimitSwitch())) {
        m_drivetrain->ArcadeDrive(0.5, 0, false);
    } else {
        m_drivetrain->ArcadeDrive(0,0,false);
    }
}

bool TestMagneticSwitchCommand::IsFinished(){
    return false;
}

void TestMagneticSwitchCommand::End(bool interrupted){
    m_drivetrain->ArcadeDrive(0,0,false);
}

