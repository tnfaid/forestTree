#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>


#ifdef GL_VERSION_1_1
static GLuint texName;
GLfloat polyfactor = 1.0;
GLfloat polyunits = 1.0;

#endif // GL_VERSION_1_1
#define TRUE  1
#define FALSE 0

/* Dimensions of texture image. */
#define IMAGE_WIDTH  64
#define IMAGE_HEIGHT 64
#define	stripeImageWidth 32
GLubyte stripeImage[4*stripeImageWidth];
/* Step to be taken for each rotation. */
#define ANGLE_STEP 10
#define PT 1 //pt untuk membua garis
#define STROKE 2 //stroke untuk garis putus
#define END 3 //end untuk mengakhiri garis dan tidak menampakan garisnya



GLubyte a[24] = {
0xc0, 0xf0,
0xc0, 0xf0,
0xc0, 0xf0,
0xc0, 0xc0,
0xc0, 0xc0,
0xff, 0xff,
0xff, 0xff,
0xc0, 0xf0,
0xc0, 0xf0,
0xc0, 0xf0,
0xff, 0xff,
0xff, 0xff};

GLubyte H[24] = {
0xc0, 0xf0,
0xc0, 0xf0,
0xc0, 0xf0,
0xc0, 0xc0,
0xc0, 0xc0,
0xff, 0xff,
0xff, 0xff,
0xc0, 0xf0,
0xc0, 0xf0,
0xc0, 0xf0,
0xc0, 0xc0,
0xc0, 0xc0};

GLubyte r[24] = {
0xc0, 0xff,
0xc0, 0xff,
0xc0, 0xf0,
0xcf, 0x00,
0xf0, 0x00,
0xff, 0xf0,
0xc0, 0xf0,
0xc0, 0xf0,
0xc0, 0xf0,
0xc0, 0xf0,
0xff, 0xf0,
0xff, 0xc0};

GLubyte o[24] = {
0x0f, 0x0f,
0x0f, 0x0f,
0xff, 0xff,
0xc0, 0xf0,
0xc0, 0xc0,
0xc0, 0xc0,
0xc0, 0xc0,
0xc0, 0xf0,
0xc0, 0xf0,
0xff, 0xff,
0x0f, 0x0f,
0x0f, 0x0f};


typedef struct charpoint{
GLfloat x,y;
int type;
}CP;
//menggambar huruf posisi samas seperti vertex
CP Adata[]={
{0,1,PT},{0,9,PT},{1,10,PT},{4,10,PT},
{5,9,PT},{5,0,STROKE},{0,5,PT},{5,5,END}
};
CP Pdata[]={
{0,0,PT},{0,10,PT},{4,10,PT},{5,9,PT},{5,6,PT},
{4,5,PT},{0,5,END}
};
CP Sdata[]={
{0,1,PT},{1,0,PT},{4,0,PT},{5,1,PT},{5,4,PT},
{4,5,PT},{1,5,PT},{0,6,PT},{0,9,PT},{1,10,PT},
{4,10,PT},{5,9,END}
};
CP Tdata[]={
{0,10,PT},{8,10,PT},{4,10, PT},{4, 0, STROKE},{3, 0, END}
};
CP Edata[]={
{0, 1,PT},{0, 10, PT},{5, 10, STROKE},{0, 5, PT}, {5, 6, STROKE},
{0, 1,PT}, {5, 1, PT}, {6, 1, END}
};
CP Rdata[]={
{0,0,PT},{0,10,PT},{4,10,PT},{5,9,PT},{5,6,PT},
{4,5,PT},{0,5,STROKE},{3,5,PT},{5,0,END}
};
CP Ndata[]={
{0,0,PT},{0,10,PT},{5,5,PT},{6,0,PT},{6,10,END}
};
CP Gdata[] = {
    {5, 10, PT}, {0, 10, PT}, {0, 1, PT}, {5, 1, PT},
    {5, 5, PT}, {3, 5, PT}, {2, 5, END}
};
CP idata[] = {
    {0, 1, PT}, {0, 8, PT}, {0, 9, STROKE}, {0, 10, PT}, {0, 11, END}
};
CP Idata[] = {
    {4, 1, PT}, {4, 9, PT}, {4, 11, END}
};
CP Ldata[] = {
    {0, 10, PT}, {0, 1, PT}, {5, 1, PT},{6, 1, END}
};
CP Mdata[] = {
    {0, 0, PT}, {0, 10, PT}, {3, 1, PT},{6, 10, PT}, {6, 0, PT}, {6, 1, END}
};
CP Kdata[] = {
    {0, 0, PT}, {0, 10, STROKE}, {5, 10, PT},{0, 5, PT}, {5, 0, PT}, {6, 1, END}
};
CP Udata[] = {
    {0, 10, PT}, {0, 0, PT}, {5, 0, PT},{5, 10, PT}, {6, 10, END}
};
CP Fdata[] = {
    {0, 0, PT}, {0, 10, PT}, {5, 10, STROKE},{5, 5, PT}, {0, 5, PT}, {0, 6, END}
};
CP Ddata[] = {
    {0, 0, PT}, {0, 10, PT}, {5, 5, PT},{0, 0, PT}, {0, 1, END}
};
CP Hdata[] = {
    {0, 0, PT}, {0, 10, STROKE}, {5, 10, STROKE},{0, 5, PT}, {5, 5, PT}, {5, 0, PT}, {5, 10, PT},
    {6, 10, END}
};
static void drawLetter(CP *I)
{
    glBegin(GL_LINE_STRIP);
    while(1){
        switch (I->type){
    case PT:
        glVertex2fv(&I->x);
        break;
    case STROKE:
        glVertex2fv(&I->x);
        glEnd();
        glBegin(GL_LINE_STRIP);
        break;
    case END:
        glVertex2fv(&I->x);
        glEnd();
        glTranslatef(8.0,0.0,0.0);
        return;
        }
    I++;
    }
}
static void huruf(){

 GLuint base;
glShadeModel(GL_FLAT);
base=glGenLists(128);
glListBase(base);
glNewList(base+'A',GL_COMPILE);drawLetter(Adata);glEndList();
glNewList(base+'E',GL_COMPILE);drawLetter(Edata);glEndList();
glNewList(base+'P',GL_COMPILE);drawLetter(Pdata);glEndList();
glNewList(base+'R',GL_COMPILE);drawLetter(Rdata);glEndList();
glNewList(base+'S',GL_COMPILE);drawLetter(Sdata);glEndList();
glNewList(base+'T',GL_COMPILE);drawLetter(Tdata);glEndList();
glNewList(base+'E',GL_COMPILE);drawLetter(Edata);glEndList();
glNewList(base+'N',GL_COMPILE);drawLetter(Ndata);glEndList();
glNewList(base+'R',GL_COMPILE);drawLetter(Rdata);glEndList();
glNewList(base+'G',GL_COMPILE);drawLetter(Gdata);glEndList();
glNewList(base+'i',GL_COMPILE);drawLetter(idata);glEndList();
glNewList(base+'I',GL_COMPILE);drawLetter(Idata);glEndList();
glNewList(base+'L',GL_COMPILE);drawLetter(Ldata);glEndList();
glNewList(base+'M',GL_COMPILE);drawLetter(Mdata);glEndList();
glNewList(base+'K',GL_COMPILE);drawLetter(Kdata);glEndList();
glNewList(base+'U',GL_COMPILE);drawLetter(Udata);glEndList();
glNewList(base+'F',GL_COMPILE);drawLetter(Fdata);glEndList();
glNewList(base+'D',GL_COMPILE);drawLetter(Ddata);glEndList();
glNewList(base+'H',GL_COMPILE);drawLetter(Hdata);glEndList();
glNewList(base+' ',GL_COMPILE);glTranslatef(8.0,0.0,0.0);glEndList();

}
char *test1= "TITIK NURFAIDAH";
char *test2= "SELAMAT UAS";
//ini untuk antialias
static float rotAngle = 0.;

static void initial(void)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_FLAT);
    glClearColor(0,0,0,0);
}
void makeStripeImage(void)
{
   int j;
   for (j = 0; j < stripeImageWidth; j++) {
      stripeImage[4*j] = (GLubyte) ((j<=4) ? 255 : 0);
      stripeImage[4*j+1] = (GLubyte) ((j>4) ? 255 : 0);
      stripeImage[4*j+2] = (GLubyte) 0;
      stripeImage[4*j+3] = (GLubyte) 255;
   }
}
/* Toggles */
GLshort shaded = TRUE, anim = FALSE;
GLshort texture = FALSE, transparent = FALSE;
GLshort light1 = TRUE, light2 = FALSE;
GLshort blendingOn = TRUE, blendingOff = FALSE;

/* Storage for the angle look up table and the texture map */
GLdouble head_look_up_table[361];
GLubyte image[IMAGE_WIDTH][IMAGE_HEIGHT][3];

/* Variable used in the creaton of glu objects */
GLUquadricObj *obj;

//#include <cstdlib>
//if you got error in exit() by compiler then does not incluede stdlib.h because //exit() is also defined in glut.h file.

float angle=0.0,deltaAngle = 0.0,ratio;
int xOrigin = -1;
float x=0.0f,y=1.75f,z=5.0f;
float lx=0.0f,ly=0.0f,lz=-1.0f;
int deltaMove = 0,h,w, muter;
int font=(int)GLUT_BITMAP_8_BY_13;
static GLint snowman_display_list;
GLint texture_snowman_display_list = 1;
GLint shaded_snowman_display_list = 2;
static GLint bikin_pohon_list;
GLint texture_bikin_pohon_list = 4;
GLint shaded_bikin_pohon_list = 8;
static GLint fogMode;

int bitmapHeight=13;

int frame,time,timebase=0;
char s[30];

void initWindow();


void changeSize(int w1, int h1)
 {

 // Prevent a divide by zero, when window is too short
 // (you cant make a window of zero width).
 if(h1 == 0)
  h1 = 1;

 w = w1;
 h = h1;
 ratio = 1.0f * w / h;
 // Reset the coordinate system before modifying
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();

 // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

 // Set the clipping volume
 gluPerspective(45,ratio,0.1,1000);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 gluLookAt(x, y, z,
       x + lx,y + ly,z + lz,
    0.0f,1.0f,0.0f);


 }

void drawSnowMan() {

glPushMatrix();
 glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body
 glTranslatef(0.0f ,0.75f, 0.0f);
 glutSolidSphere(0.75f,20,20);



// Draw Head
 glTranslatef(0.0f, 1.0f, 0.0f);
 glutSolidSphere(0.25f,20,20);

// Draw Eyes
 glPushMatrix();
 glColor3f(0.0f,0.0f,0.0f);
 glTranslatef(0.05f, 0.10f, 0.18f);
 glutSolidSphere(0.05f,10,10);
 glTranslatef(-0.1f, 0.0f, 0.0f);
 glutSolidSphere(0.05f,10,10);
 glPopMatrix();

// Draw Nose
 glColor3f(1.0f, 0.5f , 0.5f);
 glRotatef(0.0f,1.0f, 0.0f, 0.0f);
 glutSolidCone(0.08f,0.5f,10,2);

 // Draw Teapot

 //draw torus
 glPushMatrix();
 glColor3f(1.5f, 1.0f, 0.0f);
 glTranslatef(0.0, 0.0, -0.5);
 glRotatef(muter,0.,0.,0.1);
 glutSolidTorus (0.15, 0.85, 50, 50);
 glPopMatrix();

 /*if (shaded){
    if(texture){
        glCallList(texture_snowman_display_list);
    }else {
        glCallList(shaded_snowman_display_list);
    }
 }*/
glPopMatrix();

}

//ini untuk timer, dimana torus berputar putar
void timer(int value){
    muter -= 8;
    glutPostRedisplay();
    glutTimerFunc(60,timer,60);
}

//ini hidmbauan hati hati terdapat gunung aktif object 2D
void amplop(){

    glPushMatrix();
        glTranslatef(0.9, 0.9, -0.1);
        glScalef(0.3, 2.0, 0.0);
        glColor3f(0.5 ,1.5, 0.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, 0.9, 0.0);
        glColor3f(0.0 ,1.0, 1.0);
        glBegin(GL_QUADS);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(0.0, 1.4, 0.0);
            glVertex3f(1.9, 1.4, 0.0);
            glVertex3f(1.9, 0.0, 0.0);
        glEnd();

        glPushMatrix();
            glTranslatef(0.0, 0.0, 0.0);
            glColor3f(1.0, 0.0, 0.0);
            glBegin(GL_LINE_LOOP);
                glVertex3f(1.5, 1.0, 0.01);
                glVertex3f(1.5, 1.3, 0.01);
                glVertex3f(1.7, 1.3, 0.01);
                glVertex3f(1.7, 1.0, 0.01);
            glEnd();

            glBegin(GL_LINE_STRIP);
                glVertex3f(1.4, 1.2, 0.1);
                glVertex3f(1.6, 1.1, 0.1);
                glVertex3f(1.8, 1.4, 0.1);
            glEnd();

            glPushMatrix();
            glTranslatef(0.2, 0.5, 0.0);
            glBegin(GL_QUAD_STRIP);
                glVertex3f(0.0, 0.0, 0.1);
                glVertex3f(0.5, 0.3, 0.1);
                glVertex3f(1.0, 0.3, 0.1);
                glVertex3f(1.5, 0.0, 0.1);
            glEnd();
        glPopMatrix();

        glBegin(GL_LINES);
            glVertex3f(0.2, 0.2, 0.1);
            glVertex3f(1.7, 0.2, 0.1);
        glEnd();

        glPushMatrix();
            glTranslatef(0.1, 1.0, 0.1);
            glScalef(0.3, 0.3, 0.3);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.0, 0.0, 0.1);
                glVertex3f(0.5, 1.0, 0.1);
                glVertex3f(1.0, 0.0, 0.1);
            glEnd();
        glPopMatrix();
        glPopMatrix();
    glPopMatrix();

}

void segitigaUlang(){
 glBegin(GL_TRIANGLE_STRIP);
     glColor3f(1.0, 0.0, 1.0);
     glVertex3f(0.0, 0.0, 0.1);
     glVertex3f(0.5, 1.0, 0.1);
     glVertex3f(1.0, 0.0, 0.1);

     glColor3f(1.0, 1.0, 1.0);
     glVertex3f(0.5, 1.0, 0.1);
     glVertex3f(1.0, 0.0, 0.1);
     glVertex3f(1.5, 1.0, 0.1);
 glEnd();

 glBegin(GL_POINTS);
    glScalef(5.0, 5.0, 5.0);
    glVertex3f(0.0, -0.5, 0.0);
 glEnd();
}
//2D mari menggambar  rambu triangle
void pelangi(){
    glPushMatrix();
         glTranslatef(-7.9, 0.0, -0.1);
         glPushMatrix();
            glTranslatef(0.9, 0.9, -0.1);
            glScalef(0.3, 2.3, 0.0);
            glColor3f(0.5 ,1.5, 0.0);
            glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
            glColor3f(0.5 ,0.0, 1.1);
            glTranslatef(0.1, 1.1, 0.0);
            glBegin(GL_POLYGON);
                glVertex3f(0.0, 0.0, 0.0);
                glVertex3f(-0.3, 0.4, 0.0);
                glVertex3f(0.0, 0.8, 0.0);
                glVertex3f(1.0, 0.8, 0.0);
                glVertex3f(1.0, 0.0, 0.0);
            glEnd();

            glPushMatrix();
            glTranslatef(0.1, 0.4, 0.1);
            glScalef(0.2, 0.2, 0.2);
                glBegin(GL_TRIANGLE_FAN);
                    glColor3f(1.0, 1.0, 0.0);
                    glVertex3f(0.0, 0.0, 0.1);
                    glVertex3f(-0.3, 1.0, 0.1);
                    glColor3f(0.0, 1.0, 0.0);
                    glVertex3f(-0.5, 0.8, 0.1);

                    glColor3f(1.0, 0.0, 0.0);
                    glVertex3f(0.0, 0.0, 0.1);
                    glVertex3f(-0.6, 0.8, 0.1);
                    glVertex3f(-0.7, 0.5, 0.1);

                    glColor3f(1.0, 0.0, 1.0);
                    glVertex3f(0.0, 0.0, 0.1);
                    glVertex3f(-0.8, 0.4, 0.1);
                    glVertex3f(-0.9, 0.2, 0.1);
                glEnd();

                //segitiga ulang dari segitiga strip
                glScalef(0.5, 0.5, 0.5);
                glTranslatef(0.0, 2.5, 0.0);
                segitigaUlang();
                glTranslatef(1.0, 0.0, 0.0);
                segitigaUlang();
                glTranslatef(1.0, 0.0, 0.0);
                segitigaUlang();
                glTranslatef(1.0, 0.0, 0.0);
                segitigaUlang();
                glTranslatef(1.0, 0.0, 0.0);
                segitigaUlang();
                glTranslatef(1.0, 0.0, 0.0);
                segitigaUlang();
                glTranslatef(1.0, 0.0, 0.0);
                segitigaUlang();
                glTranslatef(1.0, 0.0, 0.0);
                segitigaUlang();

            glPopMatrix();

        glPopMatrix();
    glPopMatrix();
}

//3D cylinder itu ntuk pohon :v
void makeCylinder(float height, float base){
GLUquadric *obj = gluNewQuadric();
//gluQuadricDrawStyle(obj, GLU_LINE);
glColor3f(0.10f, 0.81, 0.18f);
glPushMatrix();
glRotatef(-90, 1.0, 0.0, 0.0);
gluCylinder(obj, base,base-(0.2*base), height, 20,20);
glPopMatrix();
glutSwapBuffers();
}

void gambarPohon(float height, float base){

 //perulangan bikin cabang
float angle;
    makeCylinder(height, base);
    glTranslatef(0.0, height, 0.0);
    height -= height*.2;
    base-= base*0.3;

    for(int a= 0; a<3; a++){
        angle = rand()%50+20;
        if(angle >48)
        angle = -(rand()%50+20);
        if (height >1){
            glPushMatrix();
            glRotatef(angle,1,0.0,1);
            gambarPohon(height,base);
            //ini untuk daun diujung
             glColor3f(0.0, 0.1, 0.1);
             glScalef(0.1, 0.1, 0.1);
            glutSolidDodecahedron();
            glPopMatrix();
        }
    }
}


GLuint createDL() {
 GLuint snowManDL;
 GLuint pohonManDL;

 // Create the id for the list
 /*snowManDL = glGenLists(2);
 glNewList(snowManDL+1,GL_COMPILE);
  drawSnowMan();
 glEndList();
*/
 pohonManDL = glGenLists(2);
 glNewList(pohonManDL+1,GL_COMPILE);
  gambarPohon(2,0.1);
 glEndList();

 // start list
 //glNewList(snowManDL,GL_COMPILE);
 glNewList(pohonManDL,GL_COMPILE);

 // call the function that contains the rendering commands
 /*for(int i = -3; i < 3; i++)
  for(int j=-3; j < 3; j++) {
   glPushMatrix();
   glTranslatef(i*10.0,0,j * 10.0);
   glCallList(snowManDL+1);
   glPopMatrix();
  }
*/

  for(int i = -3; i < 3; i++)
  for(int j=-3; j < 3; j++) {
   glPushMatrix();
   glTranslatef(i*10.0,0,j * 10.0);
   glCallList(pohonManDL+1);
   glPopMatrix();
  }

 // endList
 glEndList();

 //return(snowManDL);
 return(pohonManDL);
}

void initScene() {

//ini untuk bitmap
    glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
    glClearColor (0.0, 0.0, 0.0, 0.0);
 //ini untuk si snowman dan si pohon
 glEnable(GL_DEPTH_TEST);
 snowman_display_list = createDL();
 bikin_pohon_list = createDL();

 /* Set up Texturing */
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, IMAGE_WIDTH,
    IMAGE_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE,
    image);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  /*ini untuk antialias */
       GLfloat values[2];
       glGetFloatv (GL_LINE_WIDTH_GRANULARITY, values);
       printf ("GL_LINE_WIDTH_GRANULARITY value is %3.1f\n", values[0]);

       glGetFloatv (GL_LINE_WIDTH_RANGE, values);
       printf ("GL_LINE_WIDTH_RANGE values are %3.1f %3.1f\n",
          values[0], values[1]);
       glEnable (GL_LINE_SMOOTH);
       glEnable (GL_BLEND);
       glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
       glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
       glLineWidth (1.5);

       glClearColor(0.0, 0.0, 0.0, 0.0);

  /* Initial render mode is with full shading and LIGHT 0
     enabled. */
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_ALPHA_TEST);

  glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  glShadeModel(GL_SMOOTH);

  /*ini untuk Fog */
  glEnable(GL_FOG);
   {
      GLfloat fogColor[4] = {0.2, 0.2, 0.2, 1.0};

      fogMode = GL_EXP;
      glFogi (GL_FOG_MODE, fogMode);
      glFogfv (GL_FOG_COLOR, fogColor);
      glFogf (GL_FOG_DENSITY, 0.1);
      glHint (GL_FOG_HINT, GL_DONT_CARE);
      glFogf (GL_FOG_START, 1.0);
      glFogf (GL_FOG_END, 5.0);
   }
   glClearColor(0.2, 0.2, 0.2, 1.0);  /* fog color */

   /*ini untuk polygon offsite
   */


}

//ini untuk orientasi lihat
void orientMe(float ang) {

 lx = sin(ang);
 lz = -cos(ang);
 glLoadIdentity();
 gluLookAt(x, y, z,
       x + lx,y + ly,z + lz,
    0.0f,1.0f,0.0f);
}

//untuk pindah di bidang rata
void moveMeFlat(int i) {
 x = x + i*(lx)*0.1;
 z = z + i*(lz)*0.1;
 glLoadIdentity();
 gluLookAt(x, y, z,
       x + lx,y + ly,z + lz,
    0.0f,1.0f,0.0f);
}

void setOrthographicProjection() {
 // switch to projection mode
 glMatrixMode(GL_PROJECTION);
 // save previous matrix which contains the
 //settings for the perspective projection
 glPushMatrix();
 // reset matrix
 glLoadIdentity();
 // set a 2D orthographic projection
 gluOrtho2D(0, w, 0, h);
 // invert the y axis, down is positive
 glScalef(1, -1, 1);
 // mover the origin from the bottom left corner
 // to the upper left corner
 glTranslatef(0, -h, 0);
 glMatrixMode(GL_MODELVIEW);
}

void resetPerspectiveProjection() {
 // set the current matrix to GL_PROJECTION
 glMatrixMode(GL_PROJECTION);
 // restore previous settings
 glPopMatrix();
 // get back to GL_MODELVIEW matrix
 glMatrixMode(GL_MODELVIEW);
}

void renderBitmapString(float x, float y, void *font,char *string)
{

  char *c;
  // set position to start drawing fonts
  glRasterPos2f(x, y);
  // loop all the characters in the string
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}

static void printStrokedString(char *s)
{
    GLsizei len = strlen(s);
    glCallLists(len ,GL_BYTE,(GLbyte *)s);
}

void renderScene(void) {

 if (deltaMove)
  moveMeFlat(deltaMove);
 if (deltaAngle) {
  angle += deltaAngle;
  orientMe(angle);
 }

 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//ini untuk bitmap
glPushMatrix();
glTranslatef(1.2,0,0);
glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);
    glRasterPos2i (0, 0);
    glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, H);
    glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, o);
    glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, r);
    glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, r);
    glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, o);
    glBitmap (10, 12, 0.0, 0.0, 11.0, 0.0, r);
    glFlush();
glPopMatrix();
//snowmanku
glPushMatrix();
glTranslatef(5.0, 5.0, 0.0);
glPushMatrix();
glRotatef(rotAngle, 0.0, 0.0, 0.1);
 glRotatef(muter,0.,0.,0.1);
glutWireCube(4);
glPopMatrix();
glTranslatef(0.0, -1.0, 0.0);
drawSnowMan();
glPopMatrix();

//ini plang gunung centang
glPushMatrix();
glTranslatef(7.0, 0.0, -15.0);
amplop();
glColor3f(1.0, 1.0, 0.0);
glScalef(0.01, 0.01, 0.01);
glTranslatef(24.0, 115.0, 0.1);
printStrokedString(test1);
glPopMatrix();

//ini pelangi worm himbauan


glPushMatrix();
glTranslatef(7.0, 0.0, -15.0);
pelangi();
glColor3f(1.0, 1.0, 0.0);
glScalef(0.01, 0.01, 0.01);
glTranslatef(-780.0, 140.0, 0.1);
printStrokedString(test2);
glPopMatrix();



glPushMatrix();
glTranslatef(-15.0, 5.0, 5.0);
glColor3f(0.0, 1.0, 1.0);
    glPushMatrix();
    glRotatef(muter,0.,0.,0.1);
    glutWireCube(4);
    glPopMatrix();
glColor3f(1.0, 1.0, 1.0);
glEnable(GL_POLYGON_OFFSET_FILL);
glutWireTeapot(1.0);
glPopMatrix();

// Draw ground

 glColor3f(0.9f, 0.9f, 0.9f);
 glBegin(GL_QUADS);
  glVertex3f(-100.0f, 0.0f, -100.0f);
  glVertex3f(-100.0f, 0.0f,  100.0f);
  glVertex3f( 100.0f, 0.0f,  100.0f);
  glVertex3f( 100.0f, 0.0f, -100.0f);
 glEnd();

 //gambar pohon
glCallList(snowman_display_list);
// Draw 36 Snow Men

 glCallList(bikin_pohon_list);

 frame++;
 time=glutGet(GLUT_ELAPSED_TIME);
 if (time - timebase > 1000) {
  sprintf(s,"FPS:%4.2f",frame*1000.0/(time-timebase));
  timebase = time;
  frame = 0;
 }

 glColor3f(0.0f,1.0f,1.0f);
 setOrthographicProjection();
 glPushMatrix();
 glLoadIdentity();
 renderBitmapString(30,15,(void *)font,"TUGAS UAS - TITIK NURFAIDAH");
 //renderBitmapString(30,35,(void *)font,s);
 renderBitmapString(30,35,(void *)font,"Esc - Keluar");
 glPopMatrix();
 resetPerspectiveProjection();

 glutSwapBuffers();
}
/*  planes for texture coordinate generation  */
static GLfloat xequalzero[] = {1.0, 0.0, 0.0, 0.0};
static GLfloat slanted[] = {1.0, 1.0, 1.0, 0.0};
static GLfloat *currentCoeff;
static GLenum currentPlane;
static GLint currentGenMode;
void processNormalKeys(unsigned char key, int x, int y) {
    switch (key) {
    case 'b'://blendingan
        if (blendingOn){
            glEnable(GL_BLEND);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glShadeModel (GL_FLAT);
            glClearColor (0.0, 0.0, 0.0, 0.0);
            blendingOn = FALSE;
        }else{
            glDisable(GL_BLEND);
            blendingOn = TRUE;
        }
      break;

    case 'a'://antialias


    break;
    case 't'://tekstru
    glClearColor (0.0, 0.0, 0.0, 0.0);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_SMOOTH);

   makeStripeImage();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

#ifdef GL_VERSION_1_1
   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_1D, texName);
#endif
   glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
#ifdef GL_VERSION_1_1
   glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, stripeImageWidth, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
#else
   glTexImage1D(GL_TEXTURE_1D, 0, 4, stripeImageWidth, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
#endif
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   currentCoeff = xequalzero;
   currentGenMode = GL_OBJECT_LINEAR;
   currentPlane = GL_OBJECT_PLANE;
   glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
   glTexGenfv(GL_S, currentPlane, currentCoeff);

   glEnable(GL_TEXTURE_GEN_S);
   glEnable(GL_TEXTURE_1D);
   glEnable(GL_CULL_FACE);
 glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_AUTO_NORMAL);
   glEnable(GL_NORMALIZE);
   glFrontFace(GL_CW);
   glCullFace(GL_BACK);
   glMaterialf (GL_FRONT, GL_SHININESS, 64.0);
   break;

    case 'f':
    case 'F':
        if (fogMode == GL_EXP) {
	    fogMode = GL_EXP2;
	    printf ("Fog mode is GL_EXP2\n");
         }
         else if (fogMode == GL_EXP2) {
            fogMode = GL_LINEAR;
            printf ("Fog mode is GL_LINEAR\n");
         }
         else if (fogMode == GL_LINEAR) {
            fogMode = GL_EXP;
            printf ("Fog mode is GL_EXP\n");
         }
         glFogi (GL_FOG_MODE, fogMode);
         glutPostRedisplay();
         break;

    case '0':
    if (light1) {
      glDisable(GL_LIGHT0);
      light1 = FALSE;
    } else {
      glEnable(GL_LIGHT0);
      light1 = TRUE;
    }
    break;
    case 27:
         exit(0);
         break;

  glutPostRedisplay();
}}

//ini fungsi untuk si mouse, sehingga bisa bergeran
void mouseButton(int button, int state, int x, int y) {
	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngle;
			xOrigin = -1;
			printf("tombol kiri (%d,%d)\n",x,y);
		}
		else  {// state = GLUT_DOWN
			xOrigin = x;
		}
	}
}

//dan yan gini untuk motion
void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.0001f;

		// update camera's direction
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}
void menu (int val){
 unsigned char key;

  switch (val) {
  case 1:
    key = 'b';//blending
    break;
  case 2:
    key = ' ';
    break;
  case 3:
    key = 't';//transparant
    break;
  case 4:
    key = 'f';//fog
    break;
  case 5:
    key = '0';//cahaya 0
    break;
  default:
    return;
  }
  processNormalKeys(key, 0, 0);
}

void create_menu(void){
    glutCreateMenu(menu);
  glutAttachMenu(GLUT_LEFT_BUTTON);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  glutAddMenuEntry("blending", 1);
  glutAddMenuEntry(" ", 2);
  glutAddMenuEntry("teksture", 3);
  glutAddMenuEntry("FOG", 4);
  glutAddMenuEntry("Cahaya", 5);;
}

void pressKey(int key, int x, int y) {

 switch (key) {
  case GLUT_KEY_LEFT : deltaAngle = -0.01f;break;
  case GLUT_KEY_RIGHT : deltaAngle = 0.01f;break;
  case GLUT_KEY_UP : deltaMove = 1;break;
  case GLUT_KEY_DOWN : deltaMove = -1;break;
 }

}

void releaseKey(int key, int x, int y) {

 switch (key) {
  case GLUT_KEY_LEFT : if (deltaAngle < 0.0f)
        deltaAngle = 0.0f;
       break;
  case GLUT_KEY_RIGHT : if (deltaAngle > 0.0f)
        deltaAngle = 0.0f;
       break;
  case GLUT_KEY_UP : if (deltaMove > 0)
        deltaMove = 0;
       break;
  case GLUT_KEY_DOWN : if (deltaMove < 0)
        deltaMove = 0;
       break;
 }
}

void
myReshape(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -5.0);  /* viewing transform  */
  glScalef(1.5, 1.5, 1.5);
}

void initWindow() {
 glutIgnoreKeyRepeat(1);
 glutKeyboardFunc(processNormalKeys);
 glutSpecialFunc(pressKey);
 glutSpecialUpFunc(releaseKey);
 glutDisplayFunc(renderScene);
 glutIdleFunc(renderScene);
 glutReshapeFunc(changeSize);
 glutTimerFunc(10, timer, 0);
 glutMouseFunc(mouseButton);
 glutMotionFunc(mouseMove);
 initScene();
 huruf();
 initial();

}

int main(int argc, char **argv)
{
  puts("Hutan Dodecahedron\n");

  puts("Guanakan keyboar arah untuk jelan dan melihat, atau bisa digunakan juga mouse");
  puts("Blending    : 'b' = jadinya nge Blend ");
  puts("tektur      : 't' =  bertekstur aneh  ");
  puts("fog         : 'f' =  berasap, sumpah serem. gawene bengi bengi salah");
  puts("cahaya gelap: '0' = cahaya terangkanlah ");
  puts("   to the left mouse button.\n");
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
 glutInitWindowPosition(100,100);
 glutInitWindowSize(640,360);
 glutCreateWindow("UAS semangat, semester 5");

 // register all callbacks
 initWindow();

 glutMainLoop();

 return(0);
}
