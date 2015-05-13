#ifndef _PATIENT_H_
#define _PATIENT_H_
#include <ctime>
#include <cstdlib>
#include <string>

extern Random random;

class Patient{
private:
	int severity;
	std::string name;

public:
	int arrivalTime; //when they show up as a sick patient
	int startServiceTime; //when they begin treatment
	int endServiceTime; //when they leave the treatment

	Patient(std::string name, int arrivalTime){
		this->arrivalTime = arrivalTime;
		this->name = name;
		severity = RandomSeverity();
	}

	std::string getName(){
		return name;
	}

	int getSeverity(){
		return severity;
	}

	int RandomSeverity(){
		int prob = random.nextInt(10) + 1;
		if (prob <= 7)
			return random.nextInt(10) + 1;
		else if (prob <= 9)
			return random.nextInt(5) + 11;
		else
			return random.nextInt(5) + 16;
	}

	bool operator<(const Patient &p1) const{
		return severity < p1.severity;
	}
};

#endif