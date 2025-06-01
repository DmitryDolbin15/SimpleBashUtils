#include "s21_cat.h"

int main(int argc, char **argv) {
  setlocale(LC_ALL, "rus");
  Toptions options = {0};
  if (argc > 1) {
    for (int x = parseOptions(&options, argc, argv); x < argc; x++) {
    }
  }
  if ((argc - optind) == 0)
    fprintf(stderr, EMPTY_FILES);
  else {
    for (int i = optind; i < argc; i++) {
      print_cat(&options, argv[i]);
    }
  }
  return 0;
}
