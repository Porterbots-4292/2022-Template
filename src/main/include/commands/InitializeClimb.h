// InitializeClimb.h

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>
#include <frc/Encoder.h>

#include "Constants.h"

#include "subsystems/Climb.h"

class InitializeClimb: public frc2::CommandHelper<frc2::CommandBase, InitializeClimb> {
    public:
        explicit InitializeClimb(Climb& climb);
        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End(bool interrupted) override;

    private:
        Climb* m_climb;
        bool m_isFinished = false;
        
};