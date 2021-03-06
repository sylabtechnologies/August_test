// https://www.hackerrank.com/challenges/3d-surface-area/problem
//
// Point z upward
// Optimize later
// Use - as distance operator

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void process_error(const char* msg)
{
	cerr << "Terminate:" << endl;
	cerr << msg << endl;
	exit(EXIT_FAILURE);
}

class Point
{
public:
	Point(int t1, int t2, int t3) : x(t1), y(t2), z(t3) {}
	bool operator==(const Point &rhs) const { return (this->x == rhs.x) && (this->y == rhs.y) && (this->z == rhs.z); }
	int operator-(const Point &rhs) const;
	void growup() { z += 1; }
private:
	int x, y, z;
};

// Use - as distance operator & perform the neighbor check
int Point::operator-(const Point &rhs) const
{
	Point p = rhs;

	p.x = rhs.x + 1; if (p == *this) return 1;
	p.x = rhs.x - 1; if (p == *this) return 1;
	p.x = rhs.x;

	p.y = rhs.y + 1; if (p == *this) return 1;
	p.y = rhs.y - 1; if (p == *this) return 1;
	p.y = rhs.y;

	p.z = rhs.z + 1; if (p == *this) return 1;
	p.z = rhs.z - 1; if (p == *this) return 1;

	return INT_MAX;
}

class OneSquare
{
public:
	OneSquare(const Point&, const Point&, const Point&, const Point&);
	~OneSquare() {}
	void growup() { for (size_t i = 0; i < points.size(); i++) points.at(i).growup(); }
	const Point& operator[] (int index) const;
	bool operator== (const OneSquare&) const;

private:
	vector<Point> points;
};

OneSquare::OneSquare(const Point &p1, const Point &p2, const Point &p3, const Point &p4)
{
	if (p1 - p2 != 1) process_error("invalid distance");
	if (p2 - p3 != 1) process_error("invalid distance");
	if (p3 - p4 != 1) process_error("invalid distance");
	if (p4 - p1 != 1) process_error("invalid distance");

    points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	points.push_back(p4);
}

// use in try block
const Point& OneSquare::operator[] (int index) const
{
	return points.at(index);
}

bool OneSquare::operator== (const OneSquare &sq) const
{
	auto iter = std::find(points.begin(), points.end(), sq[0]);
	if (iter == points.end()) return false;

	iter = std::find(points.begin(), points.end(), sq[1]);
	if (iter == points.end()) return false;

	iter = std::find(points.begin(), points.end(), sq[2]);
	if (iter == points.end()) return false;

	iter = std::find(points.begin(), points.end(), sq[3]);
	if (iter == points.end()) return false;

	return true;
}

class SurfaceArea
{
public:
	SurfaceArea() {}
	~SurfaceArea() {}
	size_t size() const { return surface.size(); }
	void add_cube(const OneSquare&);

private:
	void add_to_surface(const OneSquare&);

private:
	vector<OneSquare> surface;
};

void SurfaceArea::add_cube(const OneSquare &sq1)
{
	add_to_surface(sq1);

	try {
		Point p1 = sq1[0];
		Point p2 = sq1[1];
		Point p3 = sq1[2];
		Point p4 = sq1[3];

		Point p5 = p1; p5.growup();
		Point p6 = p2; p6.growup();
		Point p7 = p3; p7.growup();
		Point p8 = p4; p8.growup();

		OneSquare sq2(p1, p2, p6, p5);
		add_to_surface(sq2);

		OneSquare sq3(p2, p3, p7, p6);
		add_to_surface(sq3);

		OneSquare sq4(p3, p4, p8, p7);
		add_to_surface(sq4);

		OneSquare sq5(p4, p1, p5, p8);
		add_to_surface(sq5);

		OneSquare sq6 = sq1;

		sq6.growup();
		add_to_surface(sq6);
	}
	catch (const std::out_of_range &ex) {
		string msg = "out of range: ";
		msg += ex.what();
		process_error( msg.c_str());
	}

}

// definitely optimise with conic sections hash
void SurfaceArea::add_to_surface(const OneSquare &sq)
{
	for (auto iter = surface.begin(); iter != surface.end(); ++iter)
	{
		if (*iter == sq)
		{
			surface.erase(iter);
			return;
		}
	}

	// aint there
	surface.push_back(sq);

}



int main()
{
	const size_t LENGTH= 3;
	const size_t DEPTH = 3;

	vector<vector<OneSquare>> mybase;

	// create base of squares
	for (size_t i = 0; i < LENGTH; i++)
	{
		vector<OneSquare> myrow;

		for (size_t j = 0; j < DEPTH; j++)
		{
			Point p1(i, j, 0);
			Point p2(i, j+1, 0);
			Point p3(i + 1, j + 1, 0);
			Point p4(i+1, j, 0);
			OneSquare sq(p1, p2, p3, p4);

			myrow.push_back(sq);
		}

		mybase.push_back(myrow);
	}

	// create the structure as vector of squares
	size_t heights[3][3] = { {1, 3, 4}, {2, 2, 3}, {1, 2, 4} };
	SurfaceArea mysurface;

	for (size_t i = 0; i < LENGTH; i++)
	{
		for (size_t j = 0; j < DEPTH; j++)
		{
			OneSquare sq = mybase[i][j];
			for (size_t k = 0; k < heights[i][j]; k++)
			{
				mysurface.add_cube(sq);
				sq.growup();
			}
		}
	}

	cout << "Surface area = " << mysurface.size() << endl;

    return 0;
}

