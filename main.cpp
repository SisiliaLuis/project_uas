#include <windows.h>
#include "GL/glut.h"
#include "stdio.h"

float view_rotx = 20.0f, view_roty = 30.0f;
int oldMouseX, oldMouseY;

void initGL() {
    glShadeModel(GL_FLAT);

    float ambient[] = {1.0f,1.0f,1.0f,1.0f};
    float diffuse[] = {1.0f,1.0f,1.0f,1.0f};
    float specular[] = {0.2f,1.0f,0.2f,1.0f};
    float position[] = {20.0f,30.0f,20.0f,0.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

    float mambient[] ={0.1745f, 0.01175f, 0.01175f, 0.55f};
    float mdiffuse[] ={0.61424f, 0.04136f, 0.04136f, 0.55f };
    float mspecular[] ={0.727811f, 0.626959f, 0.626959f, 0.55f };
    float mshine =76.8f;

    glMaterialfv(GL_FRONT,GL_AMBIENT,mambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mdiffuse);

    glMaterialfv(GL_FRONT,GL_SPECULAR,mspecular);
    glMaterialf (GL_FRONT,GL_SHININESS,mshine);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
}

void gmbr_drone(){
glBegin(GL_POLYGON);
glColor3f(0.0f,0.0f,0.0f);
//depan
 glVertex3f(0.0f, 0.0f, 0.0f);
 glVertex3f(0.0f, 3.0f, 0.0f);
 glVertex3f(0.5f, 3.5f, 0.0f);
 glVertex3f(2.0f, 3.5f, 0.0f);
 glVertex3f(2.5f, 3.0f, 0.0f);
 glVertex3f(2.5f, 0.0f, 0.0f);

 //belakang
 glColor3f(0.0f,0.0f,0.0f);
 glVertex3f(0.0f, 0.0f, -1.0f);
 glVertex3f(0.0f, 3.0f, -1.0f);
 glVertex3f(0.5f, 3.5f, -1.0f);
 glVertex3f(2.0f, 3.5f, -1.0f);
 glVertex3f(2.5f, 3.0f, -1.0f);
 glVertex3f(2.5f, 0.0f, -1.0f);

 //sampingkiri
 glColor3f(0.0f,0.0f,0.0f);
 glVertex3f(0.0f, 0.0f, 0.0f);
 glVertex3f(0.0f, 3.0f, 0.0f);
 glVertex3f(0.0f, 0.0f, -1.0f);
 glVertex3f(0.0f, 3.0f, -1.0f);

 //sampingkanan
 glColor3f(0.0f,0.0f,0.0f);
 glVertex3f(2.5f, 3.0f, 0.0f);
 glVertex3f(2.5f, 0.0f, 0.0f);
 glVertex3f(2.5f, 3.0f, -1.0f);
 glVertex3f(2.5f, 0.0f, -1.0f);

 //bawah
 glColor3f(0.0f,0.0f,0.0f);
 glVertex3f(0.0f, 0.0f, 0.0f);
 glVertex3f(0.0f, 0.0f, -1.0f);
 glVertex3f(2.5f, 0.0f, -1.0f);
 glVertex3f(2.5f, 0.0f, 0.0f);

 //serongkiri
 glColor3f(0.0f,0.0f,0.0f);
 glVertex3f(0.3f, 0.0f, 0.0f);
 glVertex3f(0.5f, 3.5f, 0.0f);
 glVertex3f(0.3f, 0.0f, -1.0f);
 glVertex3f(0.5f, 3.5f, -1.0f);

 //serongkanan
 glColor3f(0.0f,0.0f,0.0f);
 glVertex3f(2.0f, 3.5f, 0.0f);
 glVertex3f(2.5f, 3.0f, 0.0f);
 glVertex3f(2.0f, 3.5f, -1.0f);
 glVertex3f(2.5f, 3.0f, -1.0f);

 //ataskiri
 glVertex3f(0.5f, 3.5f, 0.0f);
 glVertex3f(0.5f, 3.5f, 0.0f);
 glVertex3f(0.5f, 3.5f, -1.0f);
 glVertex3f(0.5f, 3.3f, -1.0f);

 //ataskanan
 glVertex3f(2.0f, 3.5f, 0.0f);
 glVertex3f(2.0f, 3.5f, 0.0f);
 glVertex3f(2.0f, 3.5f, -1.0f);
 glVertex3f(2.0f, 3.3f, -1.0f);


 glEnd();
}

int sudut = 0;
void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(4,4,4, // eye pos
              0,0,0, // look at
              0,0,1); // up
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
   glTranslatef(0.5f, 0.5f, 0.5f);
    glRotatef(view_rotx, 1.0f, 0.0f, 0.0f);
    glRotatef(view_roty, 0.0f, 1.0f, 0.0f);
    glTranslatef(-0.5f, -0.5f, -0.5f);
    //glRotatef(sudut, 0.0,1.0,0.0);
    gmbr_drone();
    sudut = sudut +3;
    if(sudut == 360){
        sudut = 0;
    }
    glFlush();
    glutSwapBuffers();
}

void timer(int value){
    glutPostRedisplay();
    glutTimerFunc(65, timer, 0);
}

void reshape(GLsizei width, GLsizei height){
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;glViewport(30, 6, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 1.0f, 20.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void mouseControl(int button, int state, int x, int y){
    oldMouseX = x;
    oldMouseY = y;
}

void mouseMotion(int x, int y){
    int getX = x;
    int getY = y;
    float thetaY = 360.0f*(getX - oldMouseX)/640;
    float thetaX = 360.0f*(getY - oldMouseY)/480;
    oldMouseX = getX;
    oldMouseY = getY;
    view_rotx += thetaX;
    view_roty += thetaY;
}
int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("3d-control");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    initGL();
    glutMouseFunc(mouseControl);
    glutMotionFunc(mouseMotion);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
