#ifndef _NURSE_H_
#define _NURSE_H_
#include "Staff.h"

class Nurse : public Staff{
private:

public:
	Nurse() : Staff(){
		maxSeverity = 10;
		maxTime = 10;
	}

	Nurse(int time){
		serviceTime = time;
		maxSeverity = 10;
		maxTime = 10;
	}

	void treatPatient(int clock){
		scaledServiceTime = random.nextInt(maxTime);
		serviceTime = clock + scaledServiceTime;
	}


};

#endif