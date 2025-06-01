#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY_FILES "No files found!\n"

typedef struct {
  int b;  // done / --number-nonblank | нумерует только непустые строки
  int n;  // done / --number | нумерует все выходные строки
  int s;  // done / --squeeze-blank | сжимает несколько смежных пустых строк
  int v;  // отображает невидимые символы
  /* ----------------- */
  int t;  // -t предполагает и -v | также отображает табы как ^I
  int T;  // -T то же самое, но без -v | также отображает табы как ^I
  int e;  // -e предполагает и -v | также отображает символы конца строки как $
  int E;  // -E то же самое, но без -v | также отображает символы конца строки
          // как $
  int countFiles;
} Toptions;

typedef struct option Loptions;

int parseOptions(Toptions *options, int argc, char **argv);
void print_cat(Toptions *options, char *filename);

#endif
