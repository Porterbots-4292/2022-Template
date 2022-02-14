// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "subsystems/Drivetrain.h"

/**
 * Have the robot drive until interrupted by a command which takes over the drivetrain
 */
class PorterbotDrive : public frc2::CommandHelper<frc2::CommandBase, PorterbotDrive> {

 public:
    PorterbotDrive(std::function<double()> left, std::function<double()> right,
                   Drivetrain& drivetrain);
    void Execute() override;
    bool IsFinished() override;
    void End(bool interrupted) override;

 private:

    // we just call these input1 and input2 because their action will vary depending
    // on whether we are using tank or arcade style driving
    std::function<double()> m_input1;
    std::function<double()> m_input2;

    Drivetrain* m_drivetrain;
};
