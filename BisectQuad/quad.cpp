#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

struct Point
{
    double x;
    double y;
};

bool comparePoints(Point p1, Point p2)
{
    if (p1.x != p2.x)
        return p1.x < p2.x;
    else
        return p1.y < p2.y;
}

// this function is based on w3schools "find intersection" algorithm
Point findIntersection(Point A, Point B, Point C, Point D)
{
    // Line AB represented as a1x + b1y = c1
    double a1 = B.y - A.y;
    double b1 = A.x - B.x;
    double c1 = a1 * (A.x) + b1 * (A.y);

    // Line CD represented as a2x + b2y = c2
    double a2 = D.y - C.y;
    double b2 = C.x - D.x;
    double c2 = a2 * (C.x) + b2 * (C.y);

    double determinant = a1 * b2 - a2 * b1;

    // parallel lines, shouldn't happen but doesn't hurt to check
    if (determinant == 0)
    {
        Point p;
        p.x = -1;
        p.y = -1;
        return p;
    }
    else
    {
        Point returnPoint;
        returnPoint.x = round((b2 * c1 - b1 * c2) / determinant);
        returnPoint.y = round((a1 * c2 - a2 * c1) / determinant);
        return returnPoint;
    }
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

    double left_area = -1;
    double right_area = -1;
    double verticalLineXCoordinate = v[0].x + ((v[3].x - v[0].x) / 2.0);
    do {
        // TODO: figure out where the vertical line x coordinate should move to each time
        Point topVerticalLine;
        topVerticalLine.x = verticalLineXCoordinate;
        topVerticalLine.y = 1000001;

        Point bottomVerticalLine;
        bottomVerticalLine.x = verticalLineXCoordinate;
        bottomVerticalLine.y = -1;

        Point topIntersection = findIntersection(v[1], v[3], topVerticalLine, bottomVerticalLine);
        Point bottomIntersection = findIntersection(v[0], v[2], topVerticalLine, bottomVerticalLine);

        vector<Point> left_region = { v[0], v[1], topIntersection, bottomIntersection };

        vector<Point> right_region = { topIntersection, bottomIntersection, v[2], v[3] };

        left_area = area(left_region, 4);
        right_area = area(right_region, 4);
    } while (left_area - right_area > 0.0001);
    return verticalLineXCoordinate;
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

    // TODO: loop the next 15 lines until EOF
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
    sort(v.begin(), v.end(), comparePoints);
    double verticalLineXCoordinate = bisectQuad(v);
    // TODO: Format and file output
    cout << verticalLineXCoordinate;


    fin.close();
    fout.close();
}
