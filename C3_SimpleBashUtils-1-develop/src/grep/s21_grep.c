#include "s21_grep.h"

int main(int argc, char *argv[]) {
  Toptions options = {0};
  parseOptions(&options, argc, argv);
  if (!options.e && !options.f) {
    strcat(options.template, argv[optind]);
    optind += 1;
  }
  options.countFiles = argc - optind;
  for (int i = optind; i < argc; i++) grepOutput(options, argv[i]);
  return 0;
}
