#include "RSHelper.h"
#include <stdio.h>
#include <iostream>
using namespace std;

class handsome : public RSHelper<handsome, 8> {
public:
	handsome(int a = 0) {
		i = a;
	}
	int i;
};

int main() {
	handsome* hs[13];
	for (int i = 0; i < 13; ++i) {
		hs[i] = new handsome(i);
	}
	cout << "----------------------------------------------------------" << endl;

	for (int i = 12; i >= 0; --i) {
		delete hs[i];
	}
}