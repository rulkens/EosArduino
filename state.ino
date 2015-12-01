/* EVENTS */
#define EVENT_STATE_CHANGE "state"

int state_old;

void setState(int s){
  event(EVENT_STATE_CHANGE, s, state_old);
  state_old = state;
  state = s;
  stateHasChanged = state_old != state;
}

int getState() {
  return state;
}

void loopState(){
  if(!stateHasChanged){
    breatheTimeout++;
  }
  // reset the old state
  state_old = state;
  stateHasChanged = false;
  
}
