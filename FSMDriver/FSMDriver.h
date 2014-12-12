#ifndef FSMDRIVER_H
#define FSMDRIVER_H

#include "WrapperBaseDriver.h"
#include "FSM.h"

class FSMDriver : public WrapperBaseDriver, public DrivingFSM<FSMDriver> {
private:
    float accel, brake, steer; //Actuators values
    int gear;

    static float MAX_STRAIGHT_LINE_VAR;
    static float MIN_STRAIGHT_LINE_VAR;
    static float MAX_APPROACHING_CURVE_VAR;
    static float MIN_APPROACHING_CURVE_VAR;

public:
    virtual void onShutdown();
    virtual void onRestart();

    // Initialization of the desired angles for the rangefinders
    virtual void init(float *angles);

    FSMDriver();
    virtual ~FSMDriver(){}

    // Transitions between states (if appropriate).
    void transition(CarState &);

    bool loadParameters(float*, string);

    //Main driving function.
    virtual CarControl wDrive(CarState cs);
};

#endif // FSMDRIVER_H
