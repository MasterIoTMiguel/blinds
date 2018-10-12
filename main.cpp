#include "mbed.h"
#include "rtos.h"

#define MAXVALUE 70
#define MINVALUE 40



Serial pc(USBTX,USBRX,19200);


extern Thread threadANALOG;

extern void ANALOG_thread();

extern Thread threadMOTOR;

extern void MOTOR_thread();

extern float valueLS;

extern int motorSignal; 



// main() runs in its own thread in the OS
int main() {
		

    threadANALOG.start(ANALOG_thread);
		threadMOTOR.start(callback(MOTOR_thread));

	
    pc.printf("mbed-os-rev: %d.%d.%d\r\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);	
	
    while (true) {
			
			pc.printf("\n\r");
			//threadMOTOR.signal_set(0x3);
			// SOIL MOISTURE
			pc.printf("\n\rLight Sensor: %.1f%%",valueLS);
		
			if(valueLS < MINVALUE){
				motorSignal = UP; 
				if(aperture < MAXAPERTURE){
					pc.printf("\n\rRISING BLINDS");
					up=1;
					down = !up;
					aperture = aperture + 10;
				}else{
					pc.printf("\n\rSTOP");
					up=0;
					down=0;
				}
			}else if (valueLS > MAXVALUE){
				if(aperture > MINAPERTURE){
					pc.printf("\n\rLOWERING BLINDS");
					up=0;
					down = !up;
					aperture = aperture - 10;
				}else{
					pc.printf("\n\rSTOP");
					up=0;
					down=0;
				}
			}else{
				pc.printf("\n\rSTOP");
				up=0;
				down=0;
			}

			wait(2);
			
    }
}

