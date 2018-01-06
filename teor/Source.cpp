#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "DataSheet.h"
#include "Colomn.h"

using namespace std;

int main()
{
	DataSheet dub("teor_dub.xls");
	for (int i = 0; i < dub.GetCols() - 1; i++)
	{
		Colomn col(dub.GetColumn(i));
		col.calculate(i);
	}
	

	system("pause");
	return 0;
}