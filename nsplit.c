
#include <stdio.h>
#if defined(__linux__)
#define MYOS 1
#elif defined(_WIN32)
#define MYOS 2
#elif defined(_WIN64)
#define MYOS 3
#elif defined(__unix__)
#define MYOS 4
#define PATH_MAX 2500
#else
#define MYOS 0
#endif
#include <string.h>
#include <stdlib.h>

#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h> 
#include <time.h>



#include <stdio.h>
#include <stdlib.h>

long bitcounter = 0;
long splitfilenbr = 1;


#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void fseek_filesize(const char *filename)
{
    FILE *fp = NULL;
    long off;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("failed to fopen %s\n", filename);
        exit(EXIT_FAILURE);
    }

    if (fseek(fp, 0, SEEK_END) == -1)
    {
        printf("failed to fseek %s\n", filename);
        exit(EXIT_FAILURE);
    }

    off = ftell(fp);
    if (off == (long)-1)
    {
        printf("failed to ftell %s\n", filename);
        exit(EXIT_FAILURE);
    }

    //printf("[*] fseek_filesize - file: %s, size: %ld\n", filename, off);
    printf("%ld\n", off);

    if (fclose(fp) != 0)
    {
        printf("failed to fclose %s\n", filename);
        exit(EXIT_FAILURE);
    }
}










/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
int fexist(char *a_option)
{
  char dir1[PATH_MAX]; 
  char *dir2;
  DIR *dip;
  strncpy( dir1 , "",  PATH_MAX  );
  strncpy( dir1 , a_option,  PATH_MAX  );

  struct stat st_buf; 
  int status; 
  int fileordir = 0 ; 

  status = stat ( dir1 , &st_buf);
  if (status != 0) {
    fileordir = 0;
  }

  // this is compatible to check if a file exists
  FILE *fp2check = fopen( dir1  ,"r");
  if( fp2check ) {
  // exists
  fileordir = 1; 
  fclose(fp2check);
  } 

  if (S_ISDIR (st_buf.st_mode)) {
    fileordir = 2; 
  }
return fileordir;
/////////////////////////////
}









////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
void ncp( char *filenametarget,  char *filenamesource )
{
   FILE *source, *target; 
   int ch ; 
   source = fopen( filenamesource , "r");
   if( source == NULL )
   {
      printf("Press any key to exit...\n");
      exit(EXIT_FAILURE);
   }
 

   char charo[PATH_MAX];  
   snprintf( charo, PATH_MAX , "filencp-%04ld.out" , splitfilenbr  );
 
   printf("Source: %s\n",  filenamesource );
   printf("Target: %s\n",  filenametarget );
   printf("Tmp: %s\n",  charo );
   printf("Copying...\n");
  
   target = fopen( filenametarget , "w");
   fclose(target);

   target = fopen( filenametarget , "ab+");
   while( ( ch = fgetc(source) ) != EOF )
   {
      fputc(ch, target);
      bitcounter ++;
   }
   fclose(target);
 
   printf("File copied successfully.\n");
   fclose(source);
}



////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
void nsplit( char *filenamesource )
{
   FILE *source, *target; 
   int ch ; 
   source = fopen( filenamesource , "r");
   if( source == NULL )
   {
      printf("Press any key to exit...\n");
      exit(EXIT_FAILURE);
   }
 

   char charo[PATH_MAX];  
   char filenametarget[PATH_MAX];  
   snprintf( charo, PATH_MAX , "filensplit-%04ld.out" , splitfilenbr  );
   strncpy( filenametarget, charo , PATH_MAX );
 
   printf("Source: %s\n",  filenamesource );
   printf("Target: %s\n",  filenametarget );
   printf("Tmp: %s\n",  charo );
   printf("Copying...\n");
  
   target = fopen( filenametarget , "w");
   fclose(target);

   target = fopen( filenametarget , "ab+");
   bitcounter = 0;
   while( ( ch = fgetc(source) ) != EOF )
   {
       //if ( bitcounter == 2655776 )  // 2.5mb
       //if ( bitcounter == 12655776 )   // 12.5mb
       if ( ( bitcounter >= 1 ) && ( bitcounter % 12655776 == 0))
       {
          fclose( target );
          splitfilenbr++;
          snprintf( charo, PATH_MAX , "filensplit-%04ld.out" , splitfilenbr  );
          strncpy( filenametarget, charo , PATH_MAX );
          target = fopen( filenametarget , "ab+");
          printf("Source: %s\n",  filenamesource );
          printf("Target: %s\n",  filenametarget );
          printf("Tmp: %s\n",  charo );
          printf("Copying...\n");
       }

       fputc(ch, target);
       bitcounter++;
   }
   fclose(target);
 
   printf("File copied successfully.\n");
   fclose(source);
}







int main( int argc, char *argv[])
{

   FILE *source, *target;
   int i; 


      ////////////////////////////////////////////////////////
      if ( argc >= 2)
      {
         for( i = 1 ; i <= argc-1 ; i++) 
         {
            //printf( "=> %d/%d %s \n", i , argc , argv[ i ] );
            bitcounter = 0;
            //ncat_static( argv[ i ] );
            nsplit(  argv[ i ] );
            printf("Size: %ld\n", bitcounter );
         }
      }
      return 0;



      ////////////////////////////////////////////////////////
      if ( argc >= 2)
      {
         for( i = 1 ; i <= argc-1 ; i++) 
         {
            //printf( "=> %d/%d %s \n", i , argc , argv[ i ] );
            bitcounter = 0;
            //ncat_static( argv[ i ] );
            printf("Size: %ld\n", bitcounter );
            printf("Total size: ");
            fseek_filesize( argv[i] );
            printf("\n");
         }
      }

   return 0;
}




//Size: 8655776
/*
Size: 3655776
Total size: 3655776
3.5Mb
*/




