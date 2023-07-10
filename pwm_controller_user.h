#ifndef PWM_CONTROLLER_USER_H
#define PWM_CONTROLLER_USER_H

class UserControl
{
public :

  UserControl() { }

  virtual void iterate() = 0;

  // Execute the given command on the ATTiny85 PWM controller.
  // Some commands may need an extra argument.
  // Some commands return a value, which is transferred back to the user.
  ReturnedValue executeCommand(char command, char* extraArg, char* result)
  {
    // Iterate through all known commands.
    for (int j = 0; j < sizeof(descriptions) / sizeof(descriptions[0]); j++)
    {
      // Skip a mismatch.
      auto d = descriptions[j];
      if (d.command != command) continue;

      // Write a known command down to the serial lane.
      // Furthermore, write extra argument, if required.
      if (d.extraArg)
      {
        if (!extraArg)
          return ErrorCommandArgumentMissing;

        pwmSerial.write(command);
        pwmSerial.write(*extraArg);
      }
      else
      {
        pwmSerial.write(command);
      }
      
      // If command returns a value, wait for the value to be returned.
      if (d.returnsValue)
      {
        // First char is a type of return value,
        // for example 'v' for the current value of PWM level.
        for (int ichar = 0; ichar < 2; ichar++)
        {
          // TODO Do not wait infinitely, give up after some time
          while (!pwmSerial.available())
            delay(1000);

          *result = pwmSerial.read();
        }
      }

      // Notify whether there is a value returned by command.
      return d.returnsValue;
    }

    return ErrorCommandNotRecognized;
  }
};

static void pwm_controller_setup();

static void pwm_controller_loop();

void setup()
{
  setupSerial();

  setupWiFi();

  pwm_controller_setup();

  // Use led to indicate that the setup has been completed successfully.
  digitalWrite(LED_BUILTIN, LED_LOW);
}

void loop()
{
  DBGLOG("loop");

  pwm_controller_loop();
}

#endif // PWM_CONTROLLER_USER_H
