#ifndef FSMDRIVER_H
#define FSMDRIVER_H

#include "state.h"

//-----------------------------------------------------------------------------------------------------------------------
//Finite State Machine Driver

class FsmDriver : public WrapperBaseDriver {
private:
    State* _state;
public:
    FsmDriver();
    void ChangeState(State* _newState);
    State* transition(CarState&);
    string drive(string);
};

//-----------------------------------------------------------------------------------------------------------------------
#endif // FSMDRIVER_H