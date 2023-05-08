#include <Arduino.h>
#include "Constants.h"
#include "Functions.h"
#include <TaskManagerIO.h>

void initializeOutputSignals() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void syncOutputSignals() {
  taskManager.runLoop();
}

void quadcopter_initialization_completed() {
  blink_led();
  
}

bool ledIsOn = false;
int ledBlinkTaskId;

void blink_led() {
  ledBlinkTaskId = taskManager.scheduleFixedRate(500, [] {
    if (ledIsOn) {
      digitalWrite(LED_PIN, LOW);
    } else{
      digitalWrite(LED_PIN, HIGH);
    }
    ledIsOn = !ledIsOn;
  });
}

void quadcopter_armed() {
  blink_led();
  
}

void quadcopter_disarmed() {
  taskManager.cancelTask(ledBlinkTaskId);
  
  taskManager.execute([] {
    digitalWrite(LED_PIN, HIGH);
    
  });
}
