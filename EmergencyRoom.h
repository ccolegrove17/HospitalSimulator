#ifndef _EMERGENCYROOM_H_
#define _EMERGENCYROOM_H_
#include "Doctor.h"
#include "Nurse.h"
#include "Patient.h"
#include "Random.h"
#include <list>
#include <queue>
#include <set>
#include <iterator>
#include "Record.h"

extern Random random;

class EmergencyRoom{
private:
	int nurseServed, doctorServed, visitTime, showText;
	std::priority_queue<Patient> highPatients;
	std::priority_queue<Patient> lowPatients;
	std::queue<Nurse*> nurses;
	std::queue<Doctor*> doctors;
	std::vector<std::string> people;
	std::list<Nurse*> nurseTreatment;
	std::list<Doctor*> doctorTreatment;
	double arrivalRate;
	std::multiset<Record> records;

public:
	EmergencyRoom(std::vector<std::string> people, int text){
		showText = text;
		this->people = people;
		nurseServed = 0;
		doctorServed = 0;
		visitTime = 0;
	}

	void setArrivalRate(double arrivalRate){
		this->arrivalRate = arrivalRate;
	}

	void addDoctor(int number){
		for (int i = 0; i < number; i++){
			doctors.push(new Doctor());
		}
	}

	void addNurse(int number){
		for (int i = 0; i < number; i++){
			nurses.push(new Nurse());
		}
	}

	void update(int clock){
		if (clock >= 10000)
			std::cout << "";
		if (showText == 1)
			std::cout << "\tClock tick: " << clock << std::endl;
		if (random.nextDouble() < arrivalRate)
		{
			Patient p1 = Patient(people[random.nextInt(1999)], clock);
			if (p1.getSeverity() > 10){
				if (showText == 1)
					std::cout << "A severely sick patient has arrived.\n";
				records.insert(Record(p1.getSeverity(), p1.getName()));
				highPatients.push(p1);
			}
			else{
				if (showText == 1)
					std::cout << "A lowly sick patient has arrived.\n";
				records.insert(Record(p1.getSeverity(), p1.getName()));
				lowPatients.push(p1);
			}
		}
		else
			if (showText == 1)
				std::cout << "No new patients arrived.\n";
		if (!highPatients.empty()){
			//if (doctors.empty()){
			//	if (showText == 1)
			//		std::cout << "There are no doctors to treat the " << highPatients.size() << " severely sick patients." << std::endl;
			//}
			while (!doctors.empty()){
				if (highPatients.empty())
					break;
				doctors.front()->treatPatient(clock);
				if (showText == 1)
					std::cout << "A doctor has left to treat a severely sick patient." << std::endl;
				visitTime += (clock - highPatients.top().arrivalTime);
				highPatients.pop();
				doctorTreatment.push_front(doctors.front());
				visitTime += doctorTreatment.front()->scaledServiceTime;
				doctors.pop();
				doctorServed++;
			}
		}
		if (!lowPatients.empty()){
			//if (doctors.empty() && nurses.empty())
			//	if (showText == 1)
			//		std::cout << "There is no staff to treat the " << lowPatients.size() << " lowly sick patients." << std::endl;
			while (!nurses.empty()){
				if (lowPatients.empty())
					break;
				nurses.front()->treatPatient(clock);
				if (showText == 1)
					std::cout << "A nurse has left to treat a lowly sick patient." << std::endl;
				visitTime += (clock - lowPatients.top().arrivalTime);
				lowPatients.pop();
				nurseTreatment.push_front(nurses.front());
				visitTime += nurseTreatment.front()->scaledServiceTime;
				nurses.pop();
				nurseServed++;
			}
			while (!doctors.empty()){
				if (lowPatients.empty())
					break;
				doctors.front()->treatPatient(clock);
				visitTime += (clock - lowPatients.top().arrivalTime);
				lowPatients.pop();
				if (showText == 1)
					std::cout << "A doctor has left to treat a lowly sick patient." << std::endl;
				doctorTreatment.push_front(doctors.front());
				visitTime += doctorTreatment.front()->scaledServiceTime;
				doctors.pop();
				doctorServed++;
			}
		}

		std::list<Nurse*>::iterator itN = nurseTreatment.begin();
		while (itN != nurseTreatment.end()){
			if (clock == (*itN)->serviceTime){
				nurses.push(*itN);
				//visitTime += (*itN)->scaledServiceTime;
				if (showText == 1)
					std::cout << "The nurse has finished treatment." << std::endl;
				nurseTreatment.erase(itN);
				itN = nurseTreatment.begin();//very inefficient workaround. TRY TO FIX
				continue;
			}
				itN++;
		}

		std::list<Doctor*>::iterator itD = doctorTreatment.begin();
		while (itD != doctorTreatment.end()){
			if (clock == (*itD)->serviceTime){
				doctors.push(*itD);
				//visitTime += (*itD)->scaledServiceTime;
				if (showText == 1)
					std::cout << "The doctor has finished treatment." << std::endl;
				doctorTreatment.erase(itD);
				itD = doctorTreatment.begin();//very inefficient workaround. TRY TO FIX
				continue;
			}
				itD++;
		}
		if (showText == 1){
			if (lowPatients.size() != 0)
				std::cout << "Number of lowly sick patients waiting: " << lowPatients.size() << std::endl;
			if (highPatients.size() != 0)
				std::cout << "Number of severely sick patients waiting: " << highPatients.size() << std::endl;
			if (nurseTreatment.size() != 0)
				std::cout << "Number of nurses treating patients: " << nurseTreatment.size() << std::endl;
			if (doctorTreatment.size() != 0)
				std::cout << "Number of doctors treating patients: " << doctorTreatment.size() << std::endl;
			std::cout << "\n\n";
		}

	}


	friend class Simulator;
};

#endif