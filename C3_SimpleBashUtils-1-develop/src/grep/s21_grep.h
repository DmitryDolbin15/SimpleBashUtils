#ifndef S21_GREP_H_
#define S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 10000
#define ARGBUF 500
#define FILE_ERROR "grep: %s: No such file or directory\n"
#define EMPTY_OPTIONS                                                  \
  "grep: option requires an argument -- 'e'\nUsage: grep [OPTION]... " \
  "PATTERNS [FILE]...\nTry 'grep --help' for more information.\n"

typedef struct {
  int e;              // done => использование regexp
  char earg[ARGBUF];  // аргументы флага e
  int i;              // done => игнор регистра
  int v;              // done => вывод строк без шаблона
  int c;              // done => кол-во записей
  int l;              // done => только имена файлов
  int n;              // done => нумерация строк
  int h;  // done => отключить вывод имен файлов
  int s;  // done => не выводить ошибки о несуществующих файлах
  int o;  // done => вывод ТОЛЬКО часть строки, совпадающую с шаблоном
  int f;  // done => использовать файл шаблонов (1 шаблон = 1 строка)
  char f_filename[ARGBUF];  // аргумены флага f
  int countFiles;           // кол-во файлов
  int countMatches;         // кол-во совпадений
  char template[BUFSIZE];   // шаблон поиска
} Toptions;

void parseOptions(Toptions *options, int argc, char **argv);
void construct_f_template(Toptions *options);
void grepOutput(Toptions options, char *filename);
void print_match(Toptions *options, char *filename, char *source, int num);
void print_lastchar(char *source);
void substr(char *source, int length);
void prints_file(char *filename);
void prints_snum(int num);

#endif
