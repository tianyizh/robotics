#include <assert.h>

#include "Geometry.h"
#include <cstdio>
#include <vector>

Point2D testPoint;

/*! This function returns the sign of a give float.
  1 is positive, -1 is negative
  \param d first parameter
  \return the sign of this float */
int Sign( float d )
{
  return (d>0)?1:-1;
}

/*! This function returns the maximum of two given floats.
  \param d1 first parameter
  \param d2 second parameter
  \return the maximum of these two parameters */
float max( float d1, float d2 )
{
  return (d1>d2)?d1:d2;
}

/*! This function returns the maximum of three given floats.
  \param d1 first parameter
  \param d2 second parameter
  \param d3 second parameter
  \return the maximum of these three parameters */
float max( float d1, float d2, float d3 )
{
  return max(max(d1,d2),d3);
}

/*! This function returns the minimum of two given floats.
  \param d1 first parameter
  \param d2 second parameter
  \return the minimum of these two parameters */
float min( float d1, float d2 )
{
  return (d1<d2)?d1:d2;
}

/*! This function returns the square of the given float.
  \param d1 parameter to be squared
  \return the square of this parameter */
float square( float d1 )
{
  return d1 * d1;
}

/** Crop the value to within minval, maxval */
float crop ( float val, float minval, float maxval){
  return minmax(minval, val, maxval);
}


/**
 * Function that finds the minmax of three values, x, min limit and
 * max limit...
 */
float minmax( float minx, float x, float maxx ) {
  return( min( max( minx, x ), maxx ) );
}


/**
 * Function that finds the minmax of three Point2Ds, x, min limit and
 * max limit...
 */
Point2D minmax( Point2D minP, Point2D P, Point2D maxP ) {
  Point2D tempP(0, 0);
  tempP.setX( minmax( minP.getX(), P.getX(), maxP.getX() ) );
  tempP.setY( minmax( minP.getY(), P.getY(), maxP.getY() ) );

  return tempP;
}


bool notANumber( float num ) {
  return( std::isnan(num) );
}


/*! This function returns the rounded value of a give float.  
  \param d is the input number which is float
  \returns the rounded value of d which is an int */
int Round( float d ) {
  if ( !finite(d) )
    return (int)(-1.0E10);
  else if( d > 0 )
    return (int)( d + 0.5 );
  else
    return (int)( d - 0.5 );
}


int Floor( float d ) {
 if( !finite(d) )
    return (int)(-1.0E10);
 else
   return (int)d;
}


/*! This function converts an angle in radians to the corresponding angle in
  degrees.
  \param ang an angle in radians
  \return the corresponding angle in degrees */
AngDeg Rad2Deg( AngRad ang )
{
  return ( ang * RAD_T_DEG );
}

/*! This function converts an angle in degrees to the corresponding angle in
  radians.
  \param ang an angle in degrees
  \return the corresponding angle in radians */
AngRad Deg2Rad( AngDeg ang )
{
  return ( ang * DEG_T_RAD );
}


/*! This function returns a boolean value which indicates whether the value
  'ang' (from interval [-2PI..2PI] lies in the interval [angMin..angMax].
  Examples: isAngInInterval( -100, 4, -150) returns false
  isAngInInterval(   45, 4, -150) returns true
  \param ang angle that should be checked
  \param angMin minimum angle in interval
  \param angMax maximum angle in interval
  \return boolean indicating whether ang lies in [angMin..angMax] */
bool isAngInInterval( AngRad ang, AngRad angMin, AngRad angMax )
{
  // convert all angles to interval 0..TWOPI
  if ( ( ang    + TWOPI ) < TWOPI ) ang    += TWOPI;
  if ( ( angMin + TWOPI ) < TWOPI ) angMin += TWOPI;
  if ( ( angMax + TWOPI ) < TWOPI ) angMax += TWOPI;

  if ( angMin < angMax ) 
    return angMin < ang && ang < angMax ;
  else                  
    return !( angMax < ang && ang < angMin );
}

/*! This method returns the bisector (average) of two angles. It deals
  with the boundary problem, thus when 'angMin' equals 170 and 'angMax'
  equals -100, -145 is returned.
  \param angMin minimum angle [-pi,pi]
  \param angMax maximum angle [-pi,pi]
  \return average of angMin and angMax. */
AngRad getBisectorTwoAngles( AngRad angMin, AngRad angMax )
{
  // separate sine and cosine part to circumvent boundary problem
  return normalizeAngle(atan2f( (sinf( angMin) + sinf( angMax ) )/2.0,
			       (cosf( angMin) + cosf( angMax ) )/2.0 ) );
}


/*****************/
/* Class Point2D */
/*****************/
Point2D::Point2D( float xx, float yy, CoordSystemT cs ) {
  setPoint( xx, yy, cs );
}

/*! Overloaded version of unary minus operator for Point2Ds. It returns the
  negative Point2D, i.e. both the x- and y-coordinates are multiplied by
  -1. The current Point2D itself is left unchanged.
  \return a negated version of the current Point2D */
Point2D Point2D::operator - () const
{
  return ( Point2D( -x, -y ) );
}

/*! Overloaded version of the binary plus operator for adding a given float
  value to a Point2D. The float value is added to both the x- and
  y-coordinates of the current Point2D. The current Point2D itself is
  left unchanged.
  \param d a float value which has to be added to both the x- and
  y-coordinates of the current Point2D
  \return the result of adding the given float value to the current
  Point2D */
Point2D Point2D::operator + ( const float &d ) const
{
  return ( Point2D( x + d, y + d ) );
}

/*! Overloaded version of the binary plus operator for Point2Ds. It returns
  the sum of the current Point2D and the given Point2D by adding their
  x- and y-coordinates. The Point2Ds themselves are left unchanged.
  \param p a Point2D
  \return the sum of the current Point2D and the given Point2D */
Point2D Point2D::operator + ( const Point2D &p ) const
{
  return ( Point2D( x + p.x, y + p.y ) );
}

/*! Overloaded version of the binary minus operator for subtracting a given
  float value from a Point2D. The float value is subtracted from both
  the x- and y-coordinates of the current Point2D. The current Point2D
  itself is left unchanged.
  \param d a float value which has to be subtracted from both the x- and
  y-coordinates of the current Point2D
  \return the result of subtracting the given float value from the current
  Point2D */
Point2D Point2D::operator - ( const float &d ) const
{
  return ( Point2D( x - d, y - d ) );
}

/*! Overloaded version of the binary minus operator for Point2Ds. It returns
  the difference between the current Point2D and the given Point2D by
  subtracting their x- and y-coordinates. The Point2Ds themselves are left
  unchanged.
  \param p a Point2D
  \return the difference between the current Point2D and the given
  Point2D */
Point2D Point2D::operator - ( const Point2D &p ) const
{
  return ( Point2D( x - p.x, y - p.y ) );
}

/*! Overloaded version of the multiplication operator for multiplying a
  Point2D by a given float value. Both the x- and y-coordinates of the
  current Point2D are multiplied by this value. The current Point2D
  itself is left unchanged.
  \param d the multiplication factor
  \return the result of multiplying the current Point2D by the given
  float value */
Point2D Point2D::operator * ( const float &d ) const
{
  return ( Point2D( x * d, y * d  ) );
}

/*! Overloaded version of the multiplication operator for Point2Ds. It
  returns the product of the current Point2D and the given Point2D by
  multiplying their x- and y-coordinates. The Point2Ds themselves are left
  unchanged.
  \param p a Point2D
  \return the product of the current Point2D and the given Point2D */
Point2D Point2D::operator * ( const Point2D &p ) const
{
  return ( Point2D( x * p.x, y * p.y ) );
}

/*! Overloaded version of the division operator for dividing a Point2D by a
  given float value. Both the x- and y-coordinates of the current Point2D
  are divided by this value. The current Point2D itself is left unchanged.
  \param d the division factor
  \return the result of dividing the current Point2D by the given float
  value */
Point2D Point2D::operator / ( const float &d ) const
{
  return ( Point2D( x / d, y / d  ) );
}

/*! Overloaded version of the division operator for Point2Ds. It returns the
  quotient of the current Point2D and the given Point2D by dividing
  their x- and y-coordinates. The Point2Ds themselves are left unchanged.
  \param p a Point2D
  \return the quotient of the current Point2D and the given Point2D */
Point2D Point2D::operator / ( const Point2D &p ) const
{
  return ( Point2D( x / p.x, y / p.y ) );
}

/*! Overloaded version of the assignment operator for assigning a given float
  value to both the x- and y-coordinates of the current Point2D. This
  changes the current Point2D itself.
  \param d a float value which has to be assigned to both the x- and
  y-coordinates of the current Point2D */
void Point2D::operator = ( const float &d )
{
  x = d;
  y = d;
}

/*! Overloaded version of the sum-assignment operator for Point2Ds. It
  returns the sum of the current Point2D and the given Point2D by
  adding their x- and y-coordinates. This changes the current Point2D
  itself.
  \param p a Point2D which has to be added to the current Point2D */
void Point2D::operator +=( const Point2D &p )
{
  x += p.x;
  y += p.y;
}

/*! Overloaded version of the sum-assignment operator for adding a given float
  value to a Point2D. The float value is added to both the x- and
  y-coordinates of the current Point2D. This changes the current
  Point2D itself.
  \param d a float value which has to be added to both the x- and
  y-coordinates of the current Point2D */
void Point2D::operator += ( const float &d )
{
  x += d;
  y += d;
}

/*! Overloaded version of the difference-assignment operator for Point2Ds.
  It returns the difference between the current Point2D and the given
  Point2D by subtracting their x- and y-coordinates. This changes the
  current Point2D itself.
  \param p a Point2D which has to be subtracted from the current
  Point2D */
void Point2D::operator -=( const Point2D &p )
{
  x -= p.x;
  y -= p.y;
}

/*! Overloaded version of the difference-assignment operator for subtracting a
  given float value from a Point2D. The float value is subtracted from
  both the x- and y-coordinates of the current Point2D. This changes the
  current Point2D itself.
  \param d a float value which has to be subtracted from both the x- and
  y-coordinates of the current Point2D */
void Point2D::operator -=( const float &d )
{
  x -= d;
  y -= d;
}

/*! Overloaded version of the multiplication-assignment operator for
  Point2Ds. It returns the product of the current Point2D and the
  given Point2D by multiplying their x- and y-coordinates. This changes
  the current Point2D itself.
  \param p a Point2D by which the current Point2D has to be
  multiplied */
void Point2D::operator *=( const Point2D &p )
{
  x *= p.x;
  y *= p.y;
}

/*! Overloaded version of the multiplication-assignment operator for multiplying
  a Point2D by a given float value. Both the x- and y-coordinates of the
  current Point2D are multiplied by this value. This changes the current
  Point2D itself.
  \param d a float value by which both the x- and y-coordinates of the
  current Point2D have to be multiplied */
void Point2D::operator *=( const float &d )
{
  x *= d;
  y *= d;
}

/*! Overloaded version of the division-assignment operator for Point2Ds. It
  returns the quotient of the current Point2D and the given Point2D by
  dividing their x- and y-coordinates. This changes the current Point2D
  itself.
  \param p a Point2D by which the current Point2D has to be divided */
void Point2D::operator /=( const Point2D &p )
{
  x /= p.x;
  y /= p.y;
}

/*! Overloaded version of the division-assignment operator for dividing a
  Point2D by a given float value. Both the x- and y-coordinates of the
  current Point2D are divided by this value. This changes the current
  Point2D itself.
  \param d a float value by which both the x- and y-coordinates of the
  current Point2D have to be divided */
void Point2D::operator /=( const float &d )
{
  x /= d;
  y /= d;
}

/*! Overloaded version of the inequality operator for Point2Ds. It
  determines whether the current Point2D is unequal to the given
  Point2D by comparing their x- and y-coordinates.
  \param p a Point2D
  \return true when either the x- or y-coordinates of the given Point2D
  and the current Point2D are different; false otherwise */
bool Point2D::operator !=( const Point2D &p ) const
{
  return ( ( x != p.x ) || ( y != p.y ) );
}

/*! Overloaded version of the inequality operator for comparing a Point2D to
  a float value. It determines whether either the x- or y-coordinate of the
  current Point2D is unequal to the given float value.
  \param d a float value with which both the x- and y-coordinates of the
  current Point2D have to be compared.
  \return true when either the x- or y-coordinate of the current Point2D
  is unequal to the given float value; false otherwise */
bool Point2D::operator !=( const float &d ) const
{
  return ( ( x != d ) || ( y != d ) );
}

/*! Overloaded version of the equality operator for Point2Ds. It determines
  whether the current Point2D is equal to the given Point2D by
  comparing their x- and y-coordinates.
  \param p a Point2D
  \return true when both the x- and y-coordinates of the given Point2D and
  the current Point2D are equal; false otherwise */
bool Point2D::operator ==( const Point2D &p ) const
{
  return ( ( x == p.x ) && ( y == p.y ) );
}

/*! Overloaded version of the equality operator for comparing a Point2D to a
  float value. It determines whether both the x- and y-coordinates of the
  current Point2D are equal to the given float value.
  \param d a float value with which both the x- and y-coordinates of the
  current Point2D have to be compared.
  \return true when both the x- and y-coordinates of the current Point2D
  are equal to the given float value; false otherwise */
bool Point2D::operator ==( const float &d ) const
{
  return ( ( x == d ) && ( y == d ) );
}

/*! Overloaded version of the C++ output operator for output. 
  \param os output stream to which information should be written
  \param p a Point2D which must be printed
  \return output stream containing (x,y) */
ostream& operator << ( ostream &os, Point2D p )
{
  return ( os << "( " << p.x << ", " << p.y << " )" );
}

/*! String coversion for Lua
  \return string representation of point */
const char* Point2D::__str__()
{
  static char buffer[ 128 ];
  sprintf( buffer,"( %f, %f )", x, y );
  return buffer;
}

/*! Set method for the x-coordinate of the current Point2D.
  \param x a float value representing a new x-coordinate */
void Point2D::setX( float xx )
{
  x = xx;
}

/*! Get method for the x-coordinate of the current Point2D.
  \return the x-coordinate of the current Point2D */
float Point2D::getX() const
{
  return ( x );
}

/*! Set method for the y-coordinate of the current Point2D.
  \param y a float value representing a new y-coordinate */
void Point2D::setY( float yy )
{
  y = yy;
}

/*! Get method for the y-coordinate of the current Point2D.
  \return the y-coordinate of the current Point2D */
float Point2D::getY() const
{
  return ( y );
}

/*! This method (re)sets the coordinates of the current Point2D. The given
  coordinates can either be polar or Cartesian coordinates. This is indicated
  by the value of the third argument.
  \param x a float value indicating either a new Cartesian x-coordinate when
  cs=CARTESIAN or a new polar r-coordinate (distance) when cs=POLAR
  \param y a float value indicating either a new Cartesian y-coordinate when
  cs=CARTESIAN or a new polar phi-coordinate (angle) when cs=POLAR
  \param cs a CoordSystemT indicating whether x and y denote cartesian 
  coordinates or polar coordinates */
void Point2D::setPoint( float xx, float yy, CoordSystemT cs)
{
  if ( cs == CARTESIAN ) {
    x = xx;
    y = yy;
  }
  else
    *this = getPointFromPolar( xx, yy );
}

/*! This method determines the distance between the current Point2D and a
  given Point2D. This is equal to the magnitude (length) of the vector
  connecting the two positions which is the difference vector between them.
  \param p a Vecposition
  \return the distance between the current Point2D and the given
  Point2D */
float Point2D::getDistanceTo( const Point2D p ) const {
  return ( ( *this - p ).getMagnitude() );
}

/*! This method determines the bearing to a point from the current Point2D
  assuming the given orientation.
  \param p a Vecposition
  \param o an orientation
  \return the bearing from the current Point2D to the point p
  Point2D */
AngRad Point2D::getBearingTo( const Point2D p, const AngRad o ) const {
  Point2D relPoint = p - *this;
  AngRad absDir = relPoint.getDirection();
  return normalizeAngle( absDir - o );
}


/*! Gets the angle from this point to point p
  \param p a Vecposition
  \return the angle from the current Point2D to the point p
  Point2D */
AngRad Point2D::getAngleTo( const Point2D p ) const {
  Point2D relPoint = p - *this;
  return normalizeAngle( relPoint.getDirection());
}


/*! This method adjusts the coordinates of the current Point2D in such a way
  that the magnitude of the corresponding vector equals the float value which
  is supplied as an argument. It thus scales the vector to a given length by
  multiplying both the x- and y-coordinates by the quotient of the argument
  and the current magnitude. This changes the Point2D itself.
  \param d a float value representing a new magnitude
  \return the result of scaling the vector corresponding with the current
  Point2D to the given magnitude thus yielding a different Point2D */
Point2D Point2D::setMagnitude( float d )
{
  if ( getMagnitude() > EPSILON )
    ( *this ) *= ( d / getMagnitude() );

  return ( *this );
}

/*! This method determines the magnitude (length) of the vector corresponding
  with the current Point2D using the formula of Pythagoras.
  \return the length of the vector corresponding with the current
  Point2D */
float Point2D::getMagnitude() const
{
  return sqrtf(getSquaredMagnitude());
}

float Point2D::getSquaredMagnitude() const {
  return x * x + y * y;
}


/*! This method determines the direction of the vector corresponding with the
  current Point2D (the phi-coordinate in polar representation) using the
  arc tangent function. Note that the signs of x and y have to be taken into
  account in order to determine the correct quadrant.
  \return the direction in radians of the vector corresponding with the
  current Point2D */
AngRad Point2D::getDirection() const
{
  return ( atan2f( y, x ) );
}


/*! This method determines whether the current Point2D is in front of a
  given Point2D, i.e. whether the x-coordinate of the current Point2D
  is larger than the x-coordinate of the given Point2D.
  \param p a Point2D to which the current Point2D must be compared
  \return true when the current Point2D is in front of the given
  Point2D; false otherwise */
bool Point2D::isInFrontOf( const Point2D &p ) const
{
  return ( y > p.getY() );
}

/*! This method determines whether the x-coordinate of the current Point2D
  is in front of (i.e. larger than) a given float value.
  \param y a float value to which the current x-coordinate must be compared
  \return true when the current x-coordinate is in front of the given value;
  false otherwise */
bool Point2D::isInFrontOf( const float &yy ) const
{
  return ( y > yy );
}

/*! This method determines whether the current Point2D is behind a given
  Point2D, i.e. whether the x-coordinate of the current Point2D is
  smaller than the x-coordinate of the given Point2D.
  \param p a Point2D to which the current Point2D must be compared
  \return true when the current Point2D is behind the given Point2D;
  false otherwise */
bool Point2D::isBehind( const Point2D &p ) const
{
  return ( y < p.getY() );
}

/*! This method determines whether the x-coordinate of the current Point2D
  is behind (i.e. smaller than) a given float value.
  \param y a float value to which the current x-coordinate must be compared
  \return true when the current x-coordinate is behind the given value; false
  otherwise */
bool Point2D::isBehind( const float &yy ) const
{
  return ( y < yy );
}

/*! This method determines whether the current Point2D is to the left of a
  given Point2D, i.e. whether the y-coordinate of the current Point2D
  is smaller than the y-coordinate of the given Point2D.
  \param p a Point2D to which the current Point2D must be compared
  \return true when the current Point2D is to the left of the given
  Point2D; false otherwise */
bool Point2D::isLeftOf( const Point2D &p ) const
{
  return ( x < p.getX() );
}

/*! This method determines whether the y-coordinate of the current Point2D
  is to the left of (i.e. smaller than) a given float value.
  \param x a float value to which the current y-coordinate must be compared
  \return true when the current y-coordinate is to the left of the given
  value; false otherwise */
bool Point2D::isLeftOf( const float &xx ) const
{
  return ( x < xx );
}

/*! This method determines whether the current Point2D is to the right of a
  given Point2D, i.e. whether the y-coordinate of the current Point2D
  is larger than the y-coordinate of the given Point2D.
  \param p a Point2D to which the current Point2D must be compared
  \return true when the current Point2D is to the right of the given
  Point2D; false otherwise */
bool Point2D::isRightOf( const Point2D &p ) const
{
  return ( x > p.getX() );
}

/*! This method determines whether the y-coordinate of the current Point2D
  is to the right of (i.e. larger than) a given float value.
  \param x a float value to which the current y-coordinate must be compared
  \return true when the current y-coordinate is to the right of the given
  value; false otherwise */
bool Point2D::isRightOf( const float &xx ) const
{
  return ( x > xx );
}

/*! This method determines whether the current Point2D is in between two
  given Point2Ds when looking in the x-direction, i.e. whether the current
  Point2D is in front of the first argument and behind the second.
  \param p1 a Point2D to which the current Point2D must be compared
  \param p2 a Point2D to which the current Point2D must be compared
  \return true when the current Point2D is in between the two given
  Point2Ds when looking in the x-direction; false otherwise */
bool Point2D::isBetweenX( const Point2D &p1, const Point2D &p2 ) const
{
  return ( isRightOf( p1 ) && isLeftOf( p2 ) );
}

/*! This method determines whether the x-coordinate of the current Point2D
  is in between two given float values, i.e. whether the x-coordinate of the
  current Point2D is in front of the first argument and behind the second.
  \param x1 a float value to which the current x-coordinate must be compared
  \param x2 a float value to which the current x-coordinate must be compared
  \return true when the current x-coordinate is in between the two given
  values; false otherwise */
bool Point2D::isBetweenX( const float &x1, const float &x2 ) const
{
  return ( isRightOf( x1 ) && isLeftOf( x2 ) );
}


/*! This method determines whether the current Point2D is in between two
  given Point2Ds when looking in the y-direction, i.e. whether the current
  Point2D is to the right of the first argument and to the left of the
  second.
  \param p1 a Point2D to which the current Point2D must be compared
  \param p2 a Point2D to which the current Point2D must be compared
  \return true when the current Point2D is in between the two given
  Point2Ds when looking in the y-direction; false otherwise */
bool Point2D::isBetweenY( const Point2D &p1, const Point2D &p2 ) const
{
  return ( isInFrontOf( p1 ) && isBehind( p2 ) );
}

/*! This method determines whether the y-coordinate of the current Point2D
  is in between two given float values, i.e. whether the y-coordinate of the
  current Point2D is to the right of the first argument and to the left
  of the second.
  \param y1 a float value to which the current y-coordinate must be compared
  \param y2 a float value to which the current y-coordinate must be compared
  \return true when the current y-coordinate is in between the two given
  values; false otherwise */
bool Point2D::isBetweenY( const float &y1, const float &y2 ) const
{
  return ( isInFrontOf( y1 ) && isBehind( y2 ) );
}


/**
 * Mohan::Function returns true if the current Point2D lies in between
 * (in terms of the x coordinate) the Point2Ds sent in as arguments -
 * the two inputs need not be arranged in increasing order of
 * x-coordinates...
 */
bool Point2D::pointIsBetweenX( const Point2D &p1, const Point2D &p2 ) const {
  return( ( isRightOf( p1 ) && isLeftOf( p2 ) ) ||
	  ( isLeftOf( p1 ) && isRightOf( p2 ) ) );
}


/**
 * Mohan::Function returns true if the current Point2D lies in between
 * (in terms of the y coordinate) the Point2Ds sent in as arguments -
 * the two inputs need not be arranged in increasing order of
 * y-coordinates...
 */
bool Point2D::pointIsBetweenY( const Point2D &p1, const Point2D &p2 ) const {
  return( ( isInFrontOf( p1 ) && isBehind( p2 ) ) ||
	  ( isBehind( p1 ) && isInFrontOf( p2 ) ) );
}


/**
 * Function returns true iff the input point is in between the two
 * points provided as input. ORDER IS IMPORTANT => the test point is
 * checked for being greater than the first point and lesser than the
 * second point...
 */
bool Point2D::isBetweenTwoPoints( const Point2D &p1, 
				  const Point2D &p2 ) const {
  return( x >= p1.x && x <= p2.x &&
	  y >= p1.y && y <= p2.y );
}



/*! This method normalizes a Point2D by setting the magnitude of the
  corresponding vector to 1. This thus changes the Point2D itself.
  \return the result of normalizing the current Point2D thus yielding a
  different Point2D */
Point2D Point2D::normalize()
{
  return ( setMagnitude( 1.0 ) );
}

/*! This method rotates the vector corresponding to the current Point2D over
  a given angle thereby changing the current Point2D itself. This is done
  by calculating the polar coordinates of the current Point2D and adding
  the given angle to the phi-coordinate in the polar representation. The polar
  coordinates are then converted back to Cartesian coordinates to obtain the
  desired result.
  \param ang an angle in radians over which the vector corresponding to the
  current Point2D must be rotated
  \return the result of rotating the vector corresponding to the current
  Point2D over the given angle thus yielding a different Point2D */
Point2D Point2D::rotate( AngRad ang )
{
  // determine the polar representation of the current Point2D
  float dMag    = this->getMagnitude();
  float dNewDir = this->getDirection() + ang;  // add rotation angle to phi
  setPoint( dMag, dNewDir, POLAR );          // convert back to Cartesian
  return ( *this );
}

/*! This method converts the coordinates of the current Point2D (which are
  represented in an global coordinate system with the origin at (0,0)) into
  relative coordinates in a different coordinate system (e.g. relative to a
  player). The new coordinate system is defined by the arguments to the
  method. The relative coordinates are now obtained by aligning the relative
  coordinate system with the global coordinate system using a translation to
  make both origins coincide followed by a rotation to align the axes.
  \param origin the origin of the relative coordinate frame
  \param ang the angle between the world frame and the relative frame
  (reasoning from the world frame)
  \return the result of converting the current global Point2D into a
  relative Point2D */
Point2D Point2D::globalToRelative( Point2D origin, AngRad ang )
{
  // convert global coordinates into relative coordinates by aligning relative
  // frame and world frame. First perform translation to make origins of both
  // frames coincide. Then perform rotation to make axes of both frames coincide
  // (use negative angle since you rotate relative frame to world frame).
  Point2D retVal( x, y );
  retVal -= origin;
  return ( retVal.rotate( -ang ) );
}

/*! This method converts the coordinates of the current Point2D (which are
  represented in a relative coordinate system) into global coordinates in
  the world frame (with origin at (0,0)). The relative coordinate system is
  defined by the arguments to the method. The global coordinates are now
  obtained by aligning the world frame with the relative frame using a
  rotation to align the axes followed by a translation to make both origins
  coincide.
  \param origin the origin of the relative coordinate frame
  \param ang the angle between the world frame and the relative frame
  (reasoning from the world frame)
  \return the result of converting the current relative Point2D into an
  global Point2D */
Point2D Point2D::relativeToGlobal( Point2D origin, AngRad ang )
{
  // convert relative coordinates into global coordinates by aligning world
  // frame and relative frame. First perform rotation to make axes of both
  // frames coincide (use positive angle since you rotate world frame to
  // relative frame). Then perform translation to make origins of both frames
  // coincide.
  Point2D retVal( x, y );
  retVal.rotate( ang );
  retVal += origin;
  return retVal;
}

/*! This method returns a Point2D that lies somewhere on the vector between
  the current Point2D and a given Point2D. The desired position is
  specified by a given fraction of this vector (e.g. 0.5 means exactly in
  the middle of the vector). The current Point2D itself is left unchanged.
  \param p a Point2D which defines the vector to the current Point2D
  \param frac float representing the fraction of the connecting vector at
  which the desired Point2D lies.
  \return the Point2D that lies at fraction frac on the vector
  connecting p and the current Point2D */
Point2D Point2D::getPointOnLineFraction( Point2D &p,
					 float  frac )
{
  return ( ( *this ) * ( 1.0 - frac ) + ( p * frac ) );
}

/*! This method returns the angle between the 
  vectors made by this point and the two given points.
  \param p1 Point2D of first vector endpoint
  \param p2 Point2D of second vector endpoint
  \return the angle in radians between the vectors
  (this - p1) and (this - p2) */ 
AngRad Point2D::getAngleBetweenPoints( const Point2D &p1, 
				       const Point2D &p2 )
{
  Point2D v1 = *this - p1;
  Point2D v2 = *this - p2;
  Point2D vec = v1 * v2;
  float dotProduct = vec.x + vec.y;
  return fabs( normalizeAngle( acosf( dotProduct / v1.getMagnitude() 
				     / v2.getMagnitude() ) ) );
}

/*! This method converts a polar representation of a Point2D into a
  Cartesian representation.
  \param mag a float representing the polar r-coordinate, i.e. the distance
  from the point to the origin
  \param ang the angle that the polar vector makes with the x-axis, i.e. the
  polar phi-coordinate
  \return the result of converting the given polar representation into a
  Cartesian representation thus yielding a Cartesian Point2D */
Point2D Point2D::getPointFromPolar( float mag, AngRad ang )
{
  // cosf(phi) = x/r <=> x = r*cosf(phi); sinf(phi) = y/r <=> y = r*sinf(phi)
  return ( Point2D( mag * cosf( ang ), mag * sinf( ang ) ) );
}



/*! This method normalizes an angle. This means that the resulting angle lies
  between -2PI and 2PI radians.
  \param ang the angle which must be normalized
  \return the result of normalizing the given angle */
AngRad normalizeAngle( AngRad ang )
{
  if (isinf(ang)) {
    std::cerr << "INFINITE ANGLE in normalizeAngle" << std::endl;
    return 0;
  }
  ang = fmod(ang, TWOPI);
  if(ang >  M_PI) ang -= TWOPI;
  else if(ang < -M_PI) ang += TWOPI;
  return ang;
}

AngRad normalizeAngleAroundVal( AngRad ang, AngRad center )
{
  if (isinf(ang)) {
    std::cerr << "INFINITE ANGLE in normalizeAngleAroundVal" << std::endl;
    return center;
  }
  while( ang > (center + M_PI) ) ang -= TWOPI;
  while( ang < (center - M_PI) ) ang += TWOPI;
  
  return ( ang );
}

/*! This method normalizes an angle to within +- 90 degrees (1PI) instead of 2PI
  for line orientations
  \param ang the angle which must be normalized
  \return the result of normalizing the given angle */
AngRad normalizeAngleNinety( AngRad ang )
{
  ang = fmod(ang, M_PI);
  if(ang < - M_PI / 2) ang += M_PI;
  if(ang > M_PI / 2) ang -= M_PI;
  return ang;
}

AngRad normalizeAngleNinetyAroundVal( AngRad ang, AngRad center )
{
  while( ang > (center + M_PI/2.0)  ) ang -= M_PI;
  while( ang < (center - M_PI/2.0) ) ang += M_PI;

  return ( ang );
}


/*****************/
/* Class Point3D */
/*****************/
Point3D::Point3D( float xx, float yy, float zz, CoordSystemT cs ) {
  setPoint( xx, yy, zz, cs );
}

/*! Overloaded version of unary minus operator for Point3Ds. It returns the
  negative Point3D, i.e. both the x- and y-coordinates are multiplied by
  -1. The current Point3D itself is left unchanged.
  \return a negated version of the current Point3D */
Point3D Point3D::operator - () const
{
  return ( Point3D( -x, -y, -z ) );
}

/*! Overloaded version of the binary plus operator for adding a given float
  value to a Point3D. The float value is added to both the x- and
  y-coordinates of the current Point3D. The current Point3D itself is
  left unchanged.
  \param d a float value which has to be added to both the x- and
  y-coordinates of the current Point3D
  \return the result of adding the given float value to the current
  Point3D */
Point3D Point3D::operator + ( const float &d ) const
{
  return ( Point3D( x + d, y + d, z + d ) );
}

/*! Overloaded version of the binary plus operator for Point3Ds. It returns
  the sum of the current Point3D and the given Point3D by adding their
  x- and y-coordinates. The Point3Ds themselves are left unchanged.
  \param p a Point3D
  \return the sum of the current Point3D and the given Point3D */
Point3D Point3D::operator + ( const Point3D &p ) const
{
  return ( Point3D( x + p.x, y + p.y , z + p.z ) );
}

/*! Overloaded version of the binary minus operator for subtracting a given
  float value from a Point3D. The float value is subtracted from both
  the x- and y-coordinates of the current Point3D. The current Point3D
  itself is left unchanged.
  \param d a float value which has to be subtracted from both the x- and
  y-coordinates of the current Point3D
  \return the result of subtracting the given float value from the current
  Point3D */
Point3D Point3D::operator - ( const float &d ) const
{
  return ( Point3D( x - d, y - d, z - d ) );
}

/*! Overloaded version of the binary minus operator for Point3Ds. It returns
  the difference between the current Point3D and the given Point3D by
  subtracting their x- and y-coordinates. The Point3Ds themselves are left
  unchanged.
  \param p a Point3D
  \return the difference between the current Point3D and the given
  Point3D */
Point3D Point3D::operator - ( const Point3D &p ) const
{
  return ( Point3D( x - p.x, y - p.y, z - p.z ) );
}

/*! Overloaded version of the multiplication operator for multiplying a
  Point3D by a given float value. Both the x- and y-coordinates of the
  current Point3D are multiplied by this value. The current Point3D
  itself is left unchanged.
  \param d the multiplication factor
  \return the result of multiplying the current Point3D by the given
  float value */
Point3D Point3D::operator * ( const float &d ) const
{
  return ( Point3D( x * d, y * d, y * z  ) );
}

/*! Overloaded version of the multiplication operator for Point3Ds. It
  returns the product of the current Point3D and the given Point3D by
  multiplying their x- and y-coordinates. The Point3Ds themselves are left
  unchanged.
  \param p a Point3D
  \return the product of the current Point3D and the given Point3D */
Point3D Point3D::operator * ( const Point3D &p ) const
{
  return ( Point3D( x * p.x, y * p.y, z * p.z ) );
}

/*! Overloaded version of the division operator for dividing a Point3D by a
  given float value. Both the x- and y-coordinates of the current Point3D
  are divided by this value. The current Point3D itself is left unchanged.
  \param d the division factor
  \return the result of dividing the current Point3D by the given float
  value */
Point3D Point3D::operator / ( const float &d ) const
{
  return ( Point3D( x / d, y / d, z / d   ) );
}

/*! Overloaded version of the division operator for Point3Ds. It returns the
  quotient of the current Point3D and the given Point3D by dividing
  their x- and y-coordinates. The Point3Ds themselves are left unchanged.
  \param p a Point3D
  \return the quotient of the current Point3D and the given Point3D */
Point3D Point3D::operator / ( const Point3D &p ) const
{
  return ( Point3D( x / p.x, y / p.y, z / p.z ) );
}

/*! Overloaded version of the assignment operator for assigning a given float
  value to both the x- and y-coordinates of the current Point3D. This
  changes the current Point3D itself.
  \param d a float value which has to be assigned to both the x- and
  y-coordinates of the current Point3D */
void Point3D::operator = ( const float &d )
{
  x = d;
  y = d;
  z = d;
}

/*! Overloaded version of the sum-assignment operator for Point3Ds. It
  returns the sum of the current Point3D and the given Point3D by
  adding their x- and y-coordinates. This changes the current Point3D
  itself.
  \param p a Point3D which has to be added to the current Point3D */
void Point3D::operator +=( const Point3D &p )
{
  x += p.x;
  y += p.y;
  z += p.z;
}

/*! Overloaded version of the sum-assignment operator for adding a given float
  value to a Point3D. The float value is added to both the x- and
  y-coordinates of the current Point3D. This changes the current
  Point3D itself.
  \param d a float value which has to be added to both the x- and
  y-coordinates of the current Point3D */
void Point3D::operator += ( const float &d )
{
  x += d;
  y += d;
  z += d;
}

/*! Overloaded version of the difference-assignment operator for Point3Ds.
  It returns the difference between the current Point3D and the given
  Point3D by subtracting their x- and y-coordinates. This changes the
  current Point3D itself.
  \param p a Point3D which has to be subtracted from the current
  Point3D */
void Point3D::operator -=( const Point3D &p )
{
  x -= p.x;
  y -= p.y;
  z -= p.z;
}

/*! Overloaded version of the difference-assignment operator for subtracting a
  given float value from a Point3D. The float value is subtracted from
  both the x- and y-coordinates of the current Point3D. This changes the
  current Point3D itself.
  \param d a float value which has to be subtracted from both the x- and
  y-coordinates of the current Point3D */
void Point3D::operator -=( const float &d )
{
  x -= d;
  y -= d;
  z -= d;
}

/*! Overloaded version of the multiplication-assignment operator for
  Point3Ds. It returns the product of the current Point3D and the
  given Point3D by multiplying their x- and y-coordinates. This changes
  the current Point3D itself.
  \param p a Point3D by which the current Point3D has to be
  multiplied */
void Point3D::operator *=( const Point3D &p )
{
  x *= p.x;
  y *= p.y;
  z *= p.z;
}

/*! Overloaded version of the multiplication-assignment operator for multiplying
  a Point3D by a given float value. Both the x- and y-coordinates of the
  current Point3D are multiplied by this value. This changes the current
  Point3D itself.
  \param d a float value by which both the x- and y-coordinates of the
  current Point3D have to be multiplied */
void Point3D::operator *=( const float &d )
{
  x *= d;
  y *= d;
  z *= d;
}

/*! Overloaded version of the division-assignment operator for Point3Ds. It
  returns the quotient of the current Point3D and the given Point3D by
  dividing their x- and y-coordinates. This changes the current Point3D
  itself.
  \param p a Point3D by which the current Point3D has to be divided */
void Point3D::operator /=( const Point3D &p )
{
  x /= p.x;
  y /= p.y;
  z /= p.z;
}

/*! Overloaded version of the division-assignment operator for dividing a
  Point3D by a given float value. Both the x- and y-coordinates of the
  current Point3D are divided by this value. This changes the current
  Point3D itself.
  \param d a float value by which both the x- and y-coordinates of the
  current Point3D have to be divided */
void Point3D::operator /=( const float &d )
{
  x /= d;
  y /= d;
  z /= d;
}

/*! Overloaded version of the inequality operator for Point3Ds. It
  determines whether the current Point3D is unequal to the given
  Point3D by comparing their x- and y-coordinates.
  \param p a Point3D
  \return true when either the x- ory-coordinates of the given Point3D
  and the current Point3D are different; false otherwise */
bool Point3D::operator !=( const Point3D &p ) const
{
  return ( ( x != p.x ) || ( y != p.y ) || ( z != p.z ));
}

/*! Overloaded version of the inequality operator for comparing a Point3D to
  a float value. It determines whether either the x- or y-coordinate of the
  current Point3D is unequal to the given float value.
  \param d a float value with which both the x- and y-coordinates of the
  current Point3D have to be compared.
  \return true when either the x- or y-coordinate of the current Point3D
  is unequal to the given float value; false otherwise */
bool Point3D::operator !=( const float &d ) const
{
  return ( ( x != d ) || ( y != d ) || ( z != d ));
}

/*! Overloaded version of the equality operator for Point3Ds. It determines
  whether the current Point3D is equal to the given Point3D by
  comparing their x- and y-coordinates.
  \param p a Point3D
  \return true when both the x- and y-coordinates of the given Point3D and
  the current Point3D are equal; false otherwise */
bool Point3D::operator ==( const Point3D &p ) const
{
  return ( ( x == p.x ) && ( y == p.y ) && ( z == p.z ));
}

/*! Overloaded version of the equality operator for comparing a Point3D to a
  float value. It determines whether both the x- and y-coordinates of the
  current Point3D are equal to the given float value.
  \param d a float value with which both the x- and y-coordinates of the
  current Point3D have to be compared.
  \return true when both the x- and y-coordinates of the current Point3D
  are equal to the given float value; false otherwise */
bool Point3D::operator ==( const float &d ) const
{
  return ( ( x == d ) && ( y == d ) && ( z == d ));
}

/*! Overloaded version of the C++ output operator for output. 
  \param os output stream to which information should be written
  \param p a Point3D which must be printed
  \return output stream containing (x,y) */
ostream& operator << ( ostream &os, Point3D p )
{
  return ( os << "( " << p.x << ", " << p.y << ", " << p.z << " )" );
}

/*! String coversion for Lua
  \return string representation of point */
const char* Point3D::__str__()
{
  static char buffer[ 128 ];
  sprintf( buffer,"( %f, %f, %f )", x, y, z );
  return buffer;
}

/*! Set method for the x-coordinate of the current Point3D.
  \param x a float value representing a new x-coordinate */
void Point3D::setX( float xx )
{
  x = xx;
}

/*! Get method for the x-coordinate of the current Point3D.
  \return the x-coordinate of the current Point3D */
float Point3D::getX() const
{
  return ( x );
}

/*! Set method for the y-coordinate of the current Point3D.
  \param y a float value representing a new y-coordinate */
void Point3D::setY( float yy )
{
  y = yy;
}

/*! Get method for the y-coordinate of the current Point3D.
  \return the y-coordinate of the current Point3D */
float Point3D::getY() const
{
  return ( y );
}


/*! Set method for the z-coordinate of the current Point3D.
  \param z a float value representing a new z-coordinate */
void Point3D::setZ( float zz )
{
  z = zz;
}

/*! Get method for the z-coordinate of the current Point3D.
  \return the z-coordinate of the current Point3D */
float Point3D::getZ() const
{
  return ( z );
}

/*! This method (re)sets the coordinates of the current Point3D. The given
  coordinates can either be polar or Cartesian coordinates. This is indicated
  by the value of the third argument.
  \param x a float value indicating either a new Cartesian x-coordinate when
  cs=CARTESIAN or a new polar r-coordinate (distance) when cs=POLAR
  \param y a float value indicating either a new Cartesian y-coordinate when
  cs=CARTESIAN or a new polar phi-coordinate (angle) when cs=POLAR
  \param cs a CoordSystemT indicating whether x and y denote cartesian 
  coordinates or polar coordinates */
void Point3D::setPoint( float xx, float yy, float zz, CoordSystemT cs)
{
  if ( cs == CARTESIAN ) {
    x = xx;
    y = yy;
    z = zz;
  }//
  //else
  //  *this = getPointFromPolar( xx, yy );
}


/*******************/
/* Class Rectangle */
/*******************/

/*! This is the constructor of a Rectangle. Two points will be given. The
    order does not matter as long as two opposite points are given (left
    top and right bottom or right top and left bottom).
    \param p1 first point that defines corner of rectangle
    \param p2 second point that defines other corner of rectangle
    \return rectangle with 'p1' and 'p2' as opposite corners. */
Rectangle::Rectangle( Point2D p1, Point2D p2 )
{
  setRectanglePoints( p1, p2 );
}

/*! Overloaded version of the C++ output operator for output. 
  \param os output stream to which information should be written
  \param r a Rectangle which must be printed
  \return output stream containing rectangle endpoints */
ostream& operator << ( ostream &os, Rectangle r )
{
  return ( os << "[" << r.m_pTopLeft << ", " << r.m_pBottomRight << "]" );
}

/*! Overloaded version of unary minus operator for Rectangles. It returns the
  negative Rectangle, i.e. it is rotated 180 degrees around the origin.
  The current Rectangle itself is left unchanged.
  \return a negated version of the current Rectangle */
Rectangle Rectangle::operator - () const
{
  return ( Rectangle( -m_pBottomRight, -m_pTopLeft ) );
}


/*! This method sets the upper left and right bottom point of the current
  rectangle.
  \param p1 first point that defines corner of rectangle
  \param p2 second point that defines other corner of rectangle */
void Rectangle::setRectanglePoints( Point2D p1, Point2D p2 )
{
  m_pTopLeft.setX    ( min( p1.getX(), p2.getX() ) );
  m_pTopLeft.setY    ( max( p1.getY(), p2.getY() ) );
  m_pBottomRight.setX( max( p1.getX(), p2.getX() ) );
  m_pBottomRight.setY( min( p1.getY(), p2.getY() ) );
}

/*! This method determines whether the given position lies inside the current
  rectangle.
  \param p position which is checked whether it lies in rectangle
  \return true when 'p' lies in the rectangle, false otherwise */
bool Rectangle::isInside( Point2D p ) const
{
  return p.isBetweenX( m_pTopLeft.getX(), m_pBottomRight.getX() ) &&
         p.isBetweenY( m_pBottomRight.getY(), m_pTopLeft.getY() );

}

/*! This method sets the top left position of the rectangle
  \param p new top left position of the rectangle
  \return true when update was successful */
void Rectangle::setTopLeft( Point2D p )
{
  m_pTopLeft = p;
}

/*! This method returns the top left position of the rectangle
  \return top left position of the rectangle */
Point2D Rectangle::getTopLeft() const
{
  return m_pTopLeft;
}

/*! This method sets the right bottom position of the rectangle
  \param p new right bottom position of the rectangle
  \return true when update was succesfull */
void Rectangle::setBottomRight( Point2D p )
{
  m_pBottomRight = p;
}

/*! This method returns the right bottom position of the rectangle
  \return top right bottom of the rectangle */
Point2D Rectangle::getBottomRight() const
{
  return m_pBottomRight;
}

/*! This method returns the left bottom position of the rectangle
  \return top left bottom of the rectangle */
Point2D Rectangle::getBottomLeft() const
{
  return Point2D( m_pTopLeft.getX(), m_pBottomRight.getY() );
}

/*! This method returns the right top position of the rectangle
  \return top right top of the rectangle */
Point2D Rectangle::getTopRight() const
{
  return Point2D( m_pBottomRight.getX(), m_pTopLeft.getY() );
}

Point2D Rectangle::getCenter() const
{
  return ( (m_pBottomRight + m_pTopLeft) / 2 );
}

Point2D Rectangle::getPosOutside() const
{
  return getTopRight() + 1;
}

float Rectangle::getWidth() const
{
  return ( m_pBottomRight - m_pTopLeft ).getX();
}

float Rectangle::getLength() const
{
  return ( m_pTopLeft - m_pBottomRight ).getY();
}

float Rectangle::getDiagonalLength() const
{
  return m_pTopLeft.getDistanceTo( m_pBottomRight );
}

float Rectangle::getLeft() const
{
  return m_pTopLeft.getX();
}

float Rectangle::getRight() const
{
  return m_pBottomRight.getX();
}

float Rectangle::getTop() const
{
  return m_pTopLeft.getY();
}

float Rectangle::getBottom() const
{
  return m_pBottomRight.getY();
}


/****************/
/* Class Line2D */
/****************/
Line2D::Line2D() {
  m_a = 0;
  m_b = 0;
  m_c = 0;
}

/*! This constructor creates a line by given the three coefficents of the line.
  A line is specified by the formula ay + bx + c = 0.
  \param a a coefficients of the line
  \param b b coefficients of the line
  \param c c coefficients of the line */
Line2D::Line2D( float a, float b, float c )
{
  m_a = a;
  m_b = b;
  m_c = c;
}

/*! This constructor creates a line given two points.
  \param p1 first point
  \param p2 second point */
Line2D::Line2D( const Point2D& p1, const Point2D& p2 )
{
  /*// Changing to a different (and I think better formula) MQ 16/10/2009
  m_a = p1.getY() - p2.getY();
  m_b = p2.getX() - p1.getX();
  m_c = p2.getY()*p1.getX() - p2.getX()*p1.getY();

  //normailse a,b,c
  float denom=sqrtf(powf(m_a,2)+powf(m_b,2));
  m_a=m_a/denom;
  m_b=m_b/denom;
  m_c=m_c/denom;

  center = (p1 + p2) / 2; 
*/

  // 1*y + bx + c = 0 => y = -bx - c
  // with -b the direction coefficient (or slope)
  // and c = - y - bx
  m_a=1.0;
  float dTemp = p2.getX() - p1.getX(); // determine the slope
  if ( fabs(dTemp) < EPSILON )
  {
    // ay + bx + c = 0 with vertical slope=> a = 0, b = 1
    m_a = 0.0;
    m_b = 1.0;
  }
  else
  {
    // y = (-b)x -c with -b the slope of the line
    m_a = 1.0;
    m_b = -(p2.getY() - p1.getY())/dTemp;
  }
  // ay + bx + c = 0 ==> c = -a*y - b*x
  m_c =  - m_a*p2.getY() - m_b * p2.getX();

  center = (p1 + p2) / 2;

//normailse a,b,c
  float denom=sqrtf(powf(m_a,2)+powf(m_b,2));
  m_a=m_a/denom;
  m_b=m_b/denom;
  m_c=m_c/denom;

}

Line2D::Line2D(float x1, float y1, float x2, float y2) 
{
  *this = Line2D(Point2D(x1,y1), Point2D(x2,y2));
}

/*! This constructor creates a line given a position and an angle.
  \param p position through which the line passes
  \param ang direction of the line */
Line2D::Line2D( const Point2D& p, const AngRad& ang )
{
  // calculate point somewhat further in direction 'angle' and make
  // line from these two points.
  *this = Line2D( p, p+Point2D(100,ang,POLAR));
}

Line2D Line2D::operator-() const
{

  return Line2D( m_a, m_b, -m_c);

}

/*! Overloaded version of the C++ output operator for output. 
  \param os output stream to which information should be written
  \param l a Line2D which must be printed
  \return output stream containing line equation */
ostream& operator << ( ostream &os, Line2D l )
{
  return ( os << l.m_a << "y + " << l.m_b << "x + " << l.m_c << " = 0" );
}

/*! This method returns the intersection point between the current Line and
  the specified line.
  \param line line with which the intersection should be calculated.
  \return Point2D position that is the intersection point. */
Point2D Line2D::getIntersection( Line2D line ) const
{
  Point2D p;
  float x, y;

  if(isParallelTo(line))
  {
    return p;
  }
  if ( m_a == 0 )               // bx + c = 0 and a2*y + b2*x + c2 = 0 ==> x = -c/b
  {                          // calculate x using the current line
    x = -m_c/m_b;                // and calculate the y using the second line
    y = line.getYGivenX(x);
  }
  else if ( line.getACoefficient() == 0 )
  {                         // ay + bx + c = 0 and b2*x + c2 = 0 ==> x = -c2/b2
    x = -line.getCCoefficient()/line.getBCoefficient(); // calculate x using
    y = getYGivenX(x);       // 2nd line and calculate y using current line
  }
  // ay + bx + c = 0 and a2y + b2*x + c2 = 0
  // y = (-b2/a2)x - c2/a2
  // bx = -a*y - c =>  bx = -a*(-b2/a2)x -a*(-c2/a2) - c ==>
  // ==> a2*bx = a*b2*x + a*c2 - a2*c ==> x = (a*c2 - a2*c)/(a2*b - a*b2)
  // calculate x using the above formula and the y using the current line
  else
  {
    x = (m_a*line.getCCoefficient() - line.getACoefficient()*m_c)/
                    (line.getACoefficient()*m_b - m_a*line.getBCoefficient());
    y = getYGivenX(x);
  }

  return Point2D( x, y );
}

/*! This method returns the orthogonal line to a Point2D. This is the
  line between the specified position and the closest point on the
  line to this position.  \param p Point2D point with which tangent
  line is calculated.  \return Line line tangent to this position */
Line2D Line2D::getOrthogonalLine( Point2D p ) const
{
  // ay + bx + c = 0 -> y = (-b/a)x + (-c/a)
  // tangent: y = (a/b)*x + C1 -> by - ax + C2 = 0 => C2 = ax - by
  // with p.y = y, p.x = x
  return Line2D( m_b, -m_a, m_a*p.getX() - m_b*p.getY() );
}


/**
 * Mohan::This method returns the value of the normalized angle
 * between the current line and the line sent in as input. \param
 * line: line with which the angle is to be determined. \return
 * Angrad: angle between the current line and input line...
 */
AngRad Line2D::getAngleToLine( Line2D line ) const {
  float ang = 0;
  
  float m1, m2;
  
  // In our case we shall never have a case with a line that is
  // parallel to the y-axis but I am checking for that as a
  // matter-of-fact...
  // Both lines parallel to y-axis...
  if( m_a <= EPSILON && line.getACoefficient() <= EPSILON ) {
    return ang;
  }
  // Current line parallel to y-axis...
  else if( fabs(m_a) <= EPSILON ) {
    ang = atan( fabs( line.getACoefficient() / line.getBCoefficient() ) );
    return normalizeAngle(ang);
  }
  // Input line parallel to y-axis...
  else if( fabs( line.getACoefficient() ) <= EPSILON ) {
    ang = atan( fabs( m_a / m_b ) );
    return normalizeAngle(ang);
  }
  // Neither line parallel to the y-axis...
  else {
    m1 = - m_b / m_a;
    m2 = - line.getBCoefficient() / line.getACoefficient();
    ang = atan( fabs( m2 - m1 ) / ( 1 + m1 * m2 ) );
    return normalizeAngle(ang);
  }
}

AngRad Line2D::getAngle() const {
  auto slope = getSlope();
  auto angle = atan(slope);
  return angle;
}

/**
 * Mohan::This method returns the intersection point between the
 * current Line and the specified line.  \param line line with which
 * the intersection should be calculated.  \return Point2D position
 * that is the intersection point. */
Point2D Line2D::getMyIntersection( Line2D line ) const {
  Point2D p(0,0);
  float x, y;

  float SLOPE_DIFF = EPSILON * 10;

  float y_num = m_b*line.getCCoefficient() - line.getBCoefficient()*m_c;
  float denom = m_a*line.getBCoefficient() - line.getACoefficient()*m_b;

  // If the two lines are parallel, return the zero vector as the
  // intersection point...
  if( fabs(denom) <= SLOPE_DIFF ) {
    return p;
  }

  float x_num = line.getACoefficient()*m_c - m_a*line.getCCoefficient();
  
  x = x_num/denom;
  y = y_num/denom;
  return Point2D( x, y );
}


/*! This method returns the closest point on a line to a given position.
  \param p point to which closest point should be determined
  \return Point2D closest point on line to 'p'. */
Point2D Line2D::getPointOnLineClosestTo( Point2D p ) const
{
  Line2D l2 = getOrthogonalLine( p );  // get tangent line
  return getMyIntersection( l2 );     // and intersection between the two lines
}

/*! This method returns the distance between a specified position and the
  closest point on the given line.
  \param p position to which distance should be calculated
  \return float indicating the distance to the line. */
float Line2D::getDistanceToPoint( Point2D p ) const
{
  return p.getDistanceTo( getPointOnLineClosestTo( p ) );
}

/*! This method determines whether the projection of a point on the current line
  lies between two other points ('point1' and 'point2') that lie on the same
  line.
  \param p point of which projection is checked.
  \param p1 first point on line
  \param p2 second point on line
  \return true when projection of 'p' lies between 'point1' and 'point2'.*/
bool Line2D::isInBetween( Point2D p, Point2D p1, Point2D p2) const
{
  p = getPointOnLineClosestTo( p ); // get closest point
  float dDist = p1.getDistanceTo( p2 ); // get distance between 2 p

  // if the distance from both points to the projection is smaller than this
  // dist, the p lies in between.
  return p.getDistanceTo( p1 ) <= dDist &&
         p.getDistanceTo( p2 ) <= dDist;
}

/*! This method calculates the y coordinate given the x coordinate
  \param x coordinate
  \return y coordinate on this line */
float Line2D::getYGivenX( float x ) const
{
 if ( m_a == 0 )
 {
   cerr << "(Line2D::getYGivenX) Cannot calculate Y coordinate: " ;
   cerr << endl;
   return 0;
 }
  // ay + bx + c = 0 ==> ay = -(b*x + c)/a
  return -(m_b*x+m_c)/m_a;
}

/*! This method calculates the x coordinate given the y coordinate
  \param y coordinate
  \return x coordinate on this line */
float Line2D::getXGivenY( float y ) const
{
 if ( m_b == 0 )
 {
   //FYI: I disabled this because it is annoying and not useful 100% of the time - JM 2/26/14
   //cerr << "(Line2D::getXGivenY) Cannot calculate X coordinate\n" ;
   return 0;
 }
  // ay + bx + c = 0 ==> bx = -(a*y + c)/a
  return -(m_a*y+m_c)/m_b;
}

/*! This method creates a line given two points.
  \param p1 first point
  \param p2 second point
  \return line that passes through the two specified points. */
Line2D Line2D::makeLineFromTwoPoints( Point2D p1, Point2D p2 )
{
  return Line2D( p1, p2 );
}

/*! This method creates a line given a position and an angle.
  \param p position through which the line passes
  \param ang direction
 of the line.
  \return line that goes through position 'p' with angle 'ang'. */
Line2D Line2D::makeLineFromPositionAndAngle( Point2D p, AngRad ang )
{
  return Line2D( p, ang );
}

/*! This method returns the a coefficient from the line ay + bx + c = 0.
  \return a coefficient of the line. */
float Line2D::getACoefficient() const
{
  return m_a;
}

/*! This method returns the b coefficient from the line ay + bx + c = 0.
  \return b coefficient of the line. */
float Line2D::getBCoefficient() const
{
 return m_b;
}

/*! This method returns the c coefficient from the line ay + bx + c = 0.
  \return c coefficient of the line. */
float Line2D::getCCoefficient() const
{
 return m_c;
}

/*! This method returns the slope of the line.  \return m the slope of
  the line. */
float Line2D::getSlope() const
{
  if ( m_a == 0 ) {
#ifndef NDEBUG
    cerr << "(Line2D:getSlope): divide by zero\n";
#endif
    return 1000;
  }
  return -m_b / m_a;
}

/*! This method returns the y-intercept of the line.
  \return b the y-intercept of the line. */
float Line2D::getYIntercept() const
{
  if ( m_a == 0 ) {
    return -m_c;
  }
  return -m_c / m_a;
}

/*! This method returns the x-intercept of the line.
  \return the x-intercept of the line. */
float Line2D::getXIntercept() const
{
  if ( m_b == 0 ) {
    return -m_c;
  }
  return -m_c / m_b;
}

bool Line2D::isParallelTo(Line2D other) const
{
  if(m_a == 0 || other.m_a == 0)
    return m_b == other.m_b;
  else
    return fabs(m_b / m_a - other.m_b / other.m_a) <= EPSILON;
}

Point2D Line2D::getCenter() const
{
  return center;
}

LineSegment::LineSegment() { 
}

LineSegment::LineSegment(int x1, int y1, int x2, int y2) : Line2D(x1,y1,x2,y2) {
  start.x = x1; start.y = y1;
  end.x = x2; end.y = y2;
}

LineSegment::LineSegment(Point2D start, Point2D end) : start(start), end(end), Line2D(start,end) {
}

float LineSegment::getDirection() const {
  float dir = (start - end).getDirection();
  dir = normalizeAngleNinety(dir);
  return dir;
}

float LineSegment::length() const {
    return (start - end).getMagnitude();
}

Point2D LineSegment::getPointOnSegmentClosestTo(Point2D p) const {
  const float len2 = length() * length();
  if(len2 == 0.0)
      return start;
  Point2D vec = (p - start) * (end - start);
  float dotProduct = vec.x + vec.y;
  const float t = dotProduct / len2;
  if(dotProduct < 0.0)
      return start;
  else if (t > 1.0)
      return end;
  Point2D proj = (end - start);
  proj.x *= t;
  proj.y *= t;
  proj = proj + start;
  return proj;
}

// From: http://mathworld.wolfram.com/Circle-LineIntersection.html
Point2D LineSegment::getNearestCircleIntersection(Point2D center, float radius, Point2D near) {
  Point2D cstart = start - center, cend = end - center;
  float dx = cend.x - cstart.x;
  float dy = cend.y - cstart.y;
  float dr = sqrtf(dx*dx + dy*dy);
  float D = cstart.x * cend.y - cend.x * cstart.y;
  
  int sy = dy < 0 ? -1 : 1;

  float disc = radius*radius*dr*dr - D*D;

  if(disc < 0) {
    return getPointOnSegmentClosestTo(near);
  }

  float x1 = (D * dy + sy * dx * sqrtf(disc)) / (dr*dr) + center.x;
  float x2 = (D * dy - sy * dx * sqrtf(disc)) / (dr*dr) + center.x;

  float y1 = (-D * dx + abs(dy) * sqrtf(disc)) / (dr*dr) + center.y;
  float y2 = (-D * dx - abs(dy) * sqrtf(disc)) / (dr*dr) + center.y;
  
  Point2D p1(x1,y1), p2(x2,y2);
  if(p1.getDistanceTo(near) < p2.getDistanceTo(near))
    return p1;
  return p2;
}

float LineSegment::getDistanceTo(Point2D p) const {
  Point2D closest = getPointOnSegmentClosestTo(p);
  return (p - closest).getMagnitude();
}

/*! This method returns the RMSE distance from a line to two points. */
float LineSegment::getDistanceTo(Point2D p1, Point2D p2) const {
  float d1 = getDistanceTo(p1);
  float d2 = getDistanceTo(p2);
  return sqrtf((d1 * d1 + d2 * d2)/2);
}

/**
 * Returns the signed acute angle based on the start of the line segment.
 * Standing at the start, if the closest distance to the line is on the left
 * then this angle is positive.
 */

AngRad LineSegment::getSignedAngleToLine( Line2D line ) const {
  if(isParallelTo(line)) return 0;
  Point2D intersection = line.getIntersection(*this);
  Point2D closest = line.getPointOnLineClosestTo(start);
  if(closest == intersection) return M_PI / 2.0;

  LineSegment other(closest, intersection);
  float theta = normalizeAngleNinety(other.getDirection() - getDirection());
  return theta;
}

Point2D LineSegment::getSegmentIntersection(Line2D line) const {
  Point2D intersection = getIntersection(line);
  intersection = getPointOnSegmentClosestTo(intersection);
  return intersection;
}

LineSegment LineSegment::globalToRelative(Point2D origin, AngRad ang) {
  return LineSegment(start.globalToRelative(origin, ang), end.globalToRelative(origin, ang));
}

LineSegment LineSegment::relativeToGlobal(Point2D origin, AngRad ang) {
  return LineSegment(start.relativeToGlobal(origin, ang), end.relativeToGlobal(origin, ang));
}

LineSegment LineSegment::rotate(Point2D origin, AngRad ang) {
  start -= origin;
  end -= origin;
  start.rotate(ang);
  end.rotate(ang);
  start += origin;
  end += origin;
  return *this;
}


LineSegment LineSegment::rotate(AngRad ang) {
  computeCenter();
  return rotate(center, ang);
}

LineSegment LineSegment::getVisiblePortion(Point2D origin, AngRad orientation, AngRad fov) {
  Point2D leftBound = start, rightBound = end;
  
  float leftBearing = origin.getBearingTo(leftBound, orientation);
  float rightBearing = origin.getBearingTo(rightBound, orientation);
  if(leftBearing < rightBearing) {
    Point2D t1 = leftBound;
    leftBound = rightBound;
    rightBound = t1;
    float t2 = leftBearing;
    leftBearing = rightBearing;
    rightBearing = t2;
  }
  Point2D vstart, vend;
  if(leftBearing < fov/2)
    vstart = leftBound;
  else {
    AngRad maxleft = orientation + fov/2;
    Line2D leftLine = Line2D::makeLineFromPositionAndAngle(origin, maxleft);
    Point2D leftInt = getIntersection(leftLine);
    Point2D leftPt = getPointOnSegmentClosestTo(leftInt);
    vstart = leftPt;
  }

  if(rightBearing > -fov/2)
    vend = rightBound;
  else {
    AngRad maxright = orientation - fov/2;
    Line2D rightLine = Line2D::makeLineFromPositionAndAngle(origin, maxright);
    Point2D rightInt = getIntersection(rightLine);
    Point2D rightPt = getPointOnSegmentClosestTo(rightInt);
    vend = rightPt;
  }
  LineSegment visible(vstart, vend);
  return visible;
}

LineSegment LineSegment::crop(LineSegment bounds) {
  Point2D nearestStart = bounds.getPointOnSegmentClosestTo(start);
  Point2D nearestEnd = bounds.getPointOnSegmentClosestTo(end);
  if(nearestStart.getDistanceTo(bounds.start) > nearestEnd.getDistanceTo(bounds.start)) {
    Point2D temp = nearestStart;
    nearestStart = nearestEnd;
    nearestEnd = temp;
  }
  Point2D nstart = getPointOnSegmentClosestTo(nearestStart);
  Point2D nend = getPointOnSegmentClosestTo(nearestEnd);
  start = nstart;
  end = nend;
  return *this;
}

void LineSegment::computeCenter() {
  center = (start + end) / 2;
}

/****************/
/* Class Circle */
/****************/

/*! This is the constructor of a circle.
  \param pCenter first point that defines the center of circle
  \param radius the radius of the circle
  \return circle with p as center and radius as radius*/
Circle::Circle( const Point2D& pCenter, float radius )
{
  setCircle( pCenter, radius );
}

/*! This is the constructor of a circle which initializes a circle with a
  radius of zero. */
Circle::Circle()
{
  setCircle( Point2D(-1000.0,-1000.0), 0);
}

/*! Overloaded version of the C++ output operator for output. 
  \param os output stream to which information should be written
  \param c a Circle which must be printed
  \return output stream containing center and radius */
ostream& operator << ( ostream &os, Circle c )
{
  return ( os << "c: " << c.m_pCenter << ", r: " << c.m_radius );
}

/*! String coversion for Lua
  \return string representation of circle */
const char* Circle::__str__()
{
  static char buffer[ 128 ];
  sprintf( buffer,"c: %s, r: %f ", m_pCenter.__str__(), m_radius );
  return buffer;
}

/*! This method sets the values of the circle.
  \param pCenter new center of the circle
  \param radius new radius of the circle
  ( > 0 )
  \return bool indicating whether radius was set */
bool Circle::setCircle( const Point2D& pCenter, float radius )
{
  setCenter( pCenter );
  return setRadius( radius  );
}

/*! This method sets the radius of the circle.
  \param radius new radius of the circle ( > 0 )
  \return bool indicating whether radius was set */
bool Circle::setRadius( float radius )
{
  if ( radius > 0 )
  {
    m_radius = radius;
    return true;
  }
  else
  {
    m_radius = 0.0;
    return false;
  }
}

/*! This method returns the radius of the circle.
  \return radius of the circle */
float Circle::getRadius() const
{
  return m_radius;
}

/*! This method sets the center of the circle.
  \param pCenter new center of the circle
  \return bool indicating whether center was set */
void Circle::setCenter( const Point2D& pCenter )
{
  m_pCenter = pCenter;
}

/*! This method returns the center of the circle.
  \return center of the circle */
Point2D Circle::getCenter() const
{
  return m_pCenter;
}

/*! This method returns the circumference of the circle.
  \return circumference of the circle */
float Circle::getCircumference() const
{
  return 2.0*M_PI*getRadius();
}

/*! This method returns the area inside the circle.
  \return area inside the circle */
float Circle::getArea() const 
{
  return M_PI*getRadius()*getRadius();
}

/*! This method returns a boolean that indicates whether 'p' is located inside
  the circle.
  \param pCenter position of which should be checked whether it is located in the
  circle
  \return bool indicating whether p lies inside the circle */
bool Circle::isInside( const Point2D& pCenter ) const
{
  return m_pCenter.getDistanceTo( pCenter ) < getRadius() ;
}

/*! This method returns the two possible intersection points between two
  circles. This method returns the number of solutions that were found.
  \param c circle with which intersection should be found
  \param p1 will be filled with first solution
  \param p2 will be filled with second solution
  \return number of solutions. */
int Circle::getIntersectionPoints( Circle c, Point2D *p1, Point2D *p2) const
{
  float x0, y0, r0;
  float x1, y1, r1;

  x0 = getCenter().getX();
  y0 = getCenter().getY();
  r0 = getRadius();
  x1 = c.getCenter().getX();
  y1 = c.getCenter().getY();
  r1 = c.getRadius();

  float d, dx, dy, h, a, x, y, p2_x, p2_y;
    
  // first calculate distance between two centers circles P0 and P1.
  dx = x1 - x0;
  dy = y1 - y0;
  d = sqrtf(dx*dx + dy*dy);

  // normalize differences
  dx /= d; dy /= d;

  // a is distance between p0 and point that is the intersection point P2
  // that intersects P0-P1 and the line that crosses the two intersection
  // points P3 and P4.
  // Define two triangles: P0,P2,P3 and P1,P2,P3.
  // with distances a, h, r0 and b, h, r1 with d = a + b
  // We know a^2 + h^2 = r0^2 and b^2 + h^2 = r1^2 which then gives
  // a^2 + r1^2 - b^2 = r0^2 with d = a + b ==> a^2 + r1^2 - (d-a)^2 = r0^2
  // ==> r0^2 + d^2 - r1^2 / 2*d
  a = (r0*r0 + d*d - r1*r1) / (2.0 * d);

  // h is then a^2 + h^2 = r0^2 ==> h = sqrtf( r0^2 - a^2 )
  float arg = r0*r0 - a*a;
  h = (arg > 0.0) ? sqrtf(arg) : 0.0;

  // First calculate P2
  p2_x = x0 + a * dx;
  p2_y = y0 + a * dy;

  // and finally the two intersection points
  x =  p2_x - h * dy;
  y =  p2_y + h * dx;
  p1->setPoint( x, y );
  x =  p2_x + h * dy;
  y =  p2_y - h * dx;
  p2->setPoint( x, y );
  
  return (arg < 0.0) ? 0 : ((arg == 0.0 ) ? 1 :  2);
}

/*! This method returns the size of the intersection area of two circles.
  \param c circle with which intersection should be determined
  \return size of the intersection area. */
float Circle::getIntersectionArea( Circle c ) const
{
  Point2D p1, p2, p3;
  float d, h, dArea;
  AngRad ang;

  d = getCenter().getDistanceTo( c.getCenter() ); // dist between two centers
  if ( d > c.getRadius() + getRadius() )           // larger than sum radii
    return 0.0;                                   // circles do not intersect
  if ( d <= fabs(c.getRadius() - getRadius() ) ) {   // one totally in the other
    float dR = min( c.getRadius(), getRadius() );// return area smallest circle
    return M_PI*dR*dR;
  }

  int iNrSol = getIntersectionPoints( c, &p1, &p2 );
  if ( iNrSol != 2 )
    return 0.0;

  // the intersection area of two circles can be divided into two segments:
  // left and right of the line between the two intersection points p1 and p2.
  // The outside area of each segment can be calculated by taking the part
  // of the circle pie excluding the triangle from the center to the
  // two intersection points.
  // The pie equals pi*r^2 * rad(2*ang) / 2*pi = 0.5*rad(2*ang)*r^2 with ang
  // the angle between the center c of the circle and one of the two
  // intersection points. Thus the angle between c and p1 and c and p3 where
  // p3 is the point that lies halfway between p1 and p2.
  // This can be calculated using ang = asinf( d / r ) with d the distance
  // between p1 and p3 and r the radius of the circle.
  // The area of the triangle is 2*0.5*h*d.

  p3 = p1.getPointOnLineFraction( p2, 0.5 );
  d = p1.getDistanceTo( p3 );
  h = p3.getDistanceTo( getCenter() );
  ang = asinf( d / getRadius() );

  dArea = ang*getRadius()*getRadius();
  dArea = dArea - d*h;

  // and now for the other segment the same story
  h = p3.getDistanceTo( c.getCenter() );
  ang = asinf( d / c.getRadius() );
  dArea = dArea + ang*c.getRadius()*c.getRadius();
  dArea = dArea - d*h;

  return dArea;
}
