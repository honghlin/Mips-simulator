// mips.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "parser.h"
#include "register.h"
//#include "memory.h"
//#include "instruction.h"
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<unordered_map>
#include<utility>
#include<fstream>
#include<vector>

//typedef long long LL;

const LL pow32 = 4294967295;

parser A;
//unordered_map<string, int> Lab;

using namespace std;
/*using std::unordered_map;
using std::string;
using std::pair;
using std::string;
using std::vector;
using std::ifstream;*/

/*unordered_map<string, int> Ins;
unordered_map<string, int> Reg;
unordered_map<string, int> isLab;
unordered_map<string, int> Lab;

Memory memory;

LL R[35];

void map_init() {
	Ins[".align"] = 1;
	Ins[".ascii"] = 2;
	Ins[".asciiz"] = 3;
	Ins[".byte"] = 4;
	Ins[".half"] = 5;
	Ins[".word"] = 6;
	Ins[".space"] = 7;
	Ins[".data"] = 8;
	Ins[".text"] = 9;
	Ins["add"] = 10;
	Ins["addu"] = 11;
	Ins["addiu"] = 12;
	Ins["sub"] = 13;
	Ins["subu"] = 14;
	Ins["mul"] = 15;
	Ins["mulu"] = 16;
	//Ins["mul"] = 17;
	//Ins["mulu"] = 18;
	Ins["div"] = 19;
	Ins["divu"] = 20;
	//Ins["div"] = 21;
	//Ins["divu"] = 22;
	Ins["xor"] = 23;
	Ins["xoru"] = 24;
	Ins["neg"] = 25;
	Ins["negu"] = 26;
	Ins["rem"] = 27;
	Ins["remu"] = 28;
	Ins["li"] = 29;
	Ins["seq"] = 30;
	Ins["sge"] = 31;
	Ins["sgt"] = 32;
	Ins["sle"] = 33;
	Ins["slt"] = 34;
	Ins["sne"] = 35;
	Ins["b"] = 36;
	Ins["beq"] = 37;
	Ins["bne"] = 38;
	Ins["bge"] = 39;
	Ins["ble"] = 40;
	Ins["bgt"] = 41;
	Ins["blt"] = 42;
	Ins["beqz"] = 43;
	Ins["bnez"] = 44;
	Ins["blez"] = 45;
	Ins["bgez"] = 46;
	Ins["bgtz"] = 47;
	Ins["bltz"] = 48;
	Ins["j"] = 49;
	Ins["jr"] = 50;
	Ins["jal"] = 51;
	Ins["jalr"] = 52;
	Ins["la"] = 53;
	Ins["lb"] = 54;
	Ins["lh"] = 55;
	Ins["lw"] = 56;
	Ins["sb"] = 57;
	Ins["sh"] = 58;
	Ins["sw"] = 59;
	Ins["move"] = 60;
	Ins["mfhi"] = 61;
	Ins["mflo"] = 62;
	Ins["nop"] = 63;
	Ins["syscall"] = 64;
	Reg["$0"] = 0;
	Reg["$zero"] = 0;
	Reg["$1"] = 1;
	Reg["$at"] = 1;
	Reg["$2"] = 2;
	Reg["$v0"] = 2;
	Reg["$3"] = 3;
	Reg["$v1"] = 3;
	Reg["$4"] = 4;
	Reg["$a0"] = 4;
	Reg["$5"] = 5;
	Reg["$a1"] = 5;
	Reg["$6"] = 6;
	Reg["$a2"] = 6;
	Reg["$7"] = 7;
	Reg["$a3"] = 7;
	Reg["$8"] = 8;
	Reg["$t0"] = 8;
	Reg["$9"] = 9;
	Reg["$t1"] = 9;
	Reg["$10"] = 10;
	Reg["$t2"] = 10;
	Reg["$11"] = 11;
	Reg["$t3"] = 11;
	Reg["$12"] = 12;
	Reg["$t4"] = 12;
	Reg["$13"] = 13;
	Reg["$t5"] = 13;
	Reg["$14"] = 14;
	Reg["$t6"] = 14;
	Reg["$15"] = 15;
	Reg["$t7"] = 15;
	Reg["$16"] = 16;
	Reg["$s0"] = 16;
	Reg["$17"] = 17;
	Reg["$s1"] = 17;
	Reg["$18"] = 18;
	Reg["$s2"] = 18;
	Reg["$19"] = 19;
	Reg["$s3"] = 19;
	Reg["$20"] = 20;
	Reg["$s4"] = 20;
	Reg["$21"] = 21;
	Reg["$s5"] = 21;
	Reg["$22"] = 22;
	Reg["$s6"] = 22;
	Reg["$23"] = 23;
	Reg["$s7"] = 23;
	Reg["$24"] = 24;
	Reg["$t8"] = 24;
	Reg["$25"] = 25;
	Reg["$t9"] = 25;
	Reg["$26"] = 26;
	Reg["$k0"] = 26;
	Reg["$27"] = 27;
	Reg["$k1"] = 27;
	Reg["$28"] = 28;
	Reg["$gp"] = 28;
	Reg["$29"] = 29;
	Reg["$sp"] = 29;
	Reg["$30"] = 30;
	Reg["$s8"] = 30;
	Reg["$fp"] = 30;
	Reg["$31"] = 31;
	Reg["$ra"] = 31;
	Reg["$32"] = 32;
	Reg["$lo"] = 32;
	Reg["$33"] = 33;
	Reg["$hi"] = 33;
}

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

pair<string, int> tran(string s) {
	if (Reg.count(s)) return pair<string, int> (s, 0);
	else {
		int len = strlen(s.c_str());
		int p1, p2;
		p1 = p2 = 0;
		for (p1 = 0; p1 < len; ++p1) {
			if (s[p1] == '(') break;
		}
		for (p2 = 0; p2 < len; ++p2) {
			if (s[p2] == ')') break;
		}
		p1++;
		p2--;
		string t1 ,t2;
		t1 = t2 = "";
		for (int i = p1; i <= p2; ++i) t1 += s[i];
		for (int i = 0; i < p1 - 1; ++i) t2 += s[i];
		int t = t2 == "" ? 0 : toInt(t2);
		return pair<string, int> (t1, t);
	}
}

vector<instruction> In;
vector<Data> Da;


bool isData;

void parser(const string &s0, const string &s1, const string &s2, const string &s3) {
	
	//cout << Ins[s0] << "\n";

	switch (Ins[s0]) {

	case 1: Da.push_back(Data(1, "", toInt(s1)));
		break;

	case 2:{
		string str = "";
		int len = strlen(s1.c_str());
		for (int i = 1; i < len - 1; ++i) {
			if (s1[i] != '\\') str += s1[i];
			else {
				++i;
				if (s1[i] != 'n') str += s1[i];
				else str += '\n';
			}
		}
		Da.push_back(Data(2, str));
		break;
	}

	case 3:{
		//cout << s1[2] << "           sss" << "\n";
		//cout << s1 << "\n";
		   string str = "";
		   int len = strlen(s1.c_str());
		   for (int i = 1; i < len - 1; ++i) {
			   //cout << i << "\n";
			   if (s1[i] != '\\') str += s1[i];
			   else {
				   ++i;
				   if (s1[i] != 'n') str += s1[i];
				   else str += '\n';
			   }
		   }
		   //cout << str << "              str" << "\n";
		   Da.push_back(Data(3, str));
	}
		break;

	case 4:
		Da.push_back(Data(4, "", toInt(s1)));
		break;

	case 5:
		Da.push_back(Data(5, "", toInt(s1)));
		break;

	case 6:
		Da.push_back(Data(6, "", toInt(s1)));
		break;

	case 7:
		Da.push_back(Data(7, "", toInt(s1)));
		break;

	case 8:
		//Da.push_back(Data(8, ""));
		isData = true;
		//cout << "ttt" << "\n";
		break;

	case 9:
		//Da.push_back(Data(9, ""));
		isData = false;
		break;

	case 10:
	case 11:
	case 12:
		if (!isInt(s3)) In.push_back(instruction(1, "", Reg[s1], Reg[s2], Reg[s3]));
		else In.push_back(instruction(2, "", Reg[s1], Reg[s2], toInt(s3)));
		break;

	case 13:
	case 14:
		if (!isInt(s3)) In.push_back(instruction(3, "", Reg[s1], Reg[s2], Reg[s3]));
		else In.push_back(instruction(4, "", Reg[s1], Reg[s2], toInt(s3)));
		break;

	case 15:
	case 16:
		if (s3 != "") {
			if (!isInt(s3)) In.push_back(instruction(5, "", Reg[s1], Reg[s2], Reg[s3]));
			else In.push_back(instruction(6, "", Reg[s1], Reg[s2], toInt(s3)));
		}
		else {
			if (!isInt(s2)) In.push_back(instruction(7, "", Reg[s1], Reg[s2]));
			else In.push_back(instruction(8, "", Reg[s1], toInt(s2)));
		}
		break;

	case 19:
	case 20:
		if (s3 != "") {
			if (!isInt(s3)) In.push_back(instruction(9, "", Reg[s1], Reg[s2], Reg[s3]));
			else In.push_back(instruction(10, "", Reg[s1], Reg[s2], toInt(s3)));
		}
		else {
			if (!isInt(s2)) In.push_back(instruction(11, "", Reg[s1], Reg[s2]));
			else In.push_back(instruction(12, "", Reg[s1], toInt(s2)));
		}
		break;
	
	case 23:
	case 24:
		if (!isInt(s3)) In.push_back(instruction(13, "", Reg[s1], Reg[s2], Reg[s3]));
		else In.push_back(instruction(14, "", Reg[s1], Reg[s2], toInt(s3)));
		break;

	case 25:
	case 26:
		In.push_back(instruction(15, "", Reg[s1], Reg[s2], Reg[s3]));
		break;

	case 27:
	case 28:
		if (!isInt(s3)) In.push_back(instruction(16, "", Reg[s1], Reg[s2], Reg[s3]));
		else In.push_back(instruction(17, "", Reg[s1], Reg[s2], toInt(s3)));
		break;

	case 29:
		In.push_back(instruction(18, "", Reg[s1], toInt(s2)));
		break;

	case 30:
		if (!isInt(s3)) In.push_back(instruction(19, "", Reg[s1], Reg[s2], Reg[s3]));
		else In.push_back(instruction(20, "", Reg[s1], Reg[s2], toInt(s3)));
		break;

	case 31:
		if (!isInt(s3)) In.push_back(instruction(21, "", Reg[s1], Reg[s2], Reg[s3]));
		else In.push_back(instruction(22, "", Reg[s1], Reg[s2], toInt(s3)));
		break;

	case 32:
		if (!isInt(s3)) In.push_back(instruction(23, "", Reg[s1], Reg[s2], Reg[s3]));
		else In.push_back(instruction(24, "", Reg[s1], Reg[s2], toInt(s3)));
		break;

	case 33:
		if (!isInt(s3)) In.push_back(instruction(25, "", Reg[s1], Reg[s2], Reg[s3]));
		else In.push_back(instruction(26, "", Reg[s1], Reg[s2], toInt(s3)));
		break;

	case 34:
		if (!isInt(s3)) In.push_back(instruction(27, "", Reg[s1], Reg[s2], Reg[s3]));
		else In.push_back(instruction(28, "", Reg[s1], Reg[s2], toInt(s3)));
		break;

	case 35:
		if (!isInt(s3)) In.push_back(instruction(29, "", Reg[s1], Reg[s2], Reg[s3]));
		else In.push_back(instruction(30, "", Reg[s1], Reg[s2], toInt(s3)));
		break;

	case 36:
		In.push_back(instruction(31, s1));
		break;

	case 37:
		if (!isInt(s2))In.push_back(instruction(32, s3, Reg[s1], Reg[s2]));
		else In.push_back(instruction(33, s3, Reg[s1], toInt(s2)));
		break;

	case 38:
		if (!isInt(s2))In.push_back(instruction(34, s3, Reg[s1], Reg[s2]));
		else In.push_back(instruction(35, s3, Reg[s1], toInt(s2)));
		break;

	case 39:
		if (!isInt(s2))In.push_back(instruction(36, s3, Reg[s1], Reg[s2]));
		else In.push_back(instruction(37, s3, Reg[s1], toInt(s2)));
		break;

	case 40:
		if (!isInt(s2))In.push_back(instruction(38, s3, Reg[s1], Reg[s2]));
		else In.push_back(instruction(39, s3, Reg[s1], toInt(s2)));
		break;

	case 41:
		if (!isInt(s2))In.push_back(instruction(40, s3, Reg[s1], Reg[s2]));
		else In.push_back(instruction(41, s3, Reg[s1], toInt(s2)));
		break;

	case 42:
		if (!isInt(s2))In.push_back(instruction(42, s3, Reg[s1], Reg[s2]));
		else In.push_back(instruction(43, s3, Reg[s1], toInt(s2)));
		break;

	case 43:
		In.push_back(instruction(44, s2, Reg[s1]));
		break;

	case 44:
		In.push_back(instruction(45, s2, Reg[s1]));
		break;

	case 45:
		In.push_back(instruction(46, s2, Reg[s1]));
		break;

	case 46:
		In.push_back(instruction(47, s2, Reg[s1]));
		break;

	case 47:
		In.push_back(instruction(48, s2, Reg[s1]));
		break;

	case 48:
		In.push_back(instruction(49, s2, Reg[s1]));
		break;

	case 49:
		In.push_back(instruction(50, s1));
		break;

	case 50:
		In.push_back(instruction(51, "" , Reg[s1]));
		break;

	case 51:
		In.push_back(instruction(52, s1));
		break;

	case 52:
		In.push_back(instruction(53, "", Reg[s1]));
		break;

	case 53:
		if (isLab[s2]) In.push_back(instruction(54, s2, Reg[s1]));
		else if (isInt(s2)) In.push_back(instruction(54, "", Reg[s1], toInt(s2)));
		else {
			pair<string, int> t = tran(s2);
			In.push_back(instruction(55, "", Reg[s1], Reg[t.first], t.second));
		}
		break;

	case 54:
		if (isLab[s2]) In.push_back(instruction(56, s2, Reg[s1]));
		else if (isInt(s2)) In.push_back(instruction(56, "", Reg[s1], toInt(s2)));
		else {
			pair<string, int> t = tran(s2);
			In.push_back(instruction(57, "", Reg[s1], Reg[t.first], t.second));
		}
		break;

	case 55:
		if (isLab[s2]) In.push_back(instruction(58, s2, Reg[s1]));
		else if (isInt(s2)) In.push_back(instruction(58, "", Reg[s1], toInt(s2)));
		else {
			pair<string, int> t = tran(s2);
			In.push_back(instruction(59, "", Reg[s1], Reg[t.first], t.second));
		}
		break;

	case 56:
		if(isLab[s2]) In.push_back(instruction(60, s2, Reg[s1]));
		else if (isInt(s2)) In.push_back(instruction(60, "", Reg[s1], toInt(s2)));
		else {
			pair<string, int> t = tran(s2);
			In.push_back(instruction(61, "", Reg[s1], Reg[t.first], t.second));
		}
		break;

	case 57:
		if (isLab[s2]) In.push_back(instruction(62, s2, Reg[s1]));
		else if (isInt(s2)) In.push_back(instruction(62, "", Reg[s1], toInt(s2)));
		else {
			pair<string, int> t = tran(s2);
			In.push_back(instruction(63, "", Reg[s1], Reg[t.first], t.second));
		}
		break;

	case 58:
		if (isLab[s2]) In.push_back(instruction(64, s2, Reg[s1]));
		else if (isInt(s2)) In.push_back(instruction(64, "", Reg[s1], toInt(s2)));
		else {
			pair<string, int> t = tran(s2);
			In.push_back(instruction(65, "", Reg[s1], Reg[t.first], t.second));
		}
		break;

	case 59:
		//cout << s2 << "ttt" << "\n";
		if (isLab[s2]) In.push_back(instruction(66, s2, Reg[s1]));
		else if (isInt(s2)) In.push_back(instruction(66, "", Reg[s1], toInt(s2)));
		else {
			pair<string, int> t = tran(s2);
			In.push_back(instruction(67, "", Reg[s1], Reg[t.first], t.second));
		}
		break;

	case 60:
		In.push_back(instruction(68, "", Reg[s1], Reg[s2]));
		break;

	case 61:
		In.push_back(instruction(69, "", Reg[s1]));
		break;

	case 62:
		In.push_back(instruction(70, "", Reg[s1]));
		break;

	case 63:
		In.push_back(instruction(71, ""));
		break;

	case 64:
		In.push_back(instruction(72, ""));
		break;

	default:
		isLab[s0] = 1;
		if(isData) Da.push_back(Data(0, s0));
		else In.push_back(instruction(0, s0));
	}
}

void init() {
	isData = false;
	string str;
	ifstream infile;
	infile.open("C:\\Users\\80780\\Desktop\\in\\testsuit-1\\array_test2-mahaojun.s", ios::in);
	//infile.open("C:\\Users\\80780\\Desktop\\in\\testsuit-1\\horse2-5100309153-yanghuan.s", ios::in);
	//infile.open("C:\\Users\\80780\\Desktop\\in\\testsuit-1\\builtin-5140519064-youyurong.s", ios::in);
	//cout << 1 << endl;
	int i = 0;
	while (!infile.eof()) {
		//cout << ++i << "\n";
		//++i;
		//if (i > 2000) break;
		string s0, s1, s2, s3;
		s0 = s1 = s2 = s3 = "";
		int pos = 0;
		getline(infile, str, '\n');
		int len = strlen(str.c_str());
		if (!len) continue;
		for (int i = 0; i < len; ++i) {
			if (str[i] == '#') len = i;
			break;
		}
		//cout << len << "\n";
		if (!len) continue;
		while (str[pos] == '	' || str[pos] == ' ') ++pos;
		//cout << pos << "\n";
		if (pos > len) continue;
		for (int i = 0; i < len; ++i) {
			if (str[i] == ':') {
				for (int j = pos; j < i; ++j) s0 += str[j];
				cout << s0 << "\n";
				break;
			}
		}
		if (s0 != "") {
			parser(s0, s1, s2, s3);
			continue;
		}
		while (pos < len && str[pos] != ' ' && str[pos] != ',') s0 += str[pos], ++pos;
		if (Ins[s0] == 2 || Ins[s0] == 3) {
			++pos;
			while (pos < len) s1 += str[pos], pos++;
		}
		else {
			++pos;
			if (pos < len && (str[pos] == ' ' || str[pos] == ',')) ++pos;
			while (pos < len && str[pos] != ' ' && str[pos] != ',') s1 += str[pos], ++pos;
			++pos;
			if (pos < len && (str[pos] == ' ' || str[pos] == ',')) ++pos;
			while (pos < len && str[pos] != ' ' && str[pos] != ',') s2 += str[pos], ++pos;
			++pos;
			if (pos < len && (str[pos] == ' ' || str[pos] == ',')) ++pos;
			while (pos < len && str[pos] != ' ' && str[pos] != ',') s3 += str[pos], ++pos;
		}
		if (s0 == "") continue;
		//if (s1 == "") continue;
		parser(s0, s1, s2, s3);
		cout << s0 << "   " << s1 << "   " << s2 << "   " << s3 << "   " << "\n";
	}
	vector<int> Pos;
	int l = Da.size();
	Pos.resize(l);
	//cout << "part1" << "\n";
	for (int i = 0; i < l; ++i) {
		Data t = Da[i];
		if (!t.type) continue;
		switch (t.type) {
		case 1:
			Pos[i] = memory.align(t.p[0]);
			break;

		case 2: {
			int len = strlen(t.s.c_str());
			Pos[i] = memory.pos;
			//cout << Pos[i] << "       pos[i]" << "\n";
			for (int i = 0; i < len; ++i) memory.put_s(t.s[i]);
			break;
		}

		case 3: {
			int len = strlen(t.s.c_str());
			Pos[i] = memory.pos;
			//cout << Pos[i] << "       pos[i]" << "\n";
			for (int i = 0; i < len; ++i) memory.put_s(t.s[i]);
			memory.put_s('\n');
			break;
		}

		case 4:
			Pos[i] = memory.put_b(t.p[0]);
			break;

		case 5:
			Pos[i] = memory.put_h(t.p[0]);
			break;

		case 6:
			Pos[i] = memory.put_w(t.p[0]);
			break;

		case 7:
			Pos[i] = memory.space(t.p[0]);
			break;
		}
	}
	for (int i = 0; i < l; ++i) {
		Data &t = Da[i];
		if (t.type) continue;
		int p = i + 1;
		while (!Da[p].type) ++p;
		t.p[0] = Pos[p];
		Lab[t.s] = Pos[p];
	}
	l = In.size();
	for (int i = 0; i < l; ++i) {
		instruction &t = In[i];
		if (t.type) continue;
		int p = i + 1;
		while (!In[p].type) ++p;
		t.p[0] = p;
		Lab[t.s] = p;
	}
}*/

vector<instruction> In;
vector<Data> Da;

Memory memory;

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
	
	stage(CPU* cpu) : cpu(cpu), isBlocked(false), isIdle(1) {}

};

class IF : public stage {

public:

	instruction ins;

	IF(CPU* cpu) : stage(cpu) {}

	void execute();

	void tran(const stage &b) {
		ins = b.ins;
		lab = b.lab;
		result = b.result;
		rd = b.rd, rs = b.rs, sr = b.sr, im = b.im, vRd = b.vRd, vRs = b.vRs, vSr = b.vSr, vPc = b.vPc, dis = b.dis, flag = b.flag, a1 = b.a1, va1 = b.va1;
		length = b.length;
		nex = b.nex;
		pos = b.pos;
		Hi = b.Hi, Lo = b.Lo, op = b.op;
	}
};

class IDDP : public stage {

public:

	IDDP(CPU* cpu) : stage(cpu) {}

	void execute();

	void tran(const stage &b) {
		ins = b.ins;
		lab = b.lab;
		result = b.result;
		rd = b.rd, rs = b.rs, sr = b.sr, im = b.im, vRd = b.vRd, vRs = b.vRs, vSr = b.vSr, vPc = b.vPc, dis = b.dis, flag = b.flag, a1 = b.a1, va1 = b.va1;
		length = b.length;
		nex = b.nex;
		pos = b.pos;
		Hi = b.Hi, Lo = b.Lo, op = b.op;
	}
};

class EX : public stage {

public:



public:

	EX(CPU* cpu) : stage(cpu) {}

	void execute();

	void tran(const stage &b) {
		ins = b.ins;
		lab = b.lab;
		result = b.result;
		rd = b.rd, rs = b.rs, sr = b.sr, im = b.im, vRd = b.vRd, vRs = b.vRs, vSr = b.vSr, vPc = b.vPc, dis = b.dis, flag = b.flag, a1 = b.a1, va1 = b.va1;
		length = b.length;
		nex = b.nex;
		pos = b.pos;
		Hi = b.Hi, Lo = b.Lo, op = b.op;
	}

};

class MA : public stage {

public:

public:

	MA(CPU* cpu) : stage(cpu) {}

	void execute();

	void tran(const stage &b) {
		ins = b.ins;
		lab = b.lab;
		result = b.result;
		rd = b.rd, rs = b.rs, sr = b.sr, im = b.im, vRd = b.vRd, vRs = b.vRs, vSr = b.vSr, vPc = b.vPc, dis = b.dis, flag = b.flag, a1 = b.a1, va1 = b.va1;
		length = b.length;
		nex = b.nex;
		pos = b.pos;
		Hi = b.Hi, Lo = b.Lo, op = b.op;
	}
};

class WB : public stage {

public:
	
	WB(CPU* cpu) : stage(cpu) {}

	void execute();

	void tran(const stage &b) {
		ins = b.ins;
		lab = b.lab;
		result = b.result;
		rd = b.rd, rs = b.rs, sr = b.sr, im = b.im, vRd = b.vRd, vRs = b.vRs, vSr = b.vSr, vPc = b.vPc, dis = b.dis, flag = b.flag, a1 = b.a1, va1 = b.va1;
		length = b.length;
		nex = b.nex;
		pos = b.pos;
		Hi = b.Hi, Lo = b.Lo, op = b.op;
	}

};

class CPU {

	friend class IF;
	friend class IDDP;
	friend class EX;
	friend class MA;
	friend class WB;
	
private:

	int usedReg[4];
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
	int ii;

	CPU(Register* reg, Memory* memory, vector<instruction>* Ins, vector<Data>* data) : reg(reg), memory(memory), Ins(Ins), data(data), iF(this), iddp(this), ex(this), ma(this), wb(this) {
		pipeline[0] = &iF;
		pipeline[1] = &iddp;
		pipeline[2] = &ex;
		pipeline[3] = &ma;
		pipeline[4] = &wb;
		for (int i = 0; i < 4; ++i) usedReg[i] = -2;
		ii = 0;
	}

	void setRegUsed(int n) {
		usedReg[0] = n;
	}

	bool isRegUsed(int n) {
		for (int i = 1; i < 4; ++i)
			if (usedReg[i] == n) return true;
		return false;
	}

	LL getReg(int n) {
		return reg->read(n);
	}

	void setPcUsed() {
		usedReg[0] = -1;
	}

	bool isPcUsed() {
		for (int i = 1; i < 4; ++i)
			if (usedReg[i] == -1) return true;
		return false;
	}

	LL getPc() {
		return reg->readPC();
	}

	void execute() {
		for (int i = 3; i > 0; --i) usedReg[i] = usedReg[i - 1];
		usedReg[0] = -2;
		//for (int i = 4; i > -1; --i) pipeline[i]->isBlocked = false;
		//for (int i = 4; i > -1; --i) pipeline[i]->execute();
		for (int i = 0; i <= 4; ++i) pipeline[i]->execute();
		//, cout << i << "\n"
		//cout << ++ii << "\n";
	}

	void debug(){
		cout << "\n\n\n";
		for (int i = 0; i <= 33; ++i) cout << i << "       " << reg->read(i) << "\n";
		cout << "pc       " << reg->readPC() << "\n";
		cout << "\n\n\n";
	}
};


void IF::execute() {
	/*if (cpu->iddp.isBlocked || cpu->isPcUsed()) {
		isBlocked = true;
		return;
	}*/
	insPos = cpu->getPc();
	//cout << insPos << "\n";
	ins = cpu->Ins->at(insPos);
	//cout << ins.type << "   type   " << "\n";
	//cout << ins.type << "ins.typeeee" << "\n";
	int p = insPos + 1;
	//cout << p << "\n";
	//cout << In.size() << "\n";
	while (p < In.size() && !cpu->Ins->at(p).type) ++p;
	//cout << p << "p      ";
	cpu->reg->writePC(p);
	isBlocked = false;
	cpu->iddp.isIdle = false;
}

void IDDP:: execute() {
	if (isIdle) return;
	//if (cpu->isPcUsed()) isIdle = true;
	//if (cpu->ex.isBlocked) isBlocked = true;
	//if (isIdle || isBlocked) return;
	//ins = cpu->iF.ins;
	//cout << ins.type << "      1       " << "\n";
	//tran(cpu->iF);
	ins = cpu->iF.ins;
	//cout << ins.type << "      2       " << "\n";
	//ins = cpu->Ins->at(cpu->iF.insPos);
	//cout << ins.type << "ins.type" << "\n";
	//instruction I = ins;
	//cout << I.type << "I.type" << "\n";
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
		//cout << vRs << "vRs" << "\n";
		vRs = cpu->getReg(rs);
		//cout << vRs << "vRs" << "\n";
		break;

	case 54:
	case 56:
	case 58:
	case 60:

		rd = ins.p[0];
		//vRd = cpu->getReg(rd);
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
		//cout << vSr << "      vSr       "<< "\n";
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

		rs = 2;//v0 = 2, a0 = 4, rs = v0;
		vRs = cpu->getReg(rs);
		switch (vRs) {

		case 1:
		case 4:
		case 9:
		case 17:

			sr = 4;
			vSr = cpu->getReg(sr);
			//cout << vSr << "\n";
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

	bool suc = true;
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

			break;

		case 8:

			suc = !cpu->isRegUsed(rs) & !cpu->isRegUsed(sr) & !cpu->isRegUsed(a1);
			break;

		}
		break;

	}
	suc = true;
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
	//ins = iddp.ins;
	//lab = iddp.lab;
	//if (isIdle) return;
	//ins = iddp.ins;
	//lab = ins.s;
	int InsPos = iddp.insPos;
	lab = iddp.lab;
	ins = iddp.ins;
	//cout << InsPos << "     InsPos     " << "\n";
	//tran(iddp);
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
		//Hi = result >> 32;
		//Lo = result % pow32;
		break;

	case 10:

		result = iddp.vRs / iddp.im;
		//Hi = result >> 32;
		//Lo = result % pow32;
		break;

	case 11:

		//result = iddp.vRs / iddp.vSr;
		Hi = iddp.vRs % iddp.vSr;
		Lo = iddp.vRs / iddp.vSr;
		break;

	case 12:

		//result = iddp.vRs / iddp.im;
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
		//cout << result << "re" <<"\n";
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
		//cout << result << "       pos       " << "\n";
		break;

	case 64:

		op = 2;
		result = A.Lab[lab];
		break;

	case 65:

		op = 2;
		result = iddp.vSr + iddp.dis;
		//cout << result << "       pos       " << "\n";
		break;

	case 66:

		op = 4;
		result = A.Lab[lab];
		break;

	case 67:

		op = 4;
		result = iddp.vSr + iddp.dis;
		//cout << result << "       pos       " << "\n";

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
			//cout << "ssssssssss" << "\n";
			break;

		case 4: {
			//result = vSr;
			int p = iddp.vSr;
			//cout << p << "\n";
			while (cpu->memory->data[p] != '\0') {
				//if (!cpu->memory->data[p]) cout << cpu->memory->data[p].c;
				//else
				cout << cpu->memory->data[p];
				++p;
			}
			break;
		}

		case 5:
			cin >> result;
			break;

		case 8:
			//cin >> result;
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
	//op = ex.op;
	Hi = ex.Hi;
	Lo = ex.Lo;
	nex = ex.nex;
	lab = ex.lab;
	vRs = ex.vRs;
	vSr = ex.vSr;
	//if (isIdle) return;
	//tran(ex);
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
		//cout << pos << "        " << ex.op << "\n";

		break;

	case 62:
	case 63:
	case 64:
	case 65:
	case 66:
	case 67:

		cpu->memory->store(pos, ex.vRs, ex.op);
		//cout << pos << "       pos       " << "\n";
		//cout << ex.result << "       pos       " << "\n";
 		break;

	case 72:

		switch (ex.vRs) {

		case 8: {

			string str;
			cin >> str;
			int len = strlen(str.c_str());
			//cpu->memory->pos = vSr;
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
	//tran(ma);
	ins = ma.ins;
	//cout << ma.result << "            result   " << "\n";
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

Memory M;

int main(int argc, char* argv[]) {
	/*//init();""
	/*string s;
	cin >> s;
	cout << toInt(s) << "\n";*/
	/*string s = "";
	cout << trlen(s.c_str()) << "\n";*/
	/*string s;
	cin >> s;
	cout << isInt(s) << "\n";*/
	/*int a = 111;
	int b = ~a;
	cout << a << "   " << b << "\n";*/
	/*map_init();
	string s;
	cin >> s;
	pair<string, int> t = tran(s);
	cout << t.first << "       " << t.second << "\n";
	init();*/
	//string str = argv[1];
	A.work(memory, In, Da, argv[1]);
	//int start = A.start();
	Register r;
	Register* pr = &r;
	Memory *pm = &memory;
	vector<instruction>* pIn = &In;
	vector<Data>* pDa = &Da;
	CPU c(pr, pm, pIn, pDa);
	//cout << A.start << "\n";
	c.reg->writePC(A.start);
	//while (In[c.reg->readPC()].type == 0) c.reg->writePC(c.reg->readPC() + 1);
	//cout << c.reg->readPC() << "\n";
	//c->reg->write(29, 8 * 1024 * 1024 - 1);
	/*for (int i = 0; i < In.size(); ++i) {
		instruction t = In[i];
		if(In[i].s != "") cout << A.Lab[In[i].s] << "\n";
	}*/
	int i = 0;
	//cout << In.size() << "\n";
	while (true) {
		//++i;
		c.execute();
		//cout << i << "\n";
		/*if (i >= 0) {
			cout << "\n\n\n" << ++i << "\n";
			c.debug();
		}*/
		//cout << "map          " << A.Lab.count(8388603) << "\n";
	//	memory.debug();
	}

	//memory& r
	for (int i = 0; i < Da.size(); ++i) {
		Data t = Da[i];
		cout << t.type << "       " << t.p[0] << "       " << t.p[1] << "       " << t.p[2] << "       " << t.s << "\n";
	}
	cout << "\n\n\n\n\n\n\n" << "\n";
	for (int i = 0; i < In.size(); ++i) {
		instruction t = In[i];
		cout << i << "           i             " << t.type << "       " << t.p[0] << "       " << t.p[1] << "       " << t.p[2] << "       " << t.s << "\n";
	}
/*	M.debug();
	M.space(5);
	M.pos = 16;
	M.debug();
	M.align(3);
	M.debug();
	M.store(8, -1, 1);
	M.debug();
	M.store(9, (1 << 16) - 1, 2);
	M.debug();
	M.store(11, (1 << 31) - 1, 4);
	M.debug();
	int a;
	a = M.load(8, 1);
	cout << "a   -1  " << a << "\n";
	cout << 255 << "\n";
	a = M.load(9, 2);
	cout << "a     " << a << "\n";
	cout << (1 << 16) - 1 << "\n";
	a = M.load(11, 4);
	cout << "a     " << a << "\n";
	cout << (1 << 31) - 1 << "\n";
	cout << "pos       " << M.put_s('a') << "\n";
	M.debug();
	cout << "pos       " << M.put_s('b') << "\n";
	M.debug();
	cout << "pos       " << M.put_s('c') << "\n";
	M.debug();
	cout << "pos       " << M.put_b(123) << "\n";
	M.debug();
	cout << "pos       " << M.put_b(456) << "\n";
	M.debug();
	cout << "pos       " << M.put_b(789) << "\n";
	M.debug();
	cout << "pos       " << M.put_h((1 << 16) - 1) << "\n";
	M.debug();
	cout << "pos       " << M.put_w((1 << 31) - 1) << "\n";
	M.debug();
	cout << "pos       " << M.put_h(123) << "\n";
	M.debug();
	cout << "pos       " << M.put_w(123) << "\n";
	M.debug();
	cout << "pos       " << M.put_h(456) << "\n";
	M.debug();
	cout << "pos       " << M.put_w(456) << "\n";
	M.debug();*/
//	M.store(1, -1, 1);
	//cout << M.load(1, 1) << "\n";
    return 0;
}

