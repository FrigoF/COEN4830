// Marquette University / W. Wisconsin Avenue traffic scene
// GLUT + legacy OpenGL. Campus geometry is a visual approximation, not surveyed GIS data.
// Ubuntu: g++ city_marquette.cpp -o city_marquette -lglut -lGL -lGLU
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <string>

const float ROAD_LENGTH = 115.0f;
const float ROAD_WIDTH = 18.0f;
bool running = true;
float cameraAngle = 90.0f, cameraHeight = 32.0f, cameraDistance = 62.0f;
const float CAMERA_TARGET_X = -32.0f; // Gesu Church
const float CAMERA_TARGET_Z = -22.0f;

struct Car { float x, z, speed; float r,g,b; };
Car cars[] = {
    {-45,-4.1f, 0.24f, 0.85f,0.10f,0.10f}, {-22,-4.1f, 0.20f, 0.10f,0.35f,0.90f},
    {  4,-4.1f, 0.28f, 0.95f,0.75f,0.05f}, { 38,-4.1f, 0.22f, 0.10f,0.65f,0.25f},
    { 45, 4.1f,-0.23f, 0.75f,0.20f,0.80f}, { 18, 4.1f,-0.27f, 0.25f,0.25f,0.25f},
    {-12, 4.1f,-0.20f, 0.95f,0.45f,0.05f}, {-38, 4.1f,-0.25f, 0.15f,0.70f,0.75f}
};
const int NCARS = sizeof(cars)/sizeof(cars[0]);

void cube(float x,float y,float z,float sx,float sy,float sz) {
    glPushMatrix(); glTranslatef(x,y,z); glScalef(sx,sy,sz); glutSolidCube(1); glPopMatrix();
}
void text3D(float x,float y,float z,const std::string& s) {
    glDisable(GL_LIGHTING); glColor3f(0.08f,0.08f,0.08f); glRasterPos3f(x,y,z);
    for(char c:s) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,c);
    glEnable(GL_LIGHTING);
}
void textScreen(float x,float y,const std::string& s) {
    glDisable(GL_DEPTH_TEST); glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity(); gluOrtho2D(0,glutGet(GLUT_WINDOW_WIDTH),0,glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity(); glColor3f(0.05f,0.05f,0.05f); glRasterPos2f(x,y);
    for(char c:s) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,c);
    glPopMatrix(); glMatrixMode(GL_PROJECTION); glPopMatrix(); glMatrixMode(GL_MODELVIEW); glEnable(GL_DEPTH_TEST); glEnable(GL_LIGHTING);
}
void drawRoad() {
    // Asphalt roadway; center strip is a raised, landscaped median.
    glColor3f(0.20f,0.20f,0.21f); cube(0,0.04f,0,ROAD_LENGTH,0.08f,ROAD_WIDTH);
    glColor3f(0.30f,0.52f,0.28f); cube(0,0.16f,0,ROAD_LENGTH,0.24f,2.8f);
    glDisable(GL_LIGHTING);
    // Dashed lane dividers in each carriageway
    glColor3f(0.95f,0.83f,0.12f);
    for(float x=-ROAD_LENGTH/2;x<ROAD_LENGTH/2;x+=8) {
        cube(x,0.10f,-4.5f,4.0f,0.025f,0.12f);
        cube(x,0.10f, 4.5f,4.0f,0.025f,0.12f);
    }
    glColor3f(0.92f,0.92f,0.92f);
    cube(0,0.10f,-ROAD_WIDTH/2+0.35f,ROAD_LENGTH,0.025f,0.12f);
    cube(0,0.10f, ROAD_WIDTH/2-0.35f,ROAD_LENGTH,0.025f,0.12f);
    glEnable(GL_LIGHTING);
}
void drawWindows(float x,float z,float w,float d,float h) {
    glDisable(GL_LIGHTING); glColor3f(0.30f,0.62f,0.78f);
    float faceZ=z+d/2+0.035f;
    for(float yy=2.0f; yy<h-1; yy+=3.0f)
      for(float xx=-w/2+1.2f; xx<w/2-0.7f; xx+=2.6f) cube(x+xx,yy,faceZ,1.1f,1.45f,0.07f);
    glEnable(GL_LIGHTING);
}
void building(float x,float z,float w,float d,float h,float r,float g,float b,const std::string& name) {
    glColor3f(r,g,b); cube(x,h/2,z,w,h,d);
    drawWindows(x,z,w,d,h);
    glColor3f(r*0.78f,g*0.78f,b*0.78f); cube(x,h+0.15f,z,w*0.96f,0.3f,d*0.96f);
    text3D(x-w/2+0.3f,h+0.8f,z+d/2+0.4f,name);
}
void marquetteHall(float x,float z) {
    // Historic hall body and a recognizable raised bell tower silhouette.
    building(x,z,14,13,18,0.70f,0.62f,0.53f,"Marquette Hall");
    glColor3f(0.58f,0.48f,0.40f); cube(x-3.2f,21.0f,z+1.0f,5.2f,6.0f,5.0f);
    glColor3f(0.52f,0.42f,0.34f); cube(x-3.2f,25.2f,z+1.0f,4.5f,2.4f,4.5f);
    glColor3f(0.45f,0.36f,0.29f); glPushMatrix(); glTranslatef(x-3.2f,27.0f,z+1.0f); glutSolidCone(2.5,4.0,8,4); glPopMatrix();
}
void gesuChurch(float x,float z) {
    // French-Gothic-inspired Gesu: long nave, pitched roof, twin front towers.
    const float brickR=0.62f, brickG=0.54f, brickB=0.46f;
    glColor3f(brickR,brickG,brickB); cube(x,6.0f,z,21.0f,12.0f,14.0f);
    glColor3f(0.42f,0.36f,0.31f);
    // Nave pitched roof represented by two sloped roof planes (rotated boxes).
    glPushMatrix(); glTranslatef(x,13.0f,z); glRotatef(26.0f,0,0,1); cube(0,0,0,12.0f,1.0f,15.0f); glPopMatrix();
    glPushMatrix(); glTranslatef(x,13.0f,z); glRotatef(-26.0f,0,0,1); cube(0,0,0,12.0f,1.0f,15.0f); glPopMatrix();
    // Front-facing facade and two towers toward Wisconsin Avenue (positive Z).
    glColor3f(0.66f,0.57f,0.49f); cube(x,8.0f,z+7.4f,13.0f,16.0f,1.8f);
    for(float tx : {-7.6f,7.6f}) {
        glColor3f(0.58f,0.48f,0.40f); cube(x+tx,12.0f,z+7.0f,4.2f,24.0f,4.2f);
        glColor3f(0.45f,0.37f,0.30f); glPushMatrix(); glTranslatef(x+tx,25.0f,z+7.0f); glutSolidCone(2.5,5.0,8,4); glPopMatrix();
    }
    // Tall central pointed arch/entry accent
    glColor3f(0.22f,0.20f,0.18f); cube(x,5.0f,z+8.45f,2.2f,7.0f,0.18f);
    glColor3f(0.25f,0.55f,0.70f); cube(x,10.5f,z+8.5f,1.5f,2.2f,0.2f);
    text3D(x-7.5f,27.0f,z+9.2f,"Church of the Gesu");
}
void tree(float x,float z) {
    // Trees are intentionally placed in the Wisconsin Avenue center median.
    glColor3f(0.38f,0.23f,0.12f); cube(x,1.3f,z,0.35f,2.6f,0.35f);
    glColor3f(0.10f,0.42f,0.18f); glPushMatrix(); glTranslatef(x,3.7f,z); glutSolidSphere(1.55,16,12); glPopMatrix();
}
void streetLamp(float x,float z) {
    glColor3f(0.22f,0.22f,0.22f); cube(x,3.2f,z,0.18f,6.4f,0.18f); cube(x+0.8f,6.2f,z,1.6f,0.18f,0.18f);
    glColor3f(0.95f,0.88f,0.55f); cube(x+1.5f,6.0f,z,0.55f,0.35f,0.5f);
}
void streetSign(float x,float z,const std::string& label) {
    glColor3f(0.18f,0.18f,0.18f); cube(x,2.0f,z,0.18f,4.0f,0.18f);
    glColor3f(0.12f,0.32f,0.12f); cube(x,4.3f,z,5.4f,1.0f,0.25f); text3D(x-2.35f,4.3f,z+0.18f,label);
}
void drawCampus() {
    glColor3f(0.30f,0.52f,0.28f); cube(0,-0.25f,0,135,0.5f,55);
    // Sidewalks on both sides of Wisconsin Avenue
    glColor3f(0.58f,0.58f,0.58f); cube(0,0.12f,-10.3f,ROAD_LENGTH,0.22f,3.0f); cube(0,0.12f,10.3f,ROAD_LENGTH,0.22f,3.0f);
    // Wisconsin Avenue buildings, in the requested left-to-right order:
    // Marquette Hall, Gesu Church, Cudahy Hall, Raynor Library, Haggerty Hall.
    // Each has a separate footprint and visible gap; coordinates are illustrative.
    marquetteHall(-58,-23);
    gesuChurch(-32,-22);
    building(-6,-23,13,13,23,0.60f,0.58f,0.52f,"Cudahy Hall");
    building(20,-23,16,15,19,0.68f,0.64f,0.58f,"Raynor Library");
    building(48,-23,17,15,21,0.62f,0.67f,0.70f,"Haggerty Hall");
    // Center-median trees down Wisconsin Avenue. Keep trees out of the traffic lanes.
    for(float x=-49;x<=49;x+=12) tree(x,0.0f);
    // Street lights are outside the curb lanes, not in the tree median.
    for(float x=-48;x<=48;x+=24) { streetLamp(x,-10.0f); streetLamp(x+10,10.0f); }
    streetSign(-54,-10.0f,"WISCONSIN AVE");
    streetSign(52,10.0f,"MARQUETTE");
}
void drawCar(const Car& c) {
    glPushMatrix(); glTranslatef(c.x,0.0f,c.z); if(c.speed<0) glRotatef(180,0,1,0);
    glColor3f(c.r,c.g,c.b); cube(0,0.85f,0,4.2f,1.2f,1.8f);
    glColor3f(0.55f,0.75f,0.90f); cube(-0.35f,1.55f,0,2.2f,0.75f,1.35f);
    glColor3f(0.08f,0.08f,0.08f); for(int side=-1;side<=1;side+=2) for(int axle=-1;axle<=1;axle+=2) cube(axle*1.25f,0.35f,side*0.95f,0.75f,0.55f,0.22f);
    glColor3f(1.0f,0.92f,0.65f); cube(2.12f,0.8f,-0.55f,0.12f,0.25f,0.25f); cube(2.12f,0.8f,0.55f,0.12f,0.25f,0.25f);
    glColor3f(0.9f,0.05f,0.05f); cube(-2.12f,0.8f,-0.55f,0.12f,0.25f,0.25f); cube(-2.12f,0.8f,0.55f,0.12f,0.25f,0.25f);
    glPopMatrix();
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    float a=cameraAngle*3.1415926f/180.0f;
    gluLookAt(CAMERA_TARGET_X+cameraDistance*cos(a),cameraHeight,CAMERA_TARGET_Z+cameraDistance*sin(a),CAMERA_TARGET_X,0,CAMERA_TARGET_Z,0,1,0);
    drawCampus(); drawRoad(); for(int i=0;i<NCARS;i++) drawCar(cars[i]);
    textScreen(18,glutGet(GLUT_WINDOW_HEIGHT)-28,"Marquette University - W. Wisconsin Avenue | Space: pause | A/D: rotate | W/S: height | +/-: zoom | Esc: quit");
    glutSwapBuffers();
}
void update(int) {
    if(running) for(int i=0;i<NCARS;i++) { cars[i].x+=cars[i].speed; if(cars[i].x>ROAD_LENGTH/2) cars[i].x=-ROAD_LENGTH/2; if(cars[i].x<-ROAD_LENGTH/2) cars[i].x=ROAD_LENGTH/2; }
    glutPostRedisplay(); glutTimerFunc(16,update,0);
}
void keyboard(unsigned char k,int,int) {
    switch(k) { case 'a': case 'A': cameraAngle-=5; break; case 'd': case 'D': cameraAngle+=5; break;
      case 'w': case 'W': cameraHeight+=2; break; case 's': case 'S': cameraHeight-=2; break;
      case '+': case '=': cameraDistance-=3; if(cameraDistance<25) cameraDistance=25; break;
      case '-': cameraDistance+=3; if(cameraDistance>150) cameraDistance=150; break; case ' ': running=!running; break; case 27: std::exit(0); }
    glutPostRedisplay();
}
void reshape(int w,int h) { if(h==0) h=1; glViewport(0,0,w,h); glMatrixMode(GL_PROJECTION); glLoadIdentity(); gluPerspective(55.0,(double)w/h,1.0,250.0); glMatrixMode(GL_MODELVIEW); }
void init() {
    glEnable(GL_DEPTH_TEST); glEnable(GL_LIGHTING); glEnable(GL_LIGHT0); glEnable(GL_COLOR_MATERIAL); glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    GLfloat pos[]={-30.0f,70.0f,45.0f,1.0f}, ambient[]={0.35f,0.35f,0.35f,1.0f}, diffuse[]={0.85f,0.85f,0.85f,1.0f};
    glLightfv(GL_LIGHT0,GL_POSITION,pos); glLightfv(GL_LIGHT0,GL_AMBIENT,ambient); glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse); glClearColor(0.62f,0.78f,0.93f,1.0f);
}
int main(int argc,char**argv) {
    glutInit(&argc,argv); glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH); glutInitWindowSize(1280,800); glutCreateWindow("Marquette University - Wisconsin Avenue Traffic"); init();
    glutDisplayFunc(display); glutReshapeFunc(reshape); glutKeyboardFunc(keyboard); glutTimerFunc(16,update,0); glutMainLoop(); return 0;
}
