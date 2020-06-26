#include <math.h>
#include <stdio.h>

bool aabb(float _positionA[3], float _sizeA[3], float _positionB[3], float _sizeB[3])
{
	if (_positionA[0] > _positionB[0]) // a right of b
	{
		if (_positionA[0] - _sizeA[0] > _positionB[0] + _sizeB[0]) // left edge of a greater than right edge of b (not colliding)
		{
			return false;
		}
	}
	else
	{
		if (_positionB[0] - _sizeB[0] > _positionA[0] + _sizeA[0])
		{
			return false;
		}
	}

	if (_positionA[2] > _positionB[2]) // a front of b
	{
		if (_positionA[2] - _sizeA[2] > _positionB[2] + _sizeB[2]) // back edge of a greater than front edge of b (not colliding)
		{
			return false;
		}
	}
	else
	{
		if (_positionB[2] - _sizeB[2] > _positionA[2] + _sizeA[2])
		{
			return false;
		}
	}

	if (_positionA[1] > _positionB[1]) // a above b
	{
		if (_positionA[1] - _sizeA[1] > _positionB[1] + _sizeB[1]) // bottom edge of a greater than top edge of b (not colliding)
		{
			return false;
		}
	}
	else
	{
		if (_positionB[1] - _sizeB[1] > _positionA[1] + _sizeA[1])
		{
			return false;
		}
	}

	return true;
}