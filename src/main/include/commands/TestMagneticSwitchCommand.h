#pragma once

#include <frc2/commands/CommandBase.h>
#include <frc2/commands/CommandHelper.h>

#include "subsystems/Climb.h"
#include "subsystems/Drivetrain.h"


class TestMagneticSwitchCommand : public frc2::CommandHelper<frc2::CommandBase, PorterbotDrive>{
    public:
        TestMagneticSwitchCommand::TestMagneticSwitchCommand(Climb& climb) override;

        void Execute() override;
        bool IsFinished() override;
        void End(bool interrupted) override;
    private:
        Climb* m_climb;
        Drivetrain* m_drivetrain;
};