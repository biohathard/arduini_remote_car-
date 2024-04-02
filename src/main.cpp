#include "config.h"

#include "led_controller.h"
#include "servo_controller.h"
#include "motor_controller.h"
#include "ps2_controller.h"

boolean returnCameraToDefaultPosition = true;
byte joystickDefaultPosition = 128;

void handleLeftJoystickPosition();
void handleRightJoystickPosition();
void handlePadButtonEvents();
void handleButtonEvents();

void setup() {
  Serial.begin(115200);

  initLed();
  initServo();
  initMotors();
  initPS2Controller();

  Serial.println(F("Ready!"));
}

void loop() {
  bool readResult = ps2x.read_gamepad(false, 0);

  if (readResult) {
    handleLeftJoystickPosition();
    handleRightJoystickPosition();
    handlePadButtonEvents();
    handleButtonEvents();
  } else {
    motorL.setSpeed(0);
    motorR.setSpeed(0);
  }

  delay(5);
}

void handleLeftJoystickPosition() {
  int lX = map(ps2x.Analog(PSS_LX), 255, 0, -255, 255);
  int lY = map(ps2x.Analog(PSS_LY), 255, 0, -255, 255);

  int dutyL = lY - lX;
  int dutyR = lY + lX;

  dutyL = constrain(dutyL, -255, 255);
  dutyR = constrain(dutyR, -255, 255);

  motorL.smoothTick(dutyL);
  motorR.smoothTick(dutyR);
}

void handleRightJoystickPosition() {
  byte rX = ps2x.Analog(PSS_RX);
  byte rY = ps2x.Analog(PSS_RY);

  if (rX == joystickDefaultPosition) {
    if (returnCameraToDefaultPosition) {
      horizontal.write(horizontalDefaultPosition);
    }
  } else {
    horizontalPosition = map(rX, 255, 0, HORIZONTAL_MIN_VALUE, HORIZONTAL_MAX_VALUE);
    horizontal.write(horizontalPosition);
  }

  if (rY == joystickDefaultPosition) {
    if (returnCameraToDefaultPosition) {
      vertical.write(verticalDefaultPosition);
    }
  } else {
    verticalPostion = map(rY, 0, 255, VERTICAL_MIN_VALUE, VERTICAL_MAX_VALUE);
    vertical.write(verticalPostion);
  }
}

void handlePadButtonEvents() {
  boolean isPadUpButtonPressed = ps2x.Button(PSB_PAD_UP);
  boolean isPadDownButtonPressed = ps2x.Button(PSB_PAD_DOWN);
  boolean isPadLeftButtonPressed = ps2x.Button(PSB_PAD_LEFT);
  boolean isPadRightButtonPressed = ps2x.Button(PSB_PAD_RIGHT);

  if (isPadUpButtonPressed) {
    verticalPostion = constrain(verticalPostion - 1, VERTICAL_MIN_VALUE, VERTICAL_MAX_VALUE);
    vertical.write(verticalPostion);
  }

  if (isPadDownButtonPressed) {
    verticalPostion = constrain(verticalPostion + 1, VERTICAL_MIN_VALUE, VERTICAL_MAX_VALUE);
    vertical.write(verticalPostion);
  }

  if (isPadLeftButtonPressed) {
    horizontalPosition = constrain(horizontalPosition + 1, HORIZONTAL_MIN_VALUE, HORIZONTAL_MAX_VALUE);
    horizontal.write(horizontalPosition);
  }

  if (isPadRightButtonPressed) {
    horizontalPosition = constrain(horizontalPosition - 1, HORIZONTAL_MIN_VALUE, HORIZONTAL_MAX_VALUE);
    horizontal.write(horizontalPosition);
  }
}

void handleButtonEvents() {
  boolean isSelectButtonReleased = ps2x.ButtonReleased(PSB_SELECT);
  boolean isTriangleButtonReleased = ps2x.ButtonReleased(PSB_TRIANGLE);

  if (isSelectButtonReleased) {
    returnCameraToDefaultPosition = !returnCameraToDefaultPosition;
  }

  if (isTriangleButtonReleased) {
    Serial.println(F("Toggle LED Power"));

    toggleLedPower();
  }
}
