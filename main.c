#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BaseFunctions.h"
#include "InputFunctions.h"

//  Check if enough arguments are passed
int main(int argc, char const *argv[]) {
  if (argc < 3) {
    printf("Not enough arguments\n");
    exit(-1);
  }

  int i;
  int size;
  int flag1 = 0;
  int flag2 = 0;
  char str[300];
  char comm[300];

  //  Save the -b and -o arguments
  for (i = 1; i < argc; i++) {
    if (!strcmp("-b", argv[i])) {
      flag1 = 1;
      size = atoi(argv[i+1]);
    }
    if (!strcmp("-o", argv[i])) {
      flag2 = 1;
      strcpy(comm, argv[i+1]);
    }
  }

  //  If there was no -b argument exit the program
  if (!flag1) {
    printf("Hashtable size not passed\n");
    return -1;
  }

  Hashtable *hash = hash_create(size);

  //  If -o was included, open the file
  //  and pass each line until the end of it
  if (flag2) {
    FILE *fp;
    fp = fopen(comm , "r");

    if(fp == NULL) {
       perror("Error opening the requested file");
       return -1;
    }
    while (fgets(str, sizeof(str), fp) != NULL) {
      FileExecute(hash, str);
    }
    fclose(fp);
  }

  //  User input
  printf("Insert any other commands from stdin\n");
  printf("-- Exit with ctrl D --\n");
  while (fgets(str, sizeof(str), stdin) != NULL) {
    FileExecute(hash, str);
  }
  hash_destroy(hash);
  free(hash->hashtable);
  free(hash);

  return 0;
}
