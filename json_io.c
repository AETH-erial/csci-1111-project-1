/*
 * 
 * Methods dedicated to IO operations on JSON files
 * 
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include <json-c/json.h>
#include "json_io.h"
#include "file_utils.h"

#define BUF_MAX_SIZE  4096



/*
 *parses a struct out of a json encoded string in 'buf'
 :param buf: pointer to start of memory buffer containing JSON of TestEntry
 :param out: pointer to a TestEntry struct
 * */
int parse_test_struct_from_buf(const char *buf, struct TestEntry *out) {
    json_object *root = json_tokener_parse(buf);

    // extracting the 'question' and placing it in the struct
    json_object *question;
    if (!json_object_object_get_ex(root, "question", &question)) {
        fprintf(stderr, "Missing field: question\n");
        json_object_put(root);
        return -1;
    }

    const char *qtext = json_object_get_string(question);
    strncpy((*out).question, qtext, sizeof((*out).question) - 1);
    (*out).question[sizeof((*out).question) - 1] = '\0';

    // extracting the 'choices' and placing them in the struct
    json_object *choices;
    if (!json_object_object_get_ex(root, "choices", &choices)) {
        fprintf(stderr, "Missing field: choices\n");
        json_object_put(root);
        return -1;
    }

    if (!json_object_is_type(choices, json_type_array)) {
        fprintf(stderr, "choices is not an array\n");
        json_object_put(root);
        return -1;
    }

    int choice_count = json_object_array_length(choices);
    if (choice_count > 5) choice_count = 5;   

    for (int i = 0; i < choice_count; i++) {
        json_object *choice_val = json_object_array_get_idx(choices, i);
        const char *text = json_object_get_string(choice_val);
        strncpy((*out).choices[i], text, sizeof((*out).choices[i]) - 1);
        (*out).choices[i][sizeof((*out).choices[i]) - 1] = '\0';
    }

    for (int i = choice_count; i < 5; i++) {
        (*out).choices[i][0] = '\0';
    }

    // extract the answer index and placing it in the struct
    json_object *answerIdx;
    if (!json_object_object_get_ex(root, "answerIdx", &answerIdx)) {
        fprintf(stderr, "Missing field: answerIdx\n");
        json_object_put(root);
        return -1;
    }

    (*out).answerIdx = json_object_get_int(answerIdx);

    json_object_put(root);

    return 0;
}

/*
 * Load JSON representing a single TestEntry:
 *
 */
int load_json(const char *filepath, struct TestEntry *out) {
    if (!out) {
        fprintf(stderr, "Error: output struct is NULL\n");
        return -1;
    }

    int fd = open(filepath, O_RDONLY);
    if (fd < 0) {
        perror("Couldn't open file");
        return -1;
    }

    char buf[BUF_MAX_SIZE];
    ssize_t bytes = read(fd, buf, BUF_MAX_SIZE - 1);
    close(fd);

    if (bytes <= 0) {
        perror("Error reading file");
        return -1;
    }

    buf[bytes] = '\0';
    return parse_test_struct_from_buf(buf, out);
}
