#ifndef OCR_H
#define OCR_H


#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "MakePrivatePublic.h"  // only included for testing . it converts the private methods into public

using namespace std;




class OCR
{
public:
	OCR();
	virtual ~OCR();
	void readFile(char* fileName);
private:

	char* line1;
	char* line2;
	char* line3;
	char* line4;
	
	bool isA;
	bool isB;
	bool isC;
	bool isD;
	bool isE;
	bool isF;
	bool isG;

	bool fstLineHasBadData;
	bool secLineHasBadData;
	bool thrLineHasBadData;

	int result[9];
	int resCnt;

	void parseChar();
	void setRes();
	void resetSeg();
	void setLine(char* ch, int lineNum);
	void setLCDSegments(char* fst, char* sec, char* thr);
	bool isValidAccount(const int* acNum) const;// checksum function

	
};








#endif