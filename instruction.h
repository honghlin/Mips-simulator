#include<iostream>
#include<cstring>
#include"memory.h"

typedef long long LL;

using std::string;


class instruction {

public:
	
	int type;
	
	int p[3];

	string s;

	instruction() {}

	instruction(int type, string s, int p0 = 0, int p1 = 0, int p2 = 0) : type(type), s(s) {
		p[0] = p0, p[1] = p1, p[2] = p2;
	}
};

class Data {

public:

	int type;

	int p[3];

	string s;

	Data(int type, string s, int p0 = 0, int p1 = 0, int p2 = 0) : type(type), s(s) {
		p[0] = p0, p[1] = p1, p[2] = p2;
	}
};
