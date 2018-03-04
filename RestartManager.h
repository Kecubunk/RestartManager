//------------------------------------
//AltHaFoX's RestartManager library...
//------------------------------------

#ifndef RESTART_MANAGER_H
#define RESTART_MANAGER_H

#include <Arduino.h>

typedef void (*void_callback)(void);

class RestartManager
{

public:

    RestartManager();

    void setSchedule(uint32_t scheduledRestartTime, uint32_t maxiumTimeForScheduledRestart);
    void setSchedule(uint32_t scheduledRestartTime);
    void setGpioRestart(uint8_t restartPin);
    void setBeforeRestartCallback(void_callback beforeRestartCallback);
    void setScheduledRestartTimeFailCallback(void_callback scheduledRestartTimeFailCallback);

    void restartNow();
    void forbidRestart();
    void allowRestart();
    void allowRestart(uint32_t addDelay);


    void run();

private:


  void_callback beforeRestartCallback;
  void_callback scheduledRestartTimeFailCallback;

  bool scheduledRestartTimeFailCallbackCalled = false;
  bool restartTroughGpio = false;
  bool restartAllowed = true;
  uint8_t restartPin;
  uint32_t scheduledRestartTime;
  uint32_t maxiumTimeForScheduledRestart = 4294930000;

};

#endif;
