

#define GL_SILENCE_DEPRECATION

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>


GLboolean redFlag = true, switchOne = false, switchTwo=false, switchLamp=false, amb1=true, diff1=true, spec1=true, amb2=true, diff2=true, spec2=true, amb3=true, diff3=true, spec3=true;
double windowHeight=800, windowWidth=600;
double eyeX=7.0, eyeY=2.0, eyeZ=15.0, refX = 0, refY=0,refZ=0;
double theta = 180.0, y = 1.36, z = 7.97888;

static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.0, 3.0, 0.0}, //4
    {0.0, 3.0, 3.0}, //5
    {3.0, 3.0, 3.0}, //6
    {3.0, 3.0, 0.0}  //7
};

static GLubyte quadIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};



static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}


void drawCube()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();
}

void drawCube1(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX=0, GLfloat ambY=0, GLfloat ambZ=0, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    
    glBegin(GL_QUADS);
    
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();
}

static GLfloat v_trapezoid[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.5, 3.0, 0.5}, //4
    {0.5, 3.0, 2.5}, //5
    {2.5, 3.0, 2.5}, //6
    {2.5, 3.0, 0.5}  //7
};

static GLubyte TquadIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};

void drawTrapezoid(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_emission[] = {difX, difY, difZ, 0.0};
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    
    if(switchLamp==true){
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    } else {
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_trapezoid[TquadIndices[i][0]][0], v_trapezoid[TquadIndices[i][0]][1], v_trapezoid[TquadIndices[i][0]][2],
        v_trapezoid[TquadIndices[i][1]][0], v_trapezoid[TquadIndices[i][1]][1], v_trapezoid[TquadIndices[i][1]][2],
        v_trapezoid[TquadIndices[i][2]][0], v_trapezoid[TquadIndices[i][2]][1], v_trapezoid[TquadIndices[i][2]][2]);
        
        glVertex3fv(&v_trapezoid[TquadIndices[i][0]][0]);
        glVertex3fv(&v_trapezoid[TquadIndices[i][1]][0]);
        glVertex3fv(&v_trapezoid[TquadIndices[i][2]][0]);
        glVertex3fv(&v_trapezoid[TquadIndices[i][3]][0]);
    }
    glEnd();
}


//Drawing pyramid *************************
static GLfloat v_pyramid[5][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 2.0},
    {2.0, 0.0, 2.0},
    {2.0, 0.0, 0.0},
    {1.0, 4.0, 1.0}
};

static GLubyte p_Indices[4][3] =
{
    {4, 1, 2},
    {4, 2, 3},
    {4, 3, 0},
    {4, 0, 1}
};

static GLubyte PquadIndices[1][4] =
{
    {0, 3, 2, 1}
};

void drawpyramid(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <4; i++)
    {
        getNormal3p(v_pyramid[p_Indices[i][0]][0], v_pyramid[p_Indices[i][0]][1], v_pyramid[p_Indices[i][0]][2],
                    v_pyramid[p_Indices[i][1]][0], v_pyramid[p_Indices[i][1]][1], v_pyramid[p_Indices[i][1]][2],
                    v_pyramid[p_Indices[i][2]][0], v_pyramid[p_Indices[i][2]][1], v_pyramid[p_Indices[i][2]][2]);
        glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (GLint i = 0; i <1; i++)
    {
        getNormal3p(v_pyramid[PquadIndices[i][0]][0], v_pyramid[PquadIndices[i][0]][1], v_pyramid[PquadIndices[i][0]][2],
                    v_pyramid[PquadIndices[i][1]][0], v_pyramid[PquadIndices[i][1]][1], v_pyramid[PquadIndices[i][1]][2],
                    v_pyramid[PquadIndices[i][2]][0], v_pyramid[PquadIndices[i][2]][1], v_pyramid[PquadIndices[i][2]][2]);
        glVertex3fv(&v_pyramid[PquadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][3]][0]);
    }
    glEnd();

}

void polygon(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    
    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(6,0);
    glVertex2f(5.8,1);
    glVertex2f(5.2,2);
    glVertex2f(5, 2.2);
    glVertex2f(4, 2.8);
    glVertex2f(3,3);
    glVertex2f(2, 2.8);
    glVertex2f(1, 2.2);
    glVertex2f(0.8, 2);
    glVertex2f(0.2,1);
    //glVertex2f(0,0);
    
    glEnd();
}

void polygonLine(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glBegin(GL_LINE_STRIP);
    //glVertex2f(0,0);
    glVertex2f(6,0);
    glVertex2f(5.8,1);
    glVertex2f(5.2,2);
    glVertex2f(5, 2.2);
    glVertex2f(4, 2.8);
    glVertex2f(3,3);
    glVertex2f(2, 2.8);
    glVertex2f(1, 2.2);
    glVertex2f(0.8, 2);
    glVertex2f(0.2,1);
    glVertex2f(0,0);
    
    glEnd();
}

void drawSphere(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    
    glutSolidSphere (3.0, 20, 16);
}



void room()
{
    
    
    // right wall
    //glColor3f(1, 0.8, 0.5);
    glPushMatrix();
    glTranslatef(-1.5,-1,.5);
    glScalef(5, 2, 0.1);
    //drawCube1(1, 0.8, 0.5,  0.5,0.4,0.25);
    drawCube1(1, 0.8, 0.7,  0.5, 0.4, 0.35);
    glPopMatrix();
    
    // left wall
    //glColor3f(1, 0.8, 0.7);
    glPushMatrix();
    glTranslatef(-4.5,-1,0);
    glScalef(1, 2, 5);
    drawCube1(1, 0.8, 0.7,  0.5, 0.4, 0.35);
    glPopMatrix();
    
    // wall besides the right wall
    //glColor3f(1, 0.8, 0.7);
    glPushMatrix();
    glTranslatef(8,-1,0);
    glScalef(0.2, 2, 5);
    drawCube1(1, 0.8, 0.7,  0.5, 0.4, 0.35);
    glPopMatrix();
    
    //ceiling
     //glColor3f(1.0, 0.9, 0.8);
     glPushMatrix();
     glTranslatef(-2,5.1,0);
     glScalef(5, 0.1, 7);
     drawCube1(1.0, 0.9, 0.8,  0.5,0.45,0.4);
     glPopMatrix();
     
     
    
    // floor
    glPushMatrix();
    glScalef(5, 0.1, 7);
    glTranslatef(-1,-5,0); //-1,-5,.5
    //glScalef(5, 0.1, 7);
    drawCube1(1,0.8,0.6, 0.4,0.3,0.35);
    glPopMatrix();
}



void drawChair() {
	// mat ghe
	glColor3f(0.3,0.3,0.3);
    glPushMatrix();
    glTranslatef(3, 0.8, 10);
    glScalef(0.5, 0.1, 0.5);
    glutSolidCube(1.5);
    glPopMatrix();

    //chan ghe
    glColor3f(0.3,0.3,0.3);
    glPushMatrix();
    glTranslatef(3.3, 0.2, 9.7);
    glScalef(0.1, 1.3, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

	glColor3f(0.3,0.3,0.3);
    glPushMatrix();
    glTranslatef(3.3, 0.2, 10.3);
    glScalef(0.1, 1.3, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

	glColor3f(0.3,0.3,0.3);
    glPushMatrix();
    glTranslatef(2.7, 0.2, 10.3);
    glScalef(0.1, 1.3, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

	glColor3f(0.3,0.3,0.3);
    glPushMatrix();
    glTranslatef(2.7, 0.2, 9.7);
    glScalef(0.1, 1.3, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawChair2() {
	// mat ghe
	glColor3f(0.3,0.3,0.3);
    glPushMatrix();
    glTranslatef(7, 0.8, 10);
    glScalef(0.5, 0.1, 0.5);
    glutSolidCube(1.5);
    glPopMatrix();

    //chan ghe
    glColor3f(0.3,0.3,0.3);
    glPushMatrix();
    glTranslatef(7.3, 0.2, 9.7);
    glScalef(0.1, 1.3, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

	glColor3f(0.3,0.3,0.3);
    glPushMatrix();
    glTranslatef(7.3, 0.2, 10.3);
    glScalef(0.1, 1.3, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

	glColor3f(0.3,0.3,0.3);
    glPushMatrix();
    glTranslatef(6.7, 0.2, 10.3);
    glScalef(0.1, 1.3, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

	glColor3f(0.3,0.3,0.3);
    glPushMatrix();
    glTranslatef(6.7, 0.2, 9.7);
    glScalef(0.1, 1.3, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawChair3() {
	// mat ghe
	glColor3f(0.3,0.3,0.3);
    glPushMatrix();
    glTranslatef(5, 0.8, 8);
    glScalef(0.5, 0.1, 0.5);
    glutSolidCube(1.5);
    glPopMatrix();

    //chan ghe
    glColor3f(0.3,0.3,0.3);
    glPushMatrix();
    glTranslatef(4.7, 0.2, 7.7);
    glScalef(0.1, 1.3, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

	glColor3f(0.3,0.3,0.3);
    glPushMatrix();
    glTranslatef(5.3, 0.2, 8.3);
    glScalef(0.1, 1.3, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

	glColor3f(0.3,0.3,0.3);
    glPushMatrix();
    glTranslatef(4.7, 0.2, 8.3);
    glScalef(0.1, 1.3, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

	glColor3f(0.3,0.3,0.3);
    glPushMatrix();
    glTranslatef(5.3, 0.2, 7.7);
    glScalef(0.1, 1.3, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawChair4() {
	// mat ghe
	glColor3f(0.3,0.3,0.3);
    glPushMatrix();
    glTranslatef(5, 0.8, 12);
    glScalef(0.5, 0.1, 0.5);
    glutSolidCube(1.5);
    glPopMatrix();

    //chan ghe
    glColor3f(0.3,0.3,0.3);
    glPushMatrix();
    glTranslatef(4.7, 0.2, 11.7);
    glScalef(0.1, 1.3, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

	glColor3f(0.3,0.3,0.3);
    glPushMatrix();
    glTranslatef(5.3, 0.2, 12.3);
    glScalef(0.1, 1.3, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

	glColor3f(0.3,0.3,0.3);
    glPushMatrix();
    glTranslatef(4.7, 0.2, 12.3);
    glScalef(0.1, 1.3, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

	glColor3f(0.3,0.3,0.3);
    glPushMatrix();
    glTranslatef(5.3, 0.2, 11.7);
    glScalef(0.1, 1.3, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();
    
    
}
 

void window()
{
    //Window ********************************************
    //window white open
    glPushMatrix();
    glTranslatef(-1.3,1,8.9); //0.5,1,9.6
    glScalef(0.0001, .6, .3);
    drawCube1(1.0,1.0,1.0, 0.05,0.05,0.05);
    glPopMatrix();
        
    //window right side corner
    glPushMatrix();
    glTranslatef(-1.3,1,8.9);
    glScalef(0.04, .6, 0.0001);
    drawCube1(0.8,0.6,0.4, 0.4,0.3,0.2);
    glPopMatrix();
    
    //window left side corner
    glPushMatrix();
    glTranslatef(-1.3,1,9.8);
    glScalef(0.04, 0.6, 0.0001);
    drawCube1(0.8,0.6,0.4, 0.4,0.3,0.2);
    glPopMatrix();
        
    //window upper side corner
    glPushMatrix();
    glTranslatef(-1.1,2.7,8.9);
    glScalef(0.0001, 0.05, 0.4);
    drawCube1(0.7,0.6,0.5,  0.35,0.3,0.25);
    glPopMatrix();
        
        
    //window lower side corner
    glPushMatrix();
    glTranslatef(-1.2,1.02,8.9);
    glScalef(0.0001, 0.02, 0.34);
    drawCube1(0.7,0.6,0.5,  0.35,0.3,0.25);
    glPopMatrix();
        
        //window vertical bar 1
        glPushMatrix();
        glTranslatef(-1.27,2.1,8.9);
        //glRotatef(22, 0,0,1);
        glScalef(0.0001, 0.02, 0.3);
        drawCube1(0.0,0.0,0.0, 0.0,0.0,0.0, 5);
        glPopMatrix();
        
        //window vertical bar 2
        glPushMatrix();
        glTranslatef(-1.27,1.6,8.9);
        //glRotatef(22, 0,0,1);
        glScalef(0.0001, 0.02, 0.3);
    drawCube1(0.0,0.0,0.0, 0.0,0.0,0.0, 5);
        glPopMatrix();
        
        //window horizontal bar
        glPushMatrix();
        glTranslatef(-1.27,1,9.3);
        //glRotatef(22, 0,0,1);
        glScalef(0.0001, 0.6, 0.02);
    drawCube1(0.0,0.0,0.0, 0.0,0.0,0.0, 5);
        glPopMatrix();
}

void sphericalObject()
{
    //mat ban
    glPushMatrix();
    glTranslatef(5, 1.2,10);
    glScalef(0.4, 0.05, 0.4);
    drawSphere(0.5,0.2,0,  0.25,0.1,0,  50);
    glPopMatrix();
    
    //chan ban
    glColor3f(0.2,0.1,0.1); //0.2,0.1,0.1
    glPushMatrix();
    glTranslatef(4.98,-0.1,10);
    glScalef(0.02, 0.4, 0.02);
    drawCube1(0.5,0.2,0,  0.25,0.1,0,  50);
    glPopMatrix();
    
    //tru 
    glPushMatrix();
    glTranslatef(5, -0.1, 10);
    glScalef(0.05, 0.01, 0.05);
    drawSphere(0.5,0.2,0,  0.25,0.1,0,  50);
    glPopMatrix();
    
      //cabinet duoi
  glPushMatrix();
  glTranslatef(0.2, -0.2, 0.0);
  glScalef(2.05, 0.6, 0.8);
  drawCube1(0.5, 0.5, 0.5, 0.5,0.2,0, 50); // Draw the chair seat with red material
  glPopMatrix();
  
  

  
  
  //thanh tu duoi ben trai
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0.1,-0.2,3.4);
    glScalef(0.04, 0.6, 0.04);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix();
    
     //nut tu doc duoi ben trai
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(0.2,0.5,3.1);
    glScalef(0.01, 0.2, 0.05);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix(); 
    
     //tam tu trang duoi ben trai
    glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(0.2,-0.1,3.5);
    glScalef(0.01, 0.55, 0.79);
    drawCube1(1,1,1,  0.5,0.5,0.5);
    glPopMatrix();
    
    //thanh tu duoi ben trai
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0.1,-0.2,5.8);
    glScalef(0.04, 0.6, 0.04);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix();
    
    //nut tu doc duoi ben trai
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(0.2,0.5,6.03);
    glScalef(0.01, 0.2, 0.05);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix(); 
    
    
    
    //nut tu
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(2.2,1.1,2.5);
    glScalef(0.1, 0.06, 0.02);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix(); 
    //nut tu
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(3.5,1.1,2.5);
    glScalef(0.1, 0.06, 0.02);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix(); 
    //nut tu
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(4.8,1.1,2.5);
    glScalef(0.1, 0.06, 0.02);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix(); 
    //nut tu
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(0.8,1.1,2.5);
    glScalef(0.1, 0.06, 0.02);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix(); 
    
     //nut tu doc
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(5.8,0.5,2.5);
    glScalef(0.05, 0.2, 0.01);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix(); 
    
     //nut tu 
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(2.2,0.3,2.5);
    glScalef(0.1, 0.06, 0.02);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix(); 
    //nut tu 
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(3.5,0.3,2.5);
    glScalef(0.1, 0.06, 0.02);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix(); 
    //nut tu 
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(4.8,0.3,2.5);
    glScalef(0.1, 0.06, 0.02);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix(); 
    //nut tu 
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(0.8,0.3,2.5);
    glScalef(0.1, 0.06, 0.02);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix(); 
    
    
    //nut tu doc tren 
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(0.4,3.5,2.5);
    glScalef(0.05, 0.2, 0.01);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix(); 
    //nut tu doc tren 
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(1.9,3.5,2.5);
    glScalef(0.05, 0.2, 0.01);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix(); 
    //nut tu doc tren 
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(3.3,3.5,2.5);
    glScalef(0.05, 0.2, 0.01);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix(); 
    //nut tu doc tren 
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(4.6,3.5,2.5);
    glScalef(0.05, 0.2, 0.01);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix(); 
    //nut tu doc tren 
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(5.8,3.5,2.5);
    glScalef(0.05, 0.2, 0.01);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix(); 
    
    //nut tu 
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(0.2,1.1,4.3);
    glScalef(0.02, 0.06, 0.3);
    drawCube1(0,0,0,  0,0,0);
    glPopMatrix();
    
    // vien tu duoi
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0.2,1.53,2.4);
    glScalef(2.03, 0.02, 0.02);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    
    // vien tu trong
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(-1.3,1.58,0.9);
    glScalef(2.6, 0.02, 0.02);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    
     // vien tu duoi doc 
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(6.28,1.58,0.9);
    glScalef(0.01, 0.02, 0.6);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    
    // vien tu duoi ben trai
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0.2,1.58,2.4);
    glScalef(0.01, 0.02, 1.5);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    
     // vien tu trong ben trai
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(-1.3,1.58,0.2);
    glScalef(0.01, 0.02, 2.2);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    
    // vien tu duoi day ben trai
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0.2,-0.2,0.2);
    glScalef(0.01, 0.02, 2.2);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    
    // vien tu tren
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0.2,3.0,2.4);
    glScalef(2.03, 0.02, 0.02);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    // vien tu tren
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0.2,4.8,2.4);
    glScalef(2.03, 0.02, 0.02);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    // vien tu duoi day
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0.2,-0.2,2.4);
    glScalef(2.03, 0.02, 0.02);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    
     // vien tu duoi doc 
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(6.3,-0.2,2.4);
    glScalef(0.01, 0.6, 0.02);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    
    // vien tu duoi doc ben trai
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0.2,-0.2,2.4);
    glScalef(0.01, 0.6, 0.02);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    
     // vien tu duoi doc ben trai
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0.2,-0.2,6.8);
    glScalef(0.01, 0.6, 0.02);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    
    // vien tu ngang duoi day ben trai
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(-1.3,-0.2,6.8);
    glScalef(0.5, 0.01, 0.02);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    
    // vien tu ngang tren day ben trai
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(-1.3,1.55,6.8);
    glScalef(0.5, 0.01, 0.02);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    
     // vien tu doc day ben trai
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(-1.3,-0.2,6.8);
    glScalef(0.01, 0.6, 0.01);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    
    // vien tu tren doc ben trai
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0.2,3.0,2.4);
    glScalef(0.01, 0.6, 0.02);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    
    // vien tu ngang tren ben trai
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0.2,3.0,1.8);
    glScalef(0.01, 0.01, 1.7);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    
    
    
    // vien tu ngang tren ben trai
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0.2,4.8,1.8);
    glScalef(0.01, 0.01, 1.7);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    
    // vien tu ngang tren  ben trai
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(-1.3,4.8,6.8);
    glScalef(0.5, 0.01, 0.02);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
     // vien tu ngang tren  ben trai
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(-1.3,3.0,6.8);
    glScalef(0.5, 0.01, 0.02);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    
     // vien tu tren doc ben trai
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(-1.3,3.0,6.8);
    glScalef(0.01, 0.6, 0.01);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    
    // vien tu tren doc ben trai
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0.2,3.0,6.8);
    glScalef(0.01, 0.6, 0.01);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    
    // vien tu tren doc ben trai
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0.2,3.0,2.4);
    glScalef(0.01, 0.6, 0.02);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    
    // vien tu tren doc 
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(6.3,3.0,2.4);
    glScalef(0.01, 0.6, 0.02);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
}





void drawFlowerVase() {
    //hop xanh
    glPushMatrix();
    glTranslatef(5,1.2,9.3);
    glScalef(0.07, 0.1, 0.07);
    drawCube1(0,0,1,  0,0,0.5);
    glPopMatrix();
    // hop trang
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(5,1.5,9.3);
    glScalef(0.07, 0.03, 0.07);
    drawCube1(1, 1, 1,  1,1,1);
    glPopMatrix();
     // hop xanh
    glPushMatrix();
    glTranslatef(5.6,1.2,10);
    glScalef(0.07, 0.1, 0.07);
    drawCube1(0,0,1,  0,0,0.5);
    glPopMatrix();
    // hop trang
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(5.6,1.5,10);
    glScalef(0.07, 0.03, 0.07);
    drawCube1(1, 1, 1,  1,1,1);
    glPopMatrix();
     // hop xanh
    glPushMatrix();
    glTranslatef(5,1.2,10.6);
    glScalef(0.07, 0.1, 0.07);
    drawCube1(0,0,1,  0,0,0.5);
    glPopMatrix();
    // hop trang
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(5,1.5,10.6);
    glScalef(0.07, 0.03, 0.07);
    drawCube1(1, 1, 1,  1,1,1);
    glPopMatrix();
     // hop xanh
    glPushMatrix();
    glTranslatef(4.3,1.2,10);
    glScalef(0.07, 0.1, 0.07);
    drawCube1(0,0,1,  0,0,0.5);
    glPopMatrix();
    // hop trang
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(4.3,1.5,10);
    glScalef(0.07, 0.03, 0.07);
    drawCube1(1, 1, 1,  1,1,1);
    glPopMatrix();
   
   //chau
    glPushMatrix();
    glTranslatef(-1.0, 0.3,7.5);
    glScalef(0.1, 0.25, 0.1);
    drawSphere(0.5, 0.5, 0.5, 0.5,0.2,0,  50);
    glPopMatrix();
    
    
}


void cabinet() {

	// cabinet tren
	glPushMatrix();
  	glTranslatef(0.2, 3.0, 0.0);
  	glScalef(2.05, 0.6, 0.8);
  	drawCube1(0.5, 0.5, 0.5, 0.5,0.2,0, 50); // Draw the chair seat with red material
  	glPopMatrix();
  
  
  
  	 // thanh tu tren ben trai
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0.1,3.0,3.4);
    glScalef(0.04, 0.6, 0.04);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix();
    // thanh tu tren ben trai
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0.1,3.0,4.6);
    glScalef(0.04, 0.6, 0.04);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix();
    // thanh tu tren ben trai
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0.1,3.0,5.8);
    glScalef(0.04, 0.6, 0.04);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix();
    
    //nut tu doc tren 
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(0.2,3.5,3.0);
    glScalef(0.01, 0.2, 0.05);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix(); 
    //nut tu doc tren 
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(0.2,3.5,4.3);
    glScalef(0.01, 0.2, 0.05);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix(); 
    //nut tu doc tren 
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(0.2,3.5,5.4);
    glScalef(0.01, 0.2, 0.05);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix(); 
    //nut tu doc tren 
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(0.2,3.5,6.5);
    glScalef(0.01, 0.2, 0.05);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix(); 
    
    
    // bep ga
    glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(2.5,1.6,1.3);
    glScalef(0.6, 0.02, 0.3);
    drawCube1(0,0,0,  0,0,0);
    glPopMatrix();
    
  	// den tren bep
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(2.9,1.5,1.5);
    glScalef(0.07, 0.07, 0.07);
    drawTrapezoid(1,0.5,0,  1,1,1);
    glPopMatrix();
    // den tren bep
    glColor3f(1, 1, 1);
    glPushMatrix();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
    glTranslatef(3.8,1.5,1.5);
    glScalef(0.07, 0.07, 0.07);
    drawTrapezoid(1,0.5,0,  1,1,1);
    glPopMatrix();

	// den tu 
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0.5,2.8,1.5);
    glScalef(1.8, 0.03, 0.01);
    drawTrapezoid(1,1,1,  1,1,1);
    glPopMatrix();
    
    // den tu ben trai
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(-1.2,2.8,1);
    glScalef(0.01, 0.03, 1.8);
    drawTrapezoid(1,1,1,  1,1,1);
    glPopMatrix();
}

void cabinet2() {
	
	//cabinet duoi ben trai
	glPushMatrix();
 	 glTranslatef(0.2, -0.2, 0.9);
  	glScalef(-0.5, 0.6, 1.97);
  	drawCube1(0.5, 0.5, 0.5, 0.5,0.2,0, 50); // Draw the chair seat with red material
 	 glPopMatrix();
  
  

  	// voi nuoc dung
    glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(-1.2,1.35,5);
    glScalef(0.02, 0.3, 0.02);
    drawCube1(1,1,1,  0.5,0.5,0.5);
    glPopMatrix();
    
    	// voi nuoc ngang
    glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(-1.2,2.2,5);
    glScalef(0.2, 0.02, 0.02);
    drawCube1(1,1,1,  0.5,0.5,0.5);
    glPopMatrix();
 	 
 	// chan voi nuoc
    glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(-1.2,1.5,5);
    glScalef(0.07, 0.07, 0.07);
    drawCube1(1,1,1,  0.5,0.5,0.5);
    glPopMatrix();
    
    // lavabo
    glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(-0.8,1.5,4.5);
    glScalef(0.3, 0.15, 0.6);
    drawCube1(1,1,1,  0.5,0.5,0.5);
    glPopMatrix();
    
   
    
 	  // thanh tu doc
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(1.5,-0.2,2.4);
    glScalef(0.06, 0.6, 0.02);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix();
    // thanh tu doc
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(2.9,-0.2,2.4);
    glScalef(0.06, 0.6, 0.02);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix();
    // thanh tu doc
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(4.2,-0.2,2.4);
    glScalef(0.06, 0.6, 0.02);
   drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix();
    // thanh tu doc
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(5.5,-0.2,2.4);
    glScalef(0.06, 0.6, 0.02);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix();
     // thanh tu ngang
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(0.3,0.8,2.4);
    glScalef(1.8, 0.03, 0.02);
    drawCube1(0.5, 0.5, 0.5,  0.3,0.3,0.3);
    glPopMatrix();
}

void cabinet3() {
	
	//cabinet tren ben trai
	glPushMatrix();
 	 glTranslatef(0.2, 3.0, 1.4);
  	glScalef(-0.5, 0.6, 1.8);
  	drawCube1(0.5, 0.5, 0.5, 0.5,0.2,0, 50); // Draw the chair seat with red material
 	 glPopMatrix();
  
  

  
 	 
 	 // thanh tu doc
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(1.5,3.0,2.4);
    glScalef(0.06, 0.6, 0.02);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix();
    // thanh tu doc
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(2.9,3.0,2.4);
    glScalef(0.06, 0.6, 0.02);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix();
    // thanh tu doc
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(4.2,3.0,2.4);
    glScalef(0.06, 0.6, 0.02);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix();
    // thanh tu doc
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(5.5,3.0,2.4);
    glScalef(0.06, 0.6, 0.02);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix();
}
void fridge() {


  // tu lanh
  glPushMatrix();
  glTranslatef(6.3, -0.2, 0.0);
  glScalef(0.6, 1.3, 0.8);
  drawCube1(0.5, 0.5, 0.5, 0.3, 0.3, 0.3, 50); // Draw the chair backrest with red material
  glPopMatrix();
  
   // thanh tu lanh ngang
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(6.3,2.1,2.4);
    glScalef(0.6, 0.03, 0.02);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    // thanh tu lanh doc
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(6.3,1.7,2.4);
    glScalef(0.06, 0.3, 0.02);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
   
}

void lamp()
{
    //lamp base
    glPushMatrix();
    glTranslatef(.6,0.5,8.95);
    glScalef(0.07, 0.02, 0.07);
    drawCube1(0,0,1,  0,0,0.5);
    glPopMatrix();
    
    //lamp stand
    glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(.7,0.35,9.05);
    glScalef(0.01, 0.2, 0.01);
    drawCube1(1,0,0,  0.5,0.0,0.0);
    glPopMatrix();
        
    //lamp shade
    glColor3f(0.000, 0.000, 0.545);
    glPushMatrix();
    glTranslatef(.6,0.9,8.9);
    glScalef(0.08, 0.09, 0.08);
    drawTrapezoid(0.000, 0.000, 0.545,  0,0,0.2725);
    //drawCube1(0.000, 0.000, 0.545,  0,0,0.2725);
    glPopMatrix();
    
    
}

void drawPyramid() {
	
	// thanh quat tran ngang
    glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(1.4,4.6,8.5);
    glScalef(0.9, 0.04, 0.12);
    drawCube1(0.5,0.2,0,  0.25,0.1,0, 50);
    glPopMatrix();   
	
	//thanh quat tran doc
	 glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(2.6,4.6,7.3);
    glScalef(0.12, 0.04, 0.9);
    drawCube1(0.5,0.2,0,  0.25,0.1,0, 50);
    glPopMatrix();      
	
	//cot quat tran 
	glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(2.7,4.5,8.5);
    glScalef(0.03, 0.2, 0.03);
    drawCube1(0.5,0.2,0,  0.25,0.1,0);
    glPopMatrix();   
	
	//tru quat tran
    glPushMatrix();
    glTranslatef(2.7, 4.7,8.5);
    glScalef(0.1, 0.067, 0.1);
    drawSphere(0, 0, 0, 0,0,0,  50);
    glPopMatrix();     
    
     // cong tac quat
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(-1.3,1.7,7.4);
    glScalef(0.02, 0.2, 0.05);
    drawCube1(0.5, 0.5, 0.5, 0.3, 0.3, 0.3, 50);
    glPopMatrix();
    
    // cham cong tac
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(-1.2,2.1,7.5);
    glScalef(0.02, 0.04, 0.02);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
    // cham cong tac
    glColor3f(1, 1, 1);
    glPushMatrix();
    glTranslatef(-1.2,1.9,7.5);
    glScalef(0.02, 0.04, 0.02);
    drawCube1(0, 0, 0,  0,0,0);
    glPopMatrix();
}

void clock()
{
    //Clock ************************************************************
        
        //clock body
        glColor3f(0.545, 0.271, 0.075);
        glPushMatrix();
        glTranslatef(-1.3,2.5,8.0);
        //glRotatef(22, 0,0,1);
        glScalef(0.03, 0.25, 0.2);
        drawCube1(0.545,0.271,0.075,  0.271,0.1335,0.0375,  50);
        glPopMatrix();
        
        //clock body white
        glPushMatrix();
        glTranslatef(-1.2,2.58,8.05);
        //glRotatef(22, 0,0,1);
        glScalef(0.01, 0.2, 0.17);
        drawCube1(1.000,0.894,0.710,  1.000,0.894,0.710);
        glPopMatrix();
        
        //clock hour handle
        glPushMatrix();
        glTranslatef(-1.1,2.85,8.3);
        glRotatef(45, 1,0,0);
        glScalef(0.0001, 0.01, 0.04);
        drawCube1(0,0,0,  0,0,0);
        glPopMatrix();
        
       //clock minute handle
        glPushMatrix();
        glTranslatef(-1.1,3.05,8.3);
        glRotatef(90, 1,0,0);
        glScalef(0.0001, 0.012, 0.08);
    drawCube1(0,0,0,  0,0,0);
        glPopMatrix();
        
       

        
        
  
}

void lightBulb1()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 1.000, 0.843, 0.000, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {1.000, 1,1, 0.0};
    
    glPushMatrix();
    glTranslatef (5, 5, 8);
    glScalef(0.2, 0.2, 0.2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    
    if(switchOne == true){
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }else{
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}

void lightBulb2()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 1.000, 0.843, 0.000, 1.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {1,1,1, 1.0};
    
    glPushMatrix();
    glTranslatef (0,5,8);
    glScalef(0.2, 0.2, 0.2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    if(switchTwo == true){
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }else{
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}

void lightBulb3()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 1.000, 0.843, 0.000, 1.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {1,1,1, 1.0};
    
    glPushMatrix();
    glTranslatef (0.7, 1.5, 9.0);
    glScalef(0.2, 0.2, 0.2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    if(switchLamp == true){
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }else{
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}


void lightOne()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 5.0, 5.0, 8.0, 1.0 }; //5 5 10
    
    //glEnable( GL_LIGHT0);
    
    if(amb1 == true){glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);}
    else{glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);}
    
    if(diff1 == true){glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);}
    else{glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);}
    
    if(spec1 == true){glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);}
    else{glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);}
   
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
}

void lightTwo()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 0.9, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 5.0, 8.0, 1.0 };
    
    //glEnable( GL_LIGHT1);
    
    if(amb2 == true){glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);}
    else{glLightfv( GL_LIGHT1, GL_AMBIENT, no_light);}
    
    if(diff2 == true){glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);}
    else{glLightfv( GL_LIGHT1, GL_DIFFUSE, no_light);}
    
    if(spec2 == true){glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);}
    else{glLightfv( GL_LIGHT1, GL_SPECULAR, no_light);}
    
    glLightfv( GL_LIGHT1, GL_POSITION, light_position);
    glPopMatrix();
}

void lampLight()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.7, 1.5, 9.0, 1.0 };  //0.7, 4.5, 9.0
    
    //glEnable( GL_LIGHT2);
    
    if(amb3 == true){glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);}
    else{glLightfv( GL_LIGHT2, GL_AMBIENT, no_light);}
    
    if(diff3 == true){glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse);}
    else{glLightfv( GL_LIGHT2, GL_DIFFUSE, no_light);}
    
    if(spec3 == true){glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);}
    else{glLightfv( GL_LIGHT2, GL_SPECULAR, no_light);}

    glLightfv( GL_LIGHT2, GL_POSITION, light_position);
    GLfloat spot_direction[] = { 0.3, -1, -0.8 };
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT2, GL_SPOT_CUTOFF, 35.0);
    glPopMatrix();
}



void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(60,1,1,100);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ,  refX,refY,refZ,  0,1,0); //7,2,15, 0,0,0, 0,1,0
    
    glEnable(GL_LIGHTING);
    lightOne();
    lightTwo();
    lampLight();
    room();
    //hien thi ham o day
   	sphericalObject();
    window();
    cabinet();
    fridge();
    cabinet2();
    cabinet3();
    clock();
    drawChair();
    drawChair2();
    drawChair3();
    drawChair4();
    drawFlowerVase();
    drawPyramid();
    lightBulb1();
    lightBulb2();
    //lightBulb3();
    glDisable(GL_LIGHTING);
    
    glFlush();
    glutSwapBuffers();
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
        case 'w': // move eye point upwards along Y axis
            eyeY+=1.0;
            break;
        case 's': // move eye point downwards along Y axis
            eyeY-=1.0;
            break;
        case 'a': // move eye point left along X axis
            eyeX-=1.0;
            break;
        case 'd': // move eye point right along X axis
            eyeX+=1.0;
            break;
        case 'o':  //zoom out
            eyeZ+=1;
            break;
        case 'i': //zoom in
            eyeZ-=1;
            break;
        case 'q': //back to default eye point and ref point
                eyeX=7.0; eyeY=2.0; eyeZ=15.0;
                refX=0.0; refY=0.0; refZ=0.0;
            break;
        case 'j': // move ref point upwards along Y axis
            refY+=1.0;
            break;
        case 'n': // move ref point downwards along Y axis
            refY-=1.0;
            break;
        case 'b': // move ref point left along X axis
            refX-=1.0;
            break;
        case 'm': // move eye point right along X axis
            refX+=1.0;
            break;
        case 'k':  //move ref point away from screen/ along z axis
            refZ+=1;
            break;
        case 'l': //move ref point towards screen/ along z axis
            refZ-=1;
            break;
        case '1': //to turn on and off light one
            if(switchOne == false)
            {
                switchOne = true; amb1=true; diff1=true; spec1=true;
                glEnable( GL_LIGHT0); break;
            }
            else if(switchOne == true)
            {
                switchOne = false; amb1=false; diff1=false; spec1=false; glDisable( GL_LIGHT0); break;
            }
        case '2': //to turn on and off light two
            if(switchTwo == false)
            {
                switchTwo = true; amb2=true; diff2=true; spec2=true;
                glEnable( GL_LIGHT1); break;
            }
            else if(switchTwo == true)
            {
                switchTwo = false; amb2=false; diff2=false; spec2=false;
                glDisable( GL_LIGHT1); break;
            }
        case '3': //to turn on and off light one
            if(switchLamp == false)
            {
                switchLamp = true; amb3=true; diff3=true; spec3=true;
                glEnable( GL_LIGHT2); break;
            }
            else if(switchLamp == true)
            {
                switchLamp = false; amb3=false; diff3=false; spec3=false;
                glDisable( GL_LIGHT2); break;
            }
        case'4': //turn on/off ambient light 1
            if(amb1 == false) {amb1=true; break;}
            else{amb1=false; break;}
        case'5':
            if(diff1 == false) {diff1=true; break;}
            else{diff1=false; break;}
        case'6':
            if(spec1 == false) {spec1=true; break;}
            else{spec1=false; break;}
        case'7': //turn on/off ambient light 2
            if(amb2 == false) {amb2=true; break;}
            else{amb2=false; break;}
        case'8':
            if(diff2 == false) {diff2=true; break;}
            else{diff2=false; break;}
        case'9':
            if(spec2 == false) {spec2=true; break;}
            else{spec2=false; break;}
        case'e': //turn on/off ambient lamp light
            if(amb3 == false) {amb3=true; break;}
            else{amb3=false; break;}
        case'r':
            if(diff3 == false) {diff3=true; break;}
            else{diff3=false; break;}
        case't':
            if(spec3 == false) {spec3=true; break;}
            else{spec3=false; break;}
        case 27:    // Escape key
            exit(1);
    }
    
    glutPostRedisplay();
}


void animate()
{
    if(redFlag == true)
    {
        theta+=2;
        z-=0.02; //0.016667;
        if(theta >= 196 && theta <= 210)
        {
            y = 1.44;
        }
        else if(theta >= 180 && theta <= 194)
        {
            y = 1.42;
        }
        else if(theta >= 180 && theta <= 194)
        {
            y = 1.4;
        }
        else if(theta >= 164 && theta <= 178)
        {
            y = 1.42;
        }
        
        if(theta == 210)
        {
            redFlag = false;
        }
    }
    else if(redFlag == false)
    {
        theta-=2;
        z+=0.02;//0.016667;
        
        if(theta >= 196 && theta <= 210)
        {
            y = 1.44;
        }
        else if(theta >= 180 && theta <= 194)
        {
            y = 1.42;
        }
        else if(theta >= 180 && theta <= 194)
        {
            y = 1.4;
        }
        else if(theta >= 164 && theta <= 178)
        {
            y = 1.42;
        }
        
        if(theta == 150)
        {
            redFlag = true;
        }
    }
    
    glutPostRedisplay();

}

void fullScreen(int w, int h)
{
    //Prevent a divide by zero, when window is too short;you cant make a window of zero width.
    if (h == 0)
        h = 1;
    float ratio = (GLfloat)w / (GLfloat)h;         //Calculate aspect ratio of the window

    //Set the perspective coordinate system
    glMatrixMode(GL_PROJECTION);                   //Use the Projection Matrix
    glLoadIdentity();                              //Reset Matrix

    glViewport(0, 0, w, h);                        //Set the viewport to be the entire window
    gluPerspective(60, ratio, 1, 500);             //Set the correct perspective.
    //glFrustum(-2.5,2.5,-2.5,2.5, ratio, 200);
    glMatrixMode(GL_MODELVIEW);                    //Get Back to the Modelview
}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    
    std::cout<<"di chuyen mat:"<< std::endl;
    std::cout<<"w: len cao"<<std::endl;
    std::cout<<"s: xuong thap"<<std::endl;
    std::cout<<"a: sang trai"<<std::endl;
    std::cout<<"d: sang phai"<<std::endl;
    std::cout<<"i: phong to"<<std::endl;
    std::cout<<"o: thu nho"<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"di chuyen camera:"<< std::endl;
    std::cout<<"j: len cao"<<std::endl;
    std::cout<<"n: xuong thap"<<std::endl;
    std::cout<<"b: sang trai"<<std::endl;
    std::cout<<"m: sang phai"<<std::endl;
    std::cout<<"l: tien lai gan"<<std::endl;
    std::cout<<"k: di chuyen ra xa"<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"nhan q de di chuyen ve vi tri mac dinh"<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"anh sang:      "<<std::endl;
    std::cout<<"den ben phai      "<<std::endl;
    std::cout<<"1: bat/tat den 1    "<<std::endl;
    std::cout<<"4: bat/tat den xung quanh 1     "<<std::endl;
    std::cout<<"5: bat/tat den khuech tan 1     "<<std::endl;
    std::cout<<"6: bat/tat den phan chieu 1      "<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"den ben trai "<<std::endl;
    std::cout<<"2: bat/tat den 2     "<<std::endl;
    std::cout<<"7: bat/tat den xung quanh 2    "<<std::endl;
    std::cout<<"8: bat/tat den khuech tan 2     "<<std::endl;
    std::cout<<"9: bat/tat den phan chieu 2      "<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"den chieu diem(spot light)" <<std::endl;
    std::cout<<"3: bat/tat     "<<std::endl;
    std::cout<<"e: bat/tat den xung quanh    "<<std::endl;
    std::cout<<"r: bat/tat den khuech tan      "<<std::endl;
    std::cout<<"t: bat/tat den bong den     "<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"____________________"<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"      "<<std::endl;
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Thiet ke phong bep");

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
 
    glutReshapeFunc(fullScreen);
    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboardFunc);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}

