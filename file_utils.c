#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "file_utils.h"
#include "server.h"
#include <json-c/json.h>
#include <sys/stat.h>

#define INITIAL_CAPACITY 16
/*
 *provides a list of files in a directory
 * */
char **list_files_in_dir(const char *dirpath, int *out_count) {
    if (!out_count) return NULL;
    *out_count = 0;

    DIR *dir = opendir(dirpath);
    if (!dir) return NULL;

    int capacity = 16;
    char **files = malloc(sizeof(char*) * capacity);
    if (!files) { closedir(dir); return NULL; }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char path[4096];
        snprintf(path, sizeof(path), "%s/%s", dirpath, entry->d_name);

        struct stat st;
        if (stat(path, &st) != 0)
            continue;

        if (!S_ISREG(st.st_mode))  
            continue;

        if (*out_count >= capacity) {
            capacity *= 2;
            char **tmp = realloc(files, sizeof(char*) * capacity);
            if (!tmp) break;
            files = tmp;
        }

        files[*out_count] = strdup(entry->d_name);
        if (files[*out_count]) (*out_count)++;
    }

    closedir(dir);
    return files;
}


/*
 * Returns a json_object* representing a JSON array of filenames.
 * Caller must call json_object_put() to free.
 * :param dirpath: the directory to read 
 */
json_object *json_from_file_list(const char *dirpath) {
    int count;
    char **files = list_files_in_dir(dirpath, &count);
    if (!files) return NULL;

    json_object *jarray = json_object_new_array();

    for (int i = 0; i < count; i++) {
        json_object *jstr = json_object_new_string(files[i]);
        json_object_array_add(jarray, jstr);
        log_msg(2, "found: ", files[i]);
        free(files[i]); 
    }
    free(files); 

    return jarray;
}


