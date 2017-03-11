#ifndef SRC_FUEL_H_
#define SRC_FUEL_H_
#include "WPILib.h"


class Fuel {
public:
	Fuel(void);
	~Fuel(void);

	void SetLaunchMotor(void);
	void StopLaunchMotor(void);

private:
	Talon *oLaunchMotor; //Object for motor
};


#endif /* SRC_FUEL_H_ */
