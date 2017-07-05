#include<cstring>

class Register {

private:

	LL reg[35];
	LL pc;

public:

	Register() {
		memset(reg, 0, sizeof(reg));
		reg[29] = 8 * 1024 * 1024 - 1;
	}

	LL read(int p) {
		return reg[p];
	}
	
	void write(int p, int v) {
		reg[p] = v;
	}

	LL readPC() {
		return pc;
	}

	void writePC(int v) {
		pc = v;
	}

};
