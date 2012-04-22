#ifndef PASMECONFIG_H
#define PASMECONFIG_H

class pasmeConfig{
public:
	int argc;
	char** argv;

	int A;
	int B;
	int C;
	int D;

	int tamChave;

	pasmeConfig():A(32),B(16),C(16),D(4),tamChave(64){}

	void set(int a, int b, int c, int d, int e){
		A=a;
		B=b;
		C=c;
		D=d;
		tamChave=e;
	}


};


#endif // PASMECONFIG_H
