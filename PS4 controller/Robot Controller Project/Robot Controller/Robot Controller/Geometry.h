#ifndef GEOMETRY_H
#define GEOMETRY_H

#define _USE_MATH_DEFINES
#include <iostream>
using namespace std;

typedef double AngRad;  /*!< Type definition for angles in degrees. */
typedef double AngDeg;  /*!< Type definition for angles in radians. */

#define EPSILON 0.0001  /*!< Value used for floating point equality tests. */

AngDeg Rad2Deg(AngRad x);
AngRad Deg2Rad(AngDeg x);

struct VecPosition
{
private:
	double m_x;
	double m_y;
public:
	double getX() const;
	double getY() const;
	bool setX(double dX);
	bool setY(double dX);

	VecPosition(double vx = 0, double vy = 0);

	void setVecPosition(double dX = 0, double dY = 0);

	VecPosition operator - ();
	VecPosition operator + (const double &d);
	VecPosition operator + (const VecPosition &p);
	VecPosition operator - (const double &d);
	VecPosition operator - (const VecPosition &p) const;
	VecPosition operator * (const double &d);
	VecPosition operator * (const VecPosition &p);
	VecPosition operator / (const double &d);
	VecPosition operator / (const VecPosition &p);

	void operator = (const double &d);
	void operator += (const VecPosition &p);
	void operator += (const double &d);
	void operator -= (const VecPosition &p);
	void operator -= (const double &d);
	void operator *= (const VecPosition &p);
	void operator *= (const double &d);
	void operator /= (const VecPosition &p);
	void operator /= (const double &d);
	bool operator != (const VecPosition &p);
	bool operator != (const double &d);
	bool operator == (const VecPosition &p);
	bool operator == (const double &d);

	friend ostream& operator << (ostream &os,VecPosition v);
	double             getMagnitude() const;
	VecPosition        setMagnitude(double            d);
	VecPosition        normalize();
};

#endif // !GEOMETRY_H
