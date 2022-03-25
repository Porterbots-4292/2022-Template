#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/ParallelCommandGroup.h>

#include "Constants.h"

#include "commands/AutonomousCommand.h"
#include "subsystems/Spinner.h"

class CompoundCommand
    : public frc2::CommandHelper<frc2::SequentialCommandGroup, CompoundCommand> {

public:

    CompoundCommand(Drivetrain& drive, Spinner& spinner);

};