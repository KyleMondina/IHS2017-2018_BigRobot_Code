#include <stdbool.h>

#define LOWER_MOTOR 3
#define UPPER_MOTOR 2

#define motorCorrectionFactor	0.95

#define GROUND 0
#define MIDDLE 2
#define TOP 3

#define REFERENCE digital(0)
//Motor Correction Factor
#define MCF 1;

// Configuration
int motorSpeed = 30;
int offsetTime = 100;

// Variables
int currentPosition = MIDDLE;
bool readyToMove = true;
bool groundOffset = true;
bool btnOpen = true;
int btnCounter = 0;

void raiseClaw(int speed, int position) {
    if (position == GROUND){
        if (currentPosition == position) {
            printf("Already in current position");
        }
        else if (currentPosition == MIDDLE) {
            if (readyToMove){
                readyToMove = false;
                while (currentPosition != position) {
                    motor(LOWER_MOTOR, speed);
                    motor(UPPER_MOTOR, speed * motorCorrectionFactor);
                    if (REFERENCE == 1 && btnOpen) {
                        msleep(100);
                        btnOpen = false;
                        btnCounter++;
                        printf("btnCounter = %i\n", btnCounter );
                        if (btnCounter == 2) {
                            currentPosition = position;
        		            motor(LOWER_MOTOR, -30);
		                    motor(UPPER_MOTOR, -30  * motorCorrectionFactor);
                            msleep(100);
                            ao();
                        }
//                        if (currentPosition == MIDDLE)
//                            msleep( 150 );
//                        currentPosition--;
			            printf("%i \n", btnCounter);
//                        msleep( 73 /*offsetTime*/);
                    } else if (REFERENCE == 0 && btnOpen == false) {
                        btnOpen = true;
                    }
                }
             }
        }
        else if (currentPosition == TOP) {
            if (readyToMove){
                readyToMove = false;
                while (currentPosition != position){
                    motor(LOWER_MOTOR, speed);
                    motor(UPPER_MOTOR, speed * motorCorrectionFactor);
                    if (REFERENCE == 1 && btnOpen){
                        btnOpen = false;
                        currentPosition--;
                        msleep(offsetTime);
                    } else if (REFERENCE == 0 && btnOpen == false) {
                        btnOpen = true;
                    }
                }
            }
        }
    }
    else if (position == MIDDLE) {
        if (currentPosition == GROUND) {
            if (readyToMove){
                readyToMove = false;
                while (currentPosition != position){
                    motor(LOWER_MOTOR, -speed);
                    motor(UPPER_MOTOR, -speed * motorCorrectionFactor);
                    printf("motors running\n");
                   	if (REFERENCE == 1 && btnOpen){
                        btnOpen = false;
                        printf("Clicked\n");
                        currentPosition++;
                        msleep(offsetTime);
                    } else if (REFERENCE == 0 && btnOpen == false) {
                        btnOpen = true;
                    }
                }
            }
        }
        else if (currentPosition == position) {
            printf("Already in current position");
        }
        else if (currentPosition == TOP) {
            if (readyToMove){
                readyToMove = false;
                while (currentPosition != position){
                    motor(LOWER_MOTOR, speed);
                    motor(UPPER_MOTOR, speed * motorCorrectionFactor);
                    if (REFERENCE == 1 && btnOpen) {
                        btnOpen = false;
                        currentPosition--;
                        msleep(offsetTime);
                    } else if (REFERENCE == 0 && btnOpen == false) {
                        btnOpen = true;
                    }
                }
            }
        }
    }
    else if (position == TOP) {
        if (currentPosition == GROUND) {
            if (readyToMove){
                while (currentPosition != TOP){
                    motor(LOWER_MOTOR, -speed);
                    motor(UPPER_MOTOR, -speed * motorCorrectionFactor);
                    if (REFERENCE == 1 && btnOpen){
                        btnOpen = false;
                        currentPosition++;
                        msleep(offsetTime);
                    } else if (REFERENCE == 0 && btnOpen == false) {
                        btnOpen = true;
                    }
                }
            }
        }
        else if (currentPosition == MIDDLE) {
            if (readyToMove){
                while (currentPosition != TOP){
                    motor(LOWER_MOTOR, -speed);
                    motor(UPPER_MOTOR, -speed * motorCorrectionFactor);
                    if (REFERENCE == 1 && btnOpen){
                        btnOpen = false;
//                        currentPosition++;
                        currentPosition = position;
                        ao();
                        msleep(offsetTime);
                    } else if (REFERENCE == 0 && btnOpen == false) {
                        btnOpen = true;
                    }
                }
            }
        }
        else if (currentPosition == position) {
            printf("Already in current position");
        }
    }
    readyToMove = true;
}

void preciseRaiseClaw(int speed){
    
    motor(LOWER_MOTOR, speed);
    motor(UPPER_MOTOR, speed * motorCorrectionFactor);
    while(REFERENCE != 1){
        msleep(10);
    }
    ao();
}

void slightRaiseClaw(int speed){
    
    motor(LOWER_MOTOR, -speed);
    motor(UPPER_MOTOR, -speed * motorCorrectionFactor);
    msleep(10);
    ao();
}

void littleRaiseClaw(int speed){
    motor(LOWER_MOTOR, -speed);
    motor(UPPER_MOTOR, -speed * motorCorrectionFactor);
    msleep(30);
    ao();
}

void customRaiseClaw(int speed, int delay){
    //-speed is up
    motor(LOWER_MOTOR, speed);
    motor(UPPER_MOTOR, speed * motorCorrectionFactor);
    msleep(delay);
    ao();
}

void newCustomRaiseClaw(int distance){
    clear_motor_position_counter(LOWER_MOTOR);
    clear_motor_position_counter(UPPER_MOTOR);
    mrp(LOWER_MOTOR, 300, distance);
    mrp(UPPER_MOTOR, 300 * motorCorrectionFactor, distance);
    bmd(UPPER_MOTOR);
    bmd(LOWER_MOTOR);
}