#include <math.h>
#include <stdio.h>

#ifndef _COBEBE_VECTOR_MACROS
#define _COBEBE_VECTOR_MACROS

#define X 0
#define Y 1
#define Z 2

#define CROSS(dest,v1,v2) \
          dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
          dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
          dest[2]=v1[0]*v2[1]-v1[1]*v2[0]; 

#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])

#define SUB(dest,v1,v2) \
          dest[0]=v1[0]-v2[0]; \
          dest[1]=v1[1]-v2[1]; \
          dest[2]=v1[2]-v2[2]; 

#define FINDMINMAX(x0,x1,x2,min,max) \
  min = max = x0;   \
  if(x1<min) min=x1;\
  if(x1>max) max=x1;\
  if(x2<min) min=x2;\
  if(x2>max) max=x2;

#endif

float rayTriIntersect(float _origin[3], float _direction[3], float _triCoords[3][3]) //USES BARYCENTRIC COORDINATES TO TEST FOR COLLISION
{
	float temp[3];                                  // Holds Barycentric coordinates (area between 2 vertices and the intersection point / total area) and ray magnitude
	float _cross[3];
	CROSS(_cross, _direction, _origin);

	float _a = DOT(_triCoords[0], _cross);

	if (_a < 0.0001 && _a > -0.0001) // First test for collision (Multiple checks vastly shortens runtime over checking after the final calculation)
	{
		return -1;
	}

	float _s[3];
	SUB(_s, _origin, _triCoords[0]);
	temp[0] = DOT(_s, _cross) / _a;

	if (temp[0] < 0.0f || temp[0] > 1.0f) // Second test for collision (x)
	{
		return -1;
	}

	float vertVector[3];
	SUB(vertVector, _triCoords[0], _triCoords[1]);

	CROSS(_cross, _s, vertVector);
	temp[1] = DOT(_direction, _cross) / _a;

	if (temp[1] < 0.0f || temp[1] + temp[0] > 1.0f) // Third test for collision (y and (1 - x - y) as barycentric coordinates add to 1) 
	{
		return -1;
	}

	SUB(vertVector, _triCoords[0], _triCoords[2]);

	temp[2] = DOT(vertVector, _cross) / _a;

	return temp[2];
}