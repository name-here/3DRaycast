#include <cstdio>
#include <limits>//This library is used to get the double max value.
#include "rays.h"

#define F_INFINITY std::numeric_limits<double>::infinity()


Color::Color( uint16_t setR, uint16_t setG, uint16_t setB, uint16_t setA ){
	r = setR;
	g = setG;
	b = setB;
	a = setA;
}


Point::Point(double setX, double setY, double setZ ){
	x = setX;
	y = setY;
	z = setZ;
}

Point& Point::operator+=( const Point& toAdd ){
	x += toAdd.x;
	y += toAdd.y;
	z += toAdd.z;
	return *this;
}
Point& Point::operator-=( const Point& toSub ){
	x -= toSub.x;
	y -= toSub.y;
	z -= toSub.z;
	return *this;
}
/*Point& Point::operator*=( const Point& toMult ){
	x *= toMult.x;
	y *= toMult.y;
	z *= toMult.z;
	return *this;
}*/
Point& Point::operator*=( const double toMult ){
	x *= toMult;
	y *= toMult;
	z *= toMult;
	return *this;
}
Point& Point::operator/=( const double toDiv ){
	x /= toDiv;
	y /= toDiv;
	z /= toDiv;
	return *this;
}


Ray::Ray( Point setP1, Point setP2 ){
	p1 = setP1;
	p2 = setP2;
	//length = dist3D(x1, y1, z1, x2, y2, z2);
}

CRay::CRay( Ray setRay ){
	ray = setRay;
	//length = dist3D(x1, y1, z1, x2, y2, z2);
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 65535;
	setPos.x = F_INFINITY;
	setPos.y = F_INFINITY;
	setPos.z = F_INFINITY;
	setDist = F_INFINITY;
	escape = true;
	bounceCount = 0;
}
void CRay::intersect( unsigned int id, Color toSet, Point hit, double dist, Point objNormalVec, bool ignoreDirection ){
	if( (ignoreDirection  ||  ( ( (ray.p2.x>ray.p1.x) == (hit.x>ray.p1.x) ) &&
								( (ray.p2.y>ray.p1.y) == (hit.y>ray.p1.y) ) &&
								( (ray.p2.z>ray.p1.z) == (hit.z>ray.p1.z) )  )   )
			&& (dist <= setDist) ){
		objLastHit = id;
		normalVec = objNormalVec;
		setDist = dist;
		setPos = hit;
		if( toSet.a > 0 ){
			setCastColor.r = toSet.r;
			setCastColor.g = toSet.g;
			setCastColor.b = toSet.b;
		}
		setCastColor.a = toSet.a;
	}
}
void CRay::finishCast( bool doSetPos ){
	if( doSetPos ){
		ray.p2 = setPos;
	}
	color.r = ( ((uint64_t)setCastColor.r) * setCastColor.a * color.a / 4294836225 )  +  ( ((uint64_t)color.r) * (4294836225 - (((uint32_t)setCastColor.a) * color.a / 4294836225) ) );
	color.g = ( ((uint64_t)setCastColor.g) * setCastColor.a * color.a / 4294836225 )  +  ( ((uint64_t)color.g) * (4294836225 - (((uint32_t)setCastColor.a) * color.a / 4294836225) ) );
	color.b = ( ((uint64_t)setCastColor.b) * setCastColor.a * color.a / 4294836225 )  +  ( ((uint64_t)color.b) * (4294836225 - (((uint32_t)setCastColor.a) * color.a / 4294836225) ) );
	color.a = ((uint32_t)color.a) * (65535 - setCastColor.a) / 65535;
	if( color.a == 0 ){ escape = false; }
}


