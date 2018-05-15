#define Pp 0.001
#define Dp 0.0001

#define P1 3.1
#define I1 0.1
#define D1 0.5 
#define right_P 0.2
#define right_I 0.5
#define right_D 0.3
#define left_P 0.2
#define left_I 0.5
#define left_D 0.3

double rightTarget = 2770;
double leftTarget = 2780;

double outMin,outMax;


void SetOutputLimits(double Min, double Max)
{
   if(Min > Max) return;
   outMin = Min;
   outMax = Max;
}


#define BUMP 1
void printLightValues(){
    while(1){
        int lfront = get_create_lfcliff_amt();
        int rfront = get_create_rfcliff_amt();
        int l = get_create_lcliff_amt();
        int r = get_create_rcliff_amt();
    
        printf("lfront :%i rfront: %i l: %i r:%i\n ", lfront, rfront, l, r);
        msleep(100);
    }
}

void printLineFollow(){
    //double dinputDistance_mm = inputDistance_cm * 10.125;
    //double currentDistance_mm = get_create_distance()*1.0;
    double lastError = 0.0;
    
    while(1){
        double dspeed = 100;
        int lfront = get_create_lfcliff_amt();
        int rfront = get_create_rfcliff_amt();
        // COMMENTED OUT SINCE COMPILER HATES US double dlfront = (double)lfront;
        //                                       double drfront = (double)rfront;
        
        double error = lfront - rfront ;
        double turner = 1.0;
        double powerUp = (turner*dspeed)+ (dspeed*(Pp*error + Dp*((error*0.8) - lastError)));
        double powerDown = (turner*dspeed)- (dspeed*(Pp*error + Dp*((error*0.8) - lastError)));
        int ipowerUp = (int)powerUp;
        int ipowerDown = (int) powerDown;
        
        if (error <-1){
            //turn left
            turner = -1.0;
            printf("Turning Left powerDown: %i\n", ipowerDown);

        }
        else if (error > 1){
            //turn right
            turner = 1.0;
            printf("Turning Right powerUp: %i\n", ipowerUp);
        }
        else{ 
			
        }
        printf("Drive Straight speed: 100\n");
        lastError = error;
        
        msleep(100);
    }
}

void refinedLineFollow(int inputDistance_cm, int speed){
    double dinputDistance_mm = inputDistance_cm * 10.125;
    double currentDistance_mm = get_create_distance()*1.0;
    double lastError = 0;
    double dspeed = (double)speed;
    
    while(currentDistance_mm < dinputDistance_mm){
        int lfront = get_create_lfcliff_amt();
        int rfront = get_create_rfcliff_amt();
        double dlfront = (double)lfront;
        double drfront = (double)rfront;
        
        double error = lfront - rfront ;
        double turner = 1.0;
        double powerUp = (turner*dspeed)+ (dspeed*(Pp*error + Dp*((error*0.8) - lastError)));
        double powerDown = (turner*dspeed)- (dspeed*(Pp*error + Dp*((error*0.8) - lastError)));
        int ipowerUp = (int)powerUp;
        int ipowerDown = (int) powerDown;
        printf("lfront: %.2f rfront: %.2f  powerUp: %i\n", dlfront, drfront, ipowerUp);
        
        if (error <-1){
            //turn left
            turner = -1.0;
            create_drive_direct(speed, ipowerDown);

        }
        else if (error > 1){
            //turn right
            turner = -1.0;
            create_drive_direct(ipowerUp, speed);
 
        }
        else{ 
            create_drive_direct(speed,speed);
        }
        
        currentDistance_mm = get_create_distance()*1.0;
        lastError = error;
        msleep(100);
    }
}

void lineFollowTillBump(int speed){
    double lastError = 0;
    double dspeed = (double)speed;
    
    while(1){
        create_drive_direct(speed,speed);
        printf("driving\n");
        if( get_create_lbump() == BUMP && get_create_rbump() == BUMP){break;}

    }
    
    while(1){
        int lfront = get_create_lfcliff_amt();
        int rfront = get_create_rfcliff_amt();
        double dlfront = (double)lfront;
        double drfront = (double)rfront;
        
        double error = lfront - rfront ;
        double turner = 1.0;
        double powerUp = (turner*dspeed)+ (dspeed*(Pp*error + Dp*((error*0.8) - lastError)));
        double powerDown = (turner*dspeed)- (dspeed*(Pp*error + Dp*((error*0.8) - lastError)));
        int ipowerUp = (int)powerUp;
        int ipowerDown = (int) powerDown;
        printf("lfront: %.2f rfront: %.2f  powerUp: %i\n", dlfront, drfront, ipowerUp);
        
        if(get_create_lbump() == BUMP && get_create_rbump() == BUMP){
            break;
        }
        else if (error <-1){
            //turn left
            turner = -1.0;
            create_drive_direct(speed, ipowerDown);

        }
        else if (error > 1){
            //turn right
            turner = -1.0;
            create_drive_direct(ipowerUp, speed);
 
        }
        else{ 
            create_drive_direct(speed,speed);
        }
        
        lastError = error;
        msleep(100);
    }
}

void fasterRefinedLineFollow(int inputDistance_cm, int speed){
    double dinputDistance_mm = inputDistance_cm * 10.125;
    double currentDistance_mm = get_create_distance()*1.0;
    
    double lastRightError = 0;
    double lastLeftError = 0;
    


    
    double dspeed = (double)speed;
    //double turner = 1.0;
    
    while (currentDistance_mm < dinputDistance_mm){
        int lfront = get_create_lfcliff_amt();
        int rfront = get_create_rfcliff_amt();
        

        
        //double target = 2830;
        double rightTarget = 2830;
        double leftTarget = 2840;
        
        double rightError = rightTarget - rfront;
        double leftError = leftTarget - lfront;
        double rightProportional = P1 * rightError;
        double leftProportional = P1 * leftError;
        double rightDifferential = (rightError-lastRightError) * D1;
        double leftDifferential = (leftError-lastLeftError) * D1;
        double rightIntegral = (rightIntegral + rightProportional) * I1;
        double leftIntegral = (leftIntegral + leftIntegral) * I1;
        
        double pdRight = dspeed + (rightProportional + rightDifferential + rightIntegral);
        double pdLeft =  dspeed + (leftProportional + leftDifferential + leftIntegral);
        
        lastRightError = rightError;
        lastLeftError = leftError;
        
        int ipowerUp = (int) pdRight;
        int ipowerDown = (int) pdLeft;
   
        printf("Right-Proportional: %f Left-Proportional: %f\n\n", rightProportional, leftProportional);
        //printf("Right-Sensor: %f Left-Sensor: %f\n", dlfront, drfront);
        //printf("rightError: %.2f  leftError: %.2f\n", rightError, leftError);
        printf("turnRight: %.2f turnLeft: %.2f\n",pdRight, pdLeft);
        //printf("lfront: %.2f rfront: %.2f  turnRight: %i  turnLeft: %i\n", dlfront, drfront, turnRight,turnLeft);
       	create_drive_direct(ipowerUp, ipowerDown);
        currentDistance_mm = get_create_distance()*1.0;

        msleep(50);
    }
}


void fasterRefinedLineFollowTillBlack(int speed){
	bool needCheck = true;
    
    double lastRightError = 0;
    double lastLeftError = 0;
   
    
    double dspeed = (double)speed;
    //double turner = 1.0;
    
    while (needCheck){
    	int checkLeft = get_create_lcliff_amt();
        int lfront = get_create_lfcliff_amt();
        int rfront = get_create_rfcliff_amt();
        
   
        
        //double target = 2830;
        double rightTarget = 2830;
        double leftTarget = 2840;
        
        double rightError = rightTarget - rfront;
        double leftError = leftTarget - lfront;
        double rightProportional = P1 * rightError;
        double leftProportional = P1 * leftError;
        double rightDifferential = (rightError-lastRightError) * D1;
        double leftDifferential = (leftError-lastLeftError) * D1;
        double rightIntegral = (rightIntegral + rightProportional) * I1;
        double leftIntegral = (leftIntegral + leftIntegral) * I1;
        
        double pdRight = dspeed + (rightProportional + rightDifferential + rightIntegral);
        double pdLeft =  dspeed + (leftProportional + leftDifferential + leftIntegral);
        
        lastRightError = rightError;
        lastLeftError = leftError;
        
        int ipowerUp = (int) pdRight;
        int ipowerDown = (int) pdLeft;
   
        printf("Right-Proportional: %f Left-Proportional: %f\n\n", rightProportional, leftProportional);
        //printf("Right-Sensor: %f Left-Sensor: %f\n", dlfront, drfront);
        //printf("rightError: %.2f  leftError: %.2f\n", rightError, leftError);
        printf("turnRight: %.2f turnLeft: %.2f\n",pdRight, pdLeft);
        //printf("lfront: %.2f rfront: %.2f  turnRight: %i  turnLeft: %i\n", dlfront, drfront, turnRight,turnLeft);
       	create_drive_direct(ipowerUp, ipowerDown);
        if(checkLeft <= BLACK) needCheck = false;
        
        msleep(50);
    }
}




void refinedLineFollowTillBlack(int speed){
    bool needCheck = true;
    double lastError = 0;
    double dspeed = (double)speed;
    
    while(needCheck){
        int checkLeft = get_create_lcliff_amt();
        int checkRight = get_create_rcliff_amt();
        if(checkLeft <= BLACK || checkRight <= BLACK) needCheck = false;
        int lfront = get_create_lfcliff_amt();
        int rfront = get_create_rfcliff_amt();
        double dlfront = (double)lfront;
        double drfront = (double)rfront;
        
        double error = lfront - rfront ;
        double turner = 1.0;
        double powerUp = (turner*dspeed)+ (dspeed*(Pp*error + Dp*((error*0.8) - lastError)));
        double powerDown = (turner*dspeed)- (dspeed*(Pp*error + Dp*((error*0.8) - lastError)));
        int ipowerUp = (int)powerUp;
        int ipowerDown = (int) powerDown;
        printf("lfront: %.2f rfront: %.2f  powerUp: %i\n", dlfront, drfront, ipowerUp);
        
        if (error <-1){
            //turn left
            turner = -1.0;
            create_drive_direct(speed, ipowerDown);

        }
        else if (error > 1){
            //turn right
            turner = -1.0;
            create_drive_direct(ipowerUp, speed);
 
        }
        else{ 
            create_drive_direct(speed,speed);
        }
        

        lastError = error;
        msleep(100);
    }
    create_stop();
    
}


void pi_LineFollow(int inputDistance_cm, int speed, int delay){
    double dinputDistance_mm = inputDistance_cm * 10.125;
    double currentDistance_mm = get_create_distance()*1.0;
    
    double lastRightError = 0;
    double lastLeftError = 0;
    
    double dspeed = (double)speed;
    //double turner = 1.0;
    
    SetOutputLimits(dspeed-70,dspeed+70);
    
    while (currentDistance_mm < dinputDistance_mm){
        int lfront = get_create_lfcliff_amt();
        int rfront = get_create_rfcliff_amt();
        
        double dlfront = (double)lfront;
        double drfront = (double)rfront;
        
        
        double rightError = rightTarget - rfront;
        double leftError = leftTarget - lfront;
        double rightProportional = right_P * rightError;
        double leftProportional = left_P * leftError;
        double rightIntegral = (rightIntegral + rightProportional) * right_I;
        double leftIntegral = (leftIntegral + leftProportional) * left_I;
        
        //Reset Windup - Limits for individual components
        if (rightIntegral > outMax) rightIntegral = outMax;
        else if(rightIntegral < outMin) rightIntegral = outMin;
        /*
        if (leftIntegral > outMax) leftIntegral = outMax;
        else if(leftIntegral < outMin) leftIntegral = outMin;
        //
        if (rightProportional > outMax) rightProportional = outMax;
        else if(rightProportional < outMin) rightProportional = outMin;
        if (leftProportional > outMax) leftProportional = outMax;
        else if(leftProportional < outMin) leftProportional = outMin;        
        */
        //Calculation turning speed
        
        double pdRight = dspeed + (rightProportional + rightIntegral);//+ rightDifferential); //+ rightIntegral);
        double pdLeft =  dspeed + (leftProportional + leftIntegral);//+ leftDifferential); //+ leftIntegral);
        
        //Reset Windup - Limits for turning speed
        /*
        if (pdRight > outMax) pdRight = outMax;
        else if(pdRight < outMin) pdRight = outMin;
        if (pdLeft > outMax) pdLeft = outMax;
        else if(pdLeft < outMin) pdLeft = outMin;
        */
        lastRightError = rightError;
        lastLeftError = leftError;
        
        int ipowerUp = (int) pdRight;
        int ipowerDown = (int) pdLeft;
        
        
        //printf("Right-Proportional: %f Left-Proportional: %f\n\n", rightProportional, leftProportional);
        printf("---------------------------------------\n");
        printf("Right-Sensor: %f Left-Sensor: %f\n", dlfront, drfront);
        //printf("rightError: %.2f  leftError: %.2f\n", rightError, leftError);
        printf("turnRight: %.2f turnLeft: %.2f\n",pdRight, pdLeft);
        //printf("lfront: %.2f rfront: %.2f  turnRight: %i  turnLeft: %i\n", dlfront, drfront, turnRight,turnLeft);
        
       	create_drive_direct(ipowerUp, ipowerDown);
        
        currentDistance_mm = get_create_distance()*1.0;

        msleep(delay);
    }
}




