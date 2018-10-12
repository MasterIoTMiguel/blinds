#include "mbed.h"
#include "rtos.h"
#include "motor.h"

#define ST 0
#define UP 1
#define DW 2
#define MAXAPERTURE 100
#define MINAPERTURE 0

extern Serial pc;

DigitalOut up(LED1);
DigitalOut down(LED2);

Thread threadMOTOR(osPriorityNormal, 512); // 1K stack size

int motorSignal;
int aperture;

void MOTOR_thread();

void MOTOR_thread() {
	motorSignal = ST;
		while (true) {
			Thread::signal_wait(0x1);
			
			switch(motorSignal){
				case ST:
						pc.printf("\n\rSTOP");
						up=0;
						down=0;
					break;
				
				case UP:
					
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
					break;
				
				case DW:
					
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
					break;
			}		
		}
}