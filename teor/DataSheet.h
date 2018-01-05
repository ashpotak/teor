#pragma once
#include <iostream>
#include <vector>
#include "BasicExcel.hpp" //бібліотека для роботи з xls-файлами, xlsx на жаль не підтримує

using namespace std;

class DataSheet {
private:
	YExcel::BasicExcel e; //об'єкт, який потім зв'язуємо з нашою таблицею
	YExcel::BasicExcelWorksheet* sheet1; //об'єкт, який зв'язуємо з потрібним листом таблиці
	int maxRows, maxCols, workRows; //максимальна кількість рядків та колонок у нашому листі та робоча к-сть рядків (без шапки)
	double **matrix;
public:
	DataSheet(char* fname);
	~DataSheet();

	vector<double> GetColumn(int num);
	void PrintSquareConsole(void);
};

