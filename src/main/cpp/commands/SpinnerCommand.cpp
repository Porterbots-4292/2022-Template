// Spinner

#include "Constants.h"

#include "commands/SpinnerCommand.h"

#ifdef  ZOGBOT


static bool distTravelCheck(int currentDist, int targetDist) {

    if (abs(currentDist) - targetDist >= 0) {

        return true;        // gone at least that far
    }
    
    return false;
}


SpinnerLeftCommand::SpinnerLeftCommand(Spinner& spinner)
:m_spinner(&spinner) {

    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    AddRequirements({m_spinner});

    m_speed = 0.0;
}


// Called just before this Command runs the first time
void SpinnerLeftCommand::Initialize() {

    m_spinner->ResetEncoder();                          // start from 0

    m_speed = -Porterbots::Spinner::kSpinnerSpeed;      // spin backwards for left

    m_spinner->Set(m_speed);
}


// Called repeatedly when this Command is scheduled to run
void SpinnerLeftCommand::Execute() {

    m_spinner->UpdateDashboard();

    m_spinner->Set(m_speed);    // hit the motor so we don't get a safety timeout if enabled
}


bool SpinnerLeftCommand::IsFinished() {

    // we can make it so that we don't care if we are going forward or backward

    return distTravelCheck(m_spinner->GetDistEncoder(), Porterbots::Spinner::kTargetDistance);
}


void SpinnerLeftCommand::End(bool interrupted) {

    m_spinner->Set(0.0);        // stop the spinner
}

bool SpinnerLeftCommand::RunsWhenDisabled() const {
    return false;
}




SpinnerRightCommand::SpinnerRightCommand(Spinner& spinner)
:m_spinner(&spinner) {

    AddRequirements({m_spinner});

    m_speed = 0.0;
}


void SpinnerRightCommand::Initialize() {

    m_spinner->ResetEncoder();

    m_speed = Porterbots::Spinner::kSpinnerSpeed;      // spin forwards for right

    m_spinner->Set(m_speed);
}


void SpinnerRightCommand::Execute() {

    m_spinner->UpdateDashboard();

    m_spinner->Set(m_speed);
}


bool SpinnerRightCommand::IsFinished() {

    return distTravelCheck(m_spinner->GetDistEncoder(), Porterbots::Spinner::kTargetDistance);
}


void SpinnerRightCommand::End(bool interrupted) {

    m_spinner->Set(0.0);
}


bool SpinnerRightCommand::RunsWhenDisabled() const {

    return false;
}

#endif  // ZOGBOT