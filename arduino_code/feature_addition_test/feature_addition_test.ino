#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(0x41);

Adafruit_PWMServoDriver myPWMs[] = {pwm, pwm1, pwm2, pwm3};

// width and height of motor array being controlled
const int MOTOR_ARRAY_WIDTH = 7;
const int MOTOR_ARRAY_HEIGHT = 7;

int matrix[MOTOR_ARRAY_HEIGHT][MOTOR_ARRAY_WIDTH];

int motor_vals[MOTOR_ARRAY_WIDTH * MOTOR_ARRAY_HEIGHT];
int motor_i = 0;
void setup()
{
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output

  pwm.begin();
  pwm.setPWMFreq(60);
}

void loop()
{
  int pwm_index = 0;
  int motor = 0;
  Adafruit_PWMServoDriver curr_pwm;
  for (int i=0; i < MOTOR_ARRAY_HEIGHT; i++){
    for (int j=0; j < MOTOR_ARRAY_WIDTH; j++){
      curr_pwm = myPWMs[pwm_index];
      curr_pwm.setPWM(motor, 0, matrix[i][j]);
      motor++;
      if (motor >= 16){
        pwm_index++;
        motor = 0;
      }
    }
  }
  delay(1000);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
  if (x == 0){
    motor_i = 0;
  } else{
    int row = motor_i / MOTOR_ARRAY_WIDTH;
    int col = motor_i % MOTOR_ARRAY_WIDTH;
    if (row >= MOTOR_ARRAY_HEIGHT || col >= MOTOR_ARRAY_WIDTH)
    {
      motor_i = 0;
    }
    else{
      matrix[row][col] = scale_depth_to_interval(x);
      motor_i += 1;
    }
  }
}

int scale_depth_to_interval(int depth){
  int ret;
  ret = map(depth, 1, 255, 0, 4095);
  return ret;
}
