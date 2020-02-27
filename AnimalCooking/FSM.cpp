#include "FSM.h"
void FSM::PushState(State* s) {
	statesStack.push(s);
}

void FSM::PopState()
{
	if(!statesStack.empty())statesStack.pop();
}
State* FSM::CurrentState() {
	return statesStack.top();
}