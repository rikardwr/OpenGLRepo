
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

};

