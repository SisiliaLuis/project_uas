#include <windows.h>
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <math.h>
#endif
#include <stdlib.h>


float Cx = 0.0f, Cy = 1.0f, Cz = 8.0f;
float Lx = 0.0f, Ly = 2.5f, Lz = -20.0f;
float angle_depanBelakang = 0.0f;
float angle_depanBelakang2 = 0.0f;
float angle_samping = 0.0f;
float angle_samping2 = 0.0f;
float angle_vertikal = 0.0f;
float angle_vertikal2 = 0.0f;
float silinderAngle = 0.0f;
float silinderAngle1 = 0.0f;
float silinderAngle2 = 0.0f;
float silinderAngle3 = 0.0f;
bool ori = true, silinder = false, silinder1 = false, silinder2 = false, silinder3 = false, silinder4 = false, silinder5 = false, kamera = false, kamera1 = false, kamera2 = false, kamera3 = false, kamera4 = false, kamera5 = false;
int sudut1=0.0f, sudut2=0.0f, sudut3=0.0f, sudut4=0.0f;

float toRadians(float angle){
    return angle * M_PI / 180;
}
class Vector{
    public:
    float x, y, z;
    void set_values (float startX, float startY, float startZ){
    x = startX;
    y = startY;
    z = startZ;
}

void vectorRotation(Vector refs, float angle){
    Vector temp = refs;
    float magnitude = sqrt(pow(temp.x, 2) + pow(temp.y, 2) + pow(temp.z, 2));
    temp.x = temp.x / magnitude;
    temp.y = temp.y / magnitude;
    temp.z = temp.z / magnitude;
    float dot_product = (x * temp.x)+(y * temp.y)+(z * temp.z);
    float cross_product_x = (y * temp.z) - (temp.z * z);
    float cross_product_y = -((x * temp.z) - (z * temp.x));
    float cross_product_z = (x * temp.y) - (y * temp.x);
    float last_factor_rodrigues = 1.0f - cos(toRadians(fmod(angle, 360.0f)));
    x = (x * cos(toRadians(fmod(angle, 360.0f)))) + (cross_product_x * sin(toRadians(fmod(angle, 360.0f)))) + (dot_product * last_factor_rodrigues * x);
    y = (y * cos(toRadians(fmod(angle, 360.0f)))) + (cross_product_y * sin(toRadians(fmod(angle, 360.0f)))) + (dot_product * last_factor_rodrigues * y);
    z = (z * cos(toRadians(fmod(angle, 360.0f)))) + (cross_product_z * sin(toRadians(fmod(angle, 360.0f)))) + (dot_product * last_factor_rodrigues * z);
    }
};

Vector depanBelakang, samping, vertikal;
void badan(){
    float BODY_LENGTH=0.5f;
    float BODY_RADIUS=1.25f;
    int SLICES=4;
    int STACKS=1;

    GLUquadric *q = gluNewQuadric();
	gluCylinder(q, BODY_RADIUS, BODY_RADIUS, BODY_LENGTH, SLICES, STACKS);
    gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS); //lingkaran untuk tutup atas
	glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, BODY_LENGTH);
    gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS); //lingkaran untuk tutup bawah

}

void sayap(){
	glBegin(GL_POLYGON); // depan
		glColor3f(0.5f, 0.0f, 0.f);
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
	glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, BODY_LENGTH);
    gluDisk(q, 0.0f, BODY_RADIUS, SLICES, STACKS); //lingkaran untuk tutup bawah
}

void baling(){
    //atas
    glBegin(GL_POLYGON);
        glVertex3f(0,0,0);
        glVertex3f(0.5,0,0);
        glVertex3f(0.4,1,0.1);
		glVertex3f(0.1,1,0.1);
		glVertex3f(0.5,0,0);
        glVertex3f(0.4,-1,0.1);
		glVertex3f(0.1,-1,0.1);
    glEnd();
    //bawah
    glBegin(GL_POLYGON);
        glVertex3f(0,0,0.2);
        glVertex3f(0.5,0,0.2);
        glVertex3f(0.4,1,0.1);
		glVertex3f(0.1,1,0.1);
		glVertex3f(0.5,0,0.2);
        glVertex3f(0.4,-1,0.1);
		glVertex3f(0.1,-1,0.1);
    glEnd();
    //kiri
    glBegin(GL_POLYGON);
        glVertex3f(0.1,1,0.1);
		glVertex3f(0.0,0.0,0.2);
        glVertex3f(0.1,-1,0.1);
		glVertex3f(0.0,0,0.0);
    glEnd();
    //kanan
    //kiri
    glBegin(GL_POLYGON);
        glVertex3f(0.4,1,0.1);
		glVertex3f(0.5,0.0,0.2);
        glVertex3f(0.4,-1,0.1);
		glVertex3f(0.5,0,0.0);
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

void vectorMovement(Vector toMove, float magnitude, float direction){
    float speedX = toMove.x * magnitude * direction;
    float speedY = toMove.y * magnitude * direction;
    float speedZ= toMove.z * magnitude * direction;
    Cx += speedX;
    Cy += speedY;
    Cz += speedZ;
    Lx += speedX;
    Ly += speedY;
    Lz += speedZ;
}

void cameraRotation(Vector refer, double angle){
    float M = sqrt(pow(refer.x, 2) + pow(refer.y, 2) + pow(refer.z, 2));
    float Up_x1 = refer.x / M;
    float Up_y1 = refer.y / M;
    float Up_z1 = refer.z / M;
    float VLx = Lx - Cx;
    float VLy = Ly - Cy;
    float VLz = Lz - Cz;
    float dot_product = (VLx * Up_x1) + (VLy * Up_y1) + (VLz * Up_z1);
    float cross_product_x = (Up_y1 * VLz) - (VLy * Up_z1);
    float cross_product_y = -((Up_x1 * VLz) - (Up_z1 * VLx));
    float cross_product_z = (Up_x1 * VLy) - (Up_y1 * VLx);
    float last_factor_rodrigues = 1.0f - cos(toRadians(angle));
    float Lx1 = (VLx * cos(toRadians(angle))) + (cross_product_x * sin(toRadians
    (angle))) + (dot_product * last_factor_rodrigues * VLx);
    float Ly1 = (VLy * cos(toRadians(angle))) + (cross_product_y * sin(toRadians
    (angle))) + (dot_product * last_factor_rodrigues * VLy);
    float Lz1 = (VLz * cos(toRadians(angle))) + (cross_product_z * sin(toRadians
    (angle))) + (dot_product * last_factor_rodrigues * VLz);
    Lx = Lx1+Cx;
    Ly = Ly1+Cy;
    Lz = Lz1+Cz;
}

void keyFunction(unsigned char key, int x, int y){
/* Agar fungsi ini bekerja, pastikan CapsLock menyala,
kecuali tombol-tombol khusus seperti Spasi, dll */
    switch(key){
    case 87: // W maju
        vectorMovement(depanBelakang, 2.0f, -1.0f);
    break;
    case 83: // S
        vectorMovement(depanBelakang, 2.0f, 1.0f);
    break;
    case 68: // D
        vectorMovement(samping, 2.0f, -1.0f);
    break;
    case 65: // A
        vectorMovement(samping, 2.0f, 1.0f);
    break;
    case 32: // Spasi
        if (silinder){
            silinder = false;
        } else {
            silinder = true;
        }
    break;
    case 116: // t Z-
        if (silinder1){
            silinder1 = false;
        } else {
            silinder1 = true;
        }
    break;
    case 102: // f Y+
        if (silinder2){
            silinder2 = false;
        } else {
            silinder2 = true;
        }
    break;
    case 104: // h Y-
        if (silinder3){
            silinder3 = false;
        } else {
            silinder3 = true;
        }
    break;
    case 103: // g X+
        if (silinder4){
            silinder4 = false;
        } else {
            silinder4 = true;
        }
    break;
    case 98: // b X-
        if (silinder5){
            silinder5 = false;
        } else {
            silinder5 = true;
        }
    break;
    case 13: // Enter
        if (kamera){
            kamera = false;
        } else {
            kamera = true;
        }
    break;
    case 84: // T X-
        if (kamera1){
            kamera1 = false;
        } else {
            kamera1 = true;
        }
    break;
    case 70: // F Y+
        if (kamera2){
            kamera2 = false;
        } else {
            kamera2 = true;
        }
    break;
    case 72: // H Y-
        if (kamera3){
            kamera3 = false;
        } else {
            kamera3 = true;
        }
    break;
    case 71: // G Z+
        if (kamera4){
            kamera4 = false;
        } else {
            kamera4 = true;
        }
    break;
    case 66: // B Z-
        if (kamera5){
            kamera5 = false;
        } else {
            kamera5 = true;
        }
    break;
    case 74: // J yawing kiri
        angle_vertikal += 5.0f;
        samping.vectorRotation(vertikal, angle_vertikal - angle_vertikal2);
        //memutar vector sumbu z terhadap x (target, patokan)
        depanBelakang.vectorRotation(vertikal, angle_vertikal - angle_vertikal2);
        cameraRotation(vertikal, angle_vertikal - angle_vertikal2); // lookat
        angle_vertikal2 = angle_vertikal;
    break;
    case 76: // L yawing kanan
        angle_vertikal -= 5.0f;
        samping.vectorRotation(vertikal, angle_vertikal - angle_vertikal2);
        depanBelakang.vectorRotation(vertikal, angle_vertikal - angle_vertikal2);
        cameraRotation(vertikal, angle_vertikal - angle_vertikal2);
        angle_vertikal2 = angle_vertikal;
    break;
    case 73: // I PICING bawah
        angle_samping -= 5.0f;
        //vertikal.vectorRotation(samping, angle_samping - angle_samping2);
        depanBelakang.vectorRotation(samping, angle_samping - angle_samping2);
        cameraRotation(samping, angle_samping - angle_samping2);
        angle_samping2 = angle_samping;
    break;
    case 75: // K PICING atas
        angle_samping += 5.0f;
        //vertikal.vectorRotation(samping, angle_samping-angle_samping2);
        depanBelakang.vectorRotation(samping, angle_samping - angle_samping2);
        cameraRotation(samping, angle_samping - angle_samping2);
        angle_samping2 = angle_samping;
    break;
    }
}

int sudut = 0;
void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	axis();
	gluLookAt(Cx, Cy, Cz,
            Lx, Ly, Lz,
            vertikal.x, vertikal.y, vertikal.z);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glRotatef(45, 1.0f, 0.0f, 0.0f);

    glTranslatef(0.0f, 0.0f, -2.0f);
    glRotatef(silinderAngle2, 0.0f, 0.0f, 1.0f);
    glRotatef(silinderAngle1, 0.0f, 1.0f, 0.0f);
    glRotatef(silinderAngle, 1.0f, 0.0f, 0.0f);
	//axis();
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
  	glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
  	glRotatef(-180.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(0.0f, 0.0f, 1.0f, 0.0f);

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

    if (silinder){
        silinderAngle += 15.0f;
    }
    if (silinder1){
        silinderAngle -= 15.0f;
    }
    if (silinder2){
        silinderAngle1 += 15.0f;
    }
    if (silinder3){
        silinderAngle1 -= 15.0f;
    }
    if (silinder4){
        silinderAngle2 += 15.0f;
    }
    if (silinder5){
        silinderAngle2 -= 15.0f;
    }
    if (kamera){
        keyFunction('K', 0, 0);
    }
    if (kamera1){
        keyFunction('I', 0, 0);
    }
    if (kamera2){
        keyFunction('J', 0, 0);
    }
    if (kamera3){
        keyFunction('L', 0, 0);
    }
    if (kamera4){
        keyFunction('Z', 0, 0);
    }
    if (kamera5){
        keyFunction('X', 0, 0);
    }

	glFlush();
	glutSwapBuffers();
}

void initGL(){
    depanBelakang.set_values(0.0f, 0.0f, -1.0f);
    samping.set_values(1.0f, 0.0f, 0.0f);
    vertikal.set_values(0.0f, 1.0f, 0.0f);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
}

void reshape(GLsizei width, GLsizei height){
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	glViewport(30, 6, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, aspect, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void keyControl(int k, int x, int y) {
    switch(k) {
        case GLUT_KEY_UP: //arrow up
            vectorMovement(vertikal, 2.0f, 1.0f);
        break;
        case GLUT_KEY_DOWN: //arrow down
            vectorMovement(vertikal, 2.0f, -1.0f);
        break;
    }
}

void timer(int value){
	glutPostRedisplay();
	glutTimerFunc(60, timer, 0);
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("UAS Grafis");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	initGL();
	glutSpecialFunc(keyControl);
	glutKeyboardFunc(keyFunction);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	return 0;
}
