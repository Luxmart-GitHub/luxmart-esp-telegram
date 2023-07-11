#ifndef PWM_CONTROLLER_COMMANDS_H
#define PWM_CONTROLLER_COMMANDS_H

// The Serial baud rate used for command communication
// between ESP 01S and ATTiny85.
#define BAUD_RATE 9600

enum Command
{
  CommandStepUp = 'u',
  CommandStepDown = 'd',
  CommandSetValue = 'w',
  CommandGetValue = 'r',
  CommandSetMax = 'm',
  CommandSetMin = '0',
  CommandReboot = 'p',
  CommandGetState = 's',
  NoCommandUntilCarriageReturn = '#' 
};

enum State
{
  NormalState = 0,
  RebootRequested = 1,
  FactoryResetRequested = 2
};

enum ExtraArgument
{
  NoExtraArgument = 0,
  ValueExtraArgument,
};

enum ReturnedValue
{
  NoReturnedValue = 0,
  ReturnsValue,
  ErrorCommandNotRecognized,
  ErrorCommandArgumentMissing,
  ErrorCommandTimedout,
};

struct Description
{
  Command command;
  ExtraArgument extraArg;
  ReturnedValue returnsValue;
  const char* message;
};

static const Description descriptions[] =
{
  {
    CommandStepUp,
    NoExtraArgument,
    NoReturnedValue,
    "Increment PWM by a fixed step",
  },
	{
    CommandStepDown,
    NoExtraArgument,
    NoReturnedValue,
    "Decrement PWM by a fixed step",
  },
  {
    CommandSetValue,
    ValueExtraArgument,
    NoReturnedValue,
    "Set PWM to a specific value",
  },
	{
    CommandGetValue,
    NoExtraArgument,
    ReturnsValue,
    "Read the current PWM value",
  },
  {
    CommandSetMax,
    NoExtraArgument,
    NoReturnedValue,
    "Set PWM to maximum value",
  },
  {
    CommandSetMin,
    NoExtraArgument,
    NoReturnedValue,
    "Set PWM to minimum value",
  },
  {
    CommandReboot,
    NoExtraArgument,
    NoReturnedValue,
    "Reboot the device"
  }
};

#endif // PWM_CONTROLLER_COMMANDS_H
