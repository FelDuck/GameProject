#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

const u_int32_t MASKLOVE = 4278190080;
const u_int32_t MASKHATE = 16711680;
const u_int32_t MASKFEAR = 65280;
const u_int32_t MASKCOMP = 240;
const u_int32_t MASKRESP = 15;
void shiftOnly(u_int32_t cobaye);
void maskShift(u_int32_t cobaye);

float timeDiff(struct timeval* start,struct timeval* end){
  return (end->tv_sec-start->tv_sec)+ 1e-6* (end->tv_usec - start->tv_usec);
}
enum {WIDTH = 100000};

int main(){
  struct timeval start;
  struct timeval end;

  u_int32_t *arr = malloc(WIDTH * sizeof(int));

  srand(time(NULL));
  for(size_t i = 0;i< WIDTH;i++){
    arr[i] = rand();
  }

  gettimeofday(&start,NULL);
  for(size_t i = 0;i< WIDTH;i++){
    shiftOnly(arr[i]);
  }
  gettimeofday(&end,NULL);
  printf("\nshiftonly = %0.8f\n",timeDiff(&start, &end));

  
  gettimeofday(&start,NULL);
  for(size_t i = 0;i< WIDTH;i++){
    maskShift(arr[i]);
  }
  gettimeofday(&end,NULL);
  printf("\nmaskShift = %0.8f\n",timeDiff(&start, &end));
  
  
  free(arr);
}
/*
//Conclusion being that the mask then shift seem to be quicker even over the shift only method when it requires to only shift 24 to the right
//aka even in the best case scenario for the shiftonly method the mask is quicker
void shiftOnly(u_int32_t cobaye){
  u_int8_t hate;
  hate = (cobaye<<8)>>24;
  printf("%x, ",hate);
}

void maskShift(u_int32_t cobaye){
  u_int8_t hate;
  hate = (cobaye & MASKHATE)>>16;
  printf("%x, ",hate);
  }*/
