#pragma once
#include <iostream>
#include <vector>
#include "BasicExcel.hpp" //�������� ��� ������ � xls-�������, xlsx �� ���� �� �������

using namespace std;

class DataSheet {
private:
	YExcel::BasicExcel e; //��'���, ���� ���� ��'����� � ����� ��������
	YExcel::BasicExcelWorksheet* sheet1; //��'���, ���� ��'����� � �������� ������ �������
	int maxRows, maxCols, workRows; //����������� ������� ����� �� ������� � ������ ���� �� ������ �-��� ����� (��� �����)
	double **matrix;
public:
	DataSheet(char* fname);
	~DataSheet();

	vector<double> GetColumn(int num);
	void PrintSquareConsole(void);
	int GetCols() { return maxCols; };
};

