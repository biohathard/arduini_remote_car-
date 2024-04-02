#include <PS2X_lib.h>

PS2X ps2x;

void initPS2Controller() {
  ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, false, false);
}
