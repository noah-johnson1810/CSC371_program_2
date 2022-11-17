#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>

using namespace std;

struct Point
{
    double x;
    double y;
};

bool comparePointsX(Point p1, Point p2)
{
    if (p1.x != p2.x)
        return p1.x < p2.x;
    else
        return p1.y > p2.y;
}

bool comparePointsY(Point p1, Point p2)
{
    if (p1.y != p2.y)
        return p1.y < p2.y;
    else
        return p1.x < p2.x;
}

// this comes from Dr. Corwin's D2L link, modified to accept vector instead of c-style array
double area(vector<Point> p, int n)
{
    int j;
    double result;

    result = 0;
    for (int i = 0; i < n; i++)
    {
        j = (i + 1) % n;
        result += p[i].x * p[j].y;
        result -= p[i].y * p[j].x;
    }
    return fabs(result / 2);
}


double bisectQuad(vector<Point> v) {
    double totalArea = area(v, 4);
    double leftArea = -1;
    double rightArea = -1;
    double slope, point;
    double minimum, maximum;
    double verticalLineX;

    auto minmax = minmax_element(v.begin(), v.end(), [](Point const& lhs, Point const& rhs) { return lhs.x < rhs.x; });
    minimum = minmax.first->x;
    maximum = minmax.second->x;
    verticalLineX = (maximum + minimum) / 2.0;

    do {
        verticalLineX = (maximum + minimum) / 2.0;
        vector<Point> leftRegion;
        for (int i = 0, j = v.size() - 1; i < v.size(); j = i, i++) {
            if (v[i].x < verticalLineX && v[j].x > verticalLineX || v[i].x > verticalLineX && v[j].x < verticalLineX) {
                slope = (v[j].y - v[i].y) / (v[j].x - v[i].x);
                point = verticalLineX - v[i].x;


                leftRegion.push_back({ verticalLineX, slope * point + v[i].y });
            }

            if (v[i].x <= verticalLineX)
                leftRegion.push_back(v[i]);
        }

        leftArea = area(leftRegion, int(leftRegion.size()));
        if ((totalArea / 2.0) - leftArea > 0.00001)
            minimum = verticalLineX;
        else if ((totalArea / 2.0) - leftArea < -0.00001)
            maximum = verticalLineX;
    } while (abs((totalArea / 2.0) - leftArea) > 0.00001);

    return verticalLineX;
}

int main(int argc, char** argv)
{

    // necessary gross main stuff

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

    bool stop = false;
    int caseCount = 1;

    while (stop == false) {
        vector<Point> v;
        for (int i = 0; i < 4; i++) {
            Point newPoint;
            fin >> newPoint.x;
            fin >> newPoint.y;
            if (newPoint.x == -1 || newPoint.y == -1) {
                stop = true;
                break;
            }
            v.push_back(newPoint);
        }
        if (stop == true)
            break;
        double verticalLineXCoordinate = bisectQuad(v);
        // change to file output
        cout << "Case " << caseCount << ": " << fixed << setprecision(5) << verticalLineXCoordinate << "\n";
        v.clear();
        caseCount += 1;
    }
    fin.close();
    fout.close();
}