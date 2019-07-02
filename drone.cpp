#include "GL/glut.h"
#include <stdio.h>

float rx=-90.0f, ry=0.0f, rz=-180.0f;
float view_rotx = 20.0f, view_roty = 30.0f;
int oldMouseX, oldMouseY;
int sudut1=0.0f, sudut2=0.0f, sudut3=0.0f, sudut4=0.0f;

void initGL(){
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
}
void badan(){  
float BODY_LENGTH=0.5f;  
float BODY_RADIUS=1.25f;  
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
        glVertex3f(0.5,1.5,0);
    glEnd();

	glBegin(GL_POLYGON); // blkg
		glColor3f(0.854f, 0.647f, 0.125f);
        glVertex3f(0,0,-0.3);
        glVertex3f(1,0,-0.3);
        glVertex3f(0.5,1.5,-0.3);
    glEnd();

	glBegin(GL_POLYGON); // kiri
        glVertex3f(0,0,0);
        glVertex3f(0,0,-0.3);
        glVertex3f(0.5,1.5,-0.3);
		glVertex3f(0.5,1.5,0);
    glEnd();

	glBegin(GL_POLYGON); // kanan
        glVertex3f(1,0,0);
        glVertex3f(1,0,-0.3);
        glVertex3f(0.5,1.5,-0.3);
		glVertex3f(0.5,1.5,0);
    glEnd();

	glBegin(GL_POLYGON); // bawah
        glVertex3f(0,0,0);
        glVertex3f(0,0,-0.3);
        glVertex3f(1,0,-0.3);
		glVertex3f(1,0,0);
    glEnd();
}

void kaki(){  
float BODY_LENGTH=1.5f;  
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

void axis() {
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

void kinciran() {
	kaki();
	glTranslatef(-0.25f,0.0f,0.0f);
	baling();
}

int sudut = 0;
void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(4,4,4, // eye pos
	0,0,0, // look at
	0,0,1); // up
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
	//axis();
	glPushMatrix();
	glTranslatef(-2, -2, 2);
	glRotatef(rx, 1.0f, 0.0f, 0.0f);
  	glRotatef(ry, 0.0f, 1.0f, 0.0f);
  	glRotatef(rz, 0.0f, 0.0f, 1.0f);
	//glRotatef(view_rotx, 1.0f, 0.0f, 0.0f);
	//glRotatef(view_roty, 0.0f, 1.0f, 0.0f);
	badan();
	//kanan atas
	glPushMatrix();
		glRotatef(-90, 0.0f,0.0f,1.0f);
		glTranslatef(-0.5f,0.5f,0.0f);
		sayap();
	glPopMatrix();
	glPushMatrix();
		glRotatef(-90, 0.0f,0.0f,1.0f);
		glTranslatef(0.0f,1.75f,-1.0f);
		glRotatef(sudut1, 0.0f,0.0f,1.0f);
		kinciran();
		sudut1+=10;
	glPopMatrix();
	
	//kiri bawah
	glPushMatrix();
		glRotatef(90, 0.0f,0.0f,1.0f);
		glTranslatef(-0.5f,0.5f,0.0f);
		sayap();
	glPopMatrix();
	glPushMatrix();
		glRotatef(90, 0.0f,0.0f,1.0f);
		glTranslatef(0.0f,1.75f,-1.0f);
		glRotatef(sudut2, 0.0f,0.0f,1.0f);
		kinciran();
		sudut2+=10;
	glPopMatrix();

	//kiri atas
	glPushMatrix();
		glRotatef(0, 0.0f,0.0f,1.0f);
		glTranslatef(-0.5f,0.5f,0.0f);
		sayap();
	glPopMatrix();
	glPushMatrix();
		glRotatef(0, 0.0f,0.0f,1.0f);
		glTranslatef(0.0f,1.75f,-1.0f);
		glRotatef(sudut3, 0.0f,0.0f,1.0f);
		kinciran();
		sudut3-=10;
	glPopMatrix();

	//kanan bawah
	glPushMatrix();
		glRotatef(180, 0.0f,0.0f,1.0f);
		glTranslatef(-0.5f,0.5f,0.0f);
		sayap();
	glPopMatrix();
	glPushMatrix();
		glRotatef(180, 0.0f,0.0f,1.0f);
		glTranslatef(0.0f,1.75f,-1.0f);
		glRotatef(sudut4, 0.0f,0.0f,1.0f);
		kinciran();
		sudut4-=10;
	glPopMatrix();

	glPopMatrix();
	
	glFlush();
	glutSwapBuffers();
}

void timer(int value){
	glutPostRedisplay();
	glutTimerFunc(60, timer, 0);
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
	glutCreateWindow("UAS Grafis");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	initGL();
    glutMouseFunc(mouseControl);
    glutMotionFunc(mouseMotion);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	return 0;
}