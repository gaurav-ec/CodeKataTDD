#include "OCR.h"
#include <CppUTest\TestHarness.h>

TEST_GROUP(OCR)
{
	OCR obj;
	void writeNumToFile(char* num)
	{
        string fst(""),sec(""),thr("");
		ofstream ofile("OCR.txt");

		while(*num)
		{
			char* tmp= num;		
			for(int j=0;j<9;j++)
			{
				switch(tmp[j])
				{
				case'0':
					fst+=" _ ";
					sec+="| |";   
					thr+="|_|";
					break;

				case'1':
					fst+="   ";
					sec+="  |";   
					thr+="  |";
					break;

				case'2':
					fst+=" _ ";
					sec+=" _|"; 
					thr+="|_ ";
					break;

				case'3':
					fst+=" _ ";
					sec+=" _|";  
					thr+=" _|";
					break;

				case'4':
					fst+="   ";
					sec+="|_|";   
					thr+="  |";
					break;

				case'5':
					fst+=" _ ";
					sec+="|_ ";   
					thr+=" _|";
					break;
				case'6':
					fst+=" _ ";
					sec+="|_ ";  
					thr+="|_|";
					break;
				case'7':
					fst+=" _ ";
					sec+="  |"; 
					thr+="  |";
					break;
				case'8':
					fst+=" _ ";
					sec+="|_|";   
					thr+="|_|";
					break;
				case'9':
					fst+=" _ ";
					sec+="|_|";   
					thr+=" _|";
					break;
				}

			}

			ofile<<fst<<'\n';
			ofile<<sec<<'\n';
			ofile<<thr<<'\n';
			ofile<<""<<'\n';
			fst="";
			sec="";
			thr="";
			num = num+9;
		}

		ofile.close();
	}
};

TEST(OCR, IfSetLineIsWorking)
{
	
	obj.setLine("line1",1);
	obj.setLine("line2",2);
	obj.setLine("line3",3);
	obj.setLine("",4);
	CHECK(obj.line1=="line1");
	CHECK(obj.line2=="line2");
	CHECK(obj.line3=="line3");
	CHECK(obj.line4=="");
};

TEST (OCR, IfSetLCDSegmentFirstLineWorking)
{
	
	obj.setLCDSegments(" _","","");
	CHECK(obj.isA == true);
};

TEST(OCR, IfFirstLineHasBadDataIsDetected)
{
	obj.setLCDSegments("","","");
	CHECK(obj.fstLineHasBadData == true);

	obj.setLCDSegments(" |","","");
	CHECK(obj.fstLineHasBadData == true);


	obj.setLCDSegments(" *","","");
	CHECK(obj.fstLineHasBadData == true);
};

TEST(OCR , IfSetLCDSegmentSecondLineWorking)
{
	obj.setLCDSegments("","|_|","");
	CHECK(obj.isF == true);
	CHECK(obj.isG == true);
	CHECK(obj.isB == true);
};

TEST(OCR, IfSecondLineHasBadData)
{
	obj.setLCDSegments("","","");
	CHECK(obj.secLineHasBadData == true);

	obj.setLCDSegments("","| |","");
	CHECK(obj.secLineHasBadData == true);

	obj.setLCDSegments("","|||","");
	CHECK(obj.secLineHasBadData == true);

	obj.setLCDSegments("","_|_","");
	CHECK(obj.secLineHasBadData == true);

	obj.setLCDSegments("","***","");
	CHECK(obj.secLineHasBadData == true);
};

TEST(OCR , IfSetLCDSegmentThirdLineWorking)
{
	obj.setLCDSegments("","","|_|");
	CHECK(obj.isE == true);
	CHECK(obj.isD == true);
	CHECK(obj.isC == true);
};

TEST(OCR , IfThirdLineHasBadData)
{
	obj.setLCDSegments("","","");
	CHECK(obj.thrLineHasBadData == true);


	obj.setLCDSegments("","","|||");
	CHECK(obj.thrLineHasBadData == true);

	obj.setLCDSegments("","","_|_");
	CHECK(obj.thrLineHasBadData == true);

	obj.setLCDSegments("","","***");
	CHECK(obj.thrLineHasBadData == true);
};

TEST (OCR, IfCheckSumIsWorkingForModOfZero)
{
	int ary[]={0,0,0,0,0,0,0,0,0};
	CHECK(obj.isValidAccount(ary) == false);
};

TEST (OCR, IfCheckSumIsWorking)
{
	int ary[]={3,4,5,8,8,2,8,6,5};
	CHECK(obj.isValidAccount(ary) == true);
}

TEST (OCR, IfCheckSumIsWorkingForWrongAccount)
{
	int ary[]={3,0,5,8,8,2,8,6,5};
	CHECK(obj.isValidAccount(ary) == false);
}

TEST(OCR , IfSetResIsWorkingForTwo)
{
	obj.isA = obj.isB = obj.isD = obj.isE = obj.isG = true;
	obj.isF = obj.isC = false;
	obj.resCnt=0;
	obj.setRes();
	CHECK(obj.result[0]==2);
};



TEST(OCR , IfSetResWorksforOne)
{
	obj.isA = obj.isD= obj.isE = obj.isF = obj.isG = false;
	obj.isB = obj.isC = true;
	obj.resCnt = 0;
	obj.setRes();
	CHECK(obj.result[0] == 1);
};

TEST(OCR , IfSetResWorksForFour)
{
	obj.isA = obj.isD= obj.isE =  false;
    obj.isF = obj.isG =	obj.isB = obj.isC = true;
	obj.resCnt = 0;
	obj.setRes();
	CHECK(obj.result[0] == 4);
};

TEST(OCR ,IfSetResWorksForFive)
{
	obj.isA = obj.isC = obj.isD = obj.isF = obj.isG = true;
	obj.isB = obj.isE = obj.isF = false;
	obj.resCnt = 0;
	obj.setRes();
	CHECK(obj.result[0] == 5);
};

TEST(OCR ,IfSetResWorksForSix)
{
	obj.isA = obj.isC = obj.isD = obj.isE = obj.isF = obj.isG = true;
	obj.isB =  false;
	obj.resCnt = 0;
	obj.setRes();
	CHECK(obj.result[0] == 6);
};

TEST(OCR ,IfSetResWorksForSeven)
{
	obj.isA = obj.isB = obj.isC= true;
	obj.isD = obj.isE = obj.isF = obj.isG  =  false;
	obj.resCnt = 0;
	obj.setRes();
	CHECK(obj.result[0] == 7);
};

TEST(OCR ,IfSetResWorksForZero)
{
	obj.isA = obj.isB = obj.isC= obj.isD= obj.isE= obj.isF=  true;
	obj.isG  =  false;
	obj.resCnt = 0;
	obj.setRes();
	CHECK(obj.result[0] == 0);
};

TEST(OCR ,IfSetResWorksForEight)
{
	obj.isA = obj.isB = obj.isC= obj.isD= obj.isE= obj.isF= obj.isG=  true;
	obj.resCnt = 0;
	obj.setRes();
	CHECK(obj.result[0] == 8);
};

TEST(OCR ,IfSetResWorksForNine)
{
	obj.isA = obj.isB = obj.isC= obj.isD= obj.isF= obj.isG=  true;
	obj.isE = false;
	obj.resCnt = 0;
	obj.setRes();
	CHECK(obj.result[0] == 9);
};

TEST(OCR ,IfSetResWorksForThree)
{
	obj.isA = obj.isB = obj.isC= obj.isD=  obj.isG=  true;
	obj.isE = obj.isF= false;
	obj.resCnt = 0;
	obj.setRes();
	CHECK(obj.result[0] == 3);
};

TEST(OCR , ReadFileTest1)
{
	char num[]="123456789";
	writeNumToFile(num);// will write characters to a file with 9 characters per line and the fourth line blank
	obj.readFile("OCR.txt");
	for(int j = 0;j < 9; j++)
	{
		CHECK(obj.result[j] == (j+1));
	}
};

TEST(OCR , ReadFileTest2)
{
	char num[]="000000000";
	writeNumToFile(num);// will write characters to a file with 9 characters per line and the fourth line blank
	obj.readFile("OCR.txt");
	for(int j = 0;j < 9; j++)
	{
		CHECK(obj.result[j] == 0);
	}
};

TEST(OCR , ReadFileTest3)
{
	char num[]="111111111";
	writeNumToFile(num);// will write characters to a file with 9 characters per line and the fourth line blank
	obj.readFile("OCR.txt");
	for(int j = 0;j < 9; j++)
	{
		CHECK(obj.result[j] == 1);
	}
};

TEST(OCR , ReadFileTest4)
{
	char num[]="222222222";
	writeNumToFile(num);// will write characters to a file with 9 characters per line and the fourth line blank
	obj.readFile("OCR.txt");
	for(int j = 0;j < 9; j++)
	{
		CHECK(obj.result[j] == 2);
	}
};

TEST(OCR , ReadFileTest5)
{
	char num[]="333333333";
	writeNumToFile(num);// will write characters to a file with 9 characters per line and the fourth line blank
	obj.readFile("OCR.txt");
	for(int j = 0;j < 9; j++)
	{
		CHECK(obj.result[j] == 3);
	}
};

TEST(OCR , ReadFileTest6)
{
	char num[]="444444444";
	writeNumToFile(num);// will write characters to a file with 9 characters per line and the fourth line blank
	obj.readFile("OCR.txt");
	for(int j = 0;j < 9; j++)
	{
		CHECK(obj.result[j] == 4);
	}
};

TEST(OCR , ReadFileTest7)
{
	char num[]="555555555";
	writeNumToFile(num);// will write characters to a file with 9 characters per line and the fourth line blank
	obj.readFile("OCR.txt");
	for(int j = 0;j < 9; j++)
	{
		CHECK(obj.result[j] == 5);
	}
};

TEST(OCR , ReadFileTest8)
{
	char num[]="666666666";
	writeNumToFile(num);// will write characters to a file with 9 characters per line and the fourth line blank
	obj.readFile("OCR.txt");
	for(int j = 0;j < 9; j++)
	{
		CHECK(obj.result[j] == 6);
	}
};

TEST(OCR , ReadFileTest9)
{
	char num[]="777777777";
	writeNumToFile(num);// will write characters to a file with 9 characters per line and the fourth line blank
	obj.readFile("OCR.txt");
	for(int j = 0;j < 9; j++)
	{
		CHECK(obj.result[j] == 7);
	}
};

TEST(OCR , ReadFileTest10)
{
	char num[]="888888888";
	writeNumToFile(num);// will write characters to a file with 9 characters per line and the fourth line blank
	obj.readFile("OCR.txt");
	for(int j = 0;j < 9; j++)
	{
		CHECK(obj.result[j] == 8);
	}
};

TEST(OCR , ReadFileTest11)
{
	char num[]="999999999";
	writeNumToFile(num);// will write characters to a file with 9 characters per line and the fourth line blank
	obj.readFile("OCR.txt");
	for(int j = 0;j < 9; j++)
	{
		CHECK(obj.result[j] == 9);
	}
};