#include "conversions.h"

#include <cmath>

using namespace carto::maths;

float pgm::fx = 5.9421434211923247e+02;
float pgm::fy = 5.9104053696870778e+02;
float pgm::cu = 3.3930780975300314e+02;
float pgm::cv = 2.4273913761751615e+02;

float pgm::R[9] = {9.9984628826577793e-01, 1.2635359098409581e-03, -1.7487233004436643e-02,
                   -1.4779096108364480e-03, 9.9992385683542895e-01, -1.2251380107679535e-02,
                   1.7470421412464927e-02, 1.2275341476520762e-02, 9.9977202419716948e-01};
Vector3f pgm::T = Vector3f(1.9985242312092553e-02, -7.4423738761617583e-04, -1.0916736334336222e-02);
/*
float pgm::cx = 1.0950266051;
float pgm::cy = .9124876196;
float pgm::ox = .04651979;
float pgm::oy = .0518825414;
//*/
/*
float pgm::cx = .9760954873;
float pgm::cy = .8915603106;
float pgm::ox = .0382362501;
float pgm::oy = .0230908135;
//*/

Vector3f pgm::toRGBCameraCoordinates(const Vector2u &pixel, const float depth)
{
    // z = depth (found with depth camera)
    // x, y, z into the depth camera's plan
    float z = depth;
    float x = ((pixel.x - pgm::cu) * z) / pgm::fx;
    float y = ((pixel.y - pgm::cv) * z) / pgm::fy;

    // Rotate
    float rgb_x = R[0] * x + R[1] * y + R[2] * z;
    float rgb_y = R[3] * x + R[4] * y + R[5] * z;

    // Translate
    rgb_x += T.x;
    rgb_y += T.y;

/*
    // Application of correction function
    rgb_x = (rgb_x - pgm::ox) / pgm::cx;
    rgb_y = (rgb_y - pgm::oy) / pgm::cy;
//*/

    return Vector3f(rgb_x, rgb_y, z);
}

Vector2u pgm::toDepthImageCoordinates(const Vector3f &position)
{
    float x = position.x;
    float y = position.y;

/*
    // Unapplication of correction function
    x = pgm::cx * x + pgm::ox;
    y = pgm::cy * y + pgm::oy;
//*/

    // Translate
    x -= T.x;
    y -= T.y;

    /* In our case, R^-1 can be made like this :
[ a b c
  d e f
  g h i ]
===>
[ a d g
  b e h
  c f i ] */

    float dx = R[0] * x + R[3] * y + R[6] * (position.z - T.z);
    float dy = R[1] * x + R[4] * y + R[7] * (position.z - T.z);

    unsigned int u = (unsigned int)(roundf((dx * pgm::fx) / position.z + pgm::cu));
    unsigned int v = (unsigned int)(roundf((dy * pgm::fy) / position.z + pgm::cv));

    return Vector2u(u, v);
}
