#include <iostream>
#include <stdlib.h> 
#include <math.h>
#include <random>
#include <pthread.h>
#include <GL/glut.h>
#include "ball.hpp"
#include "Quebuffer.h"
#include "ball.h"
#include "balls.h"

#include <string>

#include <fstream>


class Box
{
public:
    void Inizitalitionbox()
    {
        glBegin(GL_LINE_LOOP);
        //glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(boxHeight, boxWidth);
        glVertex2f(boxHeight, -boxWidth);
        glVertex2f(-boxHeight, -boxWidth);
        glVertex2f(-boxHeight, boxWidth);
        glEnd();

    }
    /*Box(const Box& b)
    {
        InnerBoxHeight_l = b.InnerBoxHeight_l;
        InnerBoxHeight_r = b.InnerBoxHeight_r;
        InnerBoxWidth_bottom = b.InnerBoxWidth_bottom;
        InnerBoxWidth_top = b.InnerBoxWidth_top;
    }*/

    Box& operator=(const Box& b)
    {
        InnerBoxHeight_l = b.InnerBoxHeight_l;
        InnerBoxHeight_r = b.InnerBoxHeight_r;
        InnerBoxWidth_bottom = b.InnerBoxWidth_bottom;
        InnerBoxWidth_top = b.InnerBoxWidth_top;
        return *this;
    }

    float boxWidth = 2.0f;
    float boxHeight = 2.0f;
    float InnerBoxHeight_l = 0.1f;
    float InnerBoxHeight_r = 0.1f;
    float InnerBoxWidth_top = 0.1f;
    float InnerBoxWidth_bottom = 0.1f;
};
Box box;

#pragma region Global_variables
#define NUMBER_OF_SEGMENTS 30
std::vector<Ball> Balls; //Number of ball object in vector
std::vector<ball2> Balls1; //vector containing balls_number Ball objects

GLfloat Speed = 0.8f; 
GLfloat Speed_1 = 1.0f;

int number_of_walls = 4;

float radius_ball = 0.1f;
int balls_number = 10;
int threads_number = 10;
int intervall_timer = 10;
int threads_counter = 3;//trhead timer
int prevIndex = balls_number;

#pragma region objectsGlobals
Box boxObject;
std::vector<Box> BoxLines;
pthread_mutex_t inizializerMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t inizilazierConditions = PTHREAD_COND_INITIALIZER;
std::vector<pthread_mutex_t> vecMutexThreads;
std::vector<pthread_cond_t> vecContidionThreads;
std::vector<bool> vecStartCond;
std::vector< Quebuffer<Ball> > vecBallQueue;
std::vector<Vector2<float>> vecSpeed2d;
std::vector < Quebuffer<ball1>> vecBallDropQueue;
std::vector<pthread_t> vecThreads;
std::vector<pthread_t> vecThreads2;
#pragma endregion


std::vector<float> vecSize(balls_number);
#pragma endregion

#pragma region CreateObject
class objects
{
public:

    //Draw circle points
    float X[NUMBER_OF_SEGMENTS + 1][NUMBER_OF_SEGMENTS + 1];
    float Y[NUMBER_OF_SEGMENTS + 1][NUMBER_OF_SEGMENTS + 1];

    void operator()()
    {
        std::cout << "Application Running";
        glClearColor(0.0, 0.0, 1.0, 1.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glEnable(GL_DEPTH_TEST);
        //InizitalitionRandomBalls();
        inizialsionDropBalls();
        InizitalitionRandomBalls();

    }
    void InizitalitionRandomBalls()
    {
        Balls.reserve(balls_number);
        std::mt19937 random_color_gen((std::random_device())());
        // the middle between the box cordinate pos_x pos_y. ball 
        std::uniform_real_distribution<> pos_x(-0.5f + radius_ball, 1.5f - radius_ball);
        std::uniform_real_distribution<> pos_y(-0.5f + radius_ball, 1.5f - radius_ball);
        std::uniform_real_distribution<> pos_generator(-0.15f, 0.15f);
        std::uniform_real_distribution<> speed_generator(-0.1f, 0.1f);
        std::uniform_real_distribution<> size_generator(0.1f, 0.3f);
        std::uniform_real_distribution<> angle_generator(0.0f, 360.0f);
        std::uniform_real_distribution<> color_generator(0.0f, 1.0f);
        std::uniform_real_distribution<> color_generator_2(0.0f, 1.0f);
        std::uniform_real_distribution<> color_generator_3(0.0f, 1.0f);
        std::uniform_real_distribution<> color_generator_4(0.0f, 1.0f);

        std::uniform_real_distribution<> color_gen(0.2, 1.0);


        for (int i = 0; i < balls_number; i++)
        {

            Ball newBall;
            newBall.initBall(pos_x, pos_y, pos_generator, color_gen, random_color_gen);
            Balls.push_back(newBall);

        }
        
        for (int i = 0; i <= NUMBER_OF_SEGMENTS; i++)
        {
            // DrawsCircle
            float first_angle = i * 2 * M_PI / NUMBER_OF_SEGMENTS;
            for (int j = 0; j <= NUMBER_OF_SEGMENTS; j++)
            {
                float reverse_angle = j * 2 * M_PI / NUMBER_OF_SEGMENTS;
                X[i][j] = cos(first_angle) * sin(reverse_angle);
                Y[i][j] = sin(first_angle) * sin(reverse_angle); }}}
    void operator()(Ball& ball)
    {
        //cout<<Z[0][0]<<endl;
        glColor3f(ball.r, ball.g, ball.b);
        for (int i = 0; i < NUMBER_OF_SEGMENTS; i++)
        {
            for (int j = 0; j < NUMBER_OF_SEGMENTS; j++)
            {
                glBegin(GL_POLYGON);
                glNormal3f(X[i][j], Y[i][j], 0.0);
                glVertex3f(ball.p01.x + ball.radius_ball * X[i][j], ball.p01.y + ball.radius_ball * Y[i][j], 0.0f);
                glNormal3f(X[i][j + 1], Y[i][j + 1], 0.0f);
                glVertex3f(ball.p01.x + ball.radius_ball * X[i][j + 1], ball.p01.y + ball.radius_ball * Y[i][j + 1], 0.0f);
                glNormal3f(X[i + 1][j + 1], Y[i + 1][j + 1], 0.0f);
                glVertex3f(ball.p01.x + ball.radius_ball * X[i + 1][j + 1], ball.p01.y + ball.radius_ball * Y[i + 1][j + 1], 0.0f);
                glNormal3f(X[i + 1][j], Y[i + 1][j], 0.0f);
                glVertex3f(ball.p01.x + ball.radius_ball * X[i + 1][j], ball.p01.y + ball.radius_ball * Y[i + 1][j], 0.0f);
                glEnd();
            }
        }
		
		
#pragma region Box
        float boxWidth = 2.0f;
        float boxHeight = 2.0f;
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex2f(boxHeight, boxWidth);
        glVertex2f(boxHeight, -boxWidth);
        glVertex2f(-boxHeight, -boxWidth);
        glVertex2f(-boxHeight, boxWidth);
        glEnd();
#pragma endregion

    }
	
    void inizialsionDropBalls() 
    {
        Balls1.reserve(balls_number);
		

    }
    
    void operator()(ball2& ball)
    {
		
			
            glBegin(GL_TRIANGLE_FAN);
            //double ox = 0.0, oy = 0.0, 
            ball.radius_ball = 1;
            ball.p01.x = 0.0;
            ball.p01.y = 0.0;
		
			glColor3f(1.0, 0.0, 0.0);
            int triangles = 32;
            //glVertex2f(ox, oy);

            glVertex2f(ball.p01.x, ball.p01.y);
            for (int i = 0; i <= triangles; i++)
            {
                ball.angle= i * 2.0 * M_PI / triangles;
                glVertex2f(ball.p01.x + ball.radius_ball * cos(ball.angle), ball.p01.y + ball.radius_ball * sin(ball.angle));
            }
            glEnd();

           
			/**
            glPushMatrix();
            glColor3f(i->red, i->green, i->blue);				// color of ball
            glTranslatef(i->x, i->y, 0.0);
            glRotatef(i->a0, 0.0, 0.0, 1.0);
            glScalef(i->radius, i->radius, 1.0);
            //glScalef(i->radius, i->radius, 1.0);
            //glCallList(DisplayListsBase + DL_BALL);
            glPopMatrix();
			/**
            * 
            */
			/**
    }
    void createBall() {
        glBegin(GL_TRIANGLE_FAN);
        double ox = 0.0, oy = 0.0, radius = 1.0;
        int triangles = 32;
        glVertex2f(ox, oy);
        for (int i = 0; i <= triangles; i++)
        {
            double angle = i * 2.0 * M_PI / triangles;
            glVertex2f(ox + radius * cos(angle), oy + radius * sin(angle));
        }
        glEnd();
		*/
		

       
    }
};


objects object;



class objectsBalls2
{
public:
    void operator()()
    {
        std::cout << "Application Running";
        glClearColor(0.0, 0.0, 1.0, 1.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glEnable(GL_DEPTH_TEST);
        //InizitalitionRandomBalls();
        inizialsionDropBalls();
        //InizitalitionRandomBalls();
    }

    void inizialsionDropBalls()
    {
        Balls1.reserve(balls_number);
        for (int i = 0; i < balls_number; i++)
        {
           ball2 newBall;
           //newBall.initBall(NUMBER_OF_SEGMENTS, CentreX,radius_ball,_);
           Balls1.push_back(newBall);
        }
    }
    void operator()(ball2& ball)
    {
        //DrawBall(int segments, double ballX, double ballY, double radius, double angle) 
        glBegin(GL_TRIANGLE_FAN);
		
        glVertex2f(ball.p01.x, ball.p01.y);
        for (int i = 0; i <= ball.segments; i++) {
            ball.angle = i * 2 * M_PI / ball.segments;
            glVertex2f(ball.p01.x + ball.radius_ball * cos(ball.angle), ball.p01.y + ball.radius_ball * sin(ball.angle));
        }
        glEnd();
    }
};


objectsBalls2 objectsBalls;

#pragma endregion

#pragma region CollsionWithBox
//
//void InnerboxCollision(Ball & ball) 
//{
//	if(ball.p0.x + ball.radius_ball > box.InnerBoxWidth)
//    {
//        ball.p0.x = box.InnerBoxWidth - ball.radius_ball;
//        ball.velocity.x *= -1;
//        ball.blue;
//    }
//    if (ball.p0.x - ball.radius_ball < -box.InnerBoxWidth)
//    {
//        ball.p0.x = -box.InnerBoxWidth + ball.radius_ball;
//        ball.velocity.x *= -1;
//        ball.red;
//    }
//    if (ball.p0.y + ball.radius_ball > box.InnerBoxHeight)
//    {
//        ball.p0.y = box.InnerBoxHeight - ball.radius_ball;
//        ball.velocity.y *= -1;
//    }
//    if (ball.p0.y - ball.radius_ball < -box.InnerBoxHeight)
//    {
//        ball.p0.y = -box.InnerBoxHeight + ball.radius_ball;
//        ball.velocity.y *= -1;
//    }
//}

void boxCollsion(Ball& ball)
{
    /*ball.p0.x = ball.p0.x + ball.velocity.y;
    ball.p0.y = ball.p0.y + ball.velocity.y;*/
	
    if (ball.p01.x + ball.radius_ball > box.boxWidth)
    {
        ball.p01.x = box.boxWidth - ball.radius_ball;
        ball.velocity.x *= -1;
        ball.b;
    }
    if (ball.p01.x - ball.radius_ball < -box.boxWidth)
    {
        ball.p01.x = -box.boxWidth + ball.radius_ball;
        ball.velocity.x *= -1;
        ball.r;
    }
    if (ball.p01.y + ball.radius_ball > box.boxHeight)
    {
        ball.p01.y = box.boxHeight - ball.radius_ball;
        ball.velocity.y *= -1;
    }
    if (ball.p01.y - ball.radius_ball < -box.boxHeight)
    {
        ball.p01.y = -box.boxHeight + ball.radius_ball;
        ball.velocity.y *= -1;
    }

}
void Collision1(ball2& ball) 
{
    /**
    if (ball->ballY > BALL_SCALE + 60) {
        i->accelerationY = ((gravity * i->mass) + (i->airRecistanceCoefficient * i->velocityY * i->velocityY)) / i->mass;
        i->velocityY = i->accelerationY * i->timerY * 0.01 + i->v0Y;                                                            //i->velocityY = i->v0Y + (i->Vt * tanh((gravity * i->timerY * 0.01) / i->Vt));
        i->ballY += i->velocityY;
        i->timerY++;
    }*/
	/*
    if (ball.p01.y > ) {
        i->accelerationY = ((gravity * i->mass) + (i->airRecistanceCoefficient * i->velocityY * i->velocityY)) / i->mass;
        i->velocityY = i->accelerationY * i->timerY * 0.01 + i->v0Y;                                                            //i->velocityY = i->v0Y + (i->Vt * tanh((gravity * i->timerY * 0.01) / i->Vt));
        i->ballY += i->velocityY;
        i->timerY++;
	

    else {
        i->v0Y = fabs(i->velocityY);
        i->timerY = 0;
        i->angle = compute_angle_after_collision(i->angle, 0.0);
        i->ballY += i->v0Y;
    }

    if (i->ballX > BALL_SCALE + 60) {
        i->accelerationX = -(i->airRecistanceCoefficient * i->velocityX * i->velocityX) / i->mass;
        i->velocityX = i->accelerationX * i->timerX * 0.01 + i->v0X;
        i->ballX += i->v0X;
        i->timerX++;
    }

    else {
        i->v0X = fabs(i->velocityX);
        i->timerX = 0;
        i->angle = compute_angle_after_collision(i->angle, 90.0);
        i->ballX += i->v0X;
    }

    if (i->ballX < 0 || i->ballX > WindowWidth || i->ballY < 0 || i->ballY > WindowHeight) //sletter ball når den exiter vinduet
        to_erase.push_back(i);
		*/
	
}


//void collisionBall2(Ball& ball)
//{
//    //Check collisions with walls
//    for (auto i = vecBallDropQueue.begin(); i != vecBallDropQueue.end(); i++) {
//        
//
//		
//        if (i BALL_SCALE + 60) {
//            i->velocityY = i->accelerationY * i->timer * 0.01 + i->v0Y;
//            i->ballY += i->velocityY;
//            cout << fixed << setprecision(2) << "Time:" << i->timer * 0.01 << "s" //print til console
//                << " | Position: (x = " << i->ballX << ", y = " << i->ballY << ")"
//                << " | Velocity x, y: (" << i->velocityX << " m/s, " << i->velocityY << " m/s)" << endl;
//            stringstream buffer;
//            buffer << fixed << setprecision(2) << "Time:" << i->timer * 0.01 << "s" //cout til string
//                << " | Position: (x = " << i->ballX << ", y = " << i->ballY << ")"
//                << " | Velocity x, y: (" << i->velocityX << " m/s, " << i->velocityY << " m/s)";
//            string output = buffer.str();
//            glColor3f(1, 0, 0);
//
//            drawText(output.data(), output.size(), 350, 20);
//        }
//
//
//        else {
//            i->v0Y = fabs(i->velocityY);
//            i->timer = 0;
//            i->angle = compute_angle_after_collision(i->angle, 0.0);
//            i->ballY += i->v0Y;
//        }
//
//        i->timer++;
//
//        if (i->ballX < BALL_SCALE + 60) {
//            i->angle = compute_angle_after_collision(i->angle, 90.0);
//            i->velocityX = fabs(i->v0X);
//            i->ballX += i->velocityX;
//        }
//
//        if (i->ballX < 0 || i->ballX > WindowWidth || i->ballY < 0 || i->ballY > WindowHeight) //sletter ball når den exiter vinduet
//            to_erase.push_back(i);
//
//        //check collisions with other balls
//        for (auto j = balls1.begin(); j != balls1.end(); j++) {
//            if (i != j && (fabs((i->ballX - j->ballX) * (i->ballX - j->ballX) +
//                (i->ballY - j->ballY) * (i->ballY - j->ballY))) <=
//                4.0 * BALL_SCALE * BALL_SCALE) {
//                double angle_centerline = compute_angle(i->ballX, i->ballY, j->ballX, j->ballY);
//                double angle_wall = normalize_angle(angle_centerline + 90.0);
//                double new_angle =
//                    compute_angle_after_collision(i->angle, angle_wall);
//                i->angle = new_angle;
//            }
//        }
//
//    }
//}

#pragma endregion
int counting = 0;

#pragma region updateBallForce
void updateBalls(Ball& a, Ball& b, float Cr)
{
    Vector2<float> temp(b.p01);
    temp.substraction(a.p01);
    Vector2<float> velcoityA(a.velocity);
    Vector2<float> VelocityB(b.velocity);
    if (temp.mod 
    () > ((a.radius_ball + b.radius_ball)))
        return;
    temp.normalized();
    Vector2<float> temp1(temp), temp2(temp), temp3(temp), temp4(temp);
    float A_ball = temp.dot_product(velcoityA);
    float B_ball = temp.dot_product(VelocityB);
    float mass1 = a.mass;
    float mass2 = mass1;
    float v1 = (mass2 * (B_ball - A_ball) + mass1 * A_ball + mass2 * B_ball) / (mass1 + mass2);
    float v2 = (mass1 * (A_ball - B_ball) + mass2 * B_ball + mass1 * A_ball) / (mass1 + mass2);
	/**
    std::cout << "******* BALL COLLSION DETECTION BALLS" << "\n";
    std::cout << "************* Ball Velocity dot A and B************************" << std::endl;
    std::cout << "Ball A: " << v1 << std::endl; std::cout << " Ball B: " << v2 << std::endl;
    std::cout << "Velocity A(dot product) :" << A_ball << std::endl;
    std::cout << "Velocity B(dot product) :" << A_ball << " " << B_ball << std::endl;
    std::cout << "A_ball: " << A_ball << " B_ball: " << B_ball << std::endl;
    std::cout << "************* mass Ball A & B************************" << std::endl;
    std::cout << "mass A: " << mass1 << std::endl << "mass : " << mass2 << std::endl;
    counting++;
    std::cout << "************* counting ************************" << std::endl;
    std::cout << "counting " << counting << std::endl;
    */
	
    temp.scaling(A_ball);
    velcoityA.substraction(temp);
    temp1.scaling(v1);
    velcoityA.add(temp1);
    temp2.scaling(B_ball);
    VelocityB.substraction(temp2);
    temp3.scaling(v2);
    VelocityB.add(temp3);
    velcoityA.compare(a.velocity);
    VelocityB.compare(b.velocity);
    Vector2<float>fpos(a.p01);
    temp4.scaling(a.radius_ball + b.radius_ball + 0.000001);
    fpos.add(temp4);
    fpos.compare(b.p01);

}


void updateBalls2(ball2& b1, ball2& b2, float cr) 
{
	
}




#pragma endregion

#pragma region UpdateBallPosistion

void* balldrop(void* args) 
{
    long i = (long)args;
    int threadRatio = balls_number / threads_number;

    int left = balls_number % threads_number;

    int lessBalls = threads_number - left;
    while (true)

    {
        //wait for signal from timer
        pthread_mutex_lock(&vecMutexThreads[i]);
        while (!vecStartCond[i])
            pthread_cond_wait(&vecContidionThreads[i], &vecMutexThreads[i]);
        pthread_mutex_unlock(&vecMutexThreads[i]);
        //after signal update ball position and check wall collisions
        int startIndex = i * threadRatio;
        int endIndex = startIndex + threadRatio;
        if (i >= lessBalls)
        {
            startIndex += (i - lessBalls);
            endIndex = startIndex + threadRatio + 1;
        }
        for (int j = startIndex; j < endIndex; j++)
        {
            /**Balls[j].p01.add(Balls[j].velocity);
            boxCollsion(Balls[j]);*/

			//update ball position
			
            Balls1[j].p01.add(Balls1[j].velocity);
            //Balls1[j].p01.add(Balls1[j].velocity);
            //boxCollsion(Balls[j]);
        }
        for (int j = 0; j < threads_number; j++)
        {
            if (j != i)
            {
                for (int k = startIndex; k < endIndex; k++)
                    vecBallQueue[j].addbuffer_item(Balls[k]);
            }
        }
        int doneSofar = 0;
        while (doneSofar != balls_number - (endIndex - startIndex))
        {
            Ball m = vecBallQueue[i].remove();
            for (int j = startIndex; j < endIndex; j++)
                updateBalls(m, Balls[j], Speed);
            doneSofar++;

        }

        pthread_mutex_lock(&inizializerMutex);
        threads_counter += 1;
        vecStartCond[i] = false;
        pthread_cond_signal(&inizilazierConditions);
        pthread_mutex_unlock(&inizializerMutex);
		
    }
   



}

void* ballControl(void* args)
{
    long i = (long)args;
    int threadRatio = balls_number / threads_number;

    int left = balls_number % threads_number;

    int lessBalls = threads_number - left;
    while (true)

    {
        //signal for timer funksjon
        pthread_mutex_lock(&vecMutexThreads[i]);
        while (!vecStartCond[i])
            pthread_cond_wait(&vecContidionThreads[i], &vecMutexThreads[i]);
        pthread_mutex_unlock(&vecMutexThreads[i]);
     // venter på oppdatering
        int startIndex = i * threadRatio;
        int endIndex = startIndex + threadRatio;
        if (i >= lessBalls)
        {
            startIndex += (i - lessBalls);
            endIndex = startIndex + threadRatio + 1;
        }
        for (int j = startIndex; j < endIndex; j++)
        {
            Balls[j].p01.add(Balls[j].velocity);
            boxCollsion(Balls[j]);

        }
        for (int j = startIndex; j < endIndex; j++)
        {
            for (int k = j + 1; k < endIndex; k++)
            {
                updateBalls(Balls[j], Balls[k], Speed);
            }
        }
		//legg i buffer kø
#pragma region Threads
        for (int j = 0; j < threads_number; j++)
        {
            if (j != i)
            {
                for (int k = startIndex; k < endIndex; k++)
                    vecBallQueue[j].addbuffer_item(Balls[k]);
            }
        }
        int doneSofar = 0;
        while (doneSofar != balls_number - (endIndex - startIndex))
        {
            Ball m = vecBallQueue[i].remove();
            for (int j = startIndex; j < endIndex; j++)
                updateBalls(m, Balls[j], Speed);
            doneSofar++;
        }
        pthread_mutex_lock(&inizializerMutex);
        threads_counter += 1;
        vecStartCond[i] = false;
        pthread_cond_signal(&inizilazierConditions);
        pthread_mutex_unlock(&inizializerMutex);
#pragma endregion
    }
}

#pragma endregion

#pragma region GlutFunctions
// state machine callsback when a key is press
void handleKeypress(unsigned char key,
    int x, int y)
{
    switch (key) {
    case 27:
        exit(0);
        break;
    }
}



void drawScene() 
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); //Description. glMatrixMode sets the current matrix mode. mode can assume one of four values: GL_MODELVIEW. Applies subsequent matrix operations to the modelview matrix stack.
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -6.4f);
    for (int i = 0; i < balls_number; i++)
        object(Balls[i]);
    //for(int i = 0; i < )
	/**for (int i = 0; i < balls_number; i++)
		object(Balls1[i]);
        */
	/**
	for(int i = 0; i < balls_number; i++)
		object(Balls1[i]);

		*/
	
	
	
    glutSwapBuffers(); 
    //swap the buffer to display the scene
}

void idle()
{
	
    drawScene();
    //drawScene1();
}


void timer(int timerParam)
{
    //std::cout << timerParam << std::endl;
    for (int i = 0; i < threads_number; i++)
    {
        pthread_mutex_lock(&vecMutexThreads[i]);
        vecStartCond[i] = true;
        pthread_cond_signal(&vecContidionThreads[i]);
        pthread_mutex_unlock(&vecMutexThreads[i]);
    }

   //vent signalet
    for (int i = 0; i < threads_number; i++)
    {
        pthread_mutex_lock(&vecMutexThreads[i]);
        vecStartCond[i] = true;
        pthread_cond_signal(&vecContidionThreads[i]);
        pthread_mutex_unlock(&vecMutexThreads[i]);
    }
  //vent på trådene
    pthread_mutex_lock(&inizializerMutex);
    while (threads_counter < threads_number)
    {
        pthread_cond_wait(&inizilazierConditions, &inizializerMutex);
    }
    pthread_mutex_unlock(&inizializerMutex);

    //set counter
    threads_counter = 0;

    glutPostRedisplay();
    glutTimerFunc(intervall_timer, timer, 0);
}

//Called when the window is resized
void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); 
    gluPerspective
    (45.0, (double)1000 / (double)1000, 1.0,200.0);  
		
    

}

static size_t winWidth = 1400, winHeight = 700;
void handleResize1(GLsizei nw, GLsizei nh)
{
    winWidth = nw;
    winHeight = nh;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, winWidth, 0, winHeight);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, winHeight, winHeight);
}

void initRendering()
{
    glEnable(GL_DEPTH_TEST);
}
#pragma endregion
void make_display_lists() 
{


}
int main(int argc, char** argv)
{
    int n;
    std::cout << "Input balls: ";
    std::cin >> n;
    threads_number = balls_number = n;
    vecStartCond.resize(threads_number, false);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000); 
 
    std::vector<pthread_t> ballControlThreads(threads_number);
    std::vector<pthread_t> ballDropThreads(threads_number);
    vecContidionThreads.resize(threads_number);
    vecMutexThreads.resize(threads_number);
    vecBallQueue.resize(threads_number);
    for (int i = 0; i < threads_number; i++)
    {
        pthread_mutex_init(&vecMutexThreads[i], NULL);
        pthread_cond_init(&vecContidionThreads[i], NULL);
    }
    for (int i = 0; i < threads_number; i++)
    {
        int m = i;
        pthread_create(&ballControlThreads[i], NULL, ballControl, (void*)m);
     
    }
    glutCreateWindow("Create Collision Application");
    object();
    initRendering();
    glutDisplayFunc(drawScene);
    glutTimerFunc(intervall_timer, timer, 0);
    glutKeyboardFunc(handleKeypress);
    glutIdleFunc(idle);
    glutReshapeFunc(handleResize);
    glutMainLoop(); 
    return 0;       
}
