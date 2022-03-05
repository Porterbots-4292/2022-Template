// Intake subsystem

#include "subsystems/Intake.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>

Intake::Intake() {

    std::cout << "Intake: Contructor" << std::endl;

    // this sets up a bunch of stats to display on the LiveWindow
    //
    // we probably don't want this much stuff to show up during competition
    // but for robot development and debugging, it can be very useful to see
    // specific components on the robot are actually doing
    SetName("Intake");
    SetSubsystem("Intake");
    AddChild("Intake Motor", &m_intakeMotor);
    AddChild("Intake Cylinder", &m_intakeCylinder);
}


// put the intake in the loading position
void Intake::SetIntakeLoadPosition() {

}


// put the intake in the scoring position
void Intake::SetIntakeScorePosition() {

}


// put the intake in the position to travel around the field
//
// will this actually be a seperate position?
//
// it might just be the same as the scoring position to get it off the floor
void Intake::SetIntakeTravelPosition() {
    
    }
    
// run the intake to load balls    
void Intake::RunIntakeLoad() {

}

//run the intake to score balls (unload)
void Intake::RunIntakeScore() {

}


// stop the intake - do we actually need it
//
// e probably could use it after scoring and before we start the next load attempt to save power
void Intake::StopIntake() {

}