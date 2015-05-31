//Goal: Return motor to initial position after allowing it to be turned by hand

#include <AccelStepper.h>
#define DIR_PIN  5
#define STEP_PIN 6
#define SLEEP_PIN 12
#define STEPS 200
#define MICROSTEPS 8
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

#include <Encoder.h>
#define ENCODER1 2
#define ENCODER2 3
#define ENCODER_STEPS 1200
Encoder encoder(ENCODER1, ENCODER2);

void setup() 
{
  Serial.begin(9600);
  stepper.setMaxSpeed(500);
  stepper.setAcceleration(500);
  stepper.setEnablePin(SLEEP_PIN);
  stepper.disableOutputs();
}

void loop()
{
  float encoder_position;  
  float microsteps;
  encoder_position = encoder.read();
  microsteps = encoder_position * ((((float)STEPS * (float)MICROSTEPS) / (float)ENCODER_STEPS));
  Serial.print("encoder position = ");
  Serial.println(encoder_position);
  Serial.print("microsteps = ");
  Serial.println(microsteps);
  if (encoder_position > 15.0 || encoder_position < -15.0)
  {
    stepper.enableOutputs();
    stepper.runToNewPosition(microsteps);
    stepper.setCurrentPosition(0);
    stepper.disableOutputs();
  }
  delay(1000);
}
