// Spinner subsystem

#include "Constants.h"

#ifdef  ZOGBOT

#include "subsystems/Spinner.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <wpi/numbers>



Spinner::Spinner() {

    SetName("Spinner");

    SetSubsystem("Spinner");
    AddChild("Motor  ", &m_spinnerController);
    AddChild("Encoder", &m_encoder);

    UpdateDashboard();

    // just pretend the encoder is connected to a 6" wheel
    m_encoder.SetDistancePerPulse((wpi::numbers::pi * kSpinnerWheelDiameter) / kSpinnerEncoderCPR);
    ResetEncoder();
}


void Spinner::Set(double speed) {
    m_savedSpeed = speed;
    m_spinnerController.Set(speed);
}


void Spinner::ResetEncoder() {
    m_encoder.Reset();
}


int Spinner::GetDistEncoder() {
    return m_encoder.GetDistance();
}


int Spinner::GetRawEncoder() {
    return m_encoder.GetRaw();
}


void Spinner::UpdateDashboard() {
    frc::SmartDashboard::PutData("Spinner Encoder:   ", &m_encoder);
    frc::SmartDashboard::PutData("Spinner Motor:     ", &m_spinnerController);
}

#endif // ZOGBOT