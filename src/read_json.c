#include "read_json.h"
#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Convert JSON file to an array of TestEntry
int json_to_test_entries(const char* filepath, TestEntry* outArray, int maxEntries) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        printf("Failed to open file: %s\n", filepath);
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buf = malloc(filesize + 1);
    if (!buf) {
        printf("Memory allocation failed\n");
        fclose(fp);
        return 0;
    }

    fread(buf, 1, filesize, fp);
    buf[filesize] = '\0';
    fclose(fp);

    struct json_object *parsed_json = json_tokener_parse(buf);
    free(buf);
    if (!parsed_json) {
        printf("Failed to parse JSON\n");
        return 0;
    }

    int count = 0;
    struct json_object *questions_array;
    if (!json_object_object_get_ex(parsed_json, "questions", &questions_array)) {
        printf("JSON does not contain 'questions' array\n");
        json_object_put(parsed_json);
        return 0;
    }

    int array_len = json_object_array_length(questions_array);
    for (int i = 0; i < array_len && count < maxEntries; i++) {
        struct json_object *q_obj = json_object_array_get_idx(questions_array, i);

        struct json_object *q_text, *q_choices, *q_answer;
        if (!json_object_object_get_ex(q_obj, "question", &q_text) ||
            !json_object_object_get_ex(q_obj, "choices", &q_choices) ||
            !json_object_object_get_ex(q_obj, "answerIdx", &q_answer)) {
            continue;
        }

        strncpy(outArray[count].question, json_object_get_string(q_text), MAX_QUESTION_LEN-1);
        outArray[count].question[MAX_QUESTION_LEN-1] = '\0';

        int choice_len = json_object_array_length(q_choices);
        for (int j = 0; j < choice_len && j < MAX_CHOICES; j++) {
            struct json_object *c_obj = json_object_array_get_idx(q_choices, j);
            strncpy(outArray[count].choices[j], json_object_get_string(c_obj), MAX_CHOICE_LEN-1);
            outArray[count].choices[j][MAX_CHOICE_LEN-1] = '\0';
        }

        outArray[count].answerIdx = json_object_get_int(q_answer);
        count++;
    }

    json_object_put(parsed_json);
    return count;
}

// -----------------------
// Serialization: struct → byte array
void test_entry_to_bytes(const TestEntry* entry, uint8_t* buffer) {
    memcpy(buffer, entry, sizeof(TestEntry));
}

// Deserialization: byte array → struct
void bytes_to_test_entry(const uint8_t* buffer, TestEntry* entry) {
    memcpy(entry, buffer, sizeof(TestEntry));
}
