
#include "main.h"

int MAPCOUNT = 0;

GLuint readppm(char *filename, int wrap)
{
  GLuint texture;
  size_t k;
  int width, height;
  char b[K];
  unsigned char *data;
  FILE *fd;
  char *rv;

  fd = fopen(filename, "rb");
  if(fd == NULL){
    fprintf(stderr,"Cannot open %s\n",filename);
    exit(0);
  }
  rv = fgets(b,K,fd);   // reads the P6 line
  if(strncmp(b,"P6",2)){
    fprintf(stderr,"%s is not a P6 file\n", filename);
    exit(0);
  }
  rv = fgets(b,K,fd);   // reads the width-height line
  sscanf(b,"%d %d",&width,&height);
  rv = fgets(b,K,fd);   // reads the max line
  data = (unsigned char *) malloc(width * height * 3);
  k = fread(data, width * height * 3, 1, fd);
  fclose(fd);

  glGenTextures( 1, &texture );
  glBindTexture( GL_TEXTURE_2D, texture );
  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );

  free(data);
  return texture;
}

int **readmap(char *filename)
{
    FILE *fd;
    int count = 0;
    int i = 0;
    int j = 0;
    char c;
    fd = fopen(filename, "r");
    if(fd == NULL)
    {    
        fprintf(stderr, "cannot open the file %s\n",filename);
        exit(0);
    }
    else
    {
        while((c = getc(fd)) != EOF)
	{
            if(c == '\n')
            count++;
        }
    }
    MAPCOUNT = count;
    rewind(fd);
    
    int **maparr = (int**)malloc(count*sizeof(int*));
    
    for(i=0;i<count;i++)
        maparr[i] = (int*)malloc(sizeof(int)*count);
    
    i=0,j=0;
    
    while((c = getc(fd)) != EOF)
    {
       if(c == '\n')
       { 
	 i++;
         j = 0;
       }
       
       if(c != ' ' && c != '\n')
        maparr[i][j++] = c - '0';
    }

    return maparr;
}
