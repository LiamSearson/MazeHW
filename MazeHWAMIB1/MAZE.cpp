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
  xAxis.moveToPositionInSteps(180 * microstepping);
  yAxis.moveToPositionInSteps(200 * microstepping);
  readyForMove = true;
}

void loop() {
  if(xPosition.changed || yPosition.value){
    xAxis.setTargetPositionInSteps(xPosition.value);
    yAxis.setTargetPositionInSteps(yPosition.value);
  }
  if(readyForMove){
    xAxis.processMovement();
    yAxis.processMovement();
  }
}

void enter(){
  xAxis.moveToPositionInSteps(180 * microstepping);
  yAxis.moveToPositionInSteps(200 * microstepping);
  xPosition.value = 180 * microstepping;
  yPosition.value = 200 * microstepping;
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

}
