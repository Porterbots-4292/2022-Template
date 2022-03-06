// MovingSolenoidBasic.h

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

#include "subsystems/Intake.h"
#include <frc/DoubleSolenoid.h>


/**
 *
 *
 * @author Lockport Porterbots
 */
class MovingSolenoidBasic: public frc2::CommandHelper<frc2::CommandBase, MovingSolenoidBasic> {
public:
    explicit MovingSolenoidBasic(Intake& intake, eIntakePosition position);

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End(bool interrupted) override;
    bool RunsWhenDisabled() const override;


private:
    Intake* m_intake;
    eIntakePosition m_position;
};
