#ifndef _STAFF_H_
#define _STAFF_H_
#include <queue>
#include "Random.h"

extern Random random;

class Staff{
public:
	int maxSeverity, maxTime, serviceTime, scaledServiceTime;
	virtual void treatPatient(int clock) = 0;
};

#endif