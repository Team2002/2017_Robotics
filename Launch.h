#ifndef SRC_LAUNCH_H_
#define SRC_LAUNCH_H_
#include "WPILib.h"


class Launch {
public:
	Launch(void);
	~Launch(void);

	void SetLaunchMotor(void);
	void StopLaunchMotor(void);

private:
	Talon *oLaunchMotor; //Object for motor
};


#endif /* SRC_LAUNCH_H_ */
