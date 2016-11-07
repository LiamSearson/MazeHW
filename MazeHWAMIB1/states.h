#pragma once

#include <Manager.h>

namespace IDLE {

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();



namespace events {

}
}

namespace MAZE {
extern Value<uint32_t> xPosition;
extern Value<uint32_t> yPosition;

__attribute__((weak)) void setup();
__attribute__((weak)) void enter();
__attribute__((weak)) void loop();
void event(uint8_t);
__attribute__((weak)) void exit();

namespace tablet {

namespace events {
void finishedAction();

}
}

namespace events {
void reset();
void moveToXPosition();
void moveToYPosition();
void demo();
}
}



enum State {
  STATE_IDLE,
  STATE_MAZE
};

extern MasterManager<State, 2, 2> manager;
