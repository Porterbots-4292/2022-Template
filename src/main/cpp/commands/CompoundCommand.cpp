#include "commands/LineAlignCommand.h"
#include "commands/SpinnerCommand.h"
#include "commands/CompoundCommand.h"

CompoundCommand::CompoundCommand(Drivetrain& drive, Spinner &spinner) {

    AddCommands(LineAlignCommand(drive), SpinnerLeftCommand(spinner));

}