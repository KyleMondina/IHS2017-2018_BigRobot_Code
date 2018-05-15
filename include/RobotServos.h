#include <kipr/botball.h>
#include <stdbool.h>

// === SERVO DEFINES === //
#define maxOpenLatch 900
#define maxCloseLatch 1800
#define LATCH_SERVO 4
#define CLAW_SERVO 2
#define CLOSE 2
#define OPEN 1
#define maxOpenClaw 100
#define minCloseClaw 850
// === END OF SERVO DEFINES === //

// === FUNCTION LIBRARY === //
/*
Servo Functions
	void clawMove(int pos); - DEFAULTS TO PORT #1
    void latch(int pos);
*/
// === FUNCTION LIBRARY === //

// === SERVO FUNCTIONS === //
void latch(int pos) {

    enable_servos();

    if (pos == CLOSE) {
        set_servo_position(LATCH_SERVO, maxCloseLatch);
    }
    else if (pos == OPEN) {
        set_servo_position(LATCH_SERVO, maxOpenLatch);
    }

}

void clawMove(int pos) {
    
    int current = get_servo_position(CLAW_SERVO);
    if (pos > current) {
        while (current < pos) {
            printf("%i\n", current);
            current+=25;
            set_servo_position(CLAW_SERVO, current);
            msleep(10);
        }
    }
    else if (pos < current) {
        while (current > pos) {
            current-=25;
            set_servo_position(CLAW_SERVO, current);
            msleep(10);
        }
    }
    
}
// === END OF SERVO FUNCTIONS === //