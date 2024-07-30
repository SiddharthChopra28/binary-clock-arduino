
const int pow0 = 2;
const int pow1 = 3;
const int pow2 = 4;
const int pow3 = 5;
const int pow4 = 6;
const int pow5 = 7;

const int motorT1 = 12;
const int motorT2 = 13;

const int MILIS_IN_AN_HOUR = 3600000;
const int NO_OF_RINGS = 20;

//make sure to start the arduino at exactly X AM/PM, and the alarm time on the clock should be X AM/PM when started (in 24 hr format)
int curr_time = 0; // this is the start hour
unsigned long int last_hour_millis = 0;


void setOffAlarm();
int getAlarmTime();

void setup() {
  Serial.begin(9600);

  pinMode(motorT1, OUTPUT);
  pinMode(motorT2, OUTPUT);



}


void loop() {

  unsigned long int curr_millis = millis();

  int alarmTime = getAlarmTime();
  Serial.println(alarmTime);

  Serial.println(curr_millis - last_hour_millis);

  if ((curr_millis - last_hour_millis) >= MILIS_IN_AN_HOUR){
    Serial.println("Bonjour");
    delay(2000);
    if (curr_time == 23){

      last_hour_millis = curr_millis;
      curr_time = 0;
    }

    else{
      last_hour_millis = curr_millis;
      curr_time++;
    }

    if (curr_time == alarmTime){
      setOffAlarm();
    }
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

int getAlarmTime(){

  int states[] = {0,0,0,0,0,0};

  for(int i=2; i<=7; i++){
    states[i-3] = digitalRead(i);
  }

  int hour = states[0]*1 + states[1]*2 + states[2]*4 + states[3]*8 + states[4]*16 + states[5]*32;

  return hour;

}
