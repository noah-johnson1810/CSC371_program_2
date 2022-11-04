#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Point
{
	int x;
	int y; 
};


int main(int argc, char **argv) 
{
    ifstream fin;
	ofstream fout;

	if (argc != 2)
	{
		cout << "Missing an Input File" << endl;
		cout << "Args: BisectQuad.exe inputfile.in" << endl;
		return -1;
	}

	string inputFile = argv[1];
	size_t extensionLocation = inputFile.find_last_of(".");
	string outputFile = inputFile.substr(0, extensionLocation) + ".out";

	fin.open(inputFile);
	fout.open(outputFile);

	if (!fin)
	{
		cout << "Input file could not be opened" << endl;
		cout << "Args: BisectQuad.exe inputfile.in" << endl;
		return -2;
	}
	if (!fout)
	{
		cout << "Output file could not be opened" << endl;
		return -3;
	}

	vector<Point> v;

	int lastInput = -2;
	while (lastInput != -1) {
		Point newPoint;
		fin >> newPoint.x;
		fin >> lastInput;
		newPoint.y = lastInput;
		v.push_back(newPoint);
	}
	v.pop_back();

	for (int i = 0; i < v.size(); i++) {
		fout << "x: ";
		fout << v[i].x;
		fout << " y: ";
		fout << v[i].y;
		fout << "\n";
	}
	fin.close();
	fout.close();
}
