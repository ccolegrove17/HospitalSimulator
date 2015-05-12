#include <iostream>
#include "EmergencyRoom.h"
#include "Simulator.h"
using namespace std;

extern Random random;

int main(){
	Simulator hospital;
	hospital.enterData();
	hospital.runSimulation();
	//hospital.endMenu();
}