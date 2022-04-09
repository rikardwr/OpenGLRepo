
float BALL_SCALE = 10.0;
int dropHeight = 500;
int dropPosFromWall = 0;
const float gravity = -9.81;
static bool paused = false;
bool fullScreen = 0;

class ball1 {
public:
    float r, g, b;
    int segments;
    double ballX;
    double ballY;
    double radius;

    double angle;
    double v0X = 1.0;
    double v0Y = 0.0;
    double velocityX = v0X; //hastighet i x retning
    double velocityY = v0Y; //hastighet i y retning
    double accelerationX;
    double accelerationY = gravity;

    int timer;

    //void RandColor();
};
/**
void ball1::RandColor() {
    float color[3];
    srand(static_cast <unsigned> (time(0)));
    for (int i = 0; i < 3; i++) {
        color[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    }
    r = color[0], g = color[1], b = color[2];
}
*/
