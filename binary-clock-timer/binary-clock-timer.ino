#include "LowPower.h"

const int pow0 = 2;
const int pow1 = 3;
const int pow2 = 4;
const int pow3 = 5;
const int pow4 = 6;
const int pow5 = 7;

const int motorT1 = 12;
const int motorT2 = 13;

const long int MILIS_IN_A_MINUTE = 60000;
const int NO_OF_RINGS = 30;


void setOffAlarm();
long int getTimerTime();

long int TIMER_TIME;
bool alarm_has_been_set_off = false;

// to start timer, press red button.



void setup() {
  Serial.begin(9600);

  pinMode(motorT1, OUTPUT);
  pinMode(motorT2, OUTPUT);
  Serial.println("peppa pig");
  Serial.println(getTimerTime());
  TIMER_TIME = getTimerTime()*MILIS_IN_A_MINUTE;
  Serial.println(TIMER_TIME);

}


void loop() {
  // getAlarmTime();
  // LowPower.deepSleep(milliseconds);


  if (!alarm_has_been_set_off){

    unsigned long int curr_millis = millis();
    // Serial.println("timer time");
    // Serial.println(TIMER_TIME);
    // Serial.println(curr_millis);
    if (curr_millis >= TIMER_TIME){
      delay(500);
      setOffAlarm();
      alarm_has_been_set_off = true;
      
    }

  }
  else{
      Serial.println("sleeeping");
      LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    
  }

  



}

void setOffAlarm(){
  Serial.println("Setting OFF");

  for (int i = 0; i<=NO_OF_RINGS; i++){
    digitalWrite(motorT1, HIGH);
    digitalWrite(motorT2, LOW);
    delay(400);
    digitalWrite(motorT1, LOW);
    digitalWrite(motorT2, HIGH);
    delay(400);

  }

  digitalWrite(motorT1, LOW);
  digitalWrite(motorT2, LOW);



}

long int getTimerTime(){

  int states[] = {0,0,0,0,0,0};

  for(int i=2; i<=7; i++){
    states[i-2] = digitalRead(i);
  }

  int minutes = states[0]*1 + states[1]*2 + states[2]*4 + states[3]*8 + states[4]*16 + states[5]*32;

  return minutes;

}
