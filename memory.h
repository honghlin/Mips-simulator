#include<iostream>

const int pow8 = (1 << 8) - 1;

class Memory {
	
public :

	int pos;
	unsigned char data[8 * 1024 * 1024];

public :

	Memory() : pos(0) {}

	int load(const int &p, const int &op) {	
		int a = (int)data[p];
		for (int i = 1; i < op; ++i) a = (a << 8) + (int)data[p + i];
		return a;
	}

	void store(const int &p, const int &a, const int &op) {
		if (op == 1) data[p] = a;
		else if (op == 2) {
			int t1 = a & pow8;
			int t2 = a >> 8;
			data[p] = t2;
			data[p + 1] = t1;
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
		return t;
	}
	
};
