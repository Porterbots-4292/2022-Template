// AutonomousCommand

#include "commands/MovingSolenoidBasic.h"


MovingSolenoidBasic::MovingSolenoidBasic(Intake& intake, eIntakePosition pos) : m_intake(&intake) {
    m_position = pos;

    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("MovingSolenoidBasic");
}


// Called just before this Command runs the first time
void MovingSolenoidBasic::Initialize() {
}


// Called repeatedly when this Command is scheduled to run
void MovingSolenoidBasic::Execute() {

    switch (m_position) {

        case IntakePosLoad:

            m_intake->SetIntakeLoadPosition();
            break;

        case IntakePosScore:

            m_intake->SetIntakeScorePosition();
            break;

        case IntakePosTravel:

            m_intake->SetIntakeTravelPosition();
            break;

        case IntakePosStop:

            m_intake->StopPneumatics();
            break;
    }
}


// Make this return true when this Command no longer needs to run execute()
bool MovingSolenoidBasic::IsFinished() {
    return true;
}


void MovingSolenoidBasic::End(bool interrupted){

}

// Called once after isFinished returns true

bool MovingSolenoidBasic::RunsWhenDisabled() const {
    return false;
}
