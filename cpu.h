#include "parser.h"
#include "Register.h"


typedef long long LL;

using namespace std;

class CPU {

	Register* reg;
	Memory* memory;
	vector<instruction>* In;
	vector<Data>* Da;

};