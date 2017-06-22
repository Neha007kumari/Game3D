
#include "main.h"

#define  FLOORFILE     "PPM/metal5.ppm"
#define  MAZEFILE      "PPM/greenwall.ppm" 
#define  BODYFILE      "PPM/metal1.ppm"
#define  MYBODYFILE    "tank.ppm"

extern GLuint floortex;
extern GLuint bodytex;
extern GLuint avatartex;
extern GLuint mazetex;

EYE eye;
MONSTER me[NMON];
MYBODY avatar;
int **map;

int main(int argc, char *argv[])
{
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(800,800);
   glutInitWindowPosition(80,60);
   glutCreateWindow("Terre Haute");

   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(specialkeyboard);
   //glutIdleFunc(animate);
   glutIdleFunc(dostuff);
   //glutIdleFunc(dostuff_avatar);

   init(argv[1]);

   glutMainLoop();
}

void init(char *fname)
{

  srand48(getpid());

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_DEPTH_TEST); 
  glEnable(GL_TEXTURE_2D);
  map = readmap(MAPFILE);
    eye.x =  5.0;//0.0;
    eye.y =  0.01;//0.0;
    eye.z =  8.0;//2.0;

  eye.facing.theta = DEG2RAD(270.0);
  eye.facing.phi   = 0.0;
  setdirection(&eye.facing);

  eye.velocity.theta = DEG2RAD(270.0);
  eye.velocity.phi   = 0.0;
  setdirection(&eye.velocity);
  floortex  = readppm(FLOORFILE,1);
  bodytex   = readppm(BODYFILE ,1);
  avatartex = readppm(MYBODYFILE ,1);
  mazetex   = readppm(MAZEFILE,1);
  
  initbuild();
  initall();
  init_build_avatar();
}

void display()
{
   int i,j;
   GLfloat dx,dy,dz;
    
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, 4.0/3.0, 0.001, 5000.0);
    
   /****************************************************************/
   
    gluLookAt(eye.x, eye.y + HGT, eye.z,
             eye.x+eye.facing.x, eye.y + HGT + eye.facing.y, eye.z+eye.facing.z,
             0.0, 1.0, 0.0);
   /*
    avatar.x = eye.x;
    avatar.y = eye.y;
    avatar.z = eye.z;
    avatar.facing.x = eye.facing.x;
    avatar.facing.y = eye.facing.y;
    avatar.facing.z = eye.facing.z;

    dx = -sin(DEG2RAD(me[0].heading));
    dz = -cos(DEG2RAD(me[0].heading));

   
   /*
    gluLookAt(avatar.x, 
  	      avatar.y + HGT, 
	      avatar.z ,
              avatar.x + avatar.facing.x, 
	      avatar.y + HGT + avatar.facing.y, 
	      avatar.z + avatar.facing.z,
              0.0, 1.0, 0.0);
   
   /****************************************************************/
   
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
   drawfloor();
   drawblock();
   draw_avatar(&avatar);

   for(i=0;i<NMON;i++)
     drawme(&me[i]);

   glPopMatrix();
   glutSwapBuffers();
}

void animate()
{
  GLfloat tx,ty,tz;

  movemonsters();
  if(eye.speed > 0){
    eye.speed *= FRICTION;
    tx = eye.x + eye.speed * eye.velocity.x;
    ty = eye.y + eye.speed * eye.velocity.y;
    tz = eye.z + eye.speed * eye.velocity.z;
    eye.x = tx;
    eye.y = ty;
    eye.z = tz;
  }
    
   if(avatar.speed > 0)
   {
       avatar.speed *= FRICTION;
       tx = avatar.x + avatar.speed * avatar.velocity.x;
       ty = avatar.y + avatar.speed * avatar.velocity.y;
       tz = avatar.z + avatar.speed * avatar.velocity.z;
       avatar.x = tx;
       avatar.y = ty;
       avatar.z = tz;
   }
}

int bouncing=0;


void dostuff_avatar()
{
    GLfloat tx,ty,tz;
    int i;
    //animate();
    if(bouncing){
        avatar.facing.theta += 0.1 * (drand48() - 0.5);
        avatar.facing.phi   += 0.1 * (drand48() - 0.5);
     
        //avatar.velocity.x = 0.05;
        //avatar.velocity.y = 0;
        //avatar.velocity.z = 0.05;
       	setdirection(&avatar.facing);
	
        if(bouncing > 0)
            --bouncing;
        glutPostRedisplay();
    } else {
        if(avatar.speed > 0){
            avatar.speed *= FRICTION;
            tx = avatar.x + avatar.speed * avatar.velocity.x;
            ty = avatar.y + avatar.speed * avatar.velocity.y;
            tz = avatar.z + avatar.speed * avatar.velocity.z;
               
            int cangoResult = cango(tx,tz);
            
	    if(cangoResult == 0)
            {
                avatar.x = tx;
                //avatar.y = ty;
                avatar.z = tz;
            }
            else
            {
                avatar.speed = 0;
                bouncing = 60;
            }
        }

      glutPostRedisplay();
    }
}


void dostuff()
{
    animate();
    dostuff_avatar();
    
    GLfloat tx,ty,tz;
    int i;
    
    if(bouncing){
        eye.facing.theta += 0.1 * (drand48() - 0.5);
        eye.facing.phi   += 0.1 * (drand48() - 0.5);
        setdirection(&eye.facing);
        
        if(bouncing > 0)
            --bouncing;
        glutPostRedisplay();
    } else {
        if(eye.speed > 0){
            eye.speed *= FRICTION;
            tx = eye.x + eye.speed * eye.velocity.x;
            ty = eye.y + eye.speed * eye.velocity.y;
            tz = eye.z + eye.speed * eye.velocity.z;
               
            int cangoResult = cango(tx,tz);
            
            if(cangoResult != 1)
            {
                eye.x = tx;
                eye.y = ty;
                eye.z = tz;
            }
            else
            {
                eye.speed = 0;
                bouncing = 60;
            }
        }
/*        
        for(i=1;i<NMON;i++){
            if(me[i].moving == 0)
           {
               me[i].facing.theta += 1.1 * (drand48() - 0.5);
               me[i].facing.phi   += 1.1 * (drand48() - 0.5);
               me[i].speed   += 0.10 * drand48();
               //me[i].x += 0.01 * drand48();
               me[i].z += 0.01 * drand48();
               setdirection(&me[i].facing);
               
               //me[i].moving = 1;
               if(me[i].moving >= 0 && me[i].moving <= 1 )
                   ++me[i].moving;

               glutPostRedisplay();
            }
        }
        
        for(i=1;i<NMON;i++){
            if(cango(me[i].x,me[i].z) == 1){
                me[i].moving = 0;
                me[i].speed = 0;
            }
        }
        
 */       
            glutPostRedisplay();
        
     }
}
