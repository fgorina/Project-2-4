#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double aKp, double aKi, double aKd) {
    Kp = aKp;
    Ki = aKi;
    Kd = aKd;
    i_error = 0.0;
}

void PID::UpdateError(double cte) {
    p_error = cte;
    i_error += cte;
    d_error = cte - old_cte;
    old_cte = cte;
 }

double PID::TotalError() {
    
    return p_error + i_error + d_error;
}


double PID::OutputValue(){
    return -Kp * p_error -Kd * d_error -Ki * i_error;
}
