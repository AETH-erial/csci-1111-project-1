#ifndef READ_JSON_H
#define READ_JSON_H

#include <stdint.h>

#define MAX_CHOICES 5
#define MAX_QUESTION_LEN 1024
#define MAX_CHOICE_LEN 512

// Struct for one test question
typedef struct {
    char question[MAX_QUESTION_LEN];
    char choices[MAX_CHOICES][MAX_CHOICE_LEN];
    int answerIdx;
} TestEntry;

// Functions
int json_to_test_entries(const char* filepath, TestEntry* outArray, int maxEntries);

// Serialization / deserialization for network
void test_entry_to_bytes(const TestEntry* entry, uint8_t* buffer);
void bytes_to_test_entry(const uint8_t* buffer, TestEntry* entry);

#endif
