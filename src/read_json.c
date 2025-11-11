#include "read_json.h"
#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>

void read_test_file(const char* filepath) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        printf("Failed to open file: %s\n", filepath);
        return;
    }

    // Get file size
    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buf = malloc(filesize + 1);
    if (!buf) {
        printf("Memory allocation failed\n");
        fclose(fp);
        return;
    }

    fread(buf, 1, filesize, fp);
    buf[filesize] = '\0';
    fclose(fp);

    // Parse JSON
    struct json_object *parsed_json = json_tokener_parse(buf);
    if (!parsed_json) {
        printf("Failed to parse JSON\n");
        free(buf);
        return;
    }

    // Example: print the JSON content
    printf("JSON file content:\n%s\n", json_object_to_json_string(parsed_json));

    // Free resources
    json_object_put(parsed_json);
    free(buf);
}
