// LineAlignCommand

#include "Constants.h"

#include "commands/LineAlignCommand.h"

LineAlignCommand::LineAlignCommand(Drivetrain& drivetrain)
:m_drivetrain(&drivetrain) {

    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    AddRequirements({m_drivetrain});

    SetName("LineAlign");

    m_state = StateStopped;
}

// Called just before this Command runs the first time
void LineAlignCommand::Initialize() {

    m_lineAlignCompleted = false;

    m_state              = StateGoingForward;

    m_rightSpeed         = Porterbots::LineDetection::kLineAlignSpeed;
    m_leftSpeed          = Porterbots::LineDetection::kLineAlignSpeed;

    // start moving ahead at our predefined speed to search for the alignment line
    //
    // do not square the input
    m_drivetrain->TankDrive(m_leftSpeed, m_rightSpeed, false);
}

// Called repeatedly when this Command is scheduled to run
void LineAlignCommand::Execute() {

    bool sensorLeft, sensorRight;

    // first off - hit the motorcontroller so we don't get a timeout
    //
    // we should be moving at this speed anyway so it won't really change the robot
    // speed but it will hit the drivetrain safety timeout
    m_drivetrain->TankDrive(m_leftSpeed, m_rightSpeed, false);

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
    // the End() routine will set the line aligned flag so we can safely bail out here
    // if that's the case
    //
    // doing this here and now could save us a robot crash or some twisty debugging later...

    if (m_lineAlignCompleted) {
        m_drivetrain->TankDrive(0.0, 0.0, false);

        return;
    }

    // read each sensor and save them becaus we'll need to look at the multiple times in the following code
    sensorLeft  = m_drivetrain->IsLineDetected(Porterbots::LineDetection::kLeftLineSensor);
    sensorRight = m_drivetrain->IsLineDetected(Porterbots::LineDetection::kRightLineSensor);

    // did we align?
    //
    // if we are aligned, *BOTH* sensors will have detected the line
    if (sensorLeft && sensorRight) {
        m_drivetrain->TankDrive(0.0, 0.0, false);   // stop the robot

        m_lineAlignCompleted = true;                // indicate we are done ("aligned" that is)

        m_state              = StateStopped;

        return;
    }

    // if we got here, were not aligned (yet) - at most we have one sensor seeing anything
    //
    // what we do next is going to depend on what we are doing and what the sensors have detected (if anything)
    switch (m_state) {

        case StateGoingForward:
            // do any of the sensors see anything at all?
            //
            // if not, we're not going to change what we are doing so we'll just return;
            if ( ! (sensorLeft || sensorRight)) {
                return;   // nothing else to do since we aren't seeing anything
            }

            // if we get here, we're not aligned but one of the sensors found the line
            //
            // which one will determine what we do next
            //
            // if the left sensor sees the line, we're coming in from the left so we'll need to turn left to align
            if (sensorLeft) {
                m_leftSpeed  = 0.0;
                m_rightSpeed = Porterbots::LineDetection::kLineAlignSpeed;    // run right side to turn left

                m_state = StateTurningLeft;
            } else {
            // the only other situation here is that the right sensor saw the line (it's not both sensors, it's not none of the
            // sensors, and it's not the left sensor so the only possibility remaining is the right sensor)
                m_leftSpeed  = Porterbots::LineDetection::kLineAlignSpeed;    // run left side to turn right
                m_rightSpeed = 0.0;

                m_state = StateTurningRight;
            }

            // whatever we set the speeds to above, drive that way now
            m_drivetrain->TankDrive(m_leftSpeed, m_rightSpeed, false);

            return;

        case StateTurningLeft:

            // the big issue here is do we keep turning or change our plan?
            //
            // depends on the whether the sensor that kicked this all off still sees the line
            //
            // in this case, we're turning left so that means the left sensor saw the line first - if the left
            // sensor still sees the line, keep turning
            //
            // if the left sensor lost the line, that means it, the sensor, moved in front of the line in which
            // case we need to drive forward until we see the line agian (with whatever sensor sees it first)
            if ( ! sensorLeft) {
                m_rightSpeed = Porterbots::LineDetection::kLineAlignSpeed;
                m_leftSpeed  = Porterbots::LineDetection::kLineAlignSpeed;

                m_drivetrain->TankDrive(m_leftSpeed, m_rightSpeed, false);

                m_state = StateGoingForward;
            }

            // otherwise the right sensor still sees the line so keep turning left a we are
            return;

        case StateTurningRight:

            // mirror ismage of when we ww're turning left so just flip left and right in the logic
            if ( ! sensorRight) {
                m_rightSpeed = Porterbots::LineDetection::kLineAlignSpeed;
                m_leftSpeed  = Porterbots::LineDetection::kLineAlignSpeed;

                m_drivetrain->TankDrive(m_leftSpeed, m_rightSpeed, false);

                m_state = StateGoingForward;
            }

            return;

        case StateStopped:

            m_lineAlignCompleted = true;        // something weird happened so just act like we're done
            break;
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

    m_state              = StateStopped;

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
