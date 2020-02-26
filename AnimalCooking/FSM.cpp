#include "FSM.h"
void FSM::PushState(State* s) {
	statesStack.push(s);
}

void FSM::PopState()
{
	statesStack.pop();
}
State* FSM::CurrentState() {
	return statesStack.top();
}