#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "BasicExcel.hpp"
#include "Interval.h"

using namespace std;

class Colomn {
private:
	vector<double> dataColomn;
	vector<Interval> interval;
public:
	Colomn(vector<double> vect) { dataColomn = vect; };

	void show() {
		for (int i = 0; i < dataColomn.size(); i++)
			cout << dataColomn[i] << endl;
	}

	void calculate(int index) {
		double min = dataColomn[0];
		double max = dataColomn[0];
		vector<double> number;
		vector<double> freqvency;
		vector<double> relativeFeqvency;

		number.insert(number.end(), dataColomn[0]); // set first element
		freqvency.insert(freqvency.end(), 0);  // set first element
		relativeFeqvency.insert(relativeFeqvency.end(), 0);  // set first element

		for (int i = 0; i < dataColomn.size(); i++) {
			/// min
			if (dataColomn[i] < min) {
				min = dataColomn[i];
			}

			///max
			if (dataColomn[i] > max) {
				max = dataColomn[i];
			}
		}
		// addElement
		int n = 0;
		for (int i = 0; i < dataColomn.size(); i++) {
			for (n = 0; n < number.size(); n++) {
				if (number[n] == dataColomn[i]) {
					break;
				}
			}
			if (n == number.size()) {
				number.insert(number.end(), dataColomn[i]);
				freqvency.insert(freqvency.end(), 0);
				relativeFeqvency.insert(relativeFeqvency.end(), 0);
			}
		}
		// freqvency
		for (n = 0; n < number.size(); n++) {
			for (int i = 0; i < dataColomn.size(); i++) {
				if (dataColomn[i] == number[n]) {
					freqvency[n] += 1;
				}
			}
		}
		//Relativefrequency
		for (n = 0; n < relativeFeqvency.size(); n++) {
			relativeFeqvency[n] = freqvency[n] / double(dataColomn.size());
		}

		// step
		float h = (max - min) / (1 + 3.2* log(dataColomn.size()));
		//cout << "h = " << h << ", n = " << dataColomn.size() << endl;

		//interval
		int countInterval = ceil(1 + 3.2* log(dataColomn.size()));
		for (int i = 0; i < countInterval; i++) {
			interval.insert(interval.end(), Interval(min + h*i, min + h*(i + 1)));
		}

		//frequency for interval
		for (n = 0; n < countInterval; n++) {
			//cout << "\nBegin = " << interval[n].begin() << "  End = " << interval[n].end() << endl;
			for (int i = 0; i < dataColomn.size(); i++) {
				\
					if ((dataColomn[i] >= interval[n].begin()) && (dataColomn[i] < interval[n].end())) {
						interval[n].addFrequency(1);
					}
			}
		}
		//Relative frequency for interval
		for (n = 0; n < countInterval; n++) {
			interval[n].setRelativeFrequency(interval[n].frequency() / double(dataColomn.size()));
		}

		//Mathematical expectation
		double mathExpectation = 0;
		for (int i = 0; i < relativeFeqvency.size(); i++) {
			mathExpectation += number[i] * relativeFeqvency[i];
		}
		//mathExpectation = double(1 / double((number.size() - 1))) * mathExpectation;

		//average deviation
		double averageDeviation = 0;
		for (int i = 0; i < relativeFeqvency.size(); i++) {
			averageDeviation += pow((number[i] - mathExpectation), 2)*relativeFeqvency[i];
		}
		averageDeviation = double(1 / double((number.size() - 1))) * averageDeviation;

		//dispersion
		double dispersion = 0;
		double squareMathExpectation = 0;
		for (int i = 0; i < relativeFeqvency.size(); i++) {
			squareMathExpectation += pow(dataColomn[i], 2)*relativeFeqvency[i];
		}
		dispersion = squareMathExpectation - pow(mathExpectation, 2);

		//asymmetry
		double asymmetry = 0;
		for (int i = 0; i < relativeFeqvency.size(); i++) {
			asymmetry += pow(dataColomn[i], 3)*relativeFeqvency[i];
		}
		asymmetry = 1 / (pow(sqrt(mathExpectation), 3))* asymmetry;

		//excess
		double excess = 0;
		for (int i = 0; i < relativeFeqvency.size(); i++) {
			excess += pow(dataColomn[i], 4)*relativeFeqvency[i];
		}
		excess = (1 / (pow(sqrt(mathExpectation), 4))* excess) - 3;

		//D(As)
		double D_As = 0;
		double k = dataColomn.size();
		D_As = sqrt((6 * (k - 1)) / ((k + 1) * (k + 3)));

		//D(Es)
		double D_Es = 0;
		k = dataColomn.size();
		D_Es = sqrt((24 * k * (k - 2)* (k - 3)* (k - 5)) / (pow((k - 1), 2) * (k + 3)* (k + 5)));


		string result("");
		if (abs(asymmetry) <= 3 * D_As && abs(excess) <= 5 * D_Es) {
			cout << "True " << endl;
			result += "Normal";
		}
		else {
			cout << "False " << endl;
			result = "Innormal";
		}


		//cout << "mathExpectation = " << mathExpectation << endl;
		//cout << "averageDeviation = " << averageDeviation << endl;
		//cout << "dispersion = " << dispersion << endl;
		//cout << "asymmetry = " << asymmetry << endl;
		//cout << "excess = " << excess << endl;

		////
		//cout << "\nNumbers \t| ";
		//for (int i = 0; i < number.size(); i++) {
		//	cout << number[i] << " \t| ";
		//}
		//cout << "\nFrequvency \t| ";
		//for (int i = 0; i < freqvency.size(); i++) {
		//	cout << freqvency[i] << " \t| ";
		//}
		//cout << "\nRelFreq \t| ";
		//for (int i = 0; i < relativeFeqvency.size(); i++) {
		//	cout.precision(2);
		//	cout << relativeFeqvency[i] << " \t| ";
		//}
		//cout << "\n\nInterval \t| ";
		//for (int i = 0; i < countInterval; i++) {
		//	cout.precision(2);
		//	cout << "[" << interval[i].begin() << ",";
		//	cout.precision(2);
		//	cout << interval[i].end() << ") | ";
		//}
		//cout << "\nFrequvency \t| ";
		//for (int i = 0; i < countInterval; i++) {
		//	cout << interval[i].frequency() << " \t| ";
		//}
		//cout << "\nRelFrequvency \t| ";
		//for (int i = 0; i < countInterval; i++) {
		//	cout.precision(5);
		//	cout << interval[i].relativeFrequency() << " \t| ";
		//}

		YExcel::BasicExcel e;
		e.Load("Result_dub.xls");
		YExcel::BasicExcelWorksheet* sheet = e.GetWorksheet(e.GetAnsiSheetName(index));
		YExcel::BasicExcelCell* cell;

		int Row = sheet->GetTotalRows();
		int Col = sheet->GetTotalCols();
		for (int i = 0; i < Row; i++)
			for (int j = 0; j < Col; j++)
				sheet->EraseCell(i, j);

		if (sheet) {
			sheet->Cell(0, 0)->SetString("Column");
			sheet->Cell(0, 1)->SetInteger(index + 1);
			sheet->Cell(1, 0)->SetString("h");
			sheet->Cell(1, 1)->SetDouble(h);
			sheet->Cell(1, 2)->SetString("n");
			sheet->Cell(1, 3)->SetDouble(dataColomn.size());
			sheet->Cell(2, 0)->SetString("mathExpectation");
			sheet->Cell(2, 1)->SetDouble(mathExpectation);
			sheet->Cell(3, 0)->SetString("averageDeviation");
			sheet->Cell(3, 1)->SetDouble(averageDeviation);
			sheet->Cell(4, 0)->SetString("dispersion");
			sheet->Cell(4, 1)->SetDouble(dispersion);
			sheet->Cell(5, 0)->SetString("asymmetry");
			sheet->Cell(5, 1)->SetDouble(asymmetry);
			sheet->Cell(6, 0)->SetString("excess");
			sheet->Cell(6, 1)->SetDouble(excess);

			sheet->Cell(8, 0)->SetString("Numbers");
			for (int i = 0, Col = 1; i < number.size(); i++, Col++)
				sheet->Cell(8, Col)->SetDouble(number[i]);

			sheet->Cell(9, 0)->SetString("Frequvency");
			for (int i = 0, Col = 1; i < freqvency.size(); i++, Col++)
				sheet->Cell(9, Col)->SetDouble(freqvency[i]);

			sheet->Cell(10, 0)->SetString("RelFreq");
			for (int i = 0, Col = 1; i < relativeFeqvency.size(); i++, Col++)
				sheet->Cell(10, Col)->SetDouble(relativeFeqvency[i]);

			string inter("");

			sheet->Cell(12, 0)->SetString("Interval");
			for (int i = 0, Col = 1; i < countInterval; i++, Col++) {
				inter += "[";
				inter += to_string(interval[i].begin());
				inter += ",";
				inter += to_string(interval[i].end());
				inter += ")";
				sheet->Cell(12, Col)->SetString(inter.c_str());
				inter.clear();
			}

			sheet->Cell(13, 0)->SetString("Frequvency");
			for (int i = 0, Col = 1; i < countInterval; i++, Col++)
				sheet->Cell(13, Col)->SetDouble(interval[i].frequency());

			sheet->Cell(14, 0)->SetString("RelFrequvency");
			for (int i = 0, Col = 1; i < countInterval; i++, Col++)
				sheet->Cell(14, Col)->SetDouble(interval[i].relativeFrequency());

			sheet->Cell(16, 0)->SetString("Result");
			sheet->Cell(16, 1)->SetString(result.c_str());

			e.Save();
		}
	}

	
};

