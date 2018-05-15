#include <kipr/botball.h>
#include <RobotMoves.h>
#include <RobotServos.h>
#include <Elevator.h>
#include <PIDLineFollowFunctions.h>
//#include <Experimental PID.h>
#define DELAY 100


void preStart(){
    wait_for_light(0);
    shut_down_in( 119 );
	create_connect();
    printf("starting\n");
    enable_servos();
    latch(CLOSE);
    clawMove(minCloseClaw);
}

void end(){
    disable_servos();
    create_disconnect();
}
void goToLine(){
    printf("goToLine()\n");
    //Old Go To Line
    //driveForwardForSomeCM(35,100);
    //turnLeft90(65);
    
    turnLeftBotGuy(70, 50);
    driveTillBlack(200);
    driveForwardForSomeCM(20, 100);
    driveTillLeftFrontBlack(200);
    driveForwardForSomeCM(3, 50);
    
    console_clear();
    printf("goToLine() Completed, Doing Next Step in 2 Seconds\n");
    console_clear();

}

void goToCenter(){
    
    printf("goToCenter()\n");
    
    //Old Go To Center
    /*refinedLineFollow(100,100);
    driveTillRightBlack(70);
	driveForwardForSomeCM(8,25);
    turnLeft90(75);
    turnRightBotGuy(30,3);*/
     
    turnLeftBotGuy(30, 50);
    driveBackwardForSomeCM(30, 70);
    printf("cookies\n");
    
	pi_LineFollow(10, 100, 100);
    driveTillBlack(100);
    
    //refinedLineFollowTillBlack(100);
	driveForwardForSomeCM(8, 25);
    
    turnLeft90(75);
    turnRightBotGuy(25,3);
    
    /*turnRight90(75);
    driveBackwardForSomeCM(17, 40);
    pi_LineFollow(20,50,DELAY);
    driveBackwardForSomeCM(15, 50);
    turnLeft180(75);
    turnLeftBotGuy(50,5);*/
    
    console_clear();
    printf("goToCenter() Completed, Doing Next Step in 2 Seconds\n");
    console_clear();

}

void grabBotGuyFromCenter(){
    
    printf("grabBotGuyFromCenter()\n");
    
    //Lower Claw
    currentPosition = MIDDLE;
    raiseClaw(33, GROUND);
    currentPosition = GROUND;
 
    ao();
    
    //Grab BotGuy
    driveBackwardForSomeCM(16, 50);
    newCustomRaiseClaw(-50);
    turnLeftBotGuy(13, 21);
    newCustomRaiseClaw(75);
    clawMove(maxOpenClaw);
    driveBackwardForSomeCM(12, 50);
    turnRightBotGuy(4, 50);
    clawMove(minCloseClaw);
    turnRightBotGuy(1, 40);
    
    console_clear();
    printf("grabBotGuyFromCenter() Completed, Doing Next Step in 2 Seconds\n");
    console_clear();
}

void dragBotGuyBackLeft(){
    
    printf("dragBotGuyBack()\n");
   	
    //dragBotGuy
    driveForwardForSomeCM(36, 100);
    clawMove(maxOpenClaw);
    
    //Knock BotGuy over
    turnRightBotGuy(10, 68);
    driveBackwardForSomeCM(4, 20);
    //re-grab BotGuy
    clawMove(minCloseClaw);		
    turnLeftBotGuy(10, 68);
    
    //Open Latch
    currentPosition = GROUND;
    /*raiseClaw(33, MIDDLE);
    currentPosition = MIDDLE;
    ao();
    latch(OPEN);*/
    
    console_clear();
    printf("dragBotGuyBack() Completed, Doing Next Step in 2 Seconds\n");
    console_clear();
}

void dragBotGuyBackRight(){
    
    printf("dragBotGuyBack()\n");
   	
    //dragBotGuy
    driveForwardForSomeCM(36, 100);
    clawMove(maxOpenClaw);
    
    //Knock BotGuy over
    turnLeftBotGuy(10, 68);
    driveBackwardForSomeCM(4, 20);
    //re-grab BotGuy
    clawMove(minCloseClaw);		
    turnRightBotGuy(10, 68);
    
    //Open Latch
    /*currentPosition = GROUND;
    raiseClaw(33, MIDDLE);
    currentPosition = MIDDLE;
    ao();
    latch(OPEN);*/
    
    console_clear();
    printf("dragBotGuyBack() Completed, Doing Next Step in 2 Seconds\n");
    console_clear();
}

void goToTram(){
    
    printf("goToTram()\n");
    
    driveTillBlack(200);
//    driveForwardForSomeCM(5,40);
    
    console_clear();
    printf("goToTram() Completed, Doing Next Step in 2 Seconds\n");
    console_clear();
}

void dunkBotGuy(){
    
    printf("dunkBotGuy()\n");
    
    //slight positioning
    console_clear();
    printf("slight positioning\n");
    turnRightBotGuy(50,30);
    driveForwardForSomeCM(5,25);
    
    //dunking botguy
    console_clear();
    printf("dunking botguy\n");
    raiseClaw(34, TOP);
    currentPosition = TOP;
    newCustomRaiseClaw(-500); //lower claw a little further
    //turnLeftBotGuy(25,10); //making sure botguy is droped at an optimal place
        
    //droping botguy
    console_clear();
    printf("droping botguy\n");
    clawMove(maxOpenClaw);
    newCustomRaiseClaw(300);
    
    //getting away
    console_clear();
    printf("getting away\n");
    driveBackwardForSomeCM(7,50);
    clawMove(minCloseClaw);
    turnLeftBotGuy(10, 30); //used to correct line 105
    
    console_clear();
    printf("dunkBotGuy() Completed, Doing Next Step in 2 Seconds\n");
    console_clear();
}

void positionToPushBotGuy(){
    
    printf("positionToPushBotGuy()\n");
    
    //positioning behind the tram
    console_clear();
    printf("positioning behind the tram\n");
    preciseRaiseClaw(10);
    turnLeft180(50);
    driveBackwardForSomeCM(6,50);
    turnLeftBotGuy(20, 40);
    
    console_clear();
    printf("goToCenter() Completed, Doing Next Step in 2 Seconds\n");
    console_clear();
}

void pushBotGuy(){
    
    printf("pushBotGuy()\n");
    
    driveTillBlack(150);
    ao();
    lineFollowTillBump(100);
    driveBackwardForSomeCM(35, 200);
    turnRight180(70);
    driveBackwardForSomeCM(30, 150); 
    ao();
    
    console_clear();
    printf("goToCenter() Completed, Doing Next Step in 2 Seconds\n");
    console_clear();
}

void goBack(){
    driveTillRightBlack(70);
	driveForwardForSomeCM(8,75);
    turnLeft90(75);
    refinedLineFollow(105, 150);
    //pi_LineFollow(105, 150, DELAY);
    turnLeft90(75);
    driveForwardForSomeCM(30,50);
}

