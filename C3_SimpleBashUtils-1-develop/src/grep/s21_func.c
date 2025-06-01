#include "s21_grep.h"

void print_match(Toptions *options, char *filename, char *source, int num) {
  regex_t regex;
  regmatch_t pmatch[1000];
  int regcomp_status =
      regcomp(&regex, options->template,
              options->i ? REG_ICASE | REG_EXTENDED : REG_EXTENDED);
  if (!(regcomp_status)) {
    int regex_status = regexec(&regex, source, 0, NULL, 0);
    if (regex_status == options->v) {
      options->countMatches += 1;
      if (!options->c && !options->l) {
        if (options->countFiles > 1 && !(options->h) && !(options->o)) {
          prints_file(filename);
          printf(":");
        }
        if (options->n && !(options->o)) {
          prints_snum(num);
          printf(":");
        }
        char *ps = source;
        while (regexec(&regex, ps, 1, pmatch, 0) == 0) {
          if (options->countFiles > 1 && !(options->h) && options->o) {
            prints_file(filename);
            printf(":");
          }
          if (options->n && options->o) {
            prints_snum(num);
            printf(":");
          }
          int pos = pmatch[0].rm_so;
          if (pos >= 0 && !options->o) substr(ps, pos);
          if (pos == 0 && options->o) substr(ps, pos);
          ps += pos;
          substr(ps, pmatch[0].rm_eo - pos);
          if (options->o) printf("\n");
          ps -= pos;
          ps += pmatch[0].rm_eo;
        }
        if (!options->o) {
          printf("%s", ps);
          print_lastchar(ps);
        }
      }
    }
  }
  regfree(&regex);
}

void grepOutput(Toptions options, char *filename) {
  options.countMatches = 0;
  FILE *f = fopen(filename, "rt");
  if (f != NULL) {
    char line[500] = {0};
    int num = 0;
    while (fgets(line, sizeof(line), f)) {
      num++;
      print_match(&options, filename, line, num);
    }
    if (options.c && !options.l) {
      if (options.countFiles > 1 && !(options.h)) {
        prints_file(filename);
        printf(":");
      }
      printf("%d\n", options.countMatches);
    }
    if (options.countMatches > 0) {
      if (options.l) {
        prints_file(filename);
        printf("\n");
      }
    }
    fclose(f);
  } else {
    if (options.countFiles > 1 && options.l)
      fprintf(stderr, FILE_ERROR, filename);
  }
}

void construct_f_template(Toptions *options) {
  FILE *f = fopen(optarg, "r");
  char line[BUFSIZE];
  if (f != NULL) {
    while (fgets(line, BUFSIZE, f) != NULL) {
      if (line[strlen(line) - 1] == '\n' && strlen(line) - 1 != '\0') {
        line[strlen(line) - 1] = '\0';
      }
      strcat(options->template, line);
      strcat(options->template, "|");
    }
    options->template[strlen(options->template) - 1] = '\0';
  } else {
    fprintf(stderr, FILE_ERROR, optarg);
    exit(EXIT_SUCCESS);
  }
  fclose(f);
}

void parseOptions(Toptions *options, int argc, char **argv) {
  for (int counter = 0;
       (counter = getopt(argc, argv, "e:ivclnhsf:o")) != (-1);) {
    switch (counter) {
      case 'f':
        options->f = 1;
        strcat(options->f_filename, optarg);
        construct_f_template(options);
        break;
      case 'e':
        options->e = 1;
        strcat(options->earg, optarg);
        strcat(options->earg, "|");
        break;
      case 'l':
        options->l = 1;
        break;
      case 'c':
        options->c = 1;
        break;
      case 'o':
        options->o = 1;
        break;
      case 'i':
        options->i = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 'h':
        options->h = 1;
        break;
      default:
        fprintf(stderr, EMPTY_OPTIONS);
        exit(EXIT_SUCCESS);
    }
  }
  if (options->e) {
    if (options->earg[strlen(options->earg) - 1] == '|')
      options->earg[strlen(options->earg) - 1] = '\0';
    if (options->f) {
      strcat(options->template, "|");
    }
    strcat(options->template, options->earg);
  }
}

void print_lastchar(char *source) {
  char lastchar = source[strlen(source) - 1];
  if (lastchar != '\n') printf("\n");
}

void substr(char *source, int length) {
  for (int i = 0; i < length; i++) printf("%c", source[i]);
}

void prints_file(char *filename) { printf("%s", filename); }

void prints_snum(int num) { printf("%d", num); }
