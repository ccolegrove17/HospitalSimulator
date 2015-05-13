#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <cstdlib>
#include <ctime>

class Random{
public:
	Random(){
		srand((unsigned int)std::time(NULL));
	}

	Random(int seed){
		srand(seed);
	}

	int nextInt(int n){
		return rand() % n;
		//return int((nextDouble() * (n)));//returns from zero to n
	}

	double nextDouble(){
		return double(rand()) / RAND_MAX; //returns from zero to one
	}
};

#endif