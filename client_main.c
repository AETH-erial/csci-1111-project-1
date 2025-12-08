#include "client.h"
#include <stdio.h>
#include <json-c/json.h>
#include <unistd.h>
#include "server.h"
#include "string.h"
#include "json_io.h"

int main() {
    const char *ip = "127.0.0.1"; // TODO: make this source from an environment variable or cli flag
    int port = PORT; // TODO: this should also be sourced from env var or cli flag

    int sockfd = connect_to_server(ip, port);
    if (sockfd < 0) return 1;

    char *response = http_get(sockfd, "/geography"); // this should be gotten from an endpoint that returns all available tests
    close(sockfd);

    if (!response) {
        fprintf(stderr, "Failed to get HTTP response\n");
        return 1;
    }

    json_object *jarray = parse_json_body(response);
    free(response);

    if (!jarray) {
        fprintf(stderr, "Failed to parse JSON\n");
        return 1;
    }


    int len = json_object_array_length(jarray);
    struct TestEntry fullTest[len];

    for (int i = 0; i < len; i++) {
        json_object *elem = json_object_array_get_idx(jarray, i);
        printf("  %s\n", json_object_get_string(elem));
        int sockfd = connect_to_server(ip, port);
        if (sockfd < 0) return 1;
        char path[1024];
        snprintf(path, sizeof(path), "/geography/%s", json_object_get_string(elem));
        char *response = http_get(sockfd, path);

        close(sockfd);

        if (!response) {
            fprintf(stderr, "Failed to get HTTP response\n");
            return 1;
        }
        json_object *resp = parse_json_body(response);
        free(response);
        struct TestEntry entry;
        parse_test_struct_from_buf(json_object_to_json_string(resp), &entry);
        fullTest[i] = entry;
        printf("question: %s\n", entry.question);
    }

    json_object_put(jarray);

    int correct = 0;

    for (int i = 0; i < len; i++) {
        printf("\nQ%d: %s\n", i + 1, fullTest[i].question);
        for (int j = 0; j < 4; j++) {
            // Below prints the question out with alphabetic index. To iterate each option, we are adding to the 
            // ASCII value of 'a', and if we are incrementing up to for, 'a' + 1 will be 'b', because 
            // ASCII value of 'a' is 97, so 'b' will be 98, so on and so forth
            printf("  %c. %s\n", 'a' + j, fullTest[i].choices[j]);
        }

        char userAnswer;
        printf("Your answer (a-d): ");
        scanf(" %c", &userAnswer);  

        int userIdx = userAnswer - 'a'; // here we are getting the absolute index of the answer with respect to our multiple choice array.
                                        // subtracting 'a', or 97 will give us the index of the answer relative to our choice arrays we defined
                                        // in our structs at program entry
        if (userIdx == fullTest[i].answerIdx) {
            correct++;
        } else {
            continue;
        }
    }
    printf("\nYou scored %d out of %d questions right.\nScore: %d/%d\n", correct, len, correct, len);
    printf("you finished the test!\n");
    return 0;
}

