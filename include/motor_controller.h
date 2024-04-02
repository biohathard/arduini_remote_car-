#include <AccelMotor.h>

AccelMotor motorL(DRIVER2WIRE, MOT_LA, MOT_LB, HIGH);
AccelMotor motorR(DRIVER2WIRE, MOT_RA, MOT_RB, HIGH);

void initMotors() {
  motorL.setMode(AUTO);
  motorR.setMode(AUTO);

  motorL.setDirection(NORMAL);
  motorR.setDirection(REVERSE);

  motorL.setMinDuty(MIN_DUTY);
  motorR.setMinDuty(MIN_DUTY);

  motorL.setSmoothSpeed(255);
  motorR.setSmoothSpeed(255);
}
