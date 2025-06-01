#include "s21_cat.h"

int parseOptions(Toptions *options, int argc, char **argv) {
  const Loptions long_options[] = {
      {"number-nonblank", no_argument, &(options->b), 1},
      {"number", no_argument, &(options->n), 1},
      {"squeeze-blank", no_argument, &(options->s), 1},
      {NULL, 0, NULL, 0}};
  const char *short_options = "bnsvtTeE";
  int sym;
  while ((sym = getopt_long(argc, argv, short_options, long_options, NULL)) !=
         (-1)) {
    switch (sym) {
      case 'b':
        options->b = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 't':
        options->t = 1;
        options->v = 1;
        break;
      case 'e':
        options->e = 1;
        options->v = 1;
        break;
      case 'T':
        options->T = 1;
        options->v = 0;
        break;
      case 'E':
        options->E = 1;
        options->v = 0;
        break;
    }
  }
  return optind;
}

void print_cat(Toptions *options, char *filename) {
  FILE *f = fopen(filename, "r");
  int line_number = 1;
  int ifPrevLineBlank = 0;
  char prev_ch = 10;
  if (f != NULL) {
    int ch;
    while ((ch = fgetc(f)) != EOF) {
      if (options->s && ch == '\n' && ifPrevLineBlank) {
        continue;
      }
      if (((options->n) && (!options->b) && prev_ch == 10) ||
          (options->b && (prev_ch == 10 && ch != 10))) {
        printf("%6d\t", line_number++);
      }
      switch (ch) {
        case '\t':
          if (options->T || options->t)
            printf("^I");
          else
            printf("\t");
          break;
        case '\n':
          if (options->E || options->e)
            printf("$\n");
          else
            printf("\n");
          break;
        default:
          if (options->v == 1 && ch != '\n' && ch != '\t') {
            if (ch >= 0 && ch <= 31) {
              printf("^%c", ch + 64);
            } else if (ch == 127) {
              printf("^%c", ch - 64);
            } else {
              printf("%c", ch);
            }
          } else {
            printf("%c", ch);
          }
      }
      ifPrevLineBlank = (prev_ch == '\n' && ch == '\n');
      prev_ch = ch;
    }
    fclose(f);
  } else
    printf("cat: %s: No such file or directory\n", filename);
}
