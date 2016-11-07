#include <FlexyStepper.h>
#include "states.h"

namespace MAZE{
FlexyStepper xAxis;
FlexyStepper yAxis;

byte xHomeSensor = 29;
byte yHomeSensor = 28;
bool readyForMove = false;
int microstepping = 8; //highest 1/32

void setup() {
  xAxis.connectToPort(1);
  yAxis.connectToPort(2);
  xAxis.enableStepper();
  yAxis.enableStepper();
  xAxis.setSpeedInStepsPerSecond(6000);
  yAxis.setSpeedInStepsPerSecond(6000);
  xAxis.setAccelerationInStepsPerSecondPerSecond(10000);
  yAxis.setAccelerationInStepsPerSecondPerSecond(10000);
  xAxis.moveToHomeInSteps(-1, 6000, 400 * microstepping, xHomeSensor);
  yAxis.moveToHomeInSteps(-1, 6000, 400 * microstepping, yHomeSensor);
  xAxis.moveToPositionInSteps(73 * microstepping);
  yAxis.moveToPositionInSteps(73 * microstepping);
  readyForMove = true;
}

void loop() {
  if(readyForMove){
    /*if(xPosition.changed){
        xAxis.moveToPositionInSteps(xPosition.value/100.0);
    }
    if(yPosition.changed){
        yAxis.moveToPositionInSteps(yPosition.value/100.0);
    }*/
    xAxis.setTargetPositionInSteps(xPosition.value);
    yAxis.setTargetPositionInSteps(yPosition.value);
  }
  xAxis.processMovement();
  yAxis.processMovement();
}

void events::reset(){
  readyForMove = false;
  xAxis.setSpeedInStepsPerSecond(3000);
  yAxis.setSpeedInStepsPerSecond(3000);
  xAxis.enableStepper();
  yAxis.enableStepper();
  xAxis.moveToHomeInSteps(-1, 3000, 400*microstepping, xHomeSensor);
  yAxis.moveToHomeInSteps(-1,3000,400*microstepping, yHomeSensor);
  xAxis.moveToPositionInSteps(.35);
  yAxis.moveToPositionInSteps(.35);
  readyForMove = true;
  tablet::events::finishedAction();
}

void events::moveToXPosition(){
    xAxis.moveToPositionInSteps(xPosition.value);  //enter from 0 to 73 * microstepping
}

void events::moveToYPosition(){
  yAxis.moveToPositionInSteps(yPosition.value); //enter from 0 to 70
}

void events::demo(){
  for(int x = 0; x < 5; x++){
    xAxis.setSpeedInStepsPerSecond(500);
    yAxis.setSpeedInStepsPerSecond(500);
    xAxis.setTargetPositionInSteps(0);
    yAxis.setTargetPositionInSteps(0);
    while(!xAxis.motionComplete() || !yAxis.motionComplete()){
      xAxis.processMovement();
      yAxis.processMovement();
    }
    xAxis.setTargetPositionInSteps(1168);
    yAxis.setTargetPositionInSteps(1168);
    while(!xAxis.motionComplete() || !yAxis.motionComplete()){
      xAxis.processMovement();
      yAxis.processMovement();
    }
  }
}

}
