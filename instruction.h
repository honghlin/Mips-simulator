#include<iostream>
#include<cstring>
#include<unordered_map>
#include"memory.h"

typedef long long LL;

using std::string;
using std::unordered_map;

//const LL pow32 = 1 << 32;

extern unordered_map<string, int> Reg;

extern Memory memory;

extern LL R[35];

class instruction {

public:
	
	int type;
	
	int p[3];

	string s;

	instruction() {}

	instruction(int type, string s, int p0 = 0, int p1 = 0, int p2 = 0) : type(type), s(s) {
		p[0] = p0, p[1] = p1, p[2] = p2;
	}

	//virtual int deal() = 0;

	int toInt(string s) {
		int len = strlen(s.c_str());
		int ans = 0;
		int i = s[0] == '-' ? 1 : 0;
		for (i; i < len; ++i) ans = ans * 10 + (s[i] - '0');
		return s[0] == '-' ? -ans : ans;
	}

	bool isInt(string s) {
		int len = strlen(s.c_str());
		int i = s[0] == '-' ? 1 : 0;
		for (i; i < len; ++i)
			if (s[i] < '0' || s[i] > '9') return false;
		return true;
	}

	unsigned int tran(int n) {
		if (n >= 0) return n;
		unsigned int t = n;
		return t;
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
