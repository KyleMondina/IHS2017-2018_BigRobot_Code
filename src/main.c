#include <kipr/botball.h>
#include <CompetitionMoves.h>

int main(){
    
	preStart();
	//printBatteryCapacity();

   	waitForSome(3);
  	goToLine();
    //waitForSome(5);

   	goToCenter();

    grabBotGuyFromCenter();
    dragBotGuyBackLeft();
    
    turnLeft90(75);
    driveForwardTillBothBumped(200);
    turnLeft90(75);
    driveForwardTillBothBumped(200);
    
    /*goToTram();
    dunkBotGuy();
    positionToPushBotGuy();
    
    pushBotGuy();
    goBack();*/
    

    end();
    
    return 0;
}
