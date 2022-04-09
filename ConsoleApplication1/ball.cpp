#include "ball.hpp"



Ball::Ball()
{
    r = 0.0;
    g = 0.0;
	b = 0.0;
	
}
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

Ball& Ball::operator<<(const Ball& a) {
	p01 = a.p01;
	velocity = a.velocity;
	r = a.r;
	g = a.g;
	b = a.b;
	radius_ball = 0.3;
	mass = 2;
	return *this;
}



std::iostream& operator<<(std::iostream& out , const Ball& a)
{
	out <<  a.r << " " << a.g << " " << a.b << " " << a.radius_ball << " " << a.mass;
	return out;
}
/**
Ball& Ball::operator<<(const Ball& a ) {
    p01 = a.p01;
    velocity = a.velocity;
    r = a.r;
    g = a.g;
    b = a.b;
    radius_ball = 0.3;
    mass = 2;
    return *this;
}
*/
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


