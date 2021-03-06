#ifndef POINT_H
#define POINT_H

namespace carto
{
	namespace maths
	{
		struct Vector2u
		{
			unsigned int x;
			unsigned int y;

            Vector2u(unsigned int x = 0, unsigned int y = 0);
			Vector2u(const Vector2u &v2u);
			
            Vector2u& operator=(const Vector2u &ori);
        };
        
        struct Vector2d
		{
			int x;
			int y;

            Vector2d(int x = 0, int y = 0);
			Vector2d(const Vector2d &v2d);
			Vector2d(const Vector2u &v2u);
			
            Vector2d &operator=(const Vector2d &ori);
        };

		struct Vector3f
		{
			float x;
			float y;
			float z;

			Vector3f(float x = 0, float y = 0, float z = 0);
            Vector3f(const Vector3f &v3f);
			Vector3f(const Vector2u &v2u);

            Vector3f& operator=(const Vector3f &ori);
        };
	}
}

#endif	// POINT_H
