/*****Version 1.1***********/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
using namespace std;

//read data from input file to corresponding variables
//return 1 if successfully done, otherwise return 0
int readFile(const char* filename, int& baseHP1,int& baseHP2,int& wp1,int& wp2,int& ground)
{
	ifstream in;
	in.open(filename);
	
	if (!in.good()) return 0;

	in >> baseHP1;
	in >> wp1;
	in >> baseHP2;
	in >> wp2;
	in >> ground;

	in.close();

	if (baseHP1 < 99 || baseHP1 > 999)
		return 0;
	if (wp1 < 0 || wp1 > 3)
		return 0;
	if (baseHP2 < 1 || baseHP2 > 888)
		return 0;
	if (wp2 < 0 || wp2 > 3)
		return 0;
	if (ground < 1 || ground > 999)
		return 0;

	return 1;

}

// TODO: Your code goes here

float Limit(float &a){ //<=999
	if (a >= 999){
		a = 999;
	}
	return a;
}

int KTsoNT(int a){
	int S = 0;
	for (int i = 1; i <= a; i++){
		if (a%i == 0){
			S = S + 1;
		}
	}
	if (S == 2) return 1;
	return 0;
}

void display(float fOut)
// display value of fOut in format of 0.XX
// no exception handled
{
	if (fOut == 1){
		cout << fOut;
	}
	else{
		char s[10];
		sprintf(s,"%.2f",fOut);
		cout << s;
	}
}


int main(int argc, char** argv)
{
	if (argc < 2) return 1;

	const char* filename = argv[1];
	cout << filename << endl;

	int baseHP1,baseHP2,wp1,wp2,ground;
	float fOut = 0.0;
	readFile(filename, baseHP1, baseHP2, wp1, wp2, ground);
	
	// TODO: Your code goes here
if (baseHP1 == 999){ //define 999,888, wp2vswp2
		fOut = 1;
	}
	else if (baseHP2 == 888){
		fOut = 0;
	}
	else if (KTsoNT(baseHP1) == 1 && KTsoNT(baseHP2) == 1){
		if (baseHP1 == baseHP2){
			fOut = 0.5;
		}
		else if (baseHP1 > baseHP2){
			fOut = 0.99;
		}
		else if (baseHP1 < baseHP2){
			fOut = 0.01;
		}
	}
	else if (KTsoNT(baseHP1) == 1){
		fOut = 0.99;
	}
	else if (KTsoNT(baseHP2) == 1){
		fOut = 0.01;
	}
	else if (wp1 == 2 && wp2 == 2){
		fOut = 0.5;
	}

	else{
		float realHP1 = baseHP1, realHP2 = baseHP2;

		if (wp1 == 1){
			realHP1 = baseHP1;
		}
		if (wp2 == 1){
			realHP2 = baseHP2;
		}
		if (wp1 == 0){
			realHP1 = baseHP1 / 10;
		}
		if (wp2 == 0){
			realHP2 = baseHP2 / 10;
		}
		if (ground == baseHP1){	//iii
			realHP1 = realHP1*1.1;
			realHP1=Limit(realHP1);

		}
		else if (ground == baseHP2){
			realHP2 = realHP2*1.1;
			realHP2 = Limit(realHP2);
		}
		if (wp1 == 3){	//sword
			realHP1 = realHP1 * 2;
			realHP1 = Limit(realHP1);
			if (wp2 == 2){
				wp2 = 1;
			}
		}
		if ((wp1 == 2 && realHP1 < realHP2) || (wp2 == 2 && realHP2 < realHP1)){	//iv, armor
			fOut = 0.5;
			goto label;
		}
		fOut = (realHP1 - realHP2 + 999) / 2000; //sai flow
	}
	label:

	display(fOut);
	return 0;
}
