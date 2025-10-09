// flying_bats.cpp
// This application shows animated flying bats.` 
// Marquette University 
// Fred J. Frigo
// 03-Oct-2025
//
// To compile: cc flying_bats.cpp -lGL -lGLU -lglut -lstdc++ -lm -o flying_bats

#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

struct Vec2 { float x,y; };

struct Bat {
    Vec2 pos;
    Vec2 vel;
    float size;
    float flapPhase;
    float flapSpeed;
};

const int WINDOW_W = 800;
const int WINDOW_H = 600;

std::vector<Bat> bats;
float globalTime = 0.0f;

float frand(float a, float b) { return a + (b-a) * (float(rand())/RAND_MAX); }

void initBats(int count) {
    bats.clear();
    for(int i=0;i<count;i++){
        Bat b;
        b.pos = { frand(-0.9f,0.9f), frand(-0.8f,0.8f) };
        b.vel = { frand(0.2f,0.6f) * (b.pos.x<0?1:-1), frand(-0.2f,0.2f) };
        b.size = frand(0.05f,0.12f);
        b.flapPhase = frand(0,6.28f);
        b.flapSpeed = frand(3.0f,6.0f);
        bats.push_back(b);
    }
}

void drawMoon(float x, float y, float radius, int segments = 60) {
    glColor3f(1.0f, 1.0f, 0.8f); // pale yellow moon
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for(int i=0;i<=segments;i++) {
            float angle = i * 2.0f * M_PI / segments;
            glVertex2f(x + cosf(angle)*radius, y + sinf(angle)*radius);
        }
    glEnd();
}

void drawBat(const Bat& b, float t) {
    float flap = sinf(t*b.flapSpeed + b.flapPhase) * 40.0f;

    glPushMatrix();
    glTranslatef(b.pos.x, b.pos.y, 0);
    glScalef(b.size * 2.5f, b.size * 2.5f, 1);

    glColor3f(1.0f, 1.0f, 0.2f);  // Yellow bats

    // Body
    glBegin(GL_TRIANGLES);
        glVertex2f( 0.2f,  0.0f);
        glVertex2f(-0.05f, 0.06f);
        glVertex2f(-0.05f,-0.06f);
    glEnd();

    // Left wing
    glPushMatrix();
        glRotatef(flap, 0,0,1);
        glBegin(GL_TRIANGLES);
            glVertex2f(-0.02f, 0.0f);
            glVertex2f(-0.6f,  0.3f);
            glVertex2f(-0.1f,  0.05f);
        glEnd();
    glPopMatrix();

    // Right wing
    glPushMatrix();
        glRotatef(-flap, 0,0,1);
        glBegin(GL_TRIANGLES);
            glVertex2f(-0.02f, 0.0f);
            glVertex2f(-0.1f, -0.05f);
            glVertex2f(-0.6f, -0.3f);
        glEnd();
    glPopMatrix();

    glPopMatrix();
}

void display() {
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f); // Dark blue sky
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1,1,-1,1,-1,1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw moon in top-right corner
    drawMoon(0.7f, 0.6f, 0.2f);

    // Draw bats
    for (auto &b : bats) {
        drawBat(b, globalTime);
    }

    glutSwapBuffers();
}

void update(int value) {
    float dt = 0.016f;
    globalTime += dt;

    for(auto &b : bats){
        b.pos.x += b.vel.x * dt * 0.3f;
        b.pos.y += b.vel.y * dt * 0.3f;

        if(b.pos.x > 1.1f) b.pos.x = -1.1f;
        if(b.pos.x < -1.1f) b.pos.x =  1.1f;
        if(b.pos.y > 1.0f) b.pos.y = -1.0f;
        if(b.pos.y < -1.0f) b.pos.y =  1.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    srand((unsigned)time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_W, WINDOW_H);
    glutCreateWindow("Flying Yellow Bats - Night Sky with Moon");

    initBats(40);

    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}

