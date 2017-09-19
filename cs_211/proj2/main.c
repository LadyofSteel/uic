/**
 *  @brief CS 211 Project 2
 *
 *  @author Ammar Subei
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "stack.h"

bool isDebug = false;

int main(int argc, char *argv[])
{
  if (argc > 1)
  {
    if (!strcmp(argv[1], "-d"))
        isDebug = true;
  }

  return 0;
}
