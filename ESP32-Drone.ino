#include <Arduino.h>
#include "Functions.h"
#include "Constants.h"
#include "Structs.h"

#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

void disableWDT() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // Disable brownout detector
  WRITE_PERI_REG(RTC_CNTL_WDTCONFIG0_REG, 0); // Set WDT timeout to longest (approximately 71 minutes)
  WRITE_PERI_REG(RTC_CNTL_WDTCONFIG1_REG, 0); // Disable WDT
}



//Create two tasks for separate cores of Xtensa LX6
TaskHandle_t Task1;
TaskHandle_t Task2;

struct ReceiverCommands commands;
struct IMU_Values imu_values;

//Task 1 pinned to core0. Mainly for communication interrupts of reciever and speedometer.
void Task1code( void * pvParameters ){

  

  for(;;){

//  tunePID(commands);
//
  struct ConstantsPID pid = getPIDValues();

//  Serial2.print(commands.PitchAngle);
//  Serial2.print(",");
//  Serial2.print(imu_values.CurrentOrientation.PitchAngle);
//  Serial2.print(",");
//
////  Serial.print("Roll, Pitch values: P: ");
//  Serial2.print(pid.KP_roll_pitch);
//  Serial2.print(",");
////  Serial.print("I: ");
//  Serial2.print(pid.KI_roll_pitch);
//  Serial2.print(",");
////  Serial.print("D: ");
//  Serial2.println(pid.KD_roll_pitch);

//    //  Serial.print("Roll: ");
//  Serial.print(commands.RollAngle);
//  Serial.print(",");
////  Serial.print("Pitch: ");
//  Serial.print(commands.PitchAngle);
//  Serial.print(",");
////  Serial.print("Throttle: ");
//  Serial.print(commands.Throttle);
//  Serial.print(",");
////  Serial.print("del_Yaw: ");
//  Serial.print(commands.YawAngleChange);
//  Serial.print(",");
////  Serial.print("Aux 1: ");
//  Serial.print(commands.Aux_1);
//  Serial.print(",");
////  Serial.print("Aux 2: ");
//  Serial.print(commands.Aux_2);
//  Serial.print(",");
////  Serial.print("Error: ");
//  Serial.print(commands.Error);
//  Serial.print(",");
////  Serial.print("Armed: ");
//  Serial.println(commands.Armed);
    delay(50);

////  Serial.print("Pitch: ");
//  Serial.print(imu_values.CurrentOrientation.PitchAngle);
//  Serial.print(",");
////  Serial.print("Roll: ");
//  Serial.print(imu_values.CurrentOrientation.RollAngle);
//  Serial.print(",");
////  Serial.print("Yaw: ");
//  Serial.print(imu_values.CurrentOrientation.YawAngle);
//  Serial.print(",");
////  Serial.print("Error: ");
//  Serial.print(imu_values.Error);
//  Serial.print(",");
////  Serial.print("New Data: ");
//  Serial.print(imu_values.NewDataAvailable);
//  Serial.print(",");
////  Serial.print("del_T: ");
//  Serial.println(imu_values.DeltaTimeInSeconds);

  } 
}

//Task2code pinned to core1. Mainly for control loop and outputs.
void Task2code( void * pvParameters ){
    InitializePIDConstants();

    initializeMotors();
  initializeOutputSignals();

    initializeIMU();
  initializeReceiver();

  for(;;){
    syncOutputSignals();

    imu_values = GetIMUvalues();
        commands = GetReceiverCommands();


  if (commands.Error || commands.Throttle < THROTTLE_START_POINT || !commands.Armed || imu_values.Error)
  {
//    Serial.println("Motors not moving");
    stopMotors();
    resetPidVariables();
  }

  else if (imu_values.NewDataAvailable) {
    struct MotorPowers motorPowers = calculateMotorPowers(commands, imu_values);
    spinMotors(motorPowers);
//    Serial.println("Motors moving!!!");
//      struct MotorPowers motorPowers;
//      motorPowers.frontLeftMotorPower = commands.Throttle;
//      motorPowers.frontRightMotorPower = commands.Throttle;
//      motorPowers.rearLeftMotorPower = commands.Throttle;
//      motorPowers.rearRightMotorPower = commands.Throttle;
//
//      spinMotors(motorPowers);
  }

  }
  delay(1);
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
  disableWDT();
//  delay(5000);

//create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */
    delay(500); 
    
}

void loop() {
}
