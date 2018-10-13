#include "mbed.h"
#include "rtos.h"
#include "motor.h"

#define MAXVALUE 70
#define MINVALUE 40



Serial pc(USBTX,USBRX,19200);


extern Thread threadANALOG;

extern void ANALOG_thread();

extern Thread threadMOTOR;

extern void MOTOR_thread();

extern float valueLS;

extern int motorSignal; 

float preValueLS=0;


// main() runs in its own thread in the OS
int main() {
		

    threadANALOG.start(ANALOG_thread);
		threadMOTOR.start(callback(MOTOR_thread));

	
    pc.printf("mbed-os-rev: %d.%d.%d\r\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);	
	
    while (true) {
			if(valueLS != preValueLS){
				pc.printf("\n\r");
				pc.printf("\n\rLight Sensor: %.1f%%",valueLS);
			
				if(valueLS < MINVALUE){
					motorSignal = UP;
				}else if (valueLS > MAXVALUE){
					motorSignal = DW;
				}else{
					motorSignal = ST;
				}
				threadMOTOR.signal_set(0x1);
			}

			wait(2);
			
    }
}

