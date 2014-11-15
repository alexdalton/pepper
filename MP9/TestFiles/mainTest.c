#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "prog9.h"

int main(int argc, char **argv){

  int choice = atoi(argv[1]);
  FILE* t2=fopen("testEnd2.txt","r");
  FILE* t4=fopen("testEnd4.txt","r");
  int end2,end4;
  WAV *wav1;

  switch(choice){

    case 1:
      if(argc != 7) return -1;
      end2=little_endian_2(t2);
      end4=little_endian_4(t4);
      printf("%x\n",end2);
      printf("%x\n",end4);
      wav1 = read_file(argv[2]);
      sloop(wav1, argv[3], atof(argv[4]), atof(argv[5]), atoi(argv[6]));
      break;
    case 2:
      if(argc != 5) return -1;
      wav1 = read_file(argv[2]);
      lo_pass(wav1, argv[3], atoi(argv[4]));
      break;
    default:
      printf("Choice not in range.\n");

  }

  fclose(t2);
  fclose(t4);
  return 0;

}
 
