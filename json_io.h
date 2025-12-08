#ifndef JSON_IO_H
#define JSON_IO_H

#include <json-c/json.h>


struct TestEntry {
    char question[1024];
    char choices[5][512];
    int answerIdx;
};


/*
 * Reads a JSON file and prints it out
 * :param filepath: the path of the file to read
 * */
void read_test_file(const char *filepath);

/*
 * Loads a JSON file and returns a parsed json_object*
 * Caller must eventually free it with json_object_put()
 */
int load_json(const char *filepath, struct TestEntry *out);

/*
 *parse a struct out of a memory buffer
 * */
int parse_test_struct_from_buf(const char *buf, struct TestEntry *out);

#endif
