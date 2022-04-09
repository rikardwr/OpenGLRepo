
#include "vector.h"



class ball2 {
public:
	
    ball2();
    ball2(const ball2& a);
    Vector2<float> p01;
    Vector2<float> velocity;
    float angle;
    float r;
    float g;
    float b;
    float segments;
    float radius_ball = 0.2;
    float mass = radius_ball * 0.125;

    ball2& operator=(const ball2& a);

    void initBall(int _segments, float ballX, float ballY, float _radius_ball, float angle);

    float v0X = 1.0;
    float v0Y = 0.0;

};

