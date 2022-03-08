// LineAlignCommand

#include "Constants.h"
#include <iostream>
#include "commands/LineAlignCommand.h"

/*
This was used for time managament but not anymore :D
static uint64_t timeSinceEpoch(){
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
*/

LineAlignCommand::LineAlignCommand(Drivetrain& drivetrain)
:m_drivetrain(&drivetrain) {

    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    AddRequirements({m_drivetrain});

    SetName("LineAlign");
}

// Called just before this Command runs the first time
void LineAlignCommand::Initialize() {
    m_lineAlignCompleted = false;

    // start moving ahead at our predefined speed to search for the alignment line
    // do not square the input
    m_drivetrain->TankDrive(Porterbots::LineDetection::kLineAlignSpeed,
                            Porterbots::LineDetection::kLineAlignSpeed,
                            false);
}

// Called repeatedly when this Command is scheduled to run
void LineAlignCommand::Execute() {

    // first off - hit the motorcontroller so we don't get a timeout
    //
    // we shoudl be moving at this speed anyway so it won't really change the robot
    // speed but it will hit the drivetrain safety timeout

    // as a safety check, if for any reason line align is completed and we still
    // got called, don't do anything else except for stopping the robot because
    // this is an unexpected condition
    //
    // this can be important because once the command is scheduled, the Execute()
    // function will get called at least once.  this means that if the command is
    // scheduled and then immediately cancelled - even if it was cancelled before the
    // Execute() function had a chance to run for the first time, Execute() will
    // be run at least once because commands are not unscheduled until after the
    // Execute() function has been run
    //
    // doing this here and now could save us a robot crash or some twisty debugging later...
    
    if (m_lineAlignCompleted) {
        m_drivetrain->TankDrive(0.0, 0.0, false);

        return;
    }

    bool left_sensor_detects_line = m_drivetrain->IsLineDetected(Porterbots::LineDetection::kLeftLineSensor);
    bool right_sensor_detects_line = m_drivetrain->IsLineDetected(Porterbots::LineDetection::kRightLineSensor);
    
    // LIGN ALIGHMENT CODE

    if(!left_sensor_detects_line && right_sensor_detects_line){
        // Rotate the robot at the rotate speed left
        m_drivetrain->TankDrive(Porterbots::LineDetection::kRotateSpeed, -Porterbots::LineDetection::kRotateSpeed, false);
        }
    else if(left_sensor_detects_line && !right_sensor_detects_line){
        // Rotate the robot at the rotate speed right
        m_drivetrain->TankDrive(-Porterbots::LineDetection::kRotateSpeed, Porterbots::LineDetection::kRotateSpeed, false);
    }
    else if(left_sensor_detects_line && right_sensor_detects_line){
        // Stops - everything is aligned!
        m_lineAlignCompleted = true;
        m_drivetrain->TankDrive(0,0,false);
        }
    else{
        // Moves the chasiss at the lineAlignSpeed
        m_drivetrain->TankDrive(Porterbots::LineDetection::kLineAlignSpeed,Porterbots::LineDetection::kLineAlignSpeed, false);
        }
}

// Make this return true when this Command no longer needs to run Execute()
bool LineAlignCommand::IsFinished() {

    // this gets set by the Execute() routine when it reaches the terminal state,
    // that is the robot aligning itself to the alignment line - we're checking
    // for our final completed state in the Execute() function and setting this flag there
    //
    // we just return it here as it's been set in Execute() if we're actually finished
    return m_lineAlignCompleted;
}

// Called once after isFinished returns true or if we get cancelled
//
// if we got cancelled, the bool flag pssed will be true, otherwise if we stopped
// ourselves (by IsFinished returning true) the flag will be false
void LineAlignCommand::End(bool interrupted) {

    // even though we didn't find the line - just set our flag like we're done
    //
    // this is a safety thing mostly
    m_lineAlignCompleted = true;

    // the interrupted flag is true if the command DID NOT finish normally - aka we got
    // "interrupted" by a Cancel() operation
    //
    // this might mean we have more things to do to reset the robot into a known state
    // like stop motors or clear other settings so we can run again
    //
    // in this case, we'll make sure we explicitely stop the robot

    if (interrupted) {
        m_drivetrain->TankDrive(0.0, 0.0, false);
    }
}

bool LineAlignCommand::RunsWhenDisabled() const {
    return false;
}
