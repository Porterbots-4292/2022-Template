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

    m_state              = StateForward;

    m_rightSpeed         = Porterbots::LineDetection::kLineAlignSpeed;
    m_leftSpeed          = Porterbots::LineDetection::kLineAlignSpeed;
    

    // start moving ahead at our predefined speed to search for the alignment line
    //
    // do not square the input
    m_drivetrain->TankDrive(Porterbots::LineDetection::kLineAlignSpeed,
                            Porterbots::LineDetection::kLineAlignSpeed,
                            false);
}

// Called repeatedly when this Command is scheduled to run
void LineAlignCommand::Execute() {

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
    // doing this here and now could save us a robot crash or some twisty debugging later...

    if (m_lineAlignCompleted) {
        m_drivetrain->TankDrive(0.0, 0.0, false);

        return;
    }

    if (m_drivetrain->IsLineDetected(Porterbots::LineDetection::kLeftLineSensor) &&
        m_drivetrain->IsLineDetected(Porterbots::LineDetection::kRightLineSensor)) {

        // found a line so for now just stop the robot and set the finished flag

        m_drivetrain->TankDrive(0.0, 0.0, false);

        m_lineAlignCompleted = true;

        return;
    }

    switch (m_state) {

        case StateForward:

            bool sensorLeft, sensorRight;

            sensorLeft  = m_drivetrain->IsLineDetected(Porterbots::LineDetection::kLeftLineSensor);
            sensorRight = m_drivetrain->IsLineDetected(Porterbots::LineDetection::kRightLineSensor);

            // did we align?
            if (sensorLeft && sensorRight) {
                m_drivetrain->TankDrive(0.0, 0.0, false);
                m_lineAlignCompleted = true;
                m_state - StateStopped;
                return;
            }

            if (sensorLeft) {
                m_drivetrain->TankDrive(0.0, Porterbots::LineDetection::kLineAlignSpeed, false);    // run right side to turn left


            }
                stop the robot 
                start the robot turning left 
                save the state that the robot is turning left 
                get out 

            if right sensor sees the line 

                stop the robot 
                start the robot turning right  
                save the state that the robot is turning right  
                get out 

            get out

        case StateTurningLeft:

            check the sensors

            do both sensors see the line?

                stop the robot 
                set aligned flag 
                get out 

            does the right sensor see the line?

                if yes 
                    Stop turning left 
                    Start turning right because we went too far 
                    save the state thet we are turning right 
                    get out

            does the left sensor still see the line?

                if no
                    stop turning 
                    start driving forward 
                    save the state that we are driving forward 
                    get out 

                if yes 
                    // everythign is cool
                    get out 


        case StateTurningRight:

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
