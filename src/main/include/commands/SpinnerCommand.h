// LineAlignCommand.h

#pragma once


#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

#include "Constants.h"

#include "commands/SpinnerCommand.h"
#include "subsystems/Spinner.h"


#ifdef  ZOGBOT

/**
 *
 *
 * @author Chris Herzog
 */
class SpinnerRightCommand: public frc2::CommandHelper<frc2::CommandBase, SpinnerRightCommand> {
public:

    explicit SpinnerRightCommand(Spinner& m_spinner);

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End(bool interrupted) override;
    bool RunsWhenDisabled() const override;

private:

    Spinner*    m_spinner;

    double      m_speed;
};


class SpinnerLeftCommand: public frc2::CommandHelper<frc2::CommandBase, SpinnerLeftCommand> {
public:

    explicit SpinnerLeftCommand(Spinner& m_spinner);

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End(bool interrupted) override;
    bool RunsWhenDisabled() const override;

private:

    Spinner*    m_spinner;

    double      m_speed;
};

#endif  // ZOGBOT