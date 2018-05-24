#include "3dmath.h"
#include "../sys/utils.h"
#include "../sys/syswin.h"
#include "v3f.h"
#include "v4f.h"
#include "v3i.h"
#include "../sys/syswin.h"

float clipf(float n, float lower, float upper)
{
	return maxf(lower, minf(n, upper));
}

int clipi(int n, int lower, int upper)
{
	return maxi(lower, mini(n, upper));
}

v3f vmin(float mf, v3f v)
{
	v.x = minf(mf, v.x);
	v.y = minf(mf, v.y);
	v.z = minf(mf, v.z);
	return v;
}

float mag3f(v3f v)
{
	return (float)sqrtf( (v.x * v.x) + (v.y * v.y) + (v.z * v.z) );
}

float mag4f(v4f v)
{
	return (float)sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

v4f norm4f(v4f v)
{
	float d = mag4f(v);
	v4fmul(&v, v, 1.0f / d);
	return v;
}

float mag2f(v2f v)
{
	return (float)sqrtf( (v.x * v.x) + (v.y * v.y) );
}

float dot3f3(v3f v)
{
	return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

//TODO these funcs need better names

float dot3f2(v3f v)
{
	return (v.x * v.x) + (v.z * v.z);
}

int dot2i2(v2i v)
{
	return v.x*v.x + v.y*v.y;
}

// manhattan distance
int man2i(v2i v)
{
	//return std::max(abs(vec.x), abs(vec.y));
	return iabs(v.x) + iabs(v.y);
}

v3f norm3f(v3f n)
{
	float m;
 
	m = mag3f(n);

	n.x /= m;
	n.y /= m;
	n.z /= m;

	return n;
}

v2f norm2f(v2f n)
{
	float m;
 
	m = mag2f(n);

	n.x /= m;
	n.y /= m;

	return n;
}

v3f cross3f(v3f v1, v3f v2)
{
	v3f n;

	n.x = ((v1.y * v2.z) - (v1.z * v2.y));
	n.y = ((v1.z * v2.x) - (v1.x * v2.z));
	n.z = ((v1.x * v2.y) - (v1.y * v2.x));

	return n;
}


v3f tov3f(v3f p1, v3f p2)
{
	v3f v;

	v.x = p1.x - p2.x;
	v.y = p1.y - p2.y;
	v.z = p1.z - p2.z;

	return v;
}

// Clockwise
v3f tnorm(v3f t[])
{
	v3f v1;
	v3f v2;
	v3f n;
	
	v1 = tov3f(t[2], t[0]);
 	v2 = tov3f(t[1], t[0]);

	n = cross3f(v1, v2);

	n = norm3f(n);

	return n;
}

// Counter-clockwise
v3f tnorm2(v3f t[])
{
	v3f v1;
	v3f v2;
	v3f n;
	
	v1 = tov3f(t[2], t[0]);
	v2 = tov3f(t[1], t[0]);

	n = cross3f(v2, v1);

	n = norm3f(n);

	return n;
}

#if 0
Vec3f IntersectionPoint(Vec3f vNormal, Vec3f vLine[], double distance)
{
	Vec3f vPoint;
	Vec3f vLineDir;
	double Numerator = 0.0, Denominator = 0.0, dist = 0.0;

	// Here comes the confusing part.  We need to find the 3D point that is actually
	// on the plane.  Here are some steps to do that:

	// 1)  First we need to get the vector of our line, Then normalize it so it's a length of 1
	vLineDir = Vector(vLine[1], vLine[0]);		// Get the Vector of the line
	vLineDir = Normalize(vLineDir);				// Normalize the lines vector


												// 2) Use the plane equation (distance = Ax + By + Cz + D) to find the distance from one of our points to the plane.
												//    Here I just chose a arbitrary point as the point to find that distance.  You notice we negate that
												//    distance.  We negate the distance because we want to eventually go BACKWARDS from our point to the plane.
												//    By doing this is will basically bring us back to the plane to find our intersection point.
	Numerator = -(vNormal.x * vLine[0].x +		// Use the plane equation with the normal and the line
		vNormal.y * vLine[0].y +
		vNormal.z * vLine[0].z + distance);

	// 3) If we take the dot product between our line vector and the normal of the polygon,
	//    this will give us the cosine of the angle between the 2 (since they are both normalized - length 1).
	//    We will then divide our Numerator by this value to find the offset towards the plane from our arbitrary point.
	Denominator = Dot(vNormal, vLineDir);		// Get the dot product of the line's vector and the normal of the plane

												// Since we are using division, we need to make sure we don't get a divide by zero error
												// If we do get a 0, that means that there are INFINATE points because the the line is
												// on the plane (the normal is perpendicular to the line - (Normal.Vector = 0)).
												// In this case, we should just return any point on the line.

	if (Denominator == 0.0)						// Check so we don't divide by zero
		return vLine[0];						// Return an arbitrary point on the line

												// We divide the (distance from the point to the plane) by (the dot product)
												// to get the distance (dist) that we need to move from our arbitrary point.  We need
												// to then times this distance (dist) by our line's vector (direction).  When you times
												// a scalar (single number) by a vector you move along that vector.  That is what we are
												// doing.  We are moving from our arbitrary point we chose from the line BACK to the plane
												// along the lines vector.  It seems logical to just get the numerator, which is the distance
												// from the point to the line, and then just move back that much along the line's vector.
												// Well, the distance from the plane means the SHORTEST distance.  What about in the case that
												// the line is almost parallel with the polygon, but doesn't actually intersect it until half
												// way down the line's length.  The distance from the plane is short, but the distance from
												// the actual intersection point is pretty long.  If we divide the distance by the dot product
												// of our line vector and the normal of the plane, we get the correct length.  Cool huh?

	dist = Numerator / Denominator;				// Divide to get the multiplying (percentage) factor

												// Now, like we said above, we times the dist by the vector, then add our arbitrary point.
												// This essentially moves the point along the vector to a certain distance.  This now gives
												// us the intersection point.  Yay!

	vPoint.x = (float)(vLine[0].x + (vLineDir.x * dist));
	vPoint.y = (float)(vLine[0].y + (vLineDir.y * dist));
	vPoint.z = (float)(vLine[0].z + (vLineDir.z * dist));

	return vPoint;								// Return the intersection point
}
#endif

dbool intpg(v3f poly[], v3f line[], v3f *n, float *origindist)
{
#if 0 //TODO
	float d1=0, d2=0;						// The distances from the 2 points of the line from the plane

	*n = tnorm(poly);

	// Let's find the distance our plane is from the origin.  We can find this value
	// from the normal to the plane (polygon) and any point that lies on that plane (Any vertice)
	origindist = PlaneDistance(n, poly[0]);

	// Get the distance from point1 from the plane using: Ax + By + Cz + D = (The distance from the plane)

	d1 = ((n->x * line[0].x)  +					// Ax +
				 (n->y * line[0].y)  +					// Bx +
				 (n->z * line[0].z)) + origindist;	// Cz + D

	// Get the distance from point2 from the plane using Ax + By + Cz + D = (The distance from the plane)

	d2 = ((n->x * line[1].x)  +					// Ax +
				 (n->y * line[1].y)  +					// Bx +
				 (n->z * line[1].z)) + origindist;	// Cz + D

	// Now that we have 2 distances from the plane, if we times them together we either
	// get a positive or negative number.  If it's a negative number, that means we collided!
	// This is because the 2 points must be on either side of the plane (IE. -1 * 1 = -1).

	if(d1 * d2 >= 0)			// Check to see if both point's distances are both negative or both positive
		return dfalse;


	// Now that we have our normal and distance passed back from IntersectedPlane(), 
	// we can use it to calculate the intersection point.  The intersection point
	// is the point that actually is ON the plane.  It is between the line.  We need
	// this point test next, if we are inside the polygon.  To get the I-Point, we
	// give our function the normal of the plan, the points of the line, and the originDistance.

	Vec3f vTemp = IntersectionPoint(vNormal, vLine, originDistance);

	// Now that we have the intersection point, we need to test if it's inside the polygon.
	// To do this, we pass in :
	// (our intersection point, the polygon, and the number of vertices our polygon has)


	const double MATCH_FACTOR = 0.9999;		// Used to cover up the error in floating point
	double Angle = 0.0;						// Initialize the angle
	Vec3f vA, vB;						// Create temp vectors

										// Just because we intersected the plane, doesn't mean we were anywhere near the polygon.
										// This functions checks our intersection point to make sure it is inside of the polygon.
										// This is another tough function to grasp at first, but let me try and explain.
										// It's a brilliant method really, what it does is create triangles within the polygon
										// from the intersection point.  It then adds up the inner angle of each of those triangles.
										// If the angles together add up to 360 degrees (or 2 * PI in radians) then we are inside!
										// If the angle is under that value, we must be outside of polygon.  To further
										// understand why this works, take a pencil and draw a perfect triangle.  Draw a dot in
										// the middle of the triangle.  Now, from that dot, draw a line to each of the vertices.
										// Now, we have 3 triangles within that triangle right?  Now, we know that if we add up
										// all of the angles in a triangle we get 180° right?  Well, that is kinda what we are doing,
										// but the inverse of that.  Say your triangle is an equilateral triangle, so add up the angles
										// and you will get 180° degree angles.  60 + 60 + 60 is 360°.

	for (int i = 0; i < verticeCount; i++)		// Go in a circle to each vertex and get the angle between
	{
		vA = Vector(Poly[i], vIntersection);	// Subtract the intersection point from the current vertex
												// Subtract the point from the next vertex
		vB = Vector(Poly[(i + 1) % verticeCount], vIntersection);

		Angle += AngleBetweenVectors(vA, vB);	// Find the angle between the 2 vectors and add them all up as we go along
	}

	// Now that we have the total angles added up, we need to check if they add up to 360 degrees.
	// Since we are using the dot product, we are working in radians, so we check if the angles
	// equals 2*PI.  We defined PI in math3d.h.  You will notice that we use a MATCH_FACTOR
	// in conjunction with our desired degree.  This is because of the inaccuracy when working
	// with floating point numbers.  It usually won't always be perfectly 2 * PI, so we need
	// to use a little twiddling.  I use .9999, but you can change this to fit your own desired accuracy.

	if (Angle >= (MATCH_FACTOR * (2.0 * M_PI)))	// If the angle is greater than 2 PI, (360 degrees)
	{
		if (vIntersection != NULL)
			(*vIntersection) = vTemp;

		return true;
	}


#endif
	return dfalse;
}

float dot3f(v3f v1, v3f v2)
{
	return ( (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) );
}

float dot4f(v4f v1, v4f v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w));
}

int dot3i(v3i v1, v3i v2)
{
	return ( (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) );
}

int dot2i(v2i v1, v2i v2)
{
	return ( (v1.x * v2.x) + (v1.y * v2.y) );
}

double angle3f(v3f v1, v3f v2)
{
	float dot, vmag;
	double angle;
	
	dot = dot3f(v1, v2);
	vmag = mag3f(v1) * mag3f(v2);
	angle = acos( dot / vmag );

	if(_isnan(angle))
		return 0;

	return( angle );
}

#if 0
v4f norm4f(v4f t[4])
{
	v4f n;

	//angle3f(n,t[0]-t[1])=pi/2
	//angle3f(n,t[0]-t[2])=pi/2
	//angle3f(n,t[0]-t[3])=pi/2

	return n;
}
#endif

#if 0
float DYaw(c3f *c, v3f p)
{
	v3f d;
	float yaw, yaw2, yaw3, dyaw, dyaw2, dyaw3, mindyaw;
	
	d.x = p.x - c->pos.x;
	d.y = p.y - c->pos.y;
	d.z = p.z - c->pos.z;
	yaw = yawf(d.x, d.z);
	yaw2 = yaw - DEGTORAD(360.0f);
	yaw3 = yaw + DEGTORAD(360.0f);

	dyaw = yaw - yaw3f(c);
	dyaw2 = yaw2 - c->yaw();
	dyaw3 = yaw3 - c->yaw();

	mindyaw = dyaw;

	if(fabs(dyaw2) < fabs(mindyaw))
		mindyaw = dyaw2;

	if(fabs(dyaw3) < fabs(mindyaw))
		mindyaw = dyaw3;

	return mindyaw;
}
#endif
v3f intpl(v3f n, v3f line[], double d)
{
	v3f p, ldir;
	double num, denom, d2;
	
	num = denom = d2 = 0.0;

	// Here comes the confusing part.  We need to find the 3D point that is actually
	// on the plane.  Here are some steps to do that:

	// 1)  First we need to get the vector of our line, Then normalize it so it's a length of 1
	ldir = tov3f(line[1], line[0]);		// Get the vector of the line
	ldir = norm3f(ldir);				// Normalize the lines vector


	// 2) Use the plane equation (distance = Ax + By + Cz + D) to find the distance from one of our points to the plane.
	//    Here I just chose a arbitrary point as the point to find that distance.  You notice we negate that
	//    distance.  We negate the distance because we want to eventually go BACKWARDS from our point to the plane.
	//    By doing this is will basically bring us back to the plane to find our intersect point.
	num = - (n.x * line[0].x +		// Use the plane equation with the normal and the line
				   n.y * line[0].y +
				   n.z * line[0].z + d);

	// 3) If we take the dot product between our line vector and the normal of the polygon,
	//    this will give us the cosine of the angle between the 2 (since they are both normalized - length 1).
	//    We will then divide our Numerator by this value to find the offset towards the plane from our arbitrary point.
	denom = dot3f(n, ldir);		// Get the dot product of the line's vector and the normal of the plane

	// Since we are using division, we need to make sure we don't get a divide by zero error
	// If we do get a 0, that means that there are INFINATE points because the the line is
	// on the plane (the normal is perpendicular to the line - (norm.vector = 0)).
	// In this case, we should just return any point on the line.

	if( denom == 0.0)						// Check so we don't divide by zero
		return line[0];						// Return an arbitrary point on the line

	// We divide the (distance from the point to the plane) by (the dot product)
	// to get the distance (dist) that we need to move from our arbitrary point.  We need
	// to then times this distance (dist) by our line's vector (direction).  When you times
	// a scalar (single number) by a vector you move along that vector.  That is what we are
	// doing.  We are moving from our arbitrary point we chose from the line BACK to the plane
	// along the lines vector.  It seems logical to just get the numerator, which is the distance
	// from the point to the line, and then just move back that much along the line's vector.
	// Well, the distance from the plane means the SHORTEST distance.  What about in the case that
	// the line is almost parallel with the polygon, but doesn't actually intersect it until half
	// way down the line's length.  The distance from the plane is short, but the distance from
	// the actual intersect point is pretty long.  If we divide the distance by the dot product
	// of our line vector and the normal of the plane, we get the correct length.  Cool huh?

	d2 = num / denom;				// Divide to get the multiplying (percentage) factor

	// Now, like we said above, we times the dist by the vector, then add our arbitrary point.
	// This essentially moves the point along the vector to a certain distance.  This now gives
	// us the intersect point.  Yay!

	p.x = (float)(line[0].x + (ldir.x * d2));
	p.y = (float)(line[0].y + (ldir.y * d2));
	p.z = (float)(line[0].z + (ldir.z * d2));

	return p;								// Return the intersect point
}

v3f rot3f(v3f v, float rad, float x, float y, float z)
{
	v3f newv;
	float costheta, sintheta;
	costheta = (float)cos(rad);
	sintheta = (float)sin(rad);

	newv.x  = (costheta + (1 - costheta) * x * x)		 *v.x;
	newv.x += ((1 - costheta) * x * y - z * sintheta)	 *v.y;
	newv.x += ((1 - costheta) * x * z + y * sintheta)	 *v.z;

	newv.y  = ((1 - costheta) * x * y + z * sintheta)	 *v.x;
	newv.y += (costheta + (1 - costheta) * y * y)		 *v.y;
	newv.y += ((1 - costheta) * y * z - x * sintheta)	 *v.z;

	newv.z  = ((1 - costheta) * x * z - y * sintheta)	 *v.x;
	newv.z += ((1 - costheta) * y * z + x * sintheta)	 *v.y;
	newv.z += (costheta + (1 - costheta) * z * z)		 *v.z;

	return newv;
}

v3f rotab3f(v3f v, v3f around, float rad, float x, float y, float z)
{
	v.x -= around.x;
	v.y -= around.y;
	v.z -= around.z;
	v = rot3f(v, rad, x, y, z);
	v.x += around.x;
	v.y += around.y;
	v.z += around.z;
	return v;
}

float yawf(float dx, float dz)
{
	return RADTODEG( atan2(dx, dz) );
}

/*
// http://webglfactory.blogspot.ca/2011/06/how-to-create-view-matrix.html
mf lookAt(v3f eye, v3f target, v3f up)
{
		 v3f vz= tnorm(eye - target);
		 v3f vx = normalize(crossProduct(up, vz));
		 // vy doesn't need to be normalized because it's a cross
		 // product of 2 normalized vectors
		 v3f vy = crossProduct(vz, vx);
		 mf inverseViewmf = mf(v4f(vx, 0), v4f(vy, 0), v4f(vz, 0), v4f(eye, 1));
		 return inverseViewmf.getInverse();
}
*/

v3f tonearo3f(int x, int y, int width, int height, v3f posvec, v3f sidevec, v3f upvec)
{
	float halfw, halfh, ratiox, ratioy, aspect, wnear, hnear;
	v3f result;
	
	halfw = (float)width / 2.0f;
	halfh = (float)height / 2.0f;

	ratiox = (x - halfw) / halfw;
	ratioy = -(y - halfh) / halfh;

	aspect = fabsf((float)width / (float)height);
	wnear = PROJ_RIGHT * aspect / g_zoom;
	hnear = PROJ_RIGHT / g_zoom;
	
	v3fmul(&sidevec, sidevec, ratiox * wnear);
	v3fmul(&upvec, upvec, ratioy * hnear);
	v3fadd(&result, posvec, sidevec);
	v3fadd(&result, result, upvec);

	return result;
}

v3f tonearp3f(int x, int y, int width, int height, v3f posvec, v3f sidevec, v3f upvec, v3f viewdir, float fov, float mind)
{
	float halfw, halfh, ratiox, ratioy, aspect, wnear, hnear;
	v3f result;
	
	viewdir = norm3f(viewdir);
	
	halfw = (float)width / 2.0f;
	halfh = (float)height / 2.0f;
	
	ratiox = (x - halfw) / halfw;
	ratioy = -(y - halfh) / halfh;

	aspect = fabsf((float)width / (float)height);
	hnear = 2 * tan( DEGTORAD(fov) / 2) * mind;
	wnear = hnear * aspect;
	
	v3fmul(&viewdir, viewdir, mind);
	v3fmul(&sidevec, sidevec, ratiox * wnear);
	v3fmul(&upvec, upvec, ratioy * hnear);
	v3fadd(&result, posvec, sidevec);
	v3fadd(&result, result, upvec);
	v3fadd(&result, result, viewdir);

	return result;
}

v3f screenpray3f(int x, int y, int width, int height, v3f posvec, v3f sidevec, v3f upvec, v3f viewdir, float fov)
{
	float halfw, halfh, ratiox, ratioy, aspect, wnear, hnear;
	v3f result;
	
	viewdir = norm3f(viewdir);
	
	halfw = (float)width / 2.0f;
	halfh = (float)height / 2.0f;
	
	ratiox = (x - halfw) / halfw;
	ratioy = -(y - halfh) / halfh;
	
	aspect = fabsf((float)width / (float)height);
	hnear = 2 * tan( DEGTORAD(fov) / 2);
	wnear = hnear * aspect;

	v3fmul(&sidevec, sidevec, ratiox * wnear / 2.0f);
	v3fmul(&upvec, upvec, ratioy * hnear / 2.0f);
	v3fadd(&result, posvec, sidevec);
	v3fadd(&result, result, upvec);
	v3fadd(&result, result, viewdir);
	
	return result;
}

float snapf(float base, float value)
{
	int count;
	
	count = value / base;

	return count * base;
}

float snapfnear(float base, float value)
{
	int count;
 
	count = (value + base/2.0f) / base;

	return count * base;
}
