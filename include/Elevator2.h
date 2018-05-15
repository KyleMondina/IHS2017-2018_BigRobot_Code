#define LOWER_MOTOR 3
#define UPPER_MOTOR 2

#define UP digital(1) == 1;
#define DOWN digital(2) == 1;
#define CLEARMTR digital(6) == 1;
#define CORRECTION_FACTOR 0.95;

#define GROUND -100 //the distance between middle to ground, replace -100 when you find the distance
#define MIDDLE 0
#define TOP 100 // the distance between the middle and the top, replace 100 when you find the distance

//use this function to find the distance between the middle to top and ground, make sure you set middle position as 
//distance 0
void showDistance(double speed) {
    
    clear_motor_position_counter(ELEVATOR1);
    
    while (1) {
        // -speed = up & speed = down
        if (UP) {
            motor(ELEVATOR1, -speed * motorCorrectionFactor);
            motor(ELEVATOR2, -speed);
            console_clear();
            printf("Motor Position  :  %d"), get_motor_position(ELEVATOR1));
        }
        else if (DOWN) {
            motor(ELEVATOR1, speed * motorCorrectionFactor);
            motor(ELEVATOR2, speed);
            console_clear();
            printf("Motor Position  :  %d"), get_motor_position(ELEVATOR1));
        }
        else if (CLEARMTR) {
            clear_motor_position_counter(ELEVATOR1);
        }
        else {
            motor(ELEVATOR1, 0);
            motor(ELEVATOR2, 0);
        }
    }
}

void moveElevatorTo(int pos, double speed){

    //middle position is always set at distance = 0

    //code assumes that distance values below middle are negative. Flip the signs of the values if this is not the case
    int motorPos = gmpc(ELEVATOR1);

    switch(pos){

        case GROUND:
	    if (motorPos>GROUND){
	        //below ground position, needs to move up, -speed is up
	        if (speed > 0 ) {speed*= -1; }

		motor(LOWER_MOTOR, speed);
		motor(UPPER_MOTOR, speed);
	        while(motorPos <= GROUND){
			msleep(10);
			momtorPos = gmpc(ELEVATOR1);
	        }
                ao();
	    }
	    else if (motorPos < GROUND ){
	        //above ground position, needs to move down, speed is down
	        if (speed < 0 ) {speed*= -1; }

		motor(LOWER_MOTOR, speed);
		motor(UPPER_MOTOR, speed);
	        while(motorPos >= GROUND){
			msleep(10);
			momtorPos = gmpc(ELEVATOR1);
	        }
                ao();
	    }
	    else{ printf("already in position"); }
            break;
    
        case MIDDLE:
	    if (motorPos>MIDDLE){
	        //below middle position, needs to move up, -speed is up
	        if (speed > 0 ) {speed*= -1; }

		motor(LOWER_MOTOR, speed);
		motor(UPPER_MOTOR, speed);
	        while(motorPos <= MIDDLE){
			msleep(10);
			momtorPos = gmpc(ELEVATOR1);
	        }
                ao();
	    }
	    else if (motorPos < MIDDLE ){
	        //above middle position, needs to move down, speed is down
	        if (speed < 0 ) {speed*= -1; }

		motor(LOWER_MOTOR, speed);
		motor(UPPER_MOTOR, speed);
	        while(motorPos >= MIDDLE){
			msleep(10);
			momtorPos = gmpc(ELEVATOR1);
	        }
                ao();
	    }
	    else{ printf("already in position"); }
            break;

        case TOP:
	    if (motorPos>TOP){
	        //below ground position, needs to move up, -speed is up
	        if (speed > 0 ) {speed*= -1; }

		motor(LOWER_MOTOR, speed);
		motor(UPPER_MOTOR, speed);
	        while(motorPos <= TOP){
			msleep(10);
			momtorPos = gmpc(ELEVATOR1);
	        }
                ao();
	    }
	    else if (motorPos < TOP ){
	        //above ground position, needs to move down, speed is down
	        if (speed < 0 ) {speed*= -1; }

		motor(LOWER_MOTOR, speed);
		motor(UPPER_MOTOR, speed);
	        while(motorPos >= TOP){
			msleep(10);
			momtorPos = gmpc(ELEVATOR1);
	        }
                ao();
	    }
	    else{ printf("already in position"); }
            break;

        default:
	    if (motorPos>pos){
	        //below ground position, needs to move up, -speed is up
	        if (speed > 0 ) {speed*= -1; }

		motor(LOWER_MOTOR, speed);
		motor(UPPER_MOTOR, speed);
	        while(motorPos <= pos){
			msleep(10);
			momtorPos = gmpc(ELEVATOR1);
	        }
                ao();
	    }
	    else if (motorPos < pos ){
	        //above ground position, needs to move down, speed is down
	        if (speed < 0 ) {speed*= -1; }

		motor(LOWER_MOTOR, speed);
		motor(UPPER_MOTOR, speed);
	        while(motorPos >= pos){
			msleep(10);
			momtorPos = gmpc(ELEVATOR1);
	        }
                ao();
	    }
	    else{ printf("already in position"); }
            
    }
}

