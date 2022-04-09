
#ifndef ball_hpp
#define ball_hpp

#include "vector.h"
#include "ball.hpp"
#include <random>
#include <iostream>

typedef std::uniform_real_distribution<> urd;

class Ball
{
public:
    Ball();
    Ball(const Ball& a);
    Vector2<float> p01;
	Vector2<float> velocity;
    float r;
    float g;
    float b;
    float radius_ball = 0.2;
    float mass = radius_ball * 0.125;
    Ball& operator=(const Ball& a);
    Ball & operator<<(const Ball& a );
    /**std::iostream& operator<<(std::iostream& out, const Ball& a) {
		out << a.p01 << " " << a.velocity << " " << a.r << " " << a.g << " " << a.b << " " << a.radius_ball << " " << a.mass;
		return out;
    }
	*/
	//std::iostream& operator>>(std::iostream& in, Ball& a);
	//Ball & operator<<(std::iostream & out);
    void initBall(urd& pos_x, urd& pos_y,urd& pos_generator, urd&color_gen, std::mt19937& ran);
};

#endif 
