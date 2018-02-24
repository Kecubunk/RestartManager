//------------------------------------
//AltHaFoX's RestartManager library...
//------------------------------------

#include "RestartManager.h"



RestartManager::RestartManager(uint32_t scheduledRestartTime){

  this->scheduledRestartTime = scheduledRestartTime;
  scheduledRestartMetro.timeout(scheduledRestartTime);
  restartTroughGpio = false;

}

bool getNTPtime(){


}

void setGpioRestart(uint8_t restartPin){


}
void setBeforeRestartCallback(*void_callback beforeRestartCallback){


}
void setScheduledRestartTimeFailCallback(*void_callback scheduledRestartTimeFailCallback){


}

void restartNow(){

beforeRestartCallback();

}

void forbidRestart(){

  restartAllowed = false;

}

void allowRestart(){

  restartAllowed = true;

}


void run(){



}








void rstTimeCalculator(){
	dateTime = NTPch.getNTPtime(1.0, 1);
	if(dateTime.valid){
		timer.setTimeout(((24-dateTime.hour+rstAtHour)+rstDay*24*60*60*1000), rstESP);
	}
	else{
		timer.setTimeout(36000, rstTimeCalculator);
	}
	Serial.println("TIME FOR RESTART ON SCHEDULE CALCULATED");
}

void rstESP(){
	if(rstIsAllowed){
		Serial.println("ESP RESTARTING");
		ESP.reset();
	}
	else{
		rstAsSoonAsPossible = true;
	}
}

void checkRstCritical(){
	if(rstAsSoonAsPossible){
		if(rstIsAllowed){
			timer.setTimeout(RST_CRITICAL_DELAY_TIME, rstESP);
			rstAsSoonAsPossible = false;
		}
	}
}
