#include "Constants.h"

#include "subsystems/Climb.h"

Climb::Climb(){

}

bool Climb::GetLimitSwitch(){
    return m_magneticLimitSwitch.Get();
}

void Climb::Periodic(){

}

void Climb::SimulationPeriodic(){

}
