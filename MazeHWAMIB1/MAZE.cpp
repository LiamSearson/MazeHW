#include <FlexyStepper.h>
#include "states.h"

namespace MAZE{
FlexyStepper xAxis;
FlexyStepper yAxis;

byte xHomeSensor = 29;
byte yHomeSensor = 28;
bool readyForMove = false;
int microstepping = 8; //highest 1/32

void setup() {        //sets up the maze with its steppers and moves it to the home position then makes it flat
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
  xAxis.moveToPositionInSteps(170 * microstepping);
  yAxis.moveToPositionInSteps(170 * microstepping);
  readyForMove = true;
  xPosition.value = 170 * microstepping;
  yPosition.value = 170 * microstepping;
}

void loop() {
  //if((xPosition.value <= 2900 && yPosition.value <= 2900) && (xPosition.value >= 0 && yPosition.value >= 0)){
    if(xPosition.changed || yPosition.value){
      xAxis.setTargetPositionInSteps(xPosition.value);
      yAxis.setTargetPositionInSteps(yPosition.value);
    } //checks to see if the values for the steppers have changed and then moves the steppers to the new values
    if(readyForMove){
      xAxis.processMovement();
      yAxis.processMovement();
    }
  //}
}


void events::reset(){ //an event to do the same thing as setup, but it just homes the maze steppers again and flattens it out
  readyForMove = false;
  xAxis.enableStepper();
  yAxis.enableStepper();
  xAxis.moveToHomeInSteps(-1, 6000, 400 * microstepping, xHomeSensor);
  yAxis.moveToHomeInSteps(-1, 6000, 400 * microstepping, yHomeSensor);
  xAxis.moveToPositionInSteps(170 * microstepping);
  yAxis.moveToPositionInSteps(170 * microstepping);
  xPosition.value = 170 * microstepping;
  yPosition.value = 170 * microstepping;
  readyForMove = true;
  tablet::events::finishedAction();
}

}
