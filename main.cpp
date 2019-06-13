#include<cstdio>
#include <GL/gl.h>
#include <GL/glut.h>
#include <string.h>
#include <sstream>
#include <cstdlib>
#include <Windows.h>
#include <mmsystem.h>
#include<math.h>>

# define PI           3.14159265358979323846
using namespace std;
static float position = 0.0;
bool wing = false;
bool hit = false;
static float positionbird = 0.0f;
static float position_one = 0.2;
static float position_two = 0.4;
static float position_one_down = 0.0;
GLfloat speed = 0.015f;

float obstacle_move = 0.0;
int frameNumber = 0;
static int flag = 0;
bool gameover = false;
float point = 0.0;
bool fullScreenMode = false;
int life = 20;


void displayRasterText(float x ,float y ,float z ,char *stringToDisplay) {
	int length;
	glRasterPos3f(x, y, z);
		length = strlen(stringToDisplay);

	for(int i=0 ;i<length ;i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 ,stringToDisplay[i]);
	}

}

void renderbitmap(float x, float y, void *font, char *str){
    char *c;
    glRasterPos2f(x,y);

    for(c = str; *c != '\0'; c++)
    {
        glutBitmapCharacter(font,*c);
    }
}
void gameOver()
{
    glColor3f(1.0f,0.0f,0.0f);
    char buf[100] = {0};
    sprintf(buf, "Game Over");
    renderbitmap(0.0, 0.7, GLUT_BITMAP_TIMES_ROMAN_24,buf);
}
void scoreDisplay()
{
    glColor3f(1.0f,0.0f,0.0f);
    char buf[100] = {0};
    sprintf(buf, "Score: %d Life: %d", (int)point,life);
    renderbitmap(-0.5, 0.7, GLUT_BITMAP_TIMES_ROMAN_24,buf);

}
void restartDisplay()
{
    glColor3f(1.0f,0.0f,0.0f);
    char buf[100] = {0};
    sprintf(buf, "Press r to restart!!!");
    renderbitmap(0.0, 0.5, GLUT_BITMAP_TIMES_ROMAN_24,buf);
}

void update(int value) {
if(!gameover){
    if(position <= -1.0 ){
        position = 0.1;}
     position -= speed;
    if(position_one<=-1.0)
        position_one = 0.25;
    position_one -= speed;
    if(position_two<=-1.0)
        position_two = 0.4;
    position_two -= speed;
    /*if(position_one_down <= -1.0 ){
        position_one_down = 0.1;}
     position_one_down -= speed;*/
    //frameNumber++;
	if(positionbird > 1.0)
        positionbird = 0.0f;
    positionbird -=speed;
    if(((fabs(position)>=0.34 && fabs(position)<=0.48) && positionbird>0.1) || ((fabs(position)>=0.34 && fabs(position)<=0.48) && positionbird<=-0.15)){
            //speed = 0.0;
    hit = true;
    if(hit){
    PlaySound("hit.wav", NULL, SND_ASYNC|SND_FILENAME);}
            life-=5;

            //printf("Collide %f\n", position_one_down);
       }/*else {
           printf("Not Not\n");
           speed = 0.008f;
    }*/
     else if(((fabs(position_one)>=0.54&& fabs(position_one)<=0.68) && positionbird>0.3) || ((fabs(position_one)>=0.54&& fabs(position_one)<=0.68) && positionbird<=0.0)){
        //speed = 0.0;
         hit = true;
        if(hit){
        PlaySound("hit.wav", NULL, SND_ASYNC|SND_FILENAME);}
        life-=5;
        //printf("Collide\n");
    }else if(((fabs(position_two)>=0.74&& fabs(position_two)<=0.88) && positionbird>0.15) || ((fabs(position_two)>=0.74&& fabs(position_two)<=0.88) && positionbird<=0.0))
    {
        //speed = 0.0;
         hit = true;
            if(hit){
            PlaySound("hit.wav", NULL, SND_ASYNC|SND_FILENAME);}
        life-=5;

        //printf("Collide\n");
    }


        //speed = 0.008f;
        point+=0.05;



}

	glutPostRedisplay();
	glutTimerFunc(100, update, 0);

}

/*void updatePos(int value) {

    if(positionbird > 1.0)
        positionbird = 0.0f;

    positionbird -= 0.02;
    //frameNumber++;
	glutPostRedisplay();


	glutTimerFunc(100, updatePos, 0);
}

void updateMain()
{
    if(position==-0.4)
    {
        printf("collide\n");
    }else {
        printf("not collide\n");
    }
}*/

void drawScene();
void handleKeypress(unsigned char key, int x, int y) {

	switch (key) {

case 'a':
    speed = 0.0f;

    break;
case 'w':
    speed = 0.015f;
    break;
case 'r':
    gameover = false;
    point = 0.0;
    life = 20;
    position = 0.0;
    positionbird = 0.0f;
    position_one = 0.2;
    position_two = 0.4;
    position_one_down = 0.0;
    drawScene();
    glutPostRedisplay();
    break;


//glutPostRedisplay();


	}
}

void handleMouse(int button, int state, int x, int y) {


		if (button == GLUT_LEFT_BUTTON)
	{
            wing = true;
			positionbird += 0.1f;
			if(wing){
            PlaySound("wing.wav", NULL, SND_ASYNC|SND_FILENAME);}
			//printf("%f %f\n", positionbird, fabs(position));

			//printf("clicked at (%d, %d)\n", x, y);

	}
//glutPostRedisplay();
}



void flappyBird()
{
     //body
    glPushMatrix();
    glTranslatef(0.0f,positionbird,0.0f);
    int i;
    glColor3f(1.0f,1.0f,0.0f);
	GLfloat x=-.4f; GLfloat y=.0f; GLfloat radius =.04f;
	int triangleAmount = 200; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)),
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
	//glFlush();
	//eye
	glColor3f(1.0f,1.0f,1.0f);
	GLfloat xx = -.389f; GLfloat yy = .02f; GLfloat eyeRadius = 0.02f;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(xx, yy); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            xx + (eyeRadius * cos(i *  twicePi / triangleAmount)),
			    yy + (eyeRadius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();

   //eyeblack
    glColor3f(0.0f,0.0f,0.0f);
	GLfloat xxx = -.38f; GLfloat yyy = .025f; GLfloat eyeBlack = 0.01f;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(xxx, yyy); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            xxx + (eyeBlack * cos(i *  twicePi / triangleAmount)),
			    yyy + (eyeBlack * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();

    //Lip
    glColor3f(1.0f,0.5f,0.0f);
    glBegin(GL_LINES);
    glLineWidth(3.0f);
    glVertex2f(-.38f,-0.01f);
    glVertex2f(-.35f,-0.01f);
    glEnd();

    glColor3f(1.0f,0.5f,0.0f);
    glBegin(GL_LINES);
    glLineWidth(3.0f);
    glVertex2f(-.38f,-0.008f);
    glVertex2f(-.35f,-0.008f);
    glEnd();

    glColor3f(1.0f,0.5f,0.0f);
    glBegin(GL_LINES);
    glLineWidth(3.0f);
    glVertex2f(-.38f,-0.004f);
    glVertex2f(-.35f,-0.004f);
    glEnd();

    glColor3f(1.0f,0.5f,0.0f);
    glBegin(GL_LINES);
    glLineWidth(3.0f);
    glVertex2f(-.38f,-0.001f);
    glVertex2f(-.35f,-0.001f);
    glEnd();

    glColor3f(1.0f,0.5f,0.0f);
    glBegin(GL_LINES);
    glLineWidth(3.0f);
    glVertex2f(-.38f,-0.023f);
    glVertex2f(-.35f,-0.001);
    glEnd();

    glColor3f(1.0f,0.5f,0.0f);
    glBegin(GL_LINES);
    glLineWidth(3.0f);
    glVertex2f(-.38f,-0.02f);
    glVertex2f(-.35f,-0.001);
    glEnd();

    glColor3f(1.0f,0.5f,0.0f);
    glBegin(GL_LINES);
    glLineWidth(3.0f);
    glVertex2f(-.38f,-0.012f);
    glVertex2f(-.35f,-0.001);
    glEnd();

    glColor3f(1.0f,0.5f,0.0f);
    glBegin(GL_LINES);
    glLineWidth(3.0f);
    glVertex2f(-.38f,-0.014f);
    glVertex2f(-.35f,-0.001);
    glEnd();

    glColor3f(1.0f,0.5f,0.0f);
    glBegin(GL_LINES);
    glLineWidth(3.0f);
    glVertex2f(-.38f,-0.016f);
    glVertex2f(-.35f,-0.001);
    glEnd();
    glPopMatrix();
    glFlush();


}


void init() {
   glClearColor(0.0,0.0,1.0,0.0);
   glMatrixMode(GL_MODELVIEW);


}
void field(){
    //glColor3f(1.0f,1.0f,1.0f);
     glColor3f(0.0, 1.0, 0.0);
     glBegin(GL_POLYGON);
     glVertex2f(-1.0f, -0.2f);
      glVertex2f(1.0f, -0.2f);
      glVertex2f(1.0f, -1.0f);
      glVertex2f(-1.0f, -1.0f);
     glEnd();
     glFlush();
}
void sky(){
        glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
     glBegin(GL_POLYGON);
     glVertex2f(-1.0f,1.0f);
     glVertex2f(1.0f,1.0f);
     glVertex2f(1.0f, -0.2f);
     glVertex2f(-1.0f, -0.2f);
     glEnd();

     glFlush();
}
void cloud() {
    int i;
    glColor3f(1.0f,1.0f,1.0f);
	GLfloat x=-.4f; GLfloat y=.83f; GLfloat radius =.1f;
	int triangleAmount = 20; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)),
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();

	//glFlush();  // Render now


	GLfloat xx = -.5f; GLfloat yy = .7f;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(xx, yy); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            xx + (radius * cos(i *  twicePi / triangleAmount)),
			    yy + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();

	//glFlush();

    GLfloat xxx = -.32f; GLfloat yyy = .7f;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(xxx, yyy); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            xxx + (radius * cos(i *  twicePi / triangleAmount)),
			    yyy + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();

	glFlush();

}

void balls()
{
    int i;
    glColor3f(1.0f,1.0f,1.0f);
	GLfloat x=-.9f; GLfloat y=.9f; GLfloat radius =.05f;
	int triangleAmount = 20; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)),
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();

	glFlush();


    glColor3f(1.0f,0.0f,0.0f);
	GLfloat xx=-.8f; GLfloat yy=.85f; //GLfloat radius =.05f;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(xx, yy); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            xx + (radius * cos(i *  twicePi / triangleAmount)),
			    yy + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();

	glFlush();

    glColor3f(1.0f,0.0f,0.0f);
	GLfloat xxx=-.7f; GLfloat yyy=.8f; //GLfloat radius =.05f;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(xxx, yyy); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            xxx + (radius * cos(i *  twicePi / triangleAmount)),
			    yyy + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();

	glFlush();


	//four

    glColor3f(1.0f,0.0f,0.0f);
	GLfloat fourx=-.6f; GLfloat foury=.9f; //GLfloat radius =.05f;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(fourx, foury); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            fourx + (radius * cos(i *  twicePi / triangleAmount)),
			    foury + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();

	glFlush();

	//five

    glColor3f(1.0f,0.0f,0.0f);
	GLfloat fivex=-.5f; GLfloat fivey=.85f; //GLfloat radius =.05f;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(fivex, fivey); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            fivex + (radius * cos(i *  twicePi / triangleAmount)),
			    fivey + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();

	glFlush();

	//six

	    glColor3f(1.0f,0.0f,0.0f);
	GLfloat sixx=-.4f; GLfloat sixy=.75f; //GLfloat radius =.05f;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(sixx, sixy); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            sixx + (radius * cos(i *  twicePi / triangleAmount)),
			    sixy + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();

	glFlush();

	//seven

	    glColor3f(1.0f,0.0f,0.0f);
	GLfloat sevenx=.4f; GLfloat seveny=.80f; //GLfloat radius =.05f;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(sevenx, seveny); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            sevenx + (radius * cos(i *  twicePi / triangleAmount)),
			    seveny + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();

	glFlush();

	//eight

	    glColor3f(1.0f,0.0f,0.0f);
	GLfloat eightx=.2f; GLfloat eighty=.95f; //GLfloat radius =.05f;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(eightx, eighty); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            eightx + (radius * cos(i *  twicePi / triangleAmount)),
			    eighty + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();

	glFlush();

	//nine

	    glColor3f(1.0f,0.0f,0.0f);
	GLfloat ninex=.1f; GLfloat niney=.8f; //GLfloat radius =.05f;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(ninex, niney); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            ninex + (radius * cos(i *  twicePi / triangleAmount)),
			    niney + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();

	glFlush();

	//ten

	    glColor3f(1.0f,0.0f,0.0f);
	GLfloat tenx=0.0f; GLfloat teny=.85f; //GLfloat radius =.05f;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(tenx, teny); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            tenx + (radius * cos(i *  twicePi / triangleAmount)),
			    teny + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();

	glFlush();

	//eleven

    glColor3f(1.0f,0.0f,0.0f);
	GLfloat elevenx=0.5f; GLfloat eleveny=.85f; //GLfloat radius =.05f;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(elevenx, eleveny); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            elevenx + (radius * cos(i *  twicePi / triangleAmount)),
			    eleveny + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();

	glFlush();

	//twelve

    glColor3f(1.0f,0.0f,0.0f);
	GLfloat twelvex=0.65f; GLfloat twelvey=.85f; //GLfloat radius =.05f;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(twelvex, twelvey); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            twelvex + (radius * cos(i *  twicePi / triangleAmount)),
			    twelvey + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();

	glFlush();

	//thirteen

    glColor3f(1.0f,0.0f,0.0f);
	GLfloat thirteenx=0.9f; GLfloat thirteeny=.85f; //GLfloat radius =.05f;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(thirteenx, thirteeny); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            thirteenx + (radius * cos(i *  twicePi / triangleAmount)),
			    thirteeny + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();

	glFlush();
}

void obstacle_one()
{
    glPushMatrix();
    glTranslatef(position,0.0f, 0.0f);
     //up_one

     glColor3f(0.0, 0.4, 0.0);
     glBegin(GL_POLYGON);
     glVertex2f(0.0, 1.0);
      glVertex2f(0.08f, 1.0f);
      glVertex2f(0.08f, 0.2f);
      glVertex2f(0.0f, 0.2f);
     glEnd();
     //glFlush();

     //down_one

    /*glColor3f(0.0, 0.4, 0.0);
     glBegin(GL_POLYGON);
     glVertex2f(0, -0.2);
      glVertex2f(0.08f, -0.2f);
      glVertex2f(0.08f, -1.0f);
      glVertex2f(0.0f, -1.0f);
     glEnd();*/
    // glFlush();
/*
     //up_two
    glColor3f(0.0, 0.4, 0.0);
     glBegin(GL_POLYGON);
     glVertex2f(0.2f, 1.0f);
      glVertex2f(0.28f, 1.0f);
      glVertex2f(0.28f, 0.4f);
      glVertex2f(0.2f, 0.4f);
     glEnd();
    // glFlush();

     //down_tow

     glColor3f(0.0, 0.4, 0.0);
     glBegin(GL_POLYGON);
     glVertex2f(0.2f, -0.08f);
      glVertex2f(0.28f, -0.08f);
      glVertex2f(0.28f, -1.0f);
      glVertex2f(0.2f, -1.0f);
     glEnd();
    // glFlush();

     //upthree

        glColor3f(0.0, 0.4, 0.0);
     glBegin(GL_POLYGON);
     glVertex2f(0.4f, 1.0f);
      glVertex2f(0.48f, 1.0f);
      glVertex2f(0.48f, 0.2f);
      glVertex2f(0.4f, 0.2f);
     glEnd();
     //glFlush();

     //downThree
    glColor3f(0.0, 0.4, 0.0);
     glBegin(GL_POLYGON);
     glVertex2f(0.4f, -0.08f);
      glVertex2f(0.48f, -0.08f);
      glVertex2f(0.48f, -1.0f);
      glVertex2f(0.4f, -1.0f);
     glEnd();
    // glFlush();

     //upFour

     glColor3f(0.0, 0.4, 0.0);
     glBegin(GL_POLYGON);
     glVertex2f(0.62f, 1.0f);
      glVertex2f(0.70f, 1.0f);
      glVertex2f(0.70f, 0.4f);
      glVertex2f(0.62f, 0.4f);
     glEnd();
     //glFlush();

     //downFour
    glColor3f(0.0, 0.4, 0.0);
     glBegin(GL_POLYGON);
     glVertex2f(0.62f, -0.0f);
      glVertex2f(0.70f, -0.0f);
      glVertex2f(0.70f,-1.0f);
      glVertex2f(0.62f, -1.0f);
     glEnd();
     //glFlush();

     //upFive

    glColor3f(0.0, 0.4, 0.0);
     glBegin(GL_POLYGON);
     glVertex2f(0.90f, 1.0f);
      glVertex2f(0.98f, 1.0f);
      glVertex2f(0.98f, 0.3f);
      glVertex2f(0.90f, 0.3f);
     glEnd();
     //glFlush();

     //downFive

    glColor3f(0.0, 0.4, 0.0);
     glBegin(GL_POLYGON);
     glVertex2f(0.90f, -0.1f);
      glVertex2f(0.98f, -0.1f);
      glVertex2f(0.98f, -1.0f);
      glVertex2f(0.90f, -1.0f);
     glEnd();*/
     glPopMatrix();

     //glFlush();

     //glutSwapBuffers();

}
void obstacle_two()
{
    glPushMatrix();
    glTranslatef(position_one,0.0f, 0.2f);
        glColor3f(0.0, 0.4, 0.0);
     glBegin(GL_POLYGON);
     glVertex2f(0.2f, 1.0f);
      glVertex2f(0.28f, 1.0f);
      glVertex2f(0.28f, 0.4f);
      glVertex2f(0.2f, 0.4f);
     glEnd();
     glPopMatrix();
     //glFlush();
     //glutSwapBuffers();
}

void obstacle_three()
{
    glPushMatrix();
    glTranslatef(position_two,0.0f, 0.0f);
        glColor3f(0.0, 0.4, 0.0);
     glBegin(GL_POLYGON);
     glVertex2f(0.4f, 1.0f);
      glVertex2f(0.48f, 1.0f);
      glVertex2f(0.48f, 0.2f);
      glVertex2f(0.4f, 0.2f);
     glEnd();
     glPopMatrix();
     //glFlush();
     //glutSwapBuffers();
}
void obstacle_one_down()
{
      glPushMatrix();
    glTranslatef(position,0.0f, 0.0f);
    glColor3f(0.0, 0.4, 0.0);
     glBegin(GL_POLYGON);
     glVertex2f(0, -0.2);
      glVertex2f(0.08f, -0.2f);
      glVertex2f(0.08f, -1.0f);
      glVertex2f(0.0f, -1.0f);
     glEnd();
     glPopMatrix();
     //glFlush();
     //glutSwapBuffers();
}

void obstacle_two_down()
{
    glPushMatrix();
    glTranslatef(position_one,0.0f, 0.0f);
    glColor3f(0.0, 0.4, 0.0);
     glBegin(GL_POLYGON);
     glVertex2f(0.2f, -0.08f);
    glVertex2f(0.28f, -0.08f);
    glVertex2f(0.28f, -1.0f);
      glVertex2f(0.2f, -1.0f);
     glEnd();
    glPopMatrix();
     //glFlush();
     //glutSwapBuffers();
}
void obstacle_three_down()
{
    glPushMatrix();
    glTranslatef(position_two,0.0f, 0.0f);
    glColor3f(0.0, 0.4, 0.0);
     glBegin(GL_POLYGON);
     glVertex2f(0.4f, -0.08f);
      glVertex2f(0.48f, -0.08f);
      glVertex2f(0.48f, -1.0f);
      glVertex2f(0.4f, -1.0f);
     glEnd();
    glPopMatrix();
     //glFlush();
     //glutSwapBuffers();
}

void gameoverScreen()
{
     glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
     glBegin(GL_POLYGON);
     glColor3f(1.0f, 1.0f, 1.0f);
     glVertex2f(-1.0f,1.0f);
     glVertex2f(1.0f,1.0f);
     glVertex2f(1.0f, -1.0f);
     glVertex2f(-1.0f, -1.0f);
     glEnd();
     gameOver();
     scoreDisplay();
     restartDisplay();
     glFlush();
}
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   if(gameover)
    {
        //firstMenuFlag = false;

      //readFromFile();
     // char temp2[40];
      //sprintf(temp2 ,"Highest Score :%d" ,atoi(high));
      //if(point>atoi(high))
        // writeIntoFile();
     // cout<<temp2<<endl;
       // stringstream ff;
        //ff << point;
        char temp[100];
        sprintf(temp,"%d",point);
        string points =temp ;

         gameoverScreen();



    }else {
   //DisplayHealthBar();
  // glFlush();
   field();
   sky();
   cloud();
   //balls();

   obstacle_one();
   obstacle_two();
   obstacle_three();
   obstacle_one_down();
   obstacle_two_down();
   obstacle_three_down();
   flappyBird();
scoreDisplay();
   glFlush();
   }
   //updateMain();

   glutSwapBuffers();
}

void drawScene(){
    if(life>0){
        display();
    }else if(life<=0){
        gameover = true;
        display();
        glutPostRedisplay();

    }
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitWindowSize(1280, 720);
   glutInitWindowPosition(50, 50);
   glutCreateWindow("Flappy Bird");
   init();
   glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
   glutMouseFunc(handleMouse);
// glutTimerFunc(100, updatePos, 0);
   glutTimerFunc(100, update, 0);
   glutMainLoop();
   return 0;
}

