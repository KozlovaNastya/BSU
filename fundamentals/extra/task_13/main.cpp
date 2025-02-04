#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

// Structure to store question data
struct Questions {
    std::string questionText;  // String with the text of the question
    std::vector<std::string> answers;  // Vector of answer options 
    int correctAnswerIndex;  // Index of the correct answer
};

std::vector<Questions> LoadQuestions() {
    // Function where questions are loaded into the vector
    std::vector<Questions> questions;
    std::ifstream test("test.txt");  // Open the file test.txt

    if (!test.is_open()) {
        std::cerr << "Error: could not open file test.txt" << std::endl;
        return questions; // If the file didn't open, return an empty vector
    }

    std::string line;
    while (std::getline(test, line)) { // Stream read from the file
        if (line.empty()) continue;  // Skip empty lines

        Questions question; // Instance of our structure
        question.questionText = line;  // Initialize the field of the structure

        // Read answer options until a number is encountered, it is assumed that the number is the answer index
        while (std::getline(test, line) && line[0] != '0' && line[0] != '1' && line[0] != '2') {
            question.answers.push_back(line.substr(0, line.size() - 1)); // Remove the last ';'
        }

        // Read the index of the correct answer
        question.correctAnswerIndex = std::stoi(line); // Convert to index (string to int)

        questions.push_back(question);  // Add the question to the vector of questions
    }

    test.close();  // Close the file
    return questions;
}

bool askQuestion(const Questions& question) {
    std::cout << question.questionText << "\n"; // Display the question text on the screen
    for (size_t i = 0; i < question.answers.size(); ++i) {  // Display all our answers in order
        std::cout << question.answers[i] << "\n";
    }

    int answer;
    std::cout << "Your answer (enter the option number in order): ";
    std::cin >> answer;
    // Check for valid input
    return (answer - 1) == question.correctAnswerIndex;
}

// Function to display the final grade based on the number of correct answers and total questions
void displayResult(int correctAnswers, int totalQuestions) {
    double score = (static_cast<double>(correctAnswers) / totalQuestions) * 10; // Convert correctAnswers to double
    std::cout << "You answered correctly " << correctAnswers << " out of " << totalQuestions << " questions.\n";
    std::cout << "Your score: " << score << "\n";
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(0))); // For generating random numbers
    // Load questions from the file into the vector
    std::vector<Questions> questions = LoadQuestions();

    std::random_shuffle(questions.begin(), questions.end());  // Shuffle the questions

    int correctAnswers = 0;

    // Ask 10 questions out of 26 to the user
    for (int i = 0; i < 10; ++i) {
        std::cout << "\nQuestion " << (i + 1) << ":\n";
        if (askQuestion(questions[i])) {
            std::cout << "Correct!\n";
            ++correctAnswers;
        }
        else {
            std::cout << "Incorrect!\n";
        }
    }

    // Display the final grade
    displayResult(correctAnswers, 10);

    return 0;
}
