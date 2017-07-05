#include<iostream>

using std::cout;

const int pow8 = (1 << 8) - 1;

class Memory {

	struct byte {

		int n;
		char c;

		byte() : n(0), c(0) {}

	};

public :

	int pos;
	unsigned char data[8 * 1024 * 1024];

public :

	Memory() : pos(0) {
		//for (int i = 0; i <= 8 * 1024 * 1024 - 1; ++i) data[i] = '\0';
	}

	int load(const int &p, const int &op) {
		//cout << "   loadp   " << p << "\n";
		//if (op == 1) return p;
		int a = (int)data[p];
		//cout << a << "     ";
		for (int i = 1; i < op; ++i) a = (a << 8) + (int)data[p + i];
		//cout << data[p + i].n << "        ", 
		//cout << "\n";
		//cout << p << "      " << p + 1 << "      " << p + 2 << "       " << p + 3 << "       ";
		//cout << "\n";
		//cout << "   load   " << a << "\n"; 
		return a;
	}

	void store(const int &p, const int &a, const int &op) {
		//cout << "       store       "  <<  op << "          " << a << "\n";
			
		//cout << "   store   " << a << "\n";
		if (op == 1) {
			//cout << a << "aaa    \n";
			data[p] = a;
			//cout << (int)data[p] << "aaaaa    \n";
			//cout << p << "   p   " << "\n";
			//cout << data[p].n << "   p   " << "\n";
			//if (pos < p + 1) pos = p + 1;
		}
		else if (op == 2) {
			int t1 = a & pow8;
			int t2 = a >> 8;
			data[p] = t2;
			data[p + 1] = t1;
			//if (pos < p + 2) pos = p + 2;
		}
		else {
			int t1 = a & pow8;
			int t2 = (a >> 8) & pow8;
			int t3 = (a >> 16) & pow8;
			int t4 = (a >> 24);
			data[p] = t4;
			data[p + 1] = t3;
			data[p + 2] = t2;
			data[p + 3] = t1;
			//if(pos < p + 4) pos = p + 4;
			//cout << t4 << "   " << t3 << "     " << t2 << "     " << t1 << "\n";
			//cout << p << "        " << p + 1 << "       " << p + 2 << "         " << p + 3 << "\n";
		}
		return;
	}

	int put_s(const char &s) {
		int t = pos;
		data[pos++] = s;
		return t;
	}

	int put_b(const int &a) {
		int t = pos;
		data[pos++] = a;
		return t;
	}

	int put_h(const int &a) {
		int t = pos;
		int t1 = a >> 8;
		int t2 = a & pow8;
		data[pos++] = t1;
		data[pos++] = t2;
		return t;
	}

	int put_w(const int &a) {
		int t = pos;
		int t1 = a >> 24;
		int t2 = (a >> 16) & pow8;
		int t3 = (a >> 8) & pow8;
		int t4 = a & pow8;
		data[pos++] = t1;
		data[pos++] = t2;
		data[pos++] = t3;
		data[pos++] = t4;
		//cout << t <<"   post   "<< "\n";
		return t;
	}

	int align(const int &n) {
		int k = 1 << n;
		if (!(pos % k)) return pos;
		int m = pos / k;
		pos = (m + 1) * k;
		return pos;
	}

	int space(const int &n) {
		int t = pos;
		pos += n;
		//cout << pos << "     pos     " << "\n";
		return t;
	}

	void debug() {
		cout << "pos  " << pos << "\n";
		for (int i = 0; i < pos; ++i) cout << i << "   " << (int)data[i]  << "\n";
	}

};
