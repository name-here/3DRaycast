#include <cstdint>


struct Color{
	uint16_t r;
	uint16_t g;
	uint16_t b;
	uint16_t a;
	Color( uint16_t setR = 0, uint16_t setG = 0, uint16_t setB = 0, uint16_t setA = 0 );
};


struct Point{
	double x;
	double y;
	double z;
	Point( double setX = 0, double setY = 0, double setZ = 0 );

	Point& operator+=( const Point& toAdd );
	Point& operator-=( const Point& toSub );
	//Point& operator*=( const Point& toMult );
	Point& operator*=( const double toMult );
	Point& operator/=( const double toDiv );
};

inline Point operator+( Point pos1, const Point& pos2 ){
	pos1 += pos2;
	return pos1;
}
inline Point operator-( Point pos1, const Point& pos2 ){
	pos1 -= pos2;
	return pos1;
}
/*inline Point operator*( Point pos1, const Point& pos2 ){
	pos1 *= pos2;
	return pos1;
}*/
inline Point operator*( Point pos, double num ){
	pos *= num;
	return pos;
}
inline Point operator/( Point pos, double num ){
	pos /= num;
	return pos;
}

inline bool operator==( const Point& point1, const Point& point2 ){
	return (point1.x == point2.x)  &&  (point1.y == point2.y)  &&  (point1.z == point2.z);
}
inline bool operator!=( const Point& point1, const Point& point2 ){
	return !( point1 == point2 );
}


struct Ray{
	Point p1;
	Point p2;
	//double length;
	Ray( Point setP1 = Point(), Point setP2 = Point() );
};

class CRay{
	Color setCastColor;
	public:
		Ray ray;
		Color color;
		//double length;
		Point setPos;
		double setDist;
		bool escape;
		uint32_t bounceCount;
		unsigned int objLastHit;
		Point normalVec;
		CRay( Ray setRay = Ray() );
		void intersect( unsigned int id, Color toSet, Point hit, double dist, Point objNormalVec, bool ignoreDirection );
		void finishCast( bool setPos );
};


