#include <cstdio>
#include <cmath>
#include <limits>//This library is used to get the double max value.
#include "point.h"
#include "rays.h"
#include "world.h"

#define F_INFINITY std::numeric_limits<double>::infinity()

inline double square( double num ){
	return num*num;
}

inline double dist3DSq( Point p1, Point p2 ){//returns the square of the distance between 2 3D points
	return square(p2.x-p1.x) + square(p2.y-p1.y) + square(p2.z-p1.z);
}
inline double dist3D( Point p1, Point p2 ){
	return sqrt( dist3DSq( p1, p2 ) );
}



Ray::Ray( Point setP1, Point setP2 ){
	p1 = setP1;
	p2 = setP2;
	//length = dist3D(x1, y1, z1, x2, y2, z2);
}

bool Ray::pointsAt( Point point ){//Make sure point is in fromt of ray (on each axis, from ray p1 to ray p2 is the same direction as ray p1 to point)
	return	(  ( p2.x >= p1.x )  ==  ( point.x >= p1.x )  )  &&
			(  ( p2.y >= p1.y )  ==  ( point.y >= p1.y )  )  &&
			(  ( p2.z >= p1.z )  ==  ( point.z >= p1.z )  )  &&
			dist3DSq( p1, point ) > INTERSECT_ERR;
}

bool Ray::inRange( Point point ){
	return 	(  ( point.x >= p1.x )  ==  ( point.x <= p2.x )  )  &&
			(  ( point.y >= p1.y )  ==  ( point.y <= p2.y )  )  &&
			(  ( point.z >= p1.z )  ==  ( point.z <= p2.z )  )  &&
			dist3DSq( p2, point ) > INTERSECT_ERR;
}

double Ray::getLength(){
	return dist3D( p1, p2 );
}

Ray& Ray::normalize(){
	double length = dist3D( p1, p2 );
	p2.x = ( p2.x - p1.x ) / length  +  p1.x;
	p2.y = ( p2.y - p1.y ) / length  +  p1.y;
	p2.x = ( p2.z - p1.z ) / length  +  p1.z;
	return *this;
}

double Ray::cosAngleToUVec( Point normalRay ){
	return dot(  ( p2 - p1 ) /= getLength(),  normalRay  );
}

double cosAngleBetween( Ray ray1, Ray ray2 ){
	return dot(  ( ray1.p2 - ray1.p1 ) / ray1.getLength(),  ( ray2.p2 - ray2.p1 ) / ray2.getLength()  );
}


CRay::CRay( Ray setRay ){
	ray = setRay;
	//length = dist3D(x1, y1, z1, x2, y2, z2);
	color.r = 0;
	color.g = 0;
	color.b = 0;
	colorMixLeft = 65535;
	currentIOR = 1;
	nextIOR = 1;
	hitPos.x = F_INFINITY;
	hitPos.y = F_INFINITY;
	hitPos.z = F_INFINITY;
	hitDist = F_INFINITY;
	escape = true;
	bounceCount = 0;
}

void CRay::intersect( Object* object, Color toSet, Point hit, double dist, Point objNormalVec ){
	if( dist <= hitDist ){
		objLastHit = object;
		normalVec = objNormalVec;
		hitDist = dist;
		hitPos = hit;
		castColor = toSet;
		escape = false;
	}
}

/*void CRay::addLight( FloatColor addLightColor ){
	lightColor.r += addLightColor.r;
	lightColor.g += addLightColor.g;
	lightColor.b += addLightColor.b;
}*/

/*void CRay::castBackground( Color backgroundColor ){
	if( escape ){//hitDist >= F_INFINITY
		objLastHit = nullptr;
		normalVec.x = 0;
		normalVec.y = 0;
		normalVec.z = 0;
		setCastColor = backgroundColor;
		setCastColor.a = 65535;
	}
}*/

void CRay::addColor( Color addColor, uint16_t addColorAlpha, FloatColor addLightColor ){
	//if( addLightColor.r < 0 ){ addLightColor.r = 0; }//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<INEFFICIENT!!
	//if( addLightColor.g < 0 ){ addLightColor.g = 0; }
	//if( addLightColor.b < 0 ){ addLightColor.b = 0; }
	double temp = (uint64_t)addColor.r  *  addColorAlpha  *  colorMixLeft / 4294836225  *  addLightColor.r  +  color.r;
	if( temp >= 65535 ){ color.r = 65535; }
	else{ color.r = (uint16_t)temp; }

	temp = (uint64_t)addColor.g  *  addColorAlpha  *  colorMixLeft / 4294836225  *  addLightColor.g  +  color.g;
	if( temp >= 65535 ){ color.g = 65535; }
	else{ color.g = (uint16_t)temp; }

	temp = (uint64_t)addColor.b  *  addColorAlpha  *  colorMixLeft / 4294836225  *  addLightColor.b  +  color.b;
	if( temp >= 65535 ){ color.b = 65535; }
	else{ color.b = (uint16_t)temp; }
	//color.r +=  (uint16_t)(  (uint64_t)addColor.r  *  addColor.a  *  colorMixLeft / 4294836225  *  lightColor.r  );
	//color.g +=  (uint16_t)(  (uint64_t)addColor.g  *  addColor.a  *  colorMixLeft / 4294836225  *  lightColor.g  );
	//color.b +=  (uint16_t)(  (uint64_t)addColor.b  *  addColor.a  *  colorMixLeft / 4294836225  *  lightColor.b  );
	colorMixLeft =  (uint32_t)colorMixLeft  *  (65535 - addColorAlpha) / 65535;
}

//void CRay::finishCast( bool doSetPos, bool doSetColor ){
//	if( doSetPos ){
//		ray.p2 = hitPos;
//	}
//	if( doSetColor ){
//		addColor( setCastColor, setCastColorAlpha, lightColor );
//	}
//
// 	 //if( hitDist < F_INFINITY ){ escape = false; }
//}


