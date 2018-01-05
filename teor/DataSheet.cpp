#include "DataSheet.h"

DataSheet::DataSheet(char* fname) {
	e.Load(fname);
	sheet1 = e.GetWorksheet("Sheet1");

	if (sheet1)
	{
		maxRows = sheet1->GetTotalRows();
		maxCols = sheet1->GetTotalCols();
		workRows = maxRows - 3;

		matrix = new double*[workRows];
		for (int i = 0; i < workRows; i++)
		{
			matrix[i] = new double[maxCols];
			for (int j = 0; j < maxCols; j++)
				matrix[i][j] = 0;
		}
	}
	else {
		cout << "File doesn't exist!" << endl;
		return;
	}

	for (int r = 3, i = 0; r < maxRows; ++r, ++i)
	{
		for (int c = 0, j = 0; c < maxCols; ++c, ++j)
		{
			YExcel::BasicExcelCell* cell = sheet1->Cell(r, c);
			matrix[i][j] = cell->GetDouble();
		}
	}
}

DataSheet::~DataSheet() {
	for (int i = 0; i < workRows; i++)
		delete[] matrix[i];
}

//метод, який повертає нам потрібну колонку у вигляді вектору даблів
vector<double> DataSheet::GetColumn(int num) {
	vector<double> column;
	for (int i = 0; i < workRows; i++)
		column.push_back(matrix[i][num]);
	return column;
}

//для перевірки коректності вводу з таблиці виводмо наш DataSheet в консоль
void DataSheet::PrintSquareConsole(void) {
	cout << "Dimension of " << sheet1->GetAnsiSheetName() << " (" << maxRows << ", " << maxCols << ")" << endl;
	for (int c = 0; c<10; ++c) printf("%10d", c + 1);
	cout << endl;

	for (int r = 0; r<workRows; ++r)
	{
		for (int c = 0; c<maxCols; ++c)
			printf("%10.3lf", matrix[r][c]);
		cout << endl;
	}
}







