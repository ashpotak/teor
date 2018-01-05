#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include  "DataSheet.h"

using namespace std;

int main()
{
	DataSheet dub("teor_dub.xls");
	dub.PrintSquareConsole();


	system("pause");
	return 0;
}