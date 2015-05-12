#ifndef _DOCTOR_H_
#define _DOCTOR_H_
#include "Staff.h"


class Doctor : public Staff{
private:

public:
	Doctor() : Staff(){
		maxSeverity = 20;
		maxTime = 20;
	}

	Doctor(int time){
		maxSeverity = 20;
		maxTime = 20;
		serviceTime = time;
	}

	void treatPatient(int clock){
		scaledServiceTime = random.nextInt(maxTime);
		serviceTime = clock + scaledServiceTime;
	}
};

#endif