// LineAlignCommand.h

#pragma once


#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

#include "subsystems/Drivetrain.h"

/**
 *
 *
 * @author Lockport Porterbots
 */
class LineAlignCommand: public frc2::CommandHelper<frc2::CommandBase, LineAlignCommand> {
public:

    explicit LineAlignCommand(Drivetrain& m_drivetrain);

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End(bool interrupted) override;
    bool RunsWhenDisabled() const override;

private:

    Drivetrain* m_drivetrain;

    bool        m_lineAlignCompleted;

    // the variables below are used to maintiain state across multiple invocations of the Execute() function
    //
    // they track what general state we are in and the robot speeds that are in effect
    enum State  { StateStopped, StateGoingForward, StateTurningLeft, StateTurningRight};
    State       m_state;

    double      m_rightSpeed, m_leftSpeed;
};