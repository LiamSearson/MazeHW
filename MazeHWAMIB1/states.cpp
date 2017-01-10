#include "states.h"

static const StateInfo state_infos[2] = {
  {IDLE::setup, IDLE::enter, IDLE::exit, IDLE::loop, IDLE::event},
  {MAZE::setup, MAZE::enter, MAZE::exit, MAZE::loop, MAZE::event}
};

static const WireValue wire_values[2] = {
  {1, 0, sizeof(uint32_t), (Value<void*>*) &MAZE::xPosition},
  {1, 1, sizeof(uint32_t), (Value<void*>*) &MAZE::yPosition}
};

MasterManager<State, 2, 2> manager(0x540a26b3, state_infos, wire_values, 0);

namespace IDLE {


void event(uint8_t ev) {
  switch (ev) {
  
  default:
    break;
  }
}


}
namespace MAZE {
Value<uint32_t> xPosition;
Value<uint32_t> yPosition;

void event(uint8_t ev) {
  switch (ev) {
  case 0:
    events::reset();
    break;
  default:
    break;
  }
}

namespace tablet {

namespace events {
void finishedAction() { manager.sendTabletEvent(0); }
}
}
}

