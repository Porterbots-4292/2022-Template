// Spinner

#include "Constants.h"

#include "commands/SpinnerCommand.h"

#ifdef  ZOGBOT

SpinnerLeftCommand::SpinnerLeftCommand(Spinner& spinner)
:m_spinner(&spinner) {

    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    AddRequirements({m_spinner});

    m_speed = 0.0;
}


// Called just before this Command runs the first time
void SpinnerLeftCommand::Initialize() {

    m_speed = -Porterbots::Spinner::kSpinnerSpeed;      // spin backwards for left

    m_spinner->Set(m_speed);
}


// Called repeatedly when this Command is scheduled to run
void SpinnerLeftCommand::Execute() {

    m_spinner->UpdateDashboard();

    m_spinner->Set(m_speed);    // hit the motor so we don't get a safety timeout if enabled
}


bool SpinnerLeftCommand::IsFinished() {

    return false;               // we keep going until we get interrupted
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

    m_speed = Porterbots::Spinner::kSpinnerSpeed;      // spin forwards for right

    m_spinner->Set(m_speed);
}


void SpinnerRightCommand::Execute() {

    m_spinner->UpdateDashboard();

    m_spinner->Set(m_speed);
}


bool SpinnerRightCommand::IsFinished() {

    return false;
}


void SpinnerRightCommand::End(bool interrupted) {

    m_spinner->Set(0.0);
}


bool SpinnerRightCommand::RunsWhenDisabled() const {

    return false;
}

#endif  // ZOGBOT