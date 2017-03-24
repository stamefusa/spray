#include <Servo.h>

Servo servo;
int num = 0;
String str = "";

int vals[3] = {0, 0, 0};
int val = 0, pre = 0, diff = 0;
int cnt = 0, move_cnt = 0;
int sensor = 0, pre_sensor= 0;

int move = 0;

void setup() {
  servo.attach(7);
  motorInit();
  Serial.begin(9600);
}

void loop() {
  val = analogRead(0);
  diff = val - pre;
  sensor = calcAve();
  //Serial.println(val);
  //Serial.println(diff);
  Serial.println(sensor);

  if (move == 0) {
    if (sensor > 400 && pre_sensor < 400) {
      motorSpray();
      delay(1000);
      motorInit();
      move = 1;
      Serial.println("spray!!");
    }
  } else if (move == 1) {
    move_cnt++;
    
    if (move_cnt > 20) {
      move_cnt = 0;
      move = 0;
      Serial.println("reset!!");
    }
  }

  vals[cnt] = val;
  cnt = (cnt+1)%3;
  pre = val;
  pre_sensor = sensor;
  delay(50);
}

int calcAve()
{
  int tmp = 0;
  for (int i=0; i<3; i++) {
    tmp += vals[i];
  }
  return (int)tmp/3;
}

void motorInit() {
  servo.write(20);
}

void motorSpray() {
  servo.write(90);
}


