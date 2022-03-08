// AutonomousCommand

#include "commands/MovingSolenoidBasic.h"


MovingSolenoidBasic::MovingSolenoidBasic(Intake& intake, frc::DoubleSolenoid::Value value) : m_intake(&intake){
    m_value = value;
    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("MovingSolenoidBasic");
}


// Called just before this Command runs the first time
void MovingSolenoidBasic::Initialize() {
}


// Called repeatedly when this Command is scheduled to run
void MovingSolenoidBasic::Execute() {

    // This moves the pneumatic cylinder based on the value passed in initially
    if(m_value == frc::DoubleSolenoid::Value::kForward){
        // extends the cylinder
        m_intake->SetIntakeLoadPosition();
    }
    else if (m_value == frc::DoubleSolenoid::Value::kReverse)
    {
        // de-extends the cylinder
        m_intake->SetIntakeScorePosition();
    }
    else if (m_value == frc::DoubleSolenoid::Value::kOff){
        // stops the cylinders
        m_intake->StopPneumatics();
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
