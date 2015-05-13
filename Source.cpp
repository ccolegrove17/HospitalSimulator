#include <iostream>
#include "EmergencyRoom.h"
#include "Simulator.h"
using namespace std;

extern Random random;
#include <queue>
int main(){
	Simulator hospital;
	hospital.enterData();
	hospital.runSimulation();
}