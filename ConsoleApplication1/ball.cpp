#include "ball.hpp"
#include <stdio.h>
#include <iostream>


Ball::Ball()
{
    r = 0.0;
    g = 0.0;
	b = 0.0;
	
}
/**
Ball::Ball(const Ball& a)
{
    p0 = a.p0;
    p0.z = 0;
    velocity = a.velocity;
    velocity.z = 0;
    red = a.red;
    green = a.green;
    blue = a.blue;
    radius_ball = 0.3;
    mass = 2;
}

Ball& Ball::operator=(const Ball& a)
{
    p0 = a.p0;
    p0.z = 0;
    velocity = a.velocity;
    velocity.z = 0;
    red = a.red;
    green = a.green;
    blue = a.blue;
    radius_ball = 0.3;
    mass = 2;
    return *this;
}

void Ball::initBall(urd& pos_x, urd& pos_y,urd& pos_generator, urd&color_gen, std::mt19937& ran)

{   //generate random velocity
    p0.x = pos_x(ran);
    p0.y = pos_y(ran);
    p0.z = 0;
    velocity.x = pos_generator(ran);
    velocity.y = pos_generator(ran);
    velocity.z = 0;
    red = color_gen(ran);
    radius_ball = 0.3;
    mass = 2;
    green = color_gen(ran);
    blue = color_gen(ran);
}
*/

Ball::Ball(const Ball& a)
{
    p01 = a.p01;
    velocity = a.velocity;
    r = a.r;
    g = a.g;
    b = a.b;
    radius_ball = 0.3;
    mass = 2;
}

Ball& Ball::operator=(const Ball& a)
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

void Ball::initBall(urd& pos_x, urd& pos_y, urd& pos_generator, urd& color_gen, std::mt19937& ran)

{   //generate random velocity
    p01.x = pos_x(ran);
    p01.y = pos_y(ran);
   
    velocity.x = pos_generator(ran);
    velocity.y = pos_generator(ran);
    r = color_gen(ran);
    radius_ball = 0.3;
    mass = 2;
    g = color_gen(ran);
    b = color_gen(ran);
}