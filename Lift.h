#ifndef SRC_LIFT_H_
#define SRC_LIFT_H_
#include "WPILib.h"


class Lift {
public:
	Lift(void);
	~Lift(void);

	void StartLiftMotor(void);
	void SlowLiftMotor(void);
	void StopLiftMotor(void);

private:
	Talon *oClimbMotor; //Object for motor
};


#endif /* SRC_LIFT_H_ */
