/*
 * Russell Hrubesky
 * Naimjon Ghafurov
 * Mohamed Abdi
 * */


#include <stdio.h>
#include <string.h>
#include "./src/read_json.c"

#include <iostream>
#include <string>
using namespace std;

#define NUM_HISTORY 3
#define NUM_GEOGRAPHY 3
#define NUM_BEYONCEOLOGY 4


// Creating and using structs: https://www.learningaboutelectronics.com/Articles/How-to-create-initialize-structure-C.php
/* typedef struct TestEntry_struct {
    char question[1024];
    char choices [5][512];
    int answerIdx;

} TestEntry;

*/

// turning the struct TestEntry to a class TestEntry

class TestEntry {
    private:
        string question;
        string choices[5];
        int answerIdx;
    public:
        TestEntry(string q, string c[5], int a);
        void setQuestion(string newQuestion);
        string getQuestion() const;
        void setAnswerIdx(int newIdx);
        int getAnswerIdx() const;
        string getChoice(int idx) const;
};
//constructor definition
TestEntry::TestEntry(string q, string c[5], int a) {
        question = q;
        for(int i = 0; i < 5; i++) {
            choices[i] = c[i];
        }
        answerIdx = a;

}

void TestEntry::setQuestion(string newQuestion) {
    question = newQuestion;
}

string TestEntry::getQuestion() const{
    return question;
}

void TestEntry::setAnswerIdx(int newIdx) {
    answerIdx = newIdx;
}

int TestEntry::getAnswerIdx() const {
    return answerIdx;
};

string TestEntry::getChoice(int idx) const {
    if (idx < 0 || idx >= 5) {
        return "";
    }
    return choices[idx];
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

/*
beyonceology:

1. What year did Beyoncé release her debut solo album, "Dangerously in Love"?

A) 2002
B) 2006
C) 2008
D) 2016

Correct Answer: B) 2003

2. Which of these Beyoncé albums was released as a surprise without prior announcement in 2013?

A) B’Day
B) Lemonade
C) 4
D) BEYONCE

Correct Answer: D) "BEYONCE"

3. Beyoncé was a member of which iconic girl group before her solo career?

A) The Pussycat Dolls
B) Destiny's Child
C) TLC
D) En Vogue

Correct Answer: B) Destiny's Child

4. In 2018, Beyoncé became the first Black woman to headline which major music festival?

A) Coachella
B) Glastonbury
C) Woodstock
D) Lollapalooza

Correct Answer: A) Coachella

*/

 /*

    TestEntry historyTest[NUM_HISTORY] = {
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

    TestEntry geographyTest[NUM_GEOGRAPHY] = {
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

    TestEntry beyonceologyTest[NUM_BEYONCEOLOGY] = {
        {
        .question = "What year did Beyoncé release her debut solo album, \"Dangerously in Love\"?",
        .choices = {"2002", "2006", "2008", "2016"},
        .answerIdx = 0
        },
        {
        .question = "Which of these Beyoncé albums was released as a surprise without prior announcement in 2013?",
        .choices = {"BDay", "Lemonade", "4", "BEYONCÉ"},
        .answerIdx = 3
        },
        {
            .question = "Beyoncé was a member of which iconic girl group before her solo career?",
            .choices = {"The Pussycat Dolls", "Destiny's Child", "TLC", "En Vogue"},
            .answerIdx = 1
        },
        {
            .question = "In 2018, Beyoncé became the first Black woman to headline which major music festival?",
            .choices = {"Coachella", "Glastonbury", "Woodstock", "Lollapalooza"},
            .answerIdx = 0
        }

    };
*/

    string historyChoices1[5] = {"1939", "1946", "1912", "1945", ""};
    string historyChoices2[5] = {"Dwight B. Eisenhower", "Edward John Smith", "Frank Lloyd Wright", "William S. Burroughs", ""};
    string historyChoices3[5] = {"Marcus Junius Brutus", "Titus Livius", "Gaius Trebonius", "Pontius Aquila", ""};

    TestEntry historyTest[NUM_HISTORY] = {
        TestEntry("When did WW2 officially end?", historyChoices1, 3),
        TestEntry("Who was the captain of the Titanic?", historyChoices2, 1),
        TestEntry("Who killed Julius Caesar?", historyChoices3, 0)
    };

    // Initialize geography questions
    string geographyChoices1[5] = {"South Korea", "Hebei Province (China)", "Hong Kong", "Shanghai", ""};
    string geographyChoices2[5] = {"South America", "Antarctica", "Africa", "Australia", ""};
    string geographyChoices3[5] = {"Caribbean", "Mediterranean", "Philippine", "South China", ""};

    TestEntry geographyTest[NUM_GEOGRAPHY] = {
        TestEntry("Where does the Great Wall of China start?", geographyChoices1, 1),
        TestEntry("What continent is the country of Sudan located on?", geographyChoices2, 2),
        TestEntry("What is the largest sea on Earth?", geographyChoices3, 1)
    };

    string beyonceChoices1[5] = {"2002", "2006", "2008", "2016", ""};
    string beyonceChoices2[5] = {"BDay", "Lemonade", "4", "BEYONCÉ", ""};
    string beyonceChoices3[5] = {"The Pussycat Dolls", "Destiny's Child", "TLC", "En Vogue", ""};
    string beyonceChoices4[5] = {"Coachella", "Glastonbury", "Woodstock", "Lollapalooza", ""};

    TestEntry beyonceologyTest[NUM_BEYONCEOLOGY] = {
        TestEntry("What year did Beyoncé release her debut solo album, \"Dangerously in Love\"?", beyonceChoices1, 0),
        TestEntry("Which of these Beyoncé albums was released as a surprise without prior announcement in 2013?", beyonceChoices2, 3),
        TestEntry("Beyoncé was a member of which iconic girl group before her solo career?", beyonceChoices3, 1),
        TestEntry("In 2018, Beyoncé became the first Black woman to headline which major music festival?", beyonceChoices4, 0)
    };

char fname[] = "./temp.json";
read_test_file(*fname);


    int choice;
    printf("Choose a test:\n");
    printf("1. History\n");
    printf("2. Geography\n");
    printf("3. Beyoncéology\n");
    printf("Enter your choice (enter the number for the test you wish to take): ");
    scanf("%d", &choice);

    TestEntry* selectedTest = NULL;
    int numQuestions = 0;

    if (choice == 1) {
        selectedTest = historyTest;
        numQuestions = NUM_HISTORY;
    } else if (choice == 2) {
        selectedTest = geographyTest;
        numQuestions = NUM_GEOGRAPHY;
    } else if (choice == 3 ) {
        selectedTest = beyonceologyTest;
        numQuestions = NUM_BEYONCEOLOGY;
    } else {
        printf("Invalid choice.\n");
        return 1;
    }

    int correct = 0;
/*
    for (int i = 0; i < numQuestions; i++) {
        printf("\nQ%d: %s\n", i + 1, selectedTest[i].question);
        for (int j = 0; j < 4; j++) {
            // Below prints the question out with alphabetic index. To iterate each option, we are adding to the 
            // ASCII value of 'a', and if we are incrementing up to for, 'a' + 1 will be 'b', because 
            // ASCII value of 'a' is 97, so 'b' will be 98, so on and so forth
            printf("  %c. %s\n", 'a' + j, selectedTest[i].choices[j]);
        }
*/

for (int i = 0; i < numQuestions; i++) {
    cout << "\nQ" << i+1 << ": " << selectedTest[i].getQuestion() << "\n";
    for (int j = 0; j < 4; j++) {
        cout << "  " << char('a'+j) << ". " << selectedTest[i].getChoice(j) << "\n";
    }

        char userAnswer;
        printf("Your answer (a-d): ");
        scanf(" %c", &userAnswer);  

        int userIdx = userAnswer - 'a'; // here we are getting the absolute index of the answer with respect to our multiple choice array.
                                        // subtracting 'a', or 97 will give us the index of the answer relative to our choice arrays we defined
                                        // in our structs at program entry
        if (userIdx == selectedTest[i].getAnswerIdx()) {
            correct++;
        } else {
            continue;
        }
    }
    printf("\nYou scored %d out of %d questions right.\nScore: %d/%d\n", correct, numQuestions, correct, numQuestions);

}
