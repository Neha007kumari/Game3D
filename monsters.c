
#include "main.h"

GLuint bodytex;
GLuint mazetex;
GLuint avatartex;

extern MONSTER me[];
extern MYBODY avatar;

void init_avatar()
{
   avatar.x       = 5.0;
   avatar.y       = 0.01;
   avatar.z       = 8.0;
   avatar.heading = 1;
   avatar.bodylen = 0.10;
   avatar.bodywid = 0.10;
   avatar.bodyhgt = 0.10;
   avatar.speed   = 0;
   avatar.moving  = 1;

   avatar.facing.theta = DEG2RAD(270.0);
   avatar.facing.phi   = 0.0;
   setdirection(&avatar.facing);

   avatar.velocity.theta = DEG2RAD(270.0);
   avatar.velocity.phi   = 0.0;
   setdirection(&avatar.velocity);
}

void init_build_avatar()
{
  memset(&avatar,0,sizeof(MYBODY));
  init_avatar();
}

void draw_avatar(MYBODY *p)
{
  glPushMatrix();
  glTranslatef(p->x, p->y, p->z);
  glRotatef(p->heading, 0, 1, 0);
        
  GLfloat e,h,r,z;

  r = p->bodywid;
  e = 0.02;
  h = p->bodyhgt;
  z = p->bodylen;
  glBindTexture(GL_TEXTURE_2D, avatartex);
  glBegin(GL_QUADS);
    glTexCoord2f(0.0,  0.0); glVertex3f(-r, e,-z);
    glTexCoord2f(0.0,  1.0); glVertex3f(-r, e, z);
    glTexCoord2f(1.0,  1.0); glVertex3f( r, e, z);
    glTexCoord2f(1.0,  0.0); glVertex3f( r, e,-z);

    glTexCoord2f(0.0,  0.0); glVertex3f( r, h,-z);
    glTexCoord2f(0.0,  1.0); glVertex3f( r, h, z);
    glTexCoord2f(1.0,  1.0); glVertex3f( r, e, z);
    glTexCoord2f(1.0,  0.0); glVertex3f( r, e,-z);

    glTexCoord2f(1.0,  1.0); glVertex3f(-r, h, z);
    glTexCoord2f(1.0,  0.0); glVertex3f(-r, h,-z);
    glTexCoord2f(0.0,  0.0); glVertex3f(-r, e,-z);
    glTexCoord2f(0.0,  1.0); glVertex3f(-r, e, z);

    glTexCoord2f(1.0,  1.0); glVertex3f(-r, h,-z);
    glTexCoord2f(1.0,  0.0); glVertex3f(-r, h, z);
    glTexCoord2f(0.0,  0.0); glVertex3f( r, h, z);
    glTexCoord2f(0.0,  1.0); glVertex3f( r, h,-z);

    glTexCoord2f(1.0,  1.0); glVertex3f(-r, e,-z);
    glTexCoord2f(1.0,  0.0); glVertex3f(-r, h,-z);
    glTexCoord2f(0.0,  0.0); glVertex3f( r, h,-z);
    glTexCoord2f(0.0,  1.0); glVertex3f( r, e,-z);

    glTexCoord2f(1.0,  1.0); glVertex3f(-r, e, z);
    glTexCoord2f(1.0,  0.0); glVertex3f(-r, h, z);
    glTexCoord2f(0.0,  0.0); glVertex3f( r, h, z);
    glTexCoord2f(0.0,  1.0); glVertex3f( r, e, z);
  glEnd();


  glPopMatrix();
}

void initone(int k)
{
  me[k].x       = 2.50 * drand48();
  me[k].y       = 0.0;
  me[k].z       = 2.50 * drand48();
  me[k].heading = 360.0 * drand48();
  me[k].bodylen = 0.10 + 0.10 * drand48();
  me[k].bodywid = 0.10 + 0.10 * drand48();
  me[k].bodyhgt = 0.10 + 0.90 * drand48();
  me[k].speed   = 0.01 + 0.01 * drand48();
  me[k].moving  = 1;
}

void initall()
{
  int i;

  memset(me,0,NMON*sizeof(MONSTER));
  for(i=1;i<NMON;i++)
    initone(i);
}

void drawbody(MONSTER *p)
{
  GLfloat e,h,r,z;

  r = p->bodywid;
  e = 0.02;
  h = p->bodyhgt;
  z = p->bodylen;
  glBindTexture(GL_TEXTURE_2D, bodytex);
  glBegin(GL_QUADS);
    glTexCoord2f(0.0,  0.0); glVertex3f(-r, e,-z);
    glTexCoord2f(0.0,  1.0); glVertex3f(-r, e, z);
    glTexCoord2f(1.0,  1.0); glVertex3f( r, e, z);
    glTexCoord2f(1.0,  0.0); glVertex3f( r, e,-z);

    glTexCoord2f(0.0,  0.0); glVertex3f( r, h,-z);
    glTexCoord2f(0.0,  1.0); glVertex3f( r, h, z);
    glTexCoord2f(1.0,  1.0); glVertex3f( r, e, z);
    glTexCoord2f(1.0,  0.0); glVertex3f( r, e,-z);

    glTexCoord2f(1.0,  1.0); glVertex3f(-r, h, z);
    glTexCoord2f(1.0,  0.0); glVertex3f(-r, h,-z);
    glTexCoord2f(0.0,  0.0); glVertex3f(-r, e,-z);
    glTexCoord2f(0.0,  1.0); glVertex3f(-r, e, z);

    glTexCoord2f(1.0,  1.0); glVertex3f(-r, h,-z);
    glTexCoord2f(1.0,  0.0); glVertex3f(-r, h, z);
    glTexCoord2f(0.0,  0.0); glVertex3f( r, h, z);
    glTexCoord2f(0.0,  1.0); glVertex3f( r, h,-z);

    glTexCoord2f(1.0,  1.0); glVertex3f(-r, e,-z);
    glTexCoord2f(1.0,  0.0); glVertex3f(-r, h,-z);
    glTexCoord2f(0.0,  0.0); glVertex3f( r, h,-z);
    glTexCoord2f(0.0,  1.0); glVertex3f( r, e,-z);

    glTexCoord2f(1.0,  1.0); glVertex3f(-r, e, z);
    glTexCoord2f(1.0,  0.0); glVertex3f(-r, h, z);
    glTexCoord2f(0.0,  0.0); glVertex3f( r, h, z);
    glTexCoord2f(0.0,  1.0); glVertex3f( r, e, z);
  glEnd();
}

void drawme(MONSTER *p)
{
  glPushMatrix();
    glTranslatef(p->x, p->y, p->z);
    glRotatef(p->heading, 0, 1, 0);
    drawbody(p);
  glPopMatrix();
}

void movemonsters()
{
  int i;
    
    for(i=0;i<NMON;i++)
    {
        me[i].x += me[i].speed * sin(DEG2RAD(me[i].heading));
        me[i].z += me[i].speed * cos(DEG2RAD(me[i].heading));
        me[i].heading +=  (drand48() - 0.1);
        
    }

  glutPostRedisplay();
}
