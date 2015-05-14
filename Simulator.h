#ifndef _SIMULATOR_H_
#define _SIMULATOR_H_
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "EmergencyRoom.h"
#include "Random.h"

Random random;


class Simulator{
private:
	int doctorNum, nurseNum, arrivalRate, times, total_time, lowPatientsSize, highPatientsSize;
	char choice;
	EmergencyRoom *emergencyRoom;

public:
	std::vector<std::string> people;

	Simulator(){
		fillVector();
	}

	void fillVector(){
		std::ifstream myfile("residents_273ville.txt");
		if (!myfile){
			std::cout << "Fail" << std::endl;
		}
		else{
			std::string str;
			while (std::getline(myfile, str)){
				people.push_back(str);
			}
			myfile.close();
		}
	}

	void runSimulation(){
		for (int i = 0; i < times; i++){
			if (choice == 'y')
				emergencyRoom = new EmergencyRoom(people, 1);
			else
				emergencyRoom = new EmergencyRoom(people, 0);
			emergencyRoom->addDoctor(doctorNum);
			emergencyRoom->addNurse(nurseNum);
			emergencyRoom->setArrivalRate(static_cast<double>(arrivalRate) / 60);
			for (int clock = 0; clock < total_time; clock++){
				(*emergencyRoom).update(clock);
			}
			lowPatientsSize = emergencyRoom->lowPatients.size();
			highPatientsSize = emergencyRoom->highPatients.size();

			//while (!emergencyRoom->lowPatients.empty()){
			//	emergencyRoom->visitTime += total_time - emergencyRoom->lowPatients.top().arrivalTime;
			//	emergencyRoom->lowPatients.pop();
			//}
			//while (!emergencyRoom->highPatients.empty()){
			//	emergencyRoom->visitTime += total_time - emergencyRoom->highPatients.top().arrivalTime;
			//	emergencyRoom->highPatients.pop();
			//}
			endMenu();
		}
	}


	void enterData(){
		std::cout << "How many doctors work at this emergency room? ";
		std::cin >> doctorNum;
		std::cout << "How many nurses work at this emergency room? ";
		std::cin >> nurseNum;
		std::cout << "What is the arrival rate of patients per hour? ";
		std::cin >> arrivalRate;
		std::cout << "For how many hours will this simulation run? ";
		std::cin >> total_time;
		total_time = total_time * 60;
		std::cout << "Would you like to display text at each clock tick (y/n)? ";
		std::cin >> choice;
		std::cout << "How many times would you like to run the simulation with these values? ";
		std::cin >> times;
	}


	void showStats(){
		std::cout << "\tFinal stats of Emergency Room: \n";
		std::cout << "Total time of simulation: " << total_time << std::endl;
		std::cout << "Number of patients served by nurses: " << emergencyRoom->nurseServed << std::endl;
		std::cout << "Number of patients served by doctor: " << emergencyRoom->doctorServed << std::endl;
		std::cout << "Number of lowly sick patients waiting: " << lowPatientsSize << std::endl;
		std::cout << "Number of severely sick patients waiting: " << highPatientsSize << std::endl;
		std::cout << "Average visit time: " << static_cast<double>(emergencyRoom->visitTime) / (emergencyRoom->nurseServed + emergencyRoom->doctorServed) << std::endl;
	}

	void displaySet(){
		for (std::multiset<Record>::iterator it = emergencyRoom->records.begin(); it != emergencyRoom->records.end(); it++){
			std::cout << "Name: " << it->getName() << ", Severity: " << it->getSeverity() << std::endl;
		}
	}

	void patientSearch(){
		int number;
		std::string name;
		std::cout << "Patient name: ";
		std::cin >> name;
		number = emergencyRoom->records.count(Record(0, name));
		if (number == 0){
			std::cout << "Patient not on record." << std::endl;
		}
		else{
			for (std::multiset<Record>::iterator it = emergencyRoom->records.begin(); it != emergencyRoom->records.end(); it++){
				if (it->getName() == name)
					std::cout << "Name: " << name << ", Severity: " << it->getSeverity() << std::endl;
			}
		}
	}

	void endMenu(){
		int choice = 0;
		while (choice != 4){
			std::cout << "\nMenu:\n";
			std::cout << "1. Show Stats\n";
			std::cout << "2. Display Patients\n";
			std::cout << "3. Search for a Patient\n";
			std::cout << "4. Exit\n";
			std::cout << "Choice: ";
			std::cin >> choice;
			std::cout << std::endl;
			switch (choice){
			case 1:
				showStats();
				break;
			case 2:
				displaySet();
				break;
			case 3:
				patientSearch();
				break;
			case 4:
				break;
			default:
				std::cout << "Invalid choice.\n";
				break;
			}
		}


	}
};




#endif