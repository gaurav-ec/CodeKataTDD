#include "OCR.h"
#include <CppUTest\TestHarness.h>

#include "OCR.h"

OCR::OCR()
{
	isA = isB = isC = isD = isE = isF = isG = false;
	resCnt = 0;
}

OCR::~OCR()
{}



void OCR::setLine(char* ch, int lineNum)
{
	switch(lineNum)
	{
	case 1:
		line1 = ch;
		break;
	case 2:
		line2 = ch;
		break;
	case 3:
		line3 = ch;
		break;
	case 4:
		line4 = ch;
		break;
	}
}

void OCR::parseChar()
{
	for(int j=0; j<27; j+=3)// 
		{
			setLCDSegments(&line1[j],&line2[j],&line3[j]);
			setRes();
	    }
}

void OCR:: setLCDSegments(char* fst, char* sec, char* thr)
{
	
	if(fst[1]== '_')
	  isA = true;
	else
	  fstLineHasBadData= true; // we are not checking first and third characters for first line

	if(sec[0]== '|')
		isF = true;
	else
		secLineHasBadData = true;

	if(sec[1]=='_')
		isG = true;
	else
		secLineHasBadData = true;

	if(sec[2]=='|')
		isB = true;
	else
		secLineHasBadData = true;

	if(thr[0] =='|')
		isE = true;
	else
	  thrLineHasBadData = true;

	if(thr[1] =='_')
		isD = true;
	else
	thrLineHasBadData = true;
	
	if(thr[2] =='|')
		isC = true;
	else
	thrLineHasBadData = true;

	
}

/*In the following function we are considering that ABCDFFG form a legitimate number and does not have any field wrong or missing*/
	void OCR::setRes()
	{
		if(resCnt > 8)
			resCnt = 0;
		if(isC == false) // result is  2 
		{
				result[resCnt++] = 2;
				resetSeg();
				return;
		}
		
		if(isA == false)// result is either 4 or 1

		{
			if(isF == false)// result is 1 
			{
					result[resCnt++] = 1;
				    resetSeg();
					return;
			}
			if(isF == true)// result is 4 
			{
					result[resCnt++] = 4;
				    resetSeg();
					return;
			}
		}

		if(isB == false)// result is either 5 or 6
		{
			if(isE == true)
			{
				result[resCnt++] = 6;
				resetSeg();
				return;
			}
			if(isE == false)
			{
				result[resCnt++] = 5;
				resetSeg();
				return;
			}
		}

		if(isG == false)// result is either 0 or 1 or 7  The 1 is already being taken care of so we wont worry about it
		{
			if(isD == true)
			{
				result[resCnt++] = 0;
				resetSeg();
				return;
			}
			else
			{
				result[resCnt++] = 7;
				resetSeg();
				return;
			}
		}

		/* following code checks for 8, 9 or 3*/

		if(isE == true)
		{
			result[resCnt++] = 8;
			resetSeg();
			return;
		}
		else if(isF == true)
		{
			result[resCnt++] = 9;
			resetSeg();
			return;
		}
		else
		{
			result[resCnt++] = 3;
			resetSeg();
			return;
		}
	}

	bool OCR::isValidAccount(const int* acNum) const
	{
		int sum = 0;
		for(int j=0, k=9;j<9;j++, k--)
			sum =sum + acNum[j]*k;
		
		if(sum<=0)
			return false;
		if( (sum % 11) == 0)
			return true;
		else
			return false;
	}

	void OCR::resetSeg()
	{
		isA=isB=isC=isD=isE=isF=isG= false;
	}


	void OCR::readFile(char* fileName)
	{
		char fst[28];
		char sec[28];
		char thr[28];
		char frt[2];// since fourth line will be a blank
		ifstream inFile(fileName);
		char ch;// for determining endOfFile
		while(1)
		{
			inFile.get(ch);
			if(!inFile)
				break;
			inFile.putback(ch);
			inFile.getline(fst,28);
			inFile.getline(sec,28);
			inFile.getline(thr,28);
			inFile.getline(frt,2);

			setLine(fst,1);
			setLine(sec,2);
			setLine(thr,3);
			setLine(frt,4);
			parseChar();
		}


	}