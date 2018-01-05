#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include  "DataSheet.h"
#include "Column.h"

using namespace std;

int main()
{
	DataSheet dub("teor_dub.xls");
	dub.PrintSquareConsole();

	Column col(dub.GetColumn(0));

	system("pause");
	return 0;
}