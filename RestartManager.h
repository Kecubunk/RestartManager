//------------------------------------
//AltHaFoX's RestartManager library...
//------------------------------------

#ifndef RESTART_MANAGER_H
#define RESTART_MANAGER_H

#include <NTPtimeESP.h>
#include <Metro.h>

Metro scheduledRestartMetro;

NTPtime NTPch("ch.pool.ntp.org");

typedef std::function<void(void)> void_callback;

class RestartManager
{

public:

    RestartManager(uint32_t scheduledRestartTime);

    bool getNTPtime();  //the device will attept automatically this in run();

    void setRecomendedHourToRestart(unit8_t hour);
    void setGpioRestart(uint8_t restartPin);
    void setBeforeRestartCallback(*void_callback beforeRestartCallback);
    void setScheduledRestartTimeFailCallback(*void_callback scheduledRestartTimeFailCallback);

    void restartNow();
    void forbidRestart();
    void allowRestart();


    void run();

private:

  void_callback beforeRestartCallback;
  void_callback scheduledRestartTimeFailCallback;

  bool restartTroughGpio;
  bool restartAllowed;
  uint8_t restartPin;
  uint32_t scheduledRestartTime;
  uint32_t maxiumTimeForScheduledRestart;

};

#endif;
