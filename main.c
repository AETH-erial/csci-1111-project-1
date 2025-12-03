/*
 * Russell Hrubesky
 * Naimjon Ghafurov
 * */


#include <stdio.h>
#include <string.h>
#include <math.h>
#include "./src/read_json.c"


#define NUM_HISTORY 3
#define NUM_GEOGRAPHY 3


// Creating and using structs: https://www.learningaboutelectronics.com/Articles/How-to-create-initialize-structure-C.php
struct TestEntry {
    char question[1024];
    char choices [5][512];
    int answerIdx;

};

int main() {



/*
 * 1. select a topic (geography or history) #TODO: Add more topics
 * 2. randomy select a number 1-NUM_HISTORY/NUM_GEOGRAPHY, which maps to an array of questions  #TODO
 * 3. each element in the array will be a structure that has two fields
 *      - list of possible answers (for multiple choice)
 *      - the correct answer
 * 4. show the number of correct answers when program exits
 *
 * Later features:
 *  - input a JSON file at compile time to embed the test contents into the binary (makes it portable + scalable)
 * */

/*
 * history: 
 *  1. when did WW2 officially end?
 *      a. 1939
 *      b. 1946
 *      c. 1912
 *      d. 1945
 *  2. Who was the captain of the Titanic?
 *      a. Edward John Smith
 *      b. Dwight B. Eisenhower
 *      c. Frank Lloyd Wright
 *      d. William S. Burroughs
 *  3. Who killed Julius Caesar?
 *      a. Marcus Junius Brutus
 *      b. Titus Livius
 *      c. Gaius Trebonius
 *      d. Pontius Aquila
 *
 * geography:
 * 1. Where does the great wall of china start?
 *      a. South Korea
 *      b. Hebei Province (China)
 *      c. Hong Kong
 *      d. Shanghai
 *
 * 2. What continent is the country of sudan located on?
 *      a. South America
 *      b. Antartica
 *      c. Australia
 *      d. Africa
 *
 * 3. what is the largest sea on earth?
 *      a. Caribbean
 *      b. Mediterranean
 *      c. Phillipine
 *      d. South China
 *
 * */

 

    struct TestEntry historyTest[NUM_HISTORY] = {
        {
            .question = "When did WW2 officially end?",
            .choices = {"1939", "1946", "1912", "1945"},
            .answerIdx = 3
        },
        {
            .question = "Who was the captain of the Titanic?",
            .choices = {"Dwight B. Eisenhower", "Edward John Smith", "Frank Lloyd Wright", "William S. Burroughs"},
            .answerIdx = 1
        },
        {
            .question = "Who killed Julius Caesar?",
            .choices = {"Marcus Junius Brutus", "Titus Livius", "Gaius Trebonius", "Pontius Aquila"},
            .answerIdx = 0
        }
    };

    struct TestEntry geographyTest[NUM_GEOGRAPHY] = {
        {
            .question = "Where does the Great Wall of China start?",
            .choices = {"South Korea", "Hebei Province (China)", "Hong Kong", "Shanghai"},
            .answerIdx = 1
        },
        {
            .question = "What continent is the country of Sudan located on?",
            .choices = {"South America", "Antarctica", "Africa", "Australia"},
            .answerIdx = 2
        },
        {
            .question = "What is the largest sea on Earth?",
            .choices = {"Caribbean", "Mediterranean", "Philippine", "South China"},
            .answerIdx = 1
        }
    };
    char fname[] = "./temp.json";
    read_test_file(*fname);


    int choice;
    printf("Choose a test:\n");
    printf("1. History\n");
    printf("2. Geography\n");
    printf("Enter your choice (enter the number for the test you wish to take): ");
    scanf("%d", &choice);

    struct TestEntry* selectedTest = NULL;
    int numQuestions = 0;

    if (choice == 1) {
        selectedTest = historyTest;
        numQuestions = NUM_HISTORY;
    } else if (choice == 2) {
        selectedTest = geographyTest;
        numQuestions = NUM_GEOGRAPHY;
    } else {
        printf("Invalid choice.\n");
        return 1;
    }

    int correct;

    for (int i = 0; i < numQuestions; i++) {
        printf("\nQ%d: %s\n", i + 1, selectedTest[i].question);
        for (int j = 0; j < 4; j++) {
            // Below prints the question out with alphabetic index. To iterate each option, we are adding to the 
            // ASCII value of 'a', and if we are incrementing up to for, 'a' + 1 will be 'b', because 
            // ASCII value of 'a' is 97, so 'b' will be 98, so on and so forth
            printf("  %c. %s\n", 'a' + j, selectedTest[i].choices[j]);
        }

        char userAnswer;
        printf("Your answer (a-d): ");
        scanf(" %c", &userAnswer);  

        int userIdx = userAnswer - 'a'; // here we are getting the absolute index of the answer with respect to our multiple choice array.
                                        // subtracting 'a', or 97 will give us the index of the answer relative to our choice arrays we defined
                                        // in our structs at program entry
        if (userIdx == selectedTest[i].answerIdx) {
            correct++;
        } else {
            continue;
        }
    }
    printf("\nYou scored %d out of %d questions right.\nScore: %d/%d\n", correct, numQuestions, correct, numQuestions);
    printf("you finished the test!\n");
}
