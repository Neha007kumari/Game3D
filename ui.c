
#include "main.h"

extern EYE eye;
extern MONSTER me[];
extern MYBODY avatar;

GLfloat length(VEC *v)
{
   GLfloat vx,vy,vz;

   vx = v->x;
   vy = v->y;
   vz = v->z;
   return sqrt(vx*vx + vy*vy + vz*vz);
}
void setdirection(VEC *v)
{
   v->x = cos(v->phi)*cos(v->theta);
   v->z = cos(v->phi)*sin(v->theta);
   v->y = sin(v->phi);
}
void setangles(VEC *v)
{
   GLfloat r;

   r = length(v);
   if(r > 0.0)
     v->theta = acosf(v->x/r);
}
void turnup(GLfloat delta)
{
  eye.velocity.phi += delta;
  setdirection(&eye.velocity);
  eye.facing.phi += delta;
  setdirection(&eye.facing); 
/*
    avatar.velocity.phi +=delta;
    setdirection(&avatar.velocity);
    avatar.facing.phi +=delta;
    setdirection(&avatar.facing);
  */
}
void turndown(GLfloat delta)
{
  eye.velocity.phi -= delta;
  setdirection(&eye.velocity);
  eye.facing.phi -= delta;
  setdirection(&eye.facing);
   
 /*   avatar.velocity.phi -=delta;
    setdirection(&avatar.velocity);
    avatar.facing.phi -=delta;
    setdirection(&avatar.facing);
*/
}
void turnleft(GLfloat delta)
{
  eye.velocity.theta -= delta;
  setdirection(&eye.velocity);
  eye.facing.theta -= delta;
  setdirection(&eye.facing);
   

}
void turnright(GLfloat delta)
{
  eye.velocity.theta += delta;
  setdirection(&eye.velocity);
  eye.facing.theta += delta;
  setdirection(&eye.facing);
    
   
}

void turnleft_avatar(GLfloat delta)
{
   // float dx = -sin(DEG2RAD(avatar.heading));
   // float dz = -cos(DEG2RAD(avatar.heading));
    
    
    avatar.velocity.theta -=delta;
    setdirection(&avatar.velocity);
    avatar.facing.theta -=delta;
    setdirection(&avatar.facing);
    
    avatar.z -= delta;
    avatar.x -= delta;
    

}

void turnright_avatar(GLfloat delta)
{
    avatar.velocity.theta +=delta;
    setdirection(&avatar.velocity);
    avatar.facing.theta +=delta;
    setdirection(&avatar.facing);
}

void keyboard(unsigned char c, int x, int y)
{
   int i;

   switch(c){
     case 'w':
           avatar.speed += POWER; break;
          // eye.speed += POWER;
       break;
     case 's':
           avatar.speed = 0; break;
          // eye.speed = 0;
       break;
       case 'a':
           turnleft_avatar(0.1); break;
       case 'd':
           turnright_avatar(0.1); break;
           
     case 'u':
           eye.speed += POWER; break;
     case 'j':
           eye.speed = 0; break;
           
           
     case 'm':
       for(i=1;i<NMON;i++)
         me[i].moving = 1;
       break;
     case 'M':
       for(i=1;i<NMON;i++)
         me[i].moving = 0;
       break;
     case 27:
       exit(0);
   }
   glutPostRedisplay();
}
void specialkeyboard(int kno, int x, int y)
{
   switch(kno){
     case GLUT_KEY_UP:
       turnup(0.1);
       break;
     case GLUT_KEY_DOWN:
       turndown(0.1);
       break;
     case GLUT_KEY_RIGHT:
       turnright(0.1);
       break;
     case GLUT_KEY_LEFT:
       turnleft(0.1);
       break;
    
   }
   glutPostRedisplay();
}
