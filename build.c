
#include "main.h"

#define NB       256
#define MINHGT   1.0
#define MAXHGT   3.0

#define ZERO     0.01
#define ONE      0.99

GLfloat bhgt[NB];
int bctr;

GLuint floortex;
extern GLuint bodytex;
extern GLuint mazetex;
extern int MAPCOUNT;
extern int **map;

void drawfloor()
{
  glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, floortex);
    glBegin(GL_QUADS);
      glTexCoord2f(0.0, 0.0);
      glVertex3f(-15.0,  0.01, -15.0);
      glTexCoord2f(40.0,  0.0);
      glVertex3f( 15.0,  0.01, -15.0);
      glTexCoord2f(40.0, 40.0);
      glVertex3f( 15.0,  0.01,  15.0);
      glTexCoord2f( 0.0, 40.0);
      glVertex3f(-15.0,  0.01,  15.0);
    glEnd();
  glPopMatrix();
}

int cango(GLfloat x, GLfloat z)
{
    int ix,iz;
    
    ix = x;
    iz = z;
    
    //printf("cango %d %d \n",ix,iz);
    
    if(ix < 0) return 0;
    if(ix >= MAPCOUNT) return 0;
    if(iz < 0) return 0;
    if(iz >= MAPCOUNT) return 0;

    return map[ix][iz];
}

void initbuild()
{
    int i;
   
    for(i=0;i<NB;i++)
        bhgt[i] = MINHGT + (MAXHGT - MINHGT) * drand48();
}

void drawbuilding(GLfloat hgt, int towerflag)
{
    
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, mazetex);
    
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(ZERO,-ZERO,ZERO);
    glTexCoord2f(5.0, 0.0);
    glVertex3f(ONE ,-ZERO,ZERO);
    glTexCoord2f(5.0, 5.0);
    glVertex3f(ONE ,ONE ,ZERO);
    glTexCoord2f(0.0, 5.0);
    glVertex3f(ZERO,ONE ,ZERO);
    
    glTexCoord2f(0.0, 0.0);
    glVertex3f(ONE ,-ZERO,ZERO);
    glTexCoord2f(5.0, 0.0);
    glVertex3f(ONE ,-ZERO,ONE );
    glTexCoord2f(5.0, 5.0);
    glVertex3f(ONE ,ONE ,ONE );
    glTexCoord2f(0.0, 5.0);
    glVertex3f(ONE ,ONE ,ZERO);
    
    glTexCoord2f(0.0, 0.0);
    glVertex3f(ZERO,-ZERO,ONE );
    glTexCoord2f(5.0, 0.0);
    glVertex3f(ONE ,-ZERO,ONE );
    glTexCoord2f(5.0, 5.0);
    glVertex3f(ONE ,ONE ,ONE );
    glTexCoord2f(0.0, 5.0);
    glVertex3f(ZERO,ONE ,ONE );
    
    glTexCoord2f(0.0, 0.0);
    glVertex3f(ZERO,-ZERO,ZERO);
    glTexCoord2f(5.0, 0.0);
    glVertex3f(ZERO,ONE ,ZERO);
    glTexCoord2f(5.0, 5.0);
    glVertex3f(ZERO,ONE ,ONE );
    glTexCoord2f(0.0, 5.0);
    glVertex3f(ZERO,-ZERO,ONE );


    glTexCoord2f(0.0, 0.0);
    glVertex3f(ZERO,-ZERO,ZERO);
    glTexCoord2f(5.0, 0.0);
    glVertex3f(ZERO,-ZERO ,ONE);
    glTexCoord2f(5.0, 5.0);
    glVertex3f(ONE,-ZERO ,ONE );
    glTexCoord2f(0.0, 5.0);
    glVertex3f(ONE,-ZERO,ONE );


    glTexCoord2f(0.0, 0.0);
    glVertex3f(ONE,ONE,ZERO);
    glTexCoord2f(5.0, 0.0);
    glVertex3f(ZERO,ONE ,ZERO);
    glTexCoord2f(5.0, 5.0);
    glVertex3f(ZERO,ONE ,ONE );
    glTexCoord2f(0.0, 5.0);
    glVertex3f(ONE,ONE,ONE );

    glEnd();
    glPopMatrix();
}

void drawblock()
{
    int i,j,k;
    
    bctr = 0;
    glPushMatrix();
    k = 0;
    for(i=0;i<MAPCOUNT;i++){
        for(j=0;j<MAPCOUNT;j++){
            if(map[i][j] == 1)
            {
             glPushMatrix();
             glTranslatef((GLfloat) i , 0.0, (GLfloat) j);
             drawbuilding(bhgt[k++], 0);
             glPopMatrix();
            }
        }
    }
    glPopMatrix();
}
