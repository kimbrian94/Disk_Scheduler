/*
EECS 3221 FINAL PROJECT
name: GISEUNG KIM
student #: 212981858
eecs login: giseung
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CYLINDERS_NUM 100
#define REQUEST_NUM 25
int disk[REQUEST_NUM];
int new_disk[REQUEST_NUM];
int init_head = 33;
FILE * input_file;
FILE * output_file;

int compareFunction (const void * x, const void * y) {
   return ( *(int*)x - *(int*)y );
}

//disk scheduling algorithm that uses the first come first serve pattern
int diskFCFS(){
  int total_movement = 0;
  int current_head = init_head;

  for(int j = 0; j < REQUEST_NUM; j++){
    fprintf(output_file, "%d\n", disk[j]);
    total_movement += abs(current_head - disk[j]);
    current_head = disk[j];
  }

  return total_movement;
}

//disk scheduling algorithm that uses the SCAN pattern
int diskSCAN(){
  qsort(disk, 25, sizeof(int), compareFunction);
  int total_movement = 0;
  int midIndex;
  int current_head = init_head;
  for (int i = 0; i < REQUEST_NUM; i++) {
    if (disk[i] < init_head && disk[i + 1] > init_head) {
      midIndex = i;
    }
  }
  for (int i = midIndex; i >= 0; i--) {
    total_movement += current_head - disk[i];
    current_head = disk[i];
    fprintf(output_file, "%d\n", current_head);
  }
  total_movement += current_head;
  current_head = disk[midIndex + 1];
  fprintf(output_file, "%d\n", current_head);
  total_movement += current_head; //starts with the right side of mid index
  for (int i = midIndex + 1; i < REQUEST_NUM - 1; i++) {
    total_movement += abs(current_head - disk[i + 1]);
    current_head = disk[i + 1];
    fprintf(output_file, "%d\n", current_head);
  }
  return total_movement;
}

//disk scheduling algorithm that uses the CSCAN pattern
int diskCSCAN(){
  qsort(disk, 25, sizeof(int), compareFunction);
  int total_movement = 0;
  int midIndex;
  int current_head = init_head;
  for (int i = 0; i < REQUEST_NUM; i++) {
    if (disk[i] < init_head && disk[i + 1] > init_head) {
      midIndex = i + 1;
    }
  }
  total_movement += disk[midIndex] - init_head;
  for (int i = midIndex; i < REQUEST_NUM - 1; i++) {
    current_head = disk[i];
    total_movement += abs(current_head - disk[i + 1]);
    fprintf(output_file, "%d\n", current_head);
  }
  fprintf(output_file, "%d\n", disk[REQUEST_NUM - 1]);
  fprintf(output_file, "%d\n", disk[0]);
  total_movement += disk[0] + CYLINDERS_NUM;
  for (int i = 1; i < midIndex; i++) {
    current_head = disk[i];
    total_movement += current_head - disk[i - 1];
    fprintf(output_file, "%d\n", current_head);
  }
  return total_movement;
}

int main(int argc, char const *argv[]) {
  for (int i = 0; i < REQUEST_NUM; i++) { disk[i] = 0; new_disk[i] = 0; } //initially set the disk elements to 0

  const char * input = argv[1];
  const char * scheduler = argv[2];

  int count = 0;

  input_file = fopen(input, "r");
  output_file = fopen("output.txt", "w");
  char buf[5];

  while (fgets(buf, 5, input_file) != NULL) {
    disk[count] = atoi(buf);
    count++;
  }

  fprintf(output_file, "\nFCFS Algorithm\nInitial head position = %d\nSeek Sequence is:\n", init_head);
  fprintf(output_file, "Total head movement for FCFS = %d\n\n", diskFCFS());
  fprintf(output_file, "SCAN Algorithm\nInitial head position = %d\nSeek Sequence is:\n", init_head);
  fprintf(output_file, "Total head movement for SCAN = %d\n\n", diskSCAN());fprintf(output_file, "C_SCAN Algorithm\nInitial head position = %d\nSeek Sequence is:\n", init_head);
  fprintf(output_file, "Total head movement for C_SCAN = %d\n", diskCSCAN());
  return 0;
}
