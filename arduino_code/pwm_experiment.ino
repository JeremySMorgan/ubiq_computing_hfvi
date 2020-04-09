#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x41);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  125 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  575 // this is the 'maximum' pulse length count (out of 4096)

// our servo # counter
uint8_t servonum = 0;
int motor_vals[2];
//int[] motor_vals = [0, 0];
int motor_i = 0;

void setup() {
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  
  Serial.begin(9600);

  pwm.begin();
//  pwm1.begin();
  
  pwm.setPWMFreq(60);  // Analog servos srun at ~60 Hz updates
//  pwm1.setPWMFreq(60);

  //yield();
}

// the code inside loop() has been updated by Robojax
void loop() {
  for (int j=0; j<2; j++){
    pwm.setPWM(j, 0, motor_vals[j]);
  }
  delay(100);
 

  

    // pwm.setPWM(channel, on, off)
    //channel --> between 0 and 15; specifies which of the ports on the driver is being used
    //on --> between 0 and 4096; specifies when during the PWM pulse it should power on
    //off --> between 0 and 4096; specifies when during the PWM pulse it should power off

    //INTENSITY COMES FROM THE LENGTH OF THE PULSE
//    pwm.setPWM(0, 1024, 3072); //half intensity
//    pwm.setPWM(1, 1024, 3072); 
//    delay(500);
//      pwm.setPWM(0, 0, 4096); //full intensity
//      pwm.setPWM(1, 0, 4096);
//    delay(500);
//    pwm.setPWM(0, 4096, 0); //no intensity
//    pwm.setPWM(1, 4096, 0);
//
//    for (int i = 0; i<3000; i++){
//      pwm.setPWM(0, 0, i);
//      pwm1.setPWM(0, 0, i);
//      delay(15);
//      Serial.println(i);
//      }

}

void receiveEvent(int howMany)
{
  while(1 < Wire.available())
  {
    char c = Wire.read();
    Serial.print(c);
  }
  int x = Wire.read();
  if (x == 0){
    motor_i = 0;
   } else{
    motor_vals[motor_i] = scale_depth_to_interval(x);
    Serial.println(motor_vals[motor_i]);
    motor_i = motor_i + 1; 
   }

//  Serial.println(x);
}

int scale_depth_to_interval(int depth){
  int ret;
  ret = map(depth, 1, 255, 0, 4095);
  return ret;
}
