#include <Servo.h>

#define VERTICAL_MIN_VALUE 0
#define VERTICAL_MAX_VALUE 180

#define HORIZONTAL_MIN_VALUE 0
#define HORIZONTAL_MAX_VALUE 180

Servo vertical, horizontal;

int verticalDefaultPosition = 100;
int verticalPostion = verticalDefaultPosition;

int horizontalDefaultPosition = 122;
int horizontalPosition = horizontalDefaultPosition;

void initServo() {
  vertical.attach(VERTICAL_SERVO_PIN);
  vertical.write(verticalPostion);

  horizontal.attach(HORIZONTAL_SERVO_PIN);
  horizontal.write(horizontalPosition);
}
