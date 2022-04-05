
#ifndef ball_hpp
#define ball_hpp

#include "vector.h"
#include "ball.hpp"
#include <random>

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

    void initBall(urd& pos_x, urd& pos_y,
        urd& pos_generator, urd&
        color_gen, std::mt19937& ran);
};

#endif 
