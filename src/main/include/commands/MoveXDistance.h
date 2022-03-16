// MoveXDistance.h

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>
#include <frc/Encoder.h>

#include "Constants.h"

#include "subsystems/Drivetrain.h"

class MoveXDistance: public frc2::CommandHelper<frc2::CommandBase, MoveXDistance> {
    public:
        explicit MoveXDistance(double x, Drivetrain& m_drivetrain);
        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End(bool interrupted) override;

    private:
        Drivetrain* m_drivetrain;
        bool m_encoderGood = false;
        double m_x = 0;
        double m_tolerance = 1;
        
};