#include "Constants.h"

#include "subsystems/Climb.h"

bool Climb::GetLimitSwitch(){
    return m_magneticLimitSwitch.Get();
}