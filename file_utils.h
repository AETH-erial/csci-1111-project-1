#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include <json-c/json.h>

// Returns a dynamically allocated array of strings (file names) in a directory.
char **list_files_in_dir(const char *dirpath, int *out_count);

json_object *json_from_file_list(const char *dirpath);

#define MAX_PATH_LENGTH 300

#endif
