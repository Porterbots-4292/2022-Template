// Intake subsystem

#include "subsystems/Intake.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>

Intake::Intake() {

    std::cout << "Intake: Contructor" << std::endl;
    m_hub.EnableCompressorAnalog(units::pounds_per_square_inch_t(40), units::pounds_per_square_inch_t(100));
    // this sets up a bunch of stats to display on the LiveWindow
    //
    // we probably don't want this much stuff to show up during competition
    // but for robot development and debugging, it can be very useful to see
    // specific components on the robot are actually doing
}


// put the intake in the loading position
void Intake::SetIntakeLoadPosition() {
    m_intakeCylinder.Set(frc::DoubleSolenoid::Value::kForward);
}


// put the intake in the scoring position
void Intake::SetIntakeScorePosition() {
    m_intakeCylinder.Set(frc::DoubleSolenoid::Value::kReverse);
}


// put the intake in the position to travel around the field
//
// will this actually be a seperate position?
//
// it might just be the same as the scoring position to get it off the floor
void Intake::SetIntakeTravelPosition() {
    
    }

void Intake::StopPneumatics(){
    m_intakeCylinder.Set(frc::DoubleSolenoid::kOff);
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


void Intake::Periodic() {
    // Put code here to be run every loop
}

void Intake::SimulationPeriodic() {
    // This method will be called once per scheduler run when in simulation

}