// mips.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "parser.h"
#include "register.h"
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<unordered_map>
#include<utility>
#include<fstream>
#include<vector>

const LL pow32 = 4294967295;

parser A;

using namespace std;

vector<instruction> In;
vector<Data> Da;

vector<instruction>* pIn = &In;
vector<Data>* pDa = &Da;

Memory memory;
Memory *pm = &memory;

Register r;
Register* pr = &r;

class CPU;

class stage {

public:

	instruction ins;
	string lab;
	LL result;
	int rd, rs, sr, im, vRd, vRs, vSr, vPc, dis, flag, a1, va1;
	int length;
	int nex;
	int pos;
	int Hi, Lo, op;

	CPU* cpu;

public:

	int insPos;

	bool isBlocked, isIdle;

	virtual void execute() = 0;
	
	stage(CPU* cpu) : cpu(cpu), isBlocked(false), isIdle(true) {}

};

class IF : public stage {

public:

	instruction ins;

	IF(CPU* cpu) : stage(cpu) {}

	void execute();
	
};

class IDDP : public stage {

public:

	IDDP(CPU* cpu) : stage(cpu) {}

	void execute();
	
};

class EX : public stage {

public:



public:

	EX(CPU* cpu) : stage(cpu) {}

	void execute();
	
};

class MA : public stage {

public:

public:

	MA(CPU* cpu) : stage(cpu) {}

	void execute();
};

class WB : public stage {

public:
	
	WB(CPU* cpu) : stage(cpu) {}

	void execute();
};

class CPU {

	friend class IF;
	friend class IDDP;
	friend class EX;
	friend class MA;
	friend class WB;
	
private:

	int usedReg[4];
	bool usedPC[4];
	bool usedHi[4];
	bool usedLo[4];
	stage* pipeline[5];
	IF iF;
	IDDP iddp;
	EX ex;
	MA ma;
	WB wb;

public:

	Register* reg;
	Memory* memory;
	vector<instruction>* Ins;
	vector<Data>* data;


	CPU(Register* reg, Memory* memory, vector<instruction>* Ins, vector<Data>* data) : reg(reg), memory(memory), Ins(Ins), data(data), iF(this), iddp(this), ex(this), ma(this), wb(this) {
		pipeline[0] = &iF;
		pipeline[1] = &iddp;
		pipeline[2] = &ex;
		pipeline[3] = &ma;
		pipeline[4] = &wb;
		for (int i = 0; i < 4; ++i) usedReg[i] = -2;
		for (int i = 0; i < 4; ++i) usedPC[i] = 0;
		for (int i = 0; i < 4; ++i) usedHi[i] = 0;
		for (int i = 0; i < 4; ++i) usedLo[i] = 0;
	}
	
	void setRegUsed(int n) {
		if (n != 32 && n != 33) usedReg[0] = n;
		else if (n == 32) usedLo[0] = 1;
		else if (n == 33) usedHi[0] = 1;
	}

	bool isRegUsed(int n) {
		if(n != 32 && n != 33) {
			for (int i = 0; i < 4; ++i)
				if (usedReg[i] == n) return true;
		}
		else if (n == 32) {
			for (int i = 0; i < 4; ++i)
				if (usedLo[i]) return true;
		}
		else if (n == 33) {
			for (int i = 0; i < 4; ++i)
				if (usedHi[i]) return true;
		}
		return false;
	}

	LL getReg(int n) {
		return reg->read(n);
	}

	void setPcUsed() {
		usedPC[0] = 1;
	}
	
	bool isPcUsed() {
		for (int i = 0; i < 4; ++i)
			if (usedPC[i]) return true;
		return false;
	}

	LL getPc() {
		return reg->readPC();
	}

	void execute() {
		for (int i = 3; i > 0; --i) usedReg[i] = usedReg[i - 1];
		for (int i = 3; i > 0; --i) usedPC[i] = usedPC[i - 1];
		for (int i = 3; i > 0; --i) usedLo[i] = usedLo[i - 1];
		for (int i = 3; i > 0; --i) usedHi[i] = usedHi[i - 1];
		usedReg[0] = -2;
		usedLo[0] = 0;
		usedPC[0] = 0;
		usedHi[0] = 0;
		for (int i = 4; i > -1; --i) pipeline[i]->execute();
		//for (int i = 0; i <= 4; ++i) pipeline[i]->execute();
	}

	void debug(){
		cout << "\n\n\n";
		for (int i = 0; i <= 33; ++i) cout << i << "       " << reg->read(i) << "\n";
		cout << "pc       " << reg->readPC() << "\n";
		cout << "\n\n\n";
	}
};



void IF::execute() {
	if (cpu->iddp.isBlocked || cpu->isPcUsed()) {
		isBlocked = true;
		return;
	}
	insPos = cpu->getPc();
	//cout << insPos << "\n";
	ins = cpu->Ins->at(insPos);
	int p = insPos + 1;
	while (p < In.size() && !cpu->Ins->at(p).type) ++p;
	cpu->reg->writePC(p);
	isBlocked = false;
	cpu->iddp.isIdle = false;
}

void IDDP:: execute() {
	if (isIdle) return;
	if (cpu->isPcUsed()) isIdle = true;
	if (cpu->ex.isBlocked) isBlocked = true;
	if (cpu->isPcUsed() || cpu->ex.isBlocked) return;
	ins = cpu->iF.ins;

	switch (ins.type) {

	case 1:
	case 3:
	case 5:
	case 9:
	case 13:
	case 16:
	case 19:
	case 21:
	case 23:
	case 25:
	case 27:
	case 29:

		rd = ins.p[0], rs = ins.p[1], sr = ins.p[2];
		vRs = cpu->getReg(rs), vSr = cpu->getReg(sr);
		break;

	case 2:
	case 4:
	case 6:
	case 10:
	case 14:
	case 17:
	case 20:
	case 22:
	case 24:
	case 26:
	case 28:
	case 30:

		rd = ins.p[0], rs = ins.p[1], im = ins.p[2];
		vRs = cpu->getReg(rs);
		break;

	case 7:
	case 11:

		rs = ins.p[0], sr = ins.p[1];
		vRs = cpu->getReg(rs), vSr = cpu->getReg(sr);
		break;

	case 8:
	case 12:

		rs = ins.p[0], im = ins.p[1];
		vRs = cpu->getReg(rs);
		break;

	case 15:

		rd = ins.p[0], rs = ins.p[1];
		vRs = cpu->getReg(rs);
		break;

	case 18:

		rd = ins.p[0], im = ins.p[1];
		break;

	case 31:
	case 50:
	case 52:

		lab = ins.s;
		break;

	case 32:
	case 34:
	case 36:
	case 38:
	case 40:
	case 42:

		rs = ins.p[0], sr = ins.p[1];
		vRs = cpu->getReg(rs), vSr = cpu->getReg(sr);
		lab = ins.s;
		break;

	case 33:
	case 35:
	case 37:
	case 39:
	case 41:
	case 43:

		rs = ins.p[0], im = ins.p[1];
		vRs = cpu->getReg(rs);
		lab = ins.s;
		break;

	case 44:
	case 45:
	case 46:
	case 47:
	case 48:
	case 49:

		rs = ins.p[0];
		vRs = cpu->getReg(rs);
		lab = ins.s;
		break;

	case 51:
	case 53:

		rs = ins.p[0];
		vRs = cpu->getReg(rs);

		break;

	case 54:
	case 56:
	case 58:
	case 60:

		rd = ins.p[0];

		lab = ins.s;
		break;

	case 55:
	case 57:
	case 59:
	case 61:

		rd = ins.p[0], rs = ins.p[1], dis = ins.p[2];
		vRs = cpu->getReg(rs);
		break;

	case 62:
	case 64:
	case 66:

		rs = ins.p[0];
		vRs = cpu->getReg(rs);
		lab = ins.s;
		break;

	case 63:
	case 65:
	case 67:

		rs = ins.p[0], sr = ins.p[1], dis = ins.p[2];
		vRs = cpu->getReg(rs);
		vSr = cpu->getReg(sr);
 		break;

	case 68:

		rd = ins.p[0], rs = ins.p[1];
		vRs = cpu->getReg(rs);
		break;

	case 69:

		rd = ins.p[0];
		rs = 33;
		vRs = cpu->getReg(rs);
		break;

	case 70:

		rd = ins.p[0];
		rs = 32;
		vRs = cpu->getReg(rs);
		break;

	case 71:

		break;

	case 72:

		rs = 2;
		vRs = cpu->getReg(rs);
		switch (vRs) {

		case 1:
		case 4:
		case 9:
		case 17:

			sr = 4;
			vSr = cpu->getReg(sr);
			break;

		case 5:
		case 10:

			break;

		case 8:

			sr = 4, a1 = 5;
			vSr = cpu->getReg(sr);
			va1 = cpu->getReg(a1);
			break;

		}
		break;
	}

	bool suc = false;
	switch (ins.type) {

	case 1:
	case 3:
	case 5:
	case 9:
	case 13:
	case 16:
	case 19:
	case 21:
	case 23:
	case 25:
	case 27:
	case 29:

		suc = !cpu->isRegUsed(rs) & !cpu->isRegUsed(sr);
		break;

	case 2:
	case 4:
	case 6:
	case 10:
	case 14:
	case 17:
	case 20:
	case 22:
	case 24:
	case 26:
	case 28:
	case 30:

		suc = !cpu->isRegUsed(rs);
		break;

	case 7:
	case 11:

		suc = !cpu->isRegUsed(rs) & !cpu->isRegUsed(sr);
		break;

	case 8:
	case 12:

		suc = !cpu->isRegUsed(rs);
		break;

	case 15:

		suc = !cpu->isRegUsed(rs);
		break;

	case 18:

		suc = true;
		break;

	case 31:
	case 50:
	case 52:

		suc = !cpu->isPcUsed();
		break;

	case 32:
	case 34:
	case 36:
	case 38:
	case 40:
	case 42:

		suc = !cpu->isRegUsed(rs) & !cpu->isRegUsed(sr) & !cpu->isPcUsed();
		break;

	case 33:
	case 35:
	case 37:
	case 39:
	case 41:
	case 43:

		suc = !cpu->isRegUsed(rs) & !cpu->isPcUsed();
		break;

	case 44:
	case 45:
	case 46:
	case 47:
	case 48:
	case 49:

		suc = !cpu->isRegUsed(rs) & !cpu->isPcUsed();
		break;

	case 51:
	case 53:

		suc = !cpu->isRegUsed(rs) & !cpu->isPcUsed();
		break;

	case 54:
	case 56:
	case 58:
	case 60:

		suc = true;
		break;

	case 55:
	case 57:
	case 59:
	case 61:

		suc = !cpu->isRegUsed(rs);
		break;

	case 62:
	case 64:
	case 66:

		suc = !cpu->isRegUsed(rs);
		break;

	case 63:
	case 65:
	case 67:

		suc = !cpu->isRegUsed(rs) && !cpu->isRegUsed(sr);
		break;

	case 68:

		suc = !cpu->isRegUsed(rs);
		break;

	case 69:
	case 70:

		suc = !cpu->isRegUsed(rs);
		break;

	case 71:

		suc = true;
		break;

	case 72:
		switch (vRs) {

		case 1:
		case 4:
		case 9:
		case 17:
			suc = !cpu->isRegUsed(rs) && !cpu->isRegUsed(sr);
			break;

		case 5:

			suc = !cpu->isRegUsed(rs);
			break;

		case 10:

			suc = true;
			break;

		case 8:

			suc = !cpu->isRegUsed(rs) & !cpu->isRegUsed(sr) & !cpu->isRegUsed(a1);
			break;

		}
		break;

	}

	if (!suc) {
		isBlocked = true;
		return;
	}

	switch (ins.type) {

	case 1:
	case 3:
	case 5:
	case 9:
	case 13:
	case 16:
	case 19:
	case 21:
	case 23:
	case 25:
	case 27:
	case 29:
	case 2:
	case 4:
	case 6:
	case 10:
	case 14:
	case 17:
	case 20:
	case 22:
	case 24:
	case 26:
	case 28:
	case 30:
	case 15:
	case 18:
	case 54:
	case 56:
	case 58:
	case 60:
	case 55:
	case 57:
	case 59:
	case 61:
	case 68:
	case 69:
	case 70:

		cpu->setRegUsed(rd);
		break;

	case 7:
	case 11:
	case 8:
	case 12:

		cpu->setRegUsed(32);
		cpu->setRegUsed(33);
		break;

	case 31:
	case 50:
	case 32:
	case 34:
	case 36:
	case 38:
	case 40:
	case 42:
	case 33:
	case 35:
	case 37:
	case 39:
	case 41:
	case 43:
	case 44:
	case 45:
	case 46:
	case 47:
	case 48:
	case 49:
	case 51:

		cpu->setPcUsed();
		break;

	case 52:
	case 53:

		cpu->setPcUsed();
		cpu->setRegUsed(31);
		break;

	case 62:
	case 64:
	case 66:
	case 63:
	case 65:
	case 67:
	case 71:

		break;

	case 72:

		switch (vRs) {

		case 1:
		case 4:
		case 8:
		case 10:
		case 17:

			break;

		case 5:
		case 9:

			cpu->setRegUsed(2);
			break;

		}

		break;

	}

	vPc = cpu->getPc();
	isBlocked = false;
	isIdle = true;
	cpu->ex.isIdle = false;
	insPos = cpu->iF.insPos;
}

void EX::execute() {

	IDDP& iddp = cpu->iddp;
	rd = iddp.rd, vRs = iddp.vRs, vSr = iddp.vSr, vPc = iddp.vPc, a1 = iddp.a1, va1 = iddp.va1;
	int InsPos = iddp.insPos;
	lab = iddp.lab;
	ins = iddp.ins;
	if (isIdle) return;
	if (cpu->ma.isBlocked) {
		isBlocked = true;
		return;
	}
	switch (ins.type) {

	case 1:

		result = iddp.vRs + iddp.vSr;
		break;

	case 2:

		result = iddp.vRs + iddp.im;
		break;

	case 3:

		result = iddp.vRs - iddp.vSr;
		break;

	case 4:

		result = iddp.vRs - iddp.im;
		break;

	case 5:

		result = iddp.vRs * iddp.vSr;
		break;

	case 6:

		result = iddp.vRs * iddp.im;
		break;

	case 7:

		result = iddp.vRs * iddp.vSr;
		Hi = result >> 32;
		Lo = result & pow32;
		break;

	case 8:

		result = iddp.vRs * iddp.im;
		Hi = result >> 32;
		Lo = result & pow32;
		break;

	case 9:

		result = iddp.vRs / iddp.vSr;
		break;

	case 10:

		result = iddp.vRs / iddp.im;
		break;

	case 11:


		Hi = iddp.vRs % iddp.vSr;
		Lo = iddp.vRs / iddp.vSr;
		break;

	case 12:


		Hi = iddp.vRs % iddp.im;
		Lo = iddp.vRs / iddp.im;
		break;

	case 13:

		result = iddp.vRs ^ iddp.vSr;
		break;

	case 14:

		result = iddp.vRs ^ iddp.im;
		break;

	case 15:

		result = -iddp.vRs;
		break;

	case 16:

		result = iddp.vRs % iddp.vSr;
		break;

	case 17:

		result = iddp.vRs % iddp.im;
		break;

	case 18:

		result = iddp.im;
		break;

	case 19:

		result = (iddp.vRs == iddp.vSr);
		break;

	case 20:

		result = (iddp.vRs == iddp.im);
		break;

	case 21:

		result = (iddp.vRs >= iddp.vSr);
		break;

	case 22:

		result = (iddp.vRs >= iddp.im);
		break;

	case 23:

		result = (iddp.vRs > iddp.vSr);
		break;

	case 24:

		result = (iddp.vRs > iddp.im);
		break;

	case 25:

		result = (iddp.vRs <= iddp.vSr);
		break;

	case 26:

		result = (iddp.vRs <= iddp.im);
		break;

	case 27:

		result = (iddp.vRs < iddp.vSr);
		break;

	case 28:

		result = (iddp.vRs < iddp.im);
		break;

	case 29:

		result = (iddp.vRs != iddp.vSr);
		break;

	case 30:

		result = (iddp.vRs != iddp.im);
		break;

	case 31:

		result = A.Lab[lab];
		break;

	case 32:

		if (iddp.vRs == iddp.vSr) result = A.Lab[lab];
		else result = iddp.vPc;
		break;

	case 33:

		if (iddp.vRs == iddp.im) result = A.Lab[lab];
		else result = iddp.vPc;
		break;

	case 34:

		if (iddp.vRs != iddp.vSr) result = A.Lab[lab];
		else result = iddp.vPc;
		break;

	case 35:

		if (iddp.vRs != iddp.im) result = A.Lab[lab];
		else result = iddp.vPc;
		break;

	case 36:

		if (iddp.vRs >= iddp.vSr) result = A.Lab[lab];
		else result = iddp.vPc;
		break;

	case 37:

		if (iddp.vRs >= iddp.im) result = A.Lab[lab];
		else result = iddp.vPc;
		break;

	case 38:

		if (iddp.vRs <= iddp.vSr) result = A.Lab[lab];
		else result = iddp.vPc;
		break;

	case 39:

		if (iddp.vRs <= iddp.im) result = A.Lab[lab];
		else result = iddp.vPc;
		break;

	case 40:

		if (iddp.vRs > iddp.vSr) result = A.Lab[lab];
		else result = iddp.vPc;
		break;

	case 41:

		if (iddp.vRs > iddp.im) result = A.Lab[lab];
		else result = iddp.vPc;
		break;

	case 42:

		if (iddp.vRs < iddp.vSr) result = A.Lab[lab];
		else result = iddp.vPc;
		break;

	case 43:

		if (iddp.vRs < iddp.im) result = A.Lab[lab];
		else result = iddp.vPc;
		break;

	case 44:

		if (!iddp.vRs) result = A.Lab[lab];
		else result = iddp.vPc;
		break;

	case 45:

		if (iddp.vRs) result = A.Lab[lab];
		else result = iddp.vPc;
		break;

	case 46:

		if (iddp.vRs <= 0) result = A.Lab[lab];
		else result = iddp.vPc;
		break;

	case 47:

		if (iddp.vRs >= 0) result = A.Lab[lab];
		else result = iddp.vPc;
		break;

	case 48:

		if (iddp.vRs > 0) result = A.Lab[lab];
		else result = iddp.vPc;
		break;

	case 49:

		if (iddp.vRs < 0) result = A.Lab[lab];
		else result = iddp.vPc;
		break;

	case 50:

		result = A.Lab[lab];
		break;

	case 51:

		result = iddp.vRs;
		break;

	case 52:{

		int p = InsPos + 1;
		while (p < In.size() && cpu->Ins->at(p).type == 0) ++p;
		nex = p;
		result = A.Lab[lab];
		break;
	}

	case 53:{

		int p = InsPos + 1;
		while (p < In.size() && cpu->Ins->at(p).type == 0) ++p;
		nex = p;
		result = iddp.vRs;
		break;
	}

	case 54:

		op = 1;
		result = A.Lab[lab];
		break;

	case 55:

		op = 1;
		result = iddp.vRs + iddp.dis;
		break;

	case 56:

		op = 1;
		result = A.Lab[lab];
		break;

	case 57:

		op = 1;
		result = iddp.vRs + iddp.dis;
		break;

	case 58:

		op = 2;
		result = A.Lab[lab];
		break;

	case 59:

		op = 2;
		result = iddp.vRs + iddp.dis;
		break;

	case 60:

		op = 4;
		result = A.Lab[lab];
		break;

	case 61:

		op = 4;
		result = iddp.vRs + iddp.dis;
		break;

	case 62:

		op = 1;
		result = A.Lab[lab];
		break;

	case 63:

		op = 1;
		result = iddp.vSr + iddp.dis;
		break;

	case 64:

		op = 2;
		result = A.Lab[lab];
		break;

	case 65:

		op = 2;
		result = iddp.vSr + iddp.dis;
		break;

	case 66:

		op = 4;
		result = A.Lab[lab];
		break;

	case 67:

		op = 4;
		result = iddp.vSr + iddp.dis;

		break;

	case 68:

		result = iddp.vRs;
		break;

	case 69:

		result = cpu->getReg(33);
		break;

	case 70:

		result = cpu->getReg(32);
		break;

	case 71:

		break;

	case 72:
		switch (iddp.vRs) {

		case 1:
			cout << iddp.vSr;
			break;

		case 4: {
			int p = iddp.vSr;
			while (cpu->memory->data[p] != '\0') cout << cpu->memory->data[p], ++p;
			break;
		}

		case 5:
			cin >> result;
			break;

		case 8:
			result = iddp.vSr;
			length = iddp.va1;
			break;

		case 9:

			result = iddp.vSr;
			break;

		case 10:
			exit(0);
			break;

		case 17:
			exit(iddp.vSr);
			break;

		}
		break;

	}

	isBlocked = false;
	isIdle = true;
	cpu->ma.isIdle = false;
	insPos = iddp.insPos;
}

void MA::execute() {


	EX& ex = cpu->ex;
	ins = ex.ins;
	result = ex.result;
	pos = ex.result;
	rd = cpu->ex.rd;
	Hi = ex.Hi;
	Lo = ex.Lo;
	nex = ex.nex;
	lab = ex.lab;
	vRs = ex.vRs;
	vSr = ex.vSr;

	if (isIdle) return;
	if (cpu->wb.isBlocked) {
		isBlocked = true;
		return;
	}
	switch (ins.type) {

	case 54:
	case 55:

		result = pos;
		break;

	case 56:
	case 57:
	case 58:
	case 59:
	case 60:
	case 61:

		result = cpu->memory->load(pos, ex.op);
		break;

	case 62:
	case 63:
	case 64:
	case 65:
	case 66:
	case 67:

		cpu->memory->store(pos, ex.vRs, ex.op);
 		break;

	case 72:

		switch (ex.vRs) {

		case 8: {

			string str;
			cin >> str;
			int len = strlen(str.c_str());
			for (int i = 0; i < len; ++i) cpu->memory->data[vSr + i] = str[i];
			break;
		}
		case 9:

			result = cpu->memory->space(vSr);
			break;
		}

		break;
	}
	isBlocked = false;
	isIdle = true;
	cpu->wb.isIdle = false;
	insPos = cpu->iF.insPos;
}


void WB::execute() {

	if (isIdle) return;
	MA& ma = cpu->ma;
	ins = ma.ins;
	if (ins.type == 7 || ins.type == 8 || ins.type == 11 || ins.type == 12) cpu->reg->write(33, ma.Hi), cpu->reg->write(32, cpu->ex.Lo);
	else if (ins.type >= 1 && ins.type <= 30) cpu->reg->write(ma.rd, ma.result);
	else if (ins.type >= 31 && ins.type <= 51) cpu->reg->writePC(ma.result);
	else if (ins.type >= 52 && ins.type <= 53) cpu->reg->writePC(ma.result), cpu->reg->write(31, ma.nex);
	else if (ins.type >= 54 && ins.type <= 61) cpu->reg->write(ma.rd, ma.result);
	else if (ins.type >= 68 && ins.type <= 70) cpu->reg->write(ma.rd, ma.result);
	else if (ins.type == 72) {
		if (ma.vRs == 5) cpu->reg->write(2, ma.result);
		else if (ma.vRs == 9) cpu->reg->write(2, ma.result);
	}
	isIdle = true;
	insPos = ma.insPos;
}


int main(int argc, char* argv[]) {//
	A.work(memory, In, Da, argv[1]);
	CPU c(pr, pm, pIn, pDa);
	c.reg->writePC(A.start);
	while (true) c.execute();
    return 0;
}


