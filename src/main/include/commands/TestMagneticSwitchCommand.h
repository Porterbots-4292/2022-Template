#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

#include "subsystems/Climb.h"
#include "subsystems/Drivetrain.h"


class TestMagneticSwitchCommand : public frc2::CommandHelper<frc2::CommandBase, TestMagneticSwitchCommand>{
    public:
        TestMagneticSwitchCommand(Drivetrain& drivetrain, Climb& climb);

        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End(bool interrupted) override;
    private:
        Climb* m_climb;
        Drivetrain* m_drivetrain;
};