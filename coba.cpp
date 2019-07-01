#include "GL/glut.h"
#include <stdio.h>


float view_rotx = 20.0f, view_roty = 30.0f;
int oldMouseX, oldMouseY;

void initGL(){
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
void badan(){  
float BODY_LENGTH=0.5f;  
float BODY_RADIUS=1.0f;  
int SLICES=4;  
int STACKS=1;  

    GLUquadric *q = gluNewQuadric();  
	
	gluCylinder(q, BODY_RADIUS, BODY_RADIUS, BODY_LENGTH, SLICES, STACKS);    
    gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS); //lingkaran untuk tutup atas
	glColor3f(0.854f, 0.647f, 0.125f);  
    glTranslatef(0.0f, 0.0f, BODY_LENGTH);  
    gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS); //lingkaran untuk tutup bawah

}  

void sayap(){
	glBegin(GL_POLYGON); // depan
		glColor3f(0.854f, 0.647f, 0.125f);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(0.5,1,0);
    glEnd();

	glBegin(GL_POLYGON); // blkg
		glColor3f(0.854f, 0.647f, 0.125f);
        glVertex3f(0,0,-0.3);
        glVertex3f(1,0,-0.3);
        glVertex3f(0.5,1,-0.3);
    glEnd();

	glBegin(GL_POLYGON); // kiri
        glVertex3f(0,0,0);
        glVertex3f(0,0,-0.3);
        glVertex3f(0.5,1,-0.3);
		glVertex3f(0.5,1,0);
    glEnd();

	glBegin(GL_POLYGON); // kanan
        glVertex3f(1,0,0);
        glVertex3f(1,0,-0.3);
        glVertex3f(0.5,1,-0.3);
		glVertex3f(0.5,1,0);
    glEnd();

	glBegin(GL_POLYGON); // bawah
        glVertex3f(0,0,0);
        glVertex3f(0,0,-0.3);
        glVertex3f(1,0,-0.3);
		glVertex3f(1,0,0);
    glEnd();
}

void kaki(){  
float BODY_LENGTH=2.0f;  
float BODY_RADIUS=0.1f;  
int SLICES=50;  
int STACKS=50;  

    GLUquadric *q = gluNewQuadric();  
	
	gluCylinder(q, BODY_RADIUS, BODY_RADIUS, BODY_LENGTH, SLICES, STACKS);    
    gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS); //lingkaran untuk tutup atas
	glColor3f(0.854f, 0.647f, 0.125f);  
    glTranslatef(0.0f, 0.0f, BODY_LENGTH);  
    gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS); //lingkaran untuk tutup bawah

}  

void baling(){
	glBegin(GL_POLYGON); // atas
        glVertex3f(0,0,0);
        glVertex3f(0.5,0,0);
        glVertex3f(0.4,1,0);
		glVertex3f(0.1,1,0);
    glEnd();

	glBegin(GL_POLYGON); // bawah
        glVertex3f(0,0,0);
        glVertex3f(0.5,0,0);
        glVertex3f(0.4,-1,0);
		glVertex3f(0.1,-1,0);
    glEnd();
}
void koordniat() {
	glTranslatef(0,0,0);
    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(2,0,0);

        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,2,0);

        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,2);
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

	//koordniat();
	glPushMatrix();
	glTranslatef(0, 0, 0);
	badan();
	sayap();
	kaki();
	baling();
	glPopMatrix();
	
	glFlush();
	glutSwapBuffers();
}

void timer(int value){
	glutPostRedisplay();
	glutTimerFunc(15, timer, 0);
}

void reshape(GLsizei width, GLsizei height){
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	glViewport(30, 6, width, height);
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

/* Program entry point */

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