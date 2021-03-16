#include <glwrap/TriFace.h>

namespace glwrap
{
	float TriFace::getMaxX()
	{
		float maxX = pa.x;

		if (pb.x > maxX)
		{
			maxX = pb.x;
		}

		if (pc.x > maxX)
		{
			maxX = pc.x;
		}

		return maxX;
	}

	float TriFace::getMinX()
	{
		float minX = pa.x;

		if (pb.x < minX)
		{
			minX = pb.x;
		}

		if (pc.x < minX)
		{
			minX = pc.x;
		}

		return minX;
	}

	float TriFace::getMaxY()
	{
		float maxY = pa.y;

		if (pb.y > maxY)
		{
			maxY = pb.y;
		}

		if (pc.y > maxY)
		{
			maxY = pc.y;
		}

		return maxY;
	}

	float TriFace::getMinY()
	{
		float minY = pa.y;

		if (pb.y < minY)
		{
			minY = pb.y;
		}

		if (pc.y < minY)
		{
			minY = pc.y;
		}

		return minY;
	}

	float TriFace::getMaxZ()
	{
		float maxZ = pa.z;

		if (pb.z > maxZ)
		{
			maxZ = pb.z;
		}

		if (pc.z > maxZ)
		{
			maxZ = pc.z;
		}

		return maxZ;
	}

	float TriFace::getMinZ()
	{
		float minZ = pa.z;

		if (pb.z < minZ)
		{
			minZ = pb.z;
		}

		if (pc.z < minZ)
		{
			minZ = pc.z;
		}

		return minZ;
	}
}