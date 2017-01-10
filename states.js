
var IDLE = {
  id: 0,
  master: {
    values: {
      
    },
    events: {
      
    }
  },
  tablet: {
    values: {
      
    },
    events: {
      
    }
  }
};
var STATE_IDLE = 0;
var MAZE = {
  id: 1,
  master: {
    values: {
      xPosition: new HardwareValue(1, 0, Manager.TYPE_UINT32),
      yPosition: new HardwareValue(1, 1, Manager.TYPE_UINT32)
    },
    events: {
      reset: function reset() { manager.sendEvent(0, 1); }
    }
  },
  tablet: {
    values: {
      
    },
    events: {
      finishedAction: new LocalEvent(1, 0)
    }
  }
};
var STATE_MAZE = 1;

var STATES = {
  IDLE: IDLE,
  MAZE: MAZE
};
var manager = new Manager([IDLE, MAZE]);
