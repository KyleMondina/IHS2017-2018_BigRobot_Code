#include <kipr/botball.h>
#include <stdbool.h>

// === ROTATION PRESETS DEFINES === //
#define REAL180 204
#define REAL90 105
// === END OF ROTATION PRESET DEFINDES === //

// === SENSOR DEFINES === //
#define BUMP 1
#define BLACK 1800
// === END OF SENSOR DEFINES === //

// === FUNCTION LIBRARY === //
/* 
Move Functions
	void turnLeft180();
	void turnLeft180();
	void turnRight90();
	void turnRight90();
    void turnLeftBotGuy(int angle, int speed);
    void turnRightBotGuy(int angle, int speed);
    void driveForwardTillBothBumped(int speed);
    void driveForwardTillOneBumped(int speed);
	void driveBackwardForSomeCM(int inputDistance_cm, int speed);
	void driveForwardForSomeCM(int inputDistance_cm, int speed);
    void driveTillBlack(int speed);
    void driveTillRightBlack(int speed);
    void driveTillLeftBlack(int speed);
    void driveTillLeftFrontBlack(int speed);
  
Misc. Functions
	void waitForSome(double sec);
    int inCmConv(double inches);
	void printBatteryCapacity();
*/
// === END OF FUNCTION LIBRARY === //

// === MOVE FUNCTIONS === //
void turnLeft180(int speed)
{

    printf("Turn left 180");
    set_create_normalized_angle(0);
    int currentAngle = get_create_normalized_angle();
    while (currentAngle < REAL180) {
        create_spin_CCW(speed);
        currentAngle = get_create_normalized_angle();
        printf("%i\n",get_create_normalized_angle());
    }

    create_stop();

}

void turnRight180(int speed)
{
    
    printf("Turn Right 180");
    set_create_normalized_angle(0);
    int currentAngle = get_create_normalized_angle();
    while (currentAngle > -REAL180) {
        create_spin_CW(speed);
        currentAngle = get_create_normalized_angle();
        printf("%i\n",get_create_normalized_angle());
    }
    
    create_stop();
    
}

void turnLeft90(int speed)
{
    
    printf("Turn left 90");
    set_create_normalized_angle(0);
    int currentAngle = get_create_normalized_angle();
    while (currentAngle < REAL90) {
        create_spin_CCW(speed);
        currentAngle = get_create_normalized_angle();
        printf("%i\n",get_create_normalized_angle());
    }
    
    create_stop();
    
}

void turnRight90(int speed)
{
    
    printf("Turn Right 90");
    set_create_normalized_angle(0);
    int currentAngle = get_create_normalized_angle();
    while (currentAngle > -REAL90) {
        create_spin_CW(speed);
        currentAngle = get_create_normalized_angle();
        printf("%i\n",get_create_normalized_angle());
    }
    
    create_stop();
    
}

void turnLeftBotGuy(int angle, int speed)
{
    
    printf("Turn left %i\n", angle);
    set_create_normalized_angle(0);
    int currentAngle = get_create_normalized_angle();
    while (currentAngle < angle) {
        create_spin_CCW(speed);
        currentAngle = get_create_normalized_angle();
        printf("%i\n",get_create_normalized_angle());
    }
    
    create_stop();
    
}

void turnRightBotGuy(int angle, int speed)
{
    
    printf("Turn Right %i\n", angle);
    set_create_normalized_angle(0);
    int currentAngle = get_create_normalized_angle();
    while (currentAngle > -angle) {
        create_spin_CW(speed);
        currentAngle = get_create_normalized_angle();
        printf("%i\n",get_create_normalized_angle());
    }
    
    create_stop();
    
}

void driveForwardTillBothBumped(int speed){
    
    while(1){
        create_drive_direct(speed,speed);
        printf("driving\n");
        if( get_create_lbump() == BUMP && get_create_rbump() == BUMP){break;}

    }
    
    printf("not driving");
    create_stop();
    
}

void driveForwardTillOneBumped(int speed){
    
    while(1){
        create_drive_direct(speed,speed);
        printf("driving\n");
        if( get_create_lbump() == BUMP || get_create_rbump() == BUMP){break;}

    }
    
    printf("not driving");
    create_stop();
    
}

void driveForwardForSomeCM(int inputDistance_cm, int speed)
{
    
    set_create_distance(0);
    
    int inputDistance_mm = inputDistance_cm * 10.125;
    int currentDistance_mm = get_create_distance();

    while(currentDistance_mm < inputDistance_mm)
    {
        create_drive_direct(speed,speed);
        currentDistance_mm = get_create_distance();
        printf("length: %i\n", currentDistance_mm);
    }

    create_stop();
    
}

void driveBackwardForSomeCM(int inputDistance_cm, int speed)
{
    
    set_create_distance(0);
    speed*=-1;
    
    int inputDistance_mm = inputDistance_cm *10.125 * -1;
    int currentDistance_mm = get_create_distance();

    while(currentDistance_mm > inputDistance_mm)
    {
        create_drive_direct(speed,speed);
        msleep(10);
        currentDistance_mm = get_create_distance();
    }
	

    create_stop();
    
}

void driveTillBlack(int speed)
{
    
    bool needCheck = true;
    create_drive_direct(speed, speed); 
    printf("driving\n");
    while(needCheck){
        int checkLeft = get_create_lcliff_amt();
        int checkRight = get_create_rcliff_amt();

        if(checkLeft <= BLACK || checkRight <= BLACK) needCheck = false;
        else if (checkLeft == 1) printf("left\n");
        else if (checkRight == 1) printf("right\n");
        else{ 
            printf ("drving right: %i left: %i\n", checkRight, checkLeft);
            msleep(100);
        }
    }
    printf("stop");

    create_stop();
    
}

void driveTillRightBlack(int speed)
{
    
    bool needCheck = true;
    create_drive_direct(speed, speed); 
    printf("driving\n");
    while(needCheck){
        int checkRight = get_create_rcliff_amt();

        if(checkRight <= BLACK) needCheck = false;
        else if (checkRight == 1) printf("right\n");
        else{ 
            printf ("drving right: %i\n", checkRight);
            msleep(100);
        }
    }

    printf("stop");
    create_stop();
    
}

void driveTillLeftBlack(int speed)
{
    
    bool needCheck = true;
    create_drive_direct(speed, speed); 
    printf("driving\n");
    while(needCheck){
        int checkLeft = get_create_lcliff_amt();

        if(checkLeft <= BLACK) needCheck = false;
        else if (checkLeft == 1) printf("left\n");
        else{ 
            printf ("drving right: %i\n", checkLeft);
            msleep(100);
        }
    }
    printf("stop");

    create_stop();
    
}

void driveTillLeftFrontBlack(int speed)
{
    
    bool needCheck = true;
    create_drive_direct(speed, speed); 
    printf("driving\n");
    while(needCheck){
        int checkLeft = get_create_lfcliff_amt();

        if(checkLeft <= BLACK) needCheck = false;
        else if (checkLeft == 1) printf("left\n");
        else{ 
            printf ("drving right: %i\n", checkLeft);
            msleep(100);
        }
    }
    printf("stop");

    create_stop();
    
}
// === END OF MOVE FUNCTIONS === //

// === MISC. FUNCTIONS === //
void waitForSome(double sec)
{
    
    ao();
    create_stop();
    double mili = sec*1000;
    msleep(mili);
    
}

int inCmConv(double inches)
{
    return (inches * 2.54) + 1;
}

void printBatteryCapacity()
{
    
    int batteryCharge = get_create_battery_charge();
    int batteryCapacity = get_create_battery_capacity();
    int batteryVoltage = get_create_battery_voltage();
    int batteryCurrent = get_create_battery_current();
    
    double batteryPercentage = ((double)(batteryCharge)/batteryCapacity)*100;
    
    printf("Battery Percentage: %lf\n", batteryPercentage);
    printf("Battery Voltage: %i\n", batteryVoltage);
    printf("Battery Current: %i\n", batteryCurrent);
    
}
// === END OF MISC. FUNCTIONS === //