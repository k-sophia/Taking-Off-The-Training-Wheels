#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;


Bicycle::Bicycle() {
    curr_speed_  = 0.0;       // initialize all private members besides b_type, 
    curr_direction_ = 0.0;    // curr_pedal_intensity_, and seat_height_ to 0;
    distance_traveled_ = 0.0;
    
    seat_height_ = 10;              // seat_height_ <- 10
    b_type_ = bike_details::bike_type(rand() % 4);           // b_type_ <- a random bike type
    curr_pedal_intensity_= bike_details::pedalling_intensity(0);    // curr_pedal_intensity_ <- bike_details::NONE
}


Bicycle::Bicycle(int kind_of_bike) {    // initialize all members besides b_type_
    curr_speed_  = 0.0;                 //to the values that they take on in the default contructor
    curr_direction_ = 0.0;
    distance_traveled_ = 0.0;
    seat_height_ = 10;
    curr_pedal_intensity_= bike_details::pedalling_intensity(0);

    b_type_ = bike_details::bike_type(kind_of_bike);   // b_type_ <- kind_of_bike
}

string Bicycle::getDirection() {
     /**
        return the string that corresponds to the curr_direction_ 
        that the caller faces relative to a cartesian plane; 
        assume that if the caller is at position (0, 0), the 
        degree measure of (1, 0) is 0 degrees, and the degree 
        measure of (-1, 0) is 180 degrees 

        "North" == 90
        0 < "Northeast" < 90 
        "East" == 0
        "Southeast" > 270
        "South" == 270
        180 < "Southwest" < 270
        "West" == 180
        90 < "Northwest" < 180
    */ 

    if (curr_direction_ == 90) {
        return "North";
    }
    else if (0 < curr_direction_ && curr_direction_ < 90) {
        return "Northeast";
    }
    else if (curr_direction_ == 0 || curr_direction_ == 360) {
        return "East";
    }
    else if (curr_direction_ > 270) {
        return "Southeast";
    }
    else if (curr_direction_ == 270) {
        return "South";
    }
    else if (180 < curr_direction_ && curr_direction_ < 270) {
        return "Southwest";
    }
    else if (curr_direction_ == 180) {
        return "West";
    }
    else if (90 < curr_direction_ && curr_direction_ < 180) {
        return "Northwest";
    }

    return 0;
}

string Bicycle::getBikeType() { // string version of b_type_
    switch(b_type_) {
        case 0 :
            return "BMX";
            break;
        case 1 :
            return "MOUNTAIN";
            break;
        case 2 :
            return "TOURING";
            break;
        case 3 :
            return "ROAD";
            break;
    }
}
int Bicycle::getSeatHeight() { // seat_height_
    return seat_height_;
}

float Bicycle::getSpeed(){ // curr_speed_
    return curr_speed_;
}

float Bicycle::getDistanceTraveled() { // distance_traveled_
    return distance_traveled_;
}

string Bicycle::getIntensity() { // curr_pedal_intensity_
    switch(curr_pedal_intensity_) {
        case 0 :
            return "None";
            break;
        case 44 :
            return "Low";
            break;
        case 88 :
            return "Medium";
            break;
        case 132 :
            return "High";
            break;
    }
}

void Bicycle::changeSeatHeight(int inches) { // seat_height_
    seat_height_ = inches;

    if (seat_height_ < 0) {
        seat_height_ = 0;
    }
    else if (seat_height_ > 36) {
        seat_height_ = 36;
    }
} 

void Bicycle::turn(float degrees) {
    /** 
    updates direction_
    @param degrees: -360 <= degrees <= 360, and if the 
    user enters a number outside of these bounds 
    adjust @param degrees to be within this range
    */

    float adjust = curr_direction_ + degrees;
    if (adjust < 0) {
        adjust += 360;
    }
    else if (adjust > 360) {
        adjust -= 360;
    }

    curr_direction_ = adjust;
}

void Bicycle::updateSpeed() {
    /**
    alters curr_speed_ depending on curr_speed_, 
    curr_pedal_intensity_, and b_type_
        
    USE THE FOLLOWING FORMULA: 
    [ (pedal intensity) / 8 ] * (bike type) 
    + [ (pedal intensity) / 8 + (bike type) ]
    */

    float first_part = ((curr_pedal_intensity_) / 8) * (b_type_);
    float second_part = ((curr_pedal_intensity_) / 8) + (b_type_);
    float new_speed = first_part + second_part;

    if (b_type_ == 1 && curr_pedal_intensity_ == 0) {
        new_speed -= 1;
    }

    curr_speed_ = new_speed;
}

void Bicycle::pedal() {
    /**
    if the current intensity is not HIGH,
    increase it by one level and call updateSpeed()
    */

    if (curr_pedal_intensity_ != 132) {
        curr_pedal_intensity_ = bike_details::pedalling_intensity(curr_pedal_intensity_ + 44);
        updateSpeed();
    }
}

void Bicycle::brake() {
    /** 
    if the current intensity is not NONE,
    decrease it by one level and call updateSpeed()
    */

    if (curr_pedal_intensity_ != 0) {
        curr_pedal_intensity_ = bike_details::pedalling_intensity(curr_pedal_intensity_ - 44);
        updateSpeed();
    }
}

float Bicycle::ride(float duration) {
    /**
    given curr_speed_, curr_pedal_intensity_, b_type_, 
    and @param float duration, calculate the 
    distance traveled during the specified time;
    increment distance_traveled_ by this amount
    @param float duration: time traveled in minutes
    @return: updated distance_traveled_
    */

    float distance = duration * curr_speed_;
    distance_traveled_ += distance;
}
