/**  @file: Stuck.h
 *
 * https://github.com/bruno147/fsmdriver
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version. 
 */


#ifndef UNB_FSMDRIVER_STATE_STUCK_H
#define UNB_FSMDRIVER_STATE_STUCK_H

#include <cmath>

#include "DrivingState.h"

/**
 * @brief Stuck state.
 * @details Handles the driving when the car is stuck. This usually means it is stopped
 * or has been driving at a very low speed for a while, mesuared by slow_speed_ticks.
 * Entering this state mean that the driver may be hitting a wall or a corner. The 
 * stuck has  a limit time to work without going to another state. it is highly desireble
 * at a actual race that the drive do not enter at this state, since the pilot can complete 
 * the race faster if it do not happend..
 * 
 * @param stuck_speed defines the threshold to monitorate if its in stuck.
 * @param minimum_distance_raced just to avoid to enter in stuck at the beginning of race when the car is stopped.
 * @param maximum_number_of_ticks_stuck maximum number of ticks in which reverse gear is allowed.
 * @param maximum_number_of_ticks_in_slow_speed maximum number of ticks in low speed before stuck is triggered.
 */
class Stuck : public DrivingState {
public:
    /** Constructor.
     *
     * Call setParameters
     *
     * @param ss (stuck speed), mrd (minimum distance raced), mst (maximum number of_ticks stuck),
     * msst (maximum number of ticks in slow speed), see description bellow.
     */
    Stuck(float ss = 5.0, int mrd = 100, int mst = 300, int msst = 50);

    /** Destructor. */
    ~Stuck();

    CarControl drive(CarState &);

    /** Indicates if the controller is stuck.
     *
     * @param cs the driver's perception of the environment.
     * @return true if the controller is stuck, false otherwise. */
    bool isStuck(CarState &cs);
    /** Initialize stuck parameters with ss, mrd, mst and msst
    * @param ss (stuck speed), mrd (minimum distance raced), mst (maximum number of_ticks stuck), 
    * msst (maximum number of ticks in slow speed), see description bellow.
    */
    void setParameters(float ss, int mrd, int mst, int msst);

private:
    /** stuck_speed is the value which bellow it a car may be stuck
    */
    float stuck_speed;
    /** minimum_distance_raced is distance raced that determine if the car is at begining of the race or not
    */
    unsigned int minimum_distance_raced;
    /** maximum_number_of_ticks_stuck determine the total time (by ticks) that stuck state can work without change to another state
    */
    unsigned int maximum_number_of_ticks_stuck;
    /** maximum_number_of_ticks_in_slow_speed is the value of ticks that the pilot can be bellow 
    *the stuck_speed to determine if is stuck or not
    */
    unsigned int maximum_number_of_ticks_in_slow_speed;

    /** Function that check if the stuck state is appropriate to the event at the race 
    * @param cs the driver's perception of the environment.
    * @return true if the car has been at bellow the stuck_speed for long enough and false if not
    */
    bool seemsStuck(CarState &cs);
    /** Based on the distance raced it verify if the driver has just started the race
    * @param cs the driver's perception of the environment.
    * @return true if the pilot is at begining of the race or false if not
    */
    bool justStartedRace(CarState &cs);
    /** Check if the car is driving according the race direction
    * @param cs the driver's perception of the environment.
    * @return true if the car is facing the right race direction or face on the other way
    */
    bool onRightWay(float trackPos, float angle);
    /**  Based on the car's speed and stuck_speed this function determine if the car is stuck or not
    * @param track_pos is the sensor value that measure the distance of the car to the tracks borders, angle 
    * is the sensors value of the angle between the car direction and race direction.
    * @return true if the car is not stuck anymore or false if it is
    */
    bool notStuckAnymore(CarState &cs);
    /** Since the driver can not be stuck for a long time without goint back the track, a time limit is used,
    *this check if the stuck state surpass that limit
    * @param cs the driver's perception of the environment.
    * @return true if the driver pass the time limit or false if not
    */
    bool hasBeenStuckLongEnough();
    /**function to determine the steer
    * @param cs the driver's perception of the environment.
    * @return -1 or 1 at stuck in order to fast turn to right way
    */
    float getSteer(float trackInitialPos, CarState &cs);
    /**Function to determine the track_pos at the begin of stuck state
    * @param cs the driver's perception of the environment.
    * @return the track_initial_pos
    */
    float getInitialPos(CarState &cs);

    unsigned int elapsed_ticks;
    /**  ticks'counter incremented when the car has been bellow the stuck_speed
    */
    unsigned int slow_speed_ticks;
    /** track_pos (sensor) value when the car enter the stuck state  
    */
    float track_initial_pos;

};

#endif // UNB_FSMDRIVER_STATE_STUCK_H
