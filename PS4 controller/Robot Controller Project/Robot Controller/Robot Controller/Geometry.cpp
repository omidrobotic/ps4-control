#include "Geometry.h"
#include <iostream>
#include <math.h>
/*! Constructor for the VecPosition class. When the supplied
Coordinate System type equals CARTESIAN, the arguments x and y
denote the x- and y-coordinates of the new position. When it
equals POLAR however, the arguments x and y denote the polar
coordinates of the new position; in this case x is thus equal to
the distance r from the origin and y is equal to the angle phi
that the polar vector makes with the x-axis.
\param x the x-coordinate of the new position when cs == CARTESIAN; the
distance of the new position from the origin when cs = POLAR
\param y the y-coordinate of the new position when cs = CARTESIAN; the
angle that the polar vector makes with the x-axis when cs = POLAR
\param cs a CoordSystemT indicating whether x and y denote cartesian
coordinates or polar coordinates
\return the VecPosition corresponding to the given arguments */
VecPosition::VecPosition(double x, double y)
{
	setVecPosition(x, y);
}

void VecPosition::setVecPosition(double dX, double dY)
{
		m_x = dX;
		m_y = dY;
}
/*! Overloaded version of unary minus operator for VecPositions. It returns the
negative VecPosition, i.e. both the x- and y-coordinates are multiplied by
-1. The current VecPosition itself is left unchanged.
\return a negated version of the current VecPosition */
VecPosition VecPosition::operator - ()
{
	return (VecPosition(-m_x, -m_y));
}

/*! Overloaded version of the binary plus operator for adding a given double
value to a VecPosition. The double value is added to both the x- and
y-coordinates of the current VecPosition. The current VecPosition itself is
left unchanged.
\param d a double value which has to be added to both the x- and
y-coordinates of the current VecPosition
\return the result of adding the given double value to the current
VecPosition */
VecPosition VecPosition::operator + (const double &d)
{
	return (VecPosition(m_x + d, m_y + d));
}

/*! Overloaded version of the binary plus operator for VecPositions. It returns
the sum of the current VecPosition and the given VecPosition by adding their
x- and y-coordinates. The VecPositions themselves are left unchanged.
\param p a VecPosition
\return the sum of the current VecPosition and the given VecPosition */
VecPosition VecPosition::operator + (const VecPosition &p)
{
	return (VecPosition(m_x + p.m_x, m_y + p.m_y));
}

/*! Overloaded version of the binary minus operator for subtracting a
given double value from a VecPosition. The double value is
subtracted from both the x- and y-coordinates of the current
VecPosition. The current VecPosition itself is left unchanged.
\param d a double value which has to be subtracted from both the x- and
y-coordinates of the current VecPosition
\return the result of subtracting the given double value from the current
VecPosition */
VecPosition VecPosition::operator - (const double &d)
{
	return (VecPosition(m_x - d, m_y - d));
}

/*! Overloaded version of the binary minus operator for
VecPositions. It returns the difference between the current
VecPosition and the given VecPosition by subtracting their x- and
y-coordinates. The VecPositions themselves are left unchanged.

\param p a VecPosition
\return the difference between the current VecPosition and the given
VecPosition */
VecPosition VecPosition::operator - (const VecPosition &p) const
{
	return (VecPosition(m_x - p.m_x, m_y - p.m_y));
}

/*! Overloaded version of the multiplication operator for multiplying a
VecPosition by a given double value. Both the x- and y-coordinates of the
current VecPosition are multiplied by this value. The current VecPosition
itself is left unchanged.
\param d the multiplication factor
\return the result of multiplying the current VecPosition by the given
double value */
VecPosition VecPosition::operator * (const double &d)
{
	return (VecPosition(m_x * d, m_y * d));
}

/*! Overloaded version of the multiplication operator for
VecPositions. It returns the product of the current VecPosition
and the given VecPosition by multiplying their x- and
y-coordinates. The VecPositions themselves are left unchanged.

\param p a VecPosition
\return the product of the current VecPosition and the given VecPosition */
VecPosition VecPosition::operator * (const VecPosition &p)
{
	return (VecPosition(m_x * p.m_x, m_y * p.m_y));
}

/*! Overloaded version of the division operator for dividing a
VecPosition by a given double value. Both the x- and y-coordinates
of the current VecPosition are divided by this value. The current
VecPosition itself is left unchanged.

\param d the division factor
\return the result of dividing the current VecPosition by the given double
value */
VecPosition VecPosition::operator / (const double &d)
{
	return (VecPosition(m_x / d, m_y / d));
}

/*! Overloaded version of the division operator for VecPositions. It
returns the quotient of the current VecPosition and the given
VecPosition by dividing their x- and y-coordinates. The
VecPositions themselves are left unchanged.

\param p a VecPosition
\return the quotient of the current VecPosition and the given one */
VecPosition VecPosition::operator / (const VecPosition &p)
{
	return (VecPosition(m_x / p.m_x, m_y / p.m_y));
}

/*! Overloaded version of the assignment operator for assigning a given double
value to both the x- and y-coordinates of the current VecPosition. This
changes the current VecPosition itself.
\param d a double value which has to be assigned to both the x- and
y-coordinates of the current VecPosition */
void VecPosition::operator = (const double &d)
{
	m_x = d;
	m_y = d;
}

/*! Overloaded version of the sum-assignment operator for VecPositions. It
returns the sum of the current VecPosition and the given VecPosition by
adding their x- and y-coordinates. This changes the current VecPosition
itself.
\param p a VecPosition which has to be added to the current VecPosition */
void VecPosition::operator +=(const VecPosition &p)
{
	m_x += p.m_x;
	m_y += p.m_y;
}

/*! Overloaded version of the sum-assignment operator for adding a given double
value to a VecPosition. The double value is added to both the x- and
y-coordinates of the current VecPosition. This changes the current
VecPosition itself.
\param d a double value which has to be added to both the x- and
y-coordinates of the current VecPosition */
void VecPosition::operator += (const double &d)
{
	m_x += d;
	m_y += d;
}

/*! Overloaded version of the difference-assignment operator for
VecPositions.  It returns the difference between the current
VecPosition and the given VecPosition by subtracting their x- and
y-coordinates. This changes the current VecPosition itself.

\param p a VecPosition which has to be subtracted from the current
VecPosition */
void VecPosition::operator -=(const VecPosition &p)
{
	m_x -= p.m_x;
	m_y -= p.m_y;
}

/*! Overloaded version of the difference-assignment operator for
subtracting a given double value from a VecPosition. The double
value is subtracted from both the x- and y-coordinates of the
current VecPosition. This changes the current VecPosition itself.

\param d a double value which has to be subtracted from both the x- and
y-coordinates of the current VecPosition */
void VecPosition::operator -=(const double &d)
{
	m_x -= d;
	m_y -= d;
}

/*! Overloaded version of the multiplication-assignment operator for
VecPositions. It returns the product of the current VecPosition
and the given VecPosition by multiplying their x- and
y-coordinates. This changes the current VecPosition itself.

\param p a VecPosition by which the current VecPosition has to be
multiplied */
void VecPosition::operator *=(const VecPosition &p)
{
	m_x *= p.m_x;
	m_y *= p.m_y;
}

/*! Overloaded version of the multiplication-assignment operator for
multiplying a VecPosition by a given double value. Both the x- and
y-coordinates of the current VecPosition are multiplied by this
value. This changes the current VecPosition itself.

\param d a double value by which both the x- and y-coordinates of the
current VecPosition have to be multiplied */
void VecPosition::operator *=(const double &d)
{
	m_x *= d;
	m_y *= d;
}

/*! Overloaded version of the division-assignment operator for
VecPositions. It returns the quotient of the current VecPosition
and the given VecPosition by dividing their x- and
y-coordinates. This changes the current VecPosition itself.

\param p a VecPosition by which the current VecPosition is divided */
void VecPosition::operator /=(const VecPosition &p)
{
	m_x /= p.m_x;
	m_y /= p.m_y;
}

/*! Overloaded version of the division-assignment operator for
dividing a VecPosition by a given double value. Both the x- and
y-coordinates of the current VecPosition are divided by this
value. This changes the current VecPosition itself.

\param d a double value by which both the x- and y-coordinates of the
current VecPosition have to be divided */
void VecPosition::operator /=(const double &d)
{
	m_x /= d;
	m_y /= d;
}

/*! Overloaded version of the inequality operator for VecPositions. It
determines whether the current VecPosition is unequal to the given
VecPosition by comparing their x- and y-coordinates.

\param p a VecPosition
\return true when either the x- or y-coordinates of the given VecPosition
and the current VecPosition are different; false otherwise */
bool VecPosition::operator !=(const VecPosition &p)
{
	return ((m_x != p.m_x) || (m_y != p.m_y));
}

/*! Overloaded version of the inequality operator for comparing a
VecPosition to a double value. It determines whether either the x-
or y-coordinate of the current VecPosition is unequal to the given
double value.

\param d a double value with which both the x- and y-coordinates of the
current VecPosition have to be compared.
\return true when either the x- or y-coordinate of the current VecPosition
is unequal to the given double value; false otherwise */
bool VecPosition::operator !=(const double &d)
{
	return ((m_x != d) || (m_y != d));
}

/*! Overloaded version of the equality operator for VecPositions. It
determines whether the current VecPosition is equal to the given
VecPosition by comparing their x- and y-coordinates.

\param p a VecPosition
\return true when both the x- and y-coordinates of the given
VecPosition and the current VecPosition are equal; false
otherwise */
bool VecPosition::operator ==(const VecPosition &p)
{
	return ((m_x == p.m_x) && (m_y == p.m_y));
}

/*! Overloaded version of the equality operator for comparing a
VecPosition to a double value. It determines whether both the x-
and y-coordinates of the current VecPosition are equal to the
given double value.

\param d a double value with which both the x- and y-coordinates of the
current VecPosition have to be compared.
\return true when both the x- and y-coordinates of the current VecPosition
are equal to the given double value; false otherwise */
bool VecPosition::operator ==(const double &d)
{
	return ((m_x == d) && (m_y == d));
}

/*! Overloaded version of the C++ output operator for
VecPositions. This operator makes it possible to use VecPositions
in output statements (e.g.  cout << v). The x- and y-coordinates
of the VecPosition are printed in the format (x,y).

\param os output stream to which information should be written
\param v a VecPosition which must be printed
\return output stream containing (x,y) */
ostream& operator << (ostream &os, VecPosition v)
{
	return (os << "( " << v.m_x << ", " << v.m_y << " )");
}

/*! Set method for the x-coordinate of the current VecPosition.

\param dX a double value representing a new x-coordinate
\return a boolean indicating whether the update was successful */
bool VecPosition::setX(double dX)
{
	m_x = dX;
	return (true);
}

/*! Get method for the x-coordinate of the current VecPosition.

\return the x-coordinate of the current VecPosition */
double VecPosition::getX() const
{
	return (m_x);
}

/*! Set method for the y-coordinate of the current VecPosition.

\param dY a double value representing a new y-coordinate
\return a boolean indicating whether the update was successful */
bool VecPosition::setY(double dY)
{
	m_y = dY;
	return (true);
}

/*! Get method for the y-coordinate of the current VecPosition.

\return the y-coordinate of the current VecPosition */
double VecPosition::getY() const
{
	return (m_y);
}

/*! This method determines the magnitude (length) of the vector
corresponding with the current VecPosition using the formula of
Pythagoras.

\return the length of the vector corresponding with the current
VecPosition */
double VecPosition::getMagnitude() const
{
	return (sqrt(m_x * m_x + m_y * m_y));
}

/*! This method adjusts the coordinates of the current VecPosition in
such a way that the magnitude of the corresponding vector equals
the double value which is supplied as an argument. It thus scales
the vector to a given length by multiplying both the x- and
y-coordinates by the quotient of the argument and the current
magnitude. This changes the VecPosition itself.

\param d a double value representing a new magnitude

\return the result of scaling the vector corresponding with the
current VecPosition to the given magnitude thus yielding a
different VecPosition */
VecPosition VecPosition::setMagnitude(double d)
{
	if (getMagnitude() > EPSILON)
		(*this) *= (d / getMagnitude());

	return (*this);
}

/*! This method normalizes a VecPosition by setting the magnitude of
the corresponding vector to 1. This thus changes the VecPosition
itself.

\return the result of normalizing the current VecPosition thus
yielding a different VecPosition */
VecPosition VecPosition::normalize()
{
	return (setMagnitude(1.0));
}

/*! This function converts an angle in radians to the corresponding angle in
degrees.
\param x an angle in radians
\return the corresponding angle in degrees */
AngDeg Rad2Deg(AngRad x)
{
	return (x * 180 / M_PI);
}

/*! This function converts an angle in degrees to the corresponding angle in
radians.
\param x an angle in degrees
\return the corresponding angle in radians */
AngRad Deg2Rad(AngDeg x)
{
	return (x * M_PI / 180);
}