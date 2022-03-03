
#include "commands/PorterbotDrive.h"

#include "Robot.h"
#include <iostream>

PorterbotDrive::PorterbotDrive(std::function<double()> in1,
                     std::function<double()> in2, int style, Drivetrain& drivetrain)
    : m_input1(std::move(in1)), m_input2(std::move(in2)), m_style(style), m_drivetrain(&drivetrain) {
        
  SetName("PorterbotDrive");
  AddRequirements({m_drivetrain});
}

void PorterbotDrive::Execute() {
  std::cout << "EXECUTE";
  m_drivetrain->Drive(m_input1(), m_input2(), m_style, Porterbots::Drivetrain::kDriveSquareInputs);
}

// we're never finished as we're the default command
bool PorterbotDrive::IsFinished() {
  return false;
}

// Called once after isFinished returns true - which will never actually happen
void PorterbotDrive::End(bool) {
  m_drivetrain->Drive(0, 0, m_style, false);
}
