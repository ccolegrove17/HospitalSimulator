#ifndef _RECORD_H_
#define _RECORD_H_
#include <string>

class Record{
private:
	int severity;
	std::string name;
public:
	Record(int severity, std::string name){
		this->severity = severity;
		this->name = name;
	}

	bool operator<(const Record &other) const {
		if (name < other.name)
			return true;
		//else if (name == other.name)
		//	return severity < other.severity;
		else
			return false;
	}

	int getSeverity() const{
		return severity;
	}

	std::string getName() const{
		return name;
	}
};



#endif