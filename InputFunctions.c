#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "InputFunctions.h"

//  Pick a str string, seperate it into tokens
//  and then call the requested function and its arguments
void FileExecute(Hashtable *ht, char *str) {
  const char s[2] = " ";
  char *token;
  char *temp1, *temp2;
  int counter;

  token = strtok(str, s);
  counter = 0;

  if (strcmp("createnodes", token) == 0) {
    token = strtok(NULL, s);
    while( token != NULL ) {
      if (!valid_check(token)) {
        token = strtok(NULL, s);
        continue;
      }
      createnodes(ht, atoi(token));
      token = strtok(NULL, s);
    }
  }
  else if (strcmp("delnodes", token) == 0) {
    token = strtok(NULL, s);
    while( token != NULL ) {
      if (!valid_check(token)) {
        token = strtok(NULL, s);
        continue;
      }
      delnodes(ht, atoi(token));
      token = strtok(NULL, s);
    }
  }
  else if (strcmp("addtran", token) == 0) {
    token = strtok(NULL, s);
    while( token != NULL ) {
      if (!valid_check(token) || (atof(token) <= 0.0)) {
        token = strtok(NULL, s);
        continue;
      }
      if (counter == 0) {
        temp1 = token;
        counter++;
        token = strtok(NULL, s);
        continue;
      }
      if (counter == 1) {
        temp2 = token;
        counter++;
        token = strtok(NULL, s);
        continue;
      }
      if (counter == 2) {
        addtran(ht, atof(token), atoi(temp1), atoi(temp2));
        token = strtok(NULL, s);
        counter++;
      }
      break;
    }
  }
  else if (strcmp("deltran", token) == 0) {
    token = strtok(NULL, s);
    while( token != NULL ) {
      if (!valid_check(token)) {
        token = strtok(NULL, s);
        continue;
      }
      if (counter == 0) {
        temp1 = token;
        counter++;
        token = strtok(NULL, s);
        continue;
      }
      if (counter == 1) {
        deltran(ht, atof(temp1), atof(token));
        token = strtok(NULL, s);
        counter++;
      }
      break;
    }
  }
  else if (strcmp("lookup", token) == 0) {
    token = strtok(NULL, s);
    while( token != NULL ) {
      if ((counter > 0) && !valid_check(token)) {
        token = strtok(NULL, s);
        continue;
      }
      if (counter == 0) {
        temp1 = token;
        counter++;
        token = strtok(NULL, s);
        continue;
      }
      if (counter == 1) {
        if (strcmp(temp1, "in") == 0) {
          lookup(ht, atoi(token), 1);
          token = strtok(NULL, s);
        }
        if (strcmp(temp1, "out") == 0) {
          lookup(ht, atoi(token), 2);
          token = strtok(NULL, s);
        }
        if (strcmp(temp1, "sum") == 0) {
          lookup(ht, atoi(token), 3);
          token = strtok(NULL, s);
        }
        counter++;
      }
      break;
    }
  }
  else if (strcmp("triangle", token) == 0) {
    token = strtok(NULL, s);
    while( token != NULL ) {
      if (!valid_check(token) || (atof(token) <= 0.0)) {
        token = strtok(NULL, s);
        continue;
      }
      if (counter == 0) {
        temp1 = token;
        counter++;
        token = strtok(NULL, s);
        continue;
      }
      if (counter == 1) {
        triangle(ht, atoi(temp1), atof(token));
        token = strtok(NULL, s);
        counter++;
      }
      break;
    }
  }
  else if (strcmp("conn", token) == 0) {
    token = strtok(NULL, s);
    while( token != NULL ) {
      if (!valid_check(token)) {
        token = strtok(NULL, s);
        continue;
      }
      if (counter == 0) {
        temp1 = token;
        counter++;
        token = strtok(NULL, s);
        continue;
      }
      if (counter == 1) {
        conn(ht, atoi(temp1), atoi(token));
        token = strtok(NULL, s);
        counter++;
      }
      break;
    }
  }
  else if (strcmp("allcycles", token) == 0) {
    token = strtok(NULL, s);
    if (!valid_check(token)) {
      token = strtok(NULL, s);
    }
    allcycles(ht, atoi(token));
    token = strtok(NULL, s);
  }
  else if (strcmp("traceflow", token) == 0) {
    token = strtok(NULL, s);
    while( token != NULL ) {
      if (!valid_check(token)) {
        token = strtok(NULL, s);
        continue;
      }
      if (counter == 0) {
        temp1 = token;
        counter++;
        token = strtok(NULL, s);
        continue;
      }
      if (counter == 1) {
        traceflow(ht, atoi(temp1), atoi(token));
        token = strtok(NULL, s);
        counter++;
      }
      break;
    }
  }
  else if (strcmp("bye\n", str) == 0) {
    token = strtok(NULL, s);
    bye(ht);
    token = strtok(NULL, s);
  }
  else if (strcmp("print\n", str) == 0) {
    token = strtok(NULL, s);
    print(ht);
    token = strtok(NULL, s);
  }
  else {
    printf("failure: passed wrong command\n");
    return;
  }
  return;
}

//  Check if the argument is correct
int valid_check(char *s) {
  if ((atoi(s) > 0) && (atoi(s) < 10000000)) {
    return 1;
  }
  return 0;
}
