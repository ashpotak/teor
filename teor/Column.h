#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Column
{
private:
	vector<double> col;
public:
	Column(vector<double> c) { col = c; };
	~Column() {};
};

