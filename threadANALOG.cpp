#include "mbed.h"
#include "rtos.h"


AnalogIn lightSensor(PA_0); 

float valueLS=0.0;

Thread threadANALOG(osPriorityNormal, 512); // 1K stack size

void ANALOG_thread(); 

void ANALOG_thread() {
		while (true) {

				//Thread::
			wait(200);
			valueLS=lightSensor*100;
				  
    }
} 


