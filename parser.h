#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<unordered_map>
#include<utility>
#include<fstream>
#include<vector>
#include "instruction.h"

typedef long long LL;

using namespace std;

class parser {

//private:
public:

	int start;
	bool isData;
	unordered_map<string, int> Ins;
	unordered_map<string, int> Reg;
	unordered_map<string, int> isLab;
	unordered_map<string, int> Lab;

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
		if (Reg.count(s)) return pair<string, int>(s, 0);
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
			string t1, t2;
			t1 = t2 = "";
			for (int i = p1; i <= p2; ++i) t1 += s[i];
			for (int i = 0; i < p1 - 1; ++i) t2 += s[i];
			int t = t2 == "" ? 0 : toInt(t2);
			return pair<string, int>(t1, t);
		}
	}

	void deal(vector<instruction> &In, vector<Data> &Da, const string &s0, const string &s1, const string &s2, const string &s3) {

		switch (Ins[s0]) {

		case 1: Da.push_back(Data(1, "", toInt(s1)));
			break;

		case 2: {
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

		case 3: {
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
			isData = true;
			break;

		case 9:
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
			In.push_back(instruction(51, "", Reg[s1]));
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
			if (isLab[s2]) In.push_back(instruction(60, s2, Reg[s1]));
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
			if (isData) Da.push_back(Data(0, s0));
			else In.push_back(instruction(0, s0));
		}
	}

public:
	parser() {
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

	void work(Memory &memory, vector<instruction> &In, vector<Data> &Da, const string &s) {
		isData = false;
		string str;
		ifstream infile;
		infile.open(s, ios::in);
		int i = 0;
		while (!infile.eof()) {
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
			if (!len) continue;
			while (str[pos] == '	' || str[pos] == ' ') ++pos;
			if (pos > len) continue;
			for (int i = 0; i < len; ++i) {
				if (str[i] == ':' && str[i - 1] != '"' && (str[i - 1] != 'l' || str[i - 2] != 'a')) {
					for (int j = pos; j < i; ++j) s0 += str[j];
					break;
				}
			}
			if (s0 != "") {
				deal(In, Da, s0, s1, s2, s3);
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
			deal(In, Da, s0, s1, s2, s3);
		}
		vector<int> Pos;
		int l = Da.size();
		Pos.resize(l);
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
				for (int i = 0; i < len; ++i) memory.put_s(t.s[i]);
				break;
			}

			case 3: {
				int len = strlen(t.s.c_str());
				Pos[i] = memory.pos;
				for (int i = 0; i < len; ++i) memory.put_s(t.s[i]);
				memory.put_s('\0');
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

		int len = In.size();
		for (int i = 0; i < len; ++i) if (In[i].type == 0 && In[i].s[0] == 'm' && In[i].s[1] == 'a') start = i + 1;
	}
};
