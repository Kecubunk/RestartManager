//------------------------------------
//AltHaFoX's RestartManager library...
//------------------------------------

#include "RestartManager.h"



RestartManager::RestartManager(){



}


void RestartManager::setSchedule(uint32_t scheduledRestartTime, uint32_t maxiumTimeForScheduledRestart){

  this->scheduledRestartTime = scheduledRestartTime;
  this->maxiumTimeForScheduledRestart = maxiumTimeForScheduledRestart;

}

void RestartManager::setSchedule(uint32_t scheduledRestartTime){

  this->scheduledRestartTime = scheduledRestartTime;

}


void RestartManager::setGpioRestart(uint8_t restartPin){

  this->restartPin = restartPin;
  restartTroughGpio = true;
  pinMode(restartPin, OUTPUT);
  digitalWrite(restartPin, true);

}

void RestartManager::setBeforeRestartCallback(void_callback beforeRestartCallback){

  this->beforeRestartCallback = beforeRestartCallback;

}

void RestartManager::setScheduledRestartTimeFailCallback(void_callback scheduledRestartTimeFailCallback){

  this->scheduledRestartTimeFailCallback = scheduledRestartTimeFailCallback;

}


void RestartManager::restartNow(){

  if(!restartAllowed){
    return;
  }

  (*beforeRestartCallback)();

  if(restartTroughGpio){
    digitalWrite(restartPin, false);
  }
  else{
    ESP.reset();
  }

}

void RestartManager::forbidRestart(){

  restartAllowed = false;

}

void RestartManager::allowRestart(){

  restartAllowed = true;

}

void RestartManager::allowRestart(uint32_t addDelay){

  uint32_t now = millis();

  restartAllowed = true;

  if(scheduledRestartTime >= now + addDelay){
    return;
  }
  else{
    scheduledRestartTime = (addDelay + now);
  }

}



void RestartManager::run(){

  uint32_t now = millis();

  if(maxiumTimeForScheduledRestart <= now{
    if(!scheduledRestartTimeFailCallbackCalled){
      (*scheduledRestartTimeFailCallback)();
    }
  }

  if(restartAllowed && scheduledRestartTime <= now{
    restartNow();
  }
}
