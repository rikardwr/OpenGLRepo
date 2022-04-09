#include "balls.h"

ball2::ball2()
{
    r = 0.0;
    g = 0.0;
    b = 0.0;

}
//newBall.initBall(pos_x, pos_y, pos_generator, color_gen, random_color_gen);
ball2::ball2(const ball2& a)
{
    p01 = a.p01;
	
    velocity = a.velocity;
    r = a.r;
    g = a.g;
    b = a.b;
    radius_ball = 0.3;
    mass = 2;
}

ball2& ball2::operator=(const ball2& a)
{
    p01 = a.p01;
    velocity = a.velocity;
    r = a.r;
    g = a.g;
    b = a.b;
    radius_ball = 0.3;
    mass = 2;
    return *this;
}

void ball2::initBall(int _segments, float ballX, float ballY, float _radius_ball, float _angle)
{   //generate random velocity
    p01.x = ballX;
    p01.y = ballY;
    segments = _segments;
    radius_ball = _radius_ball;
	angle = _angle;
    
    velocity.x = 1;
    velocity.y = 1.0;
}

