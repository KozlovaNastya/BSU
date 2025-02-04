# Quiz Game

This is a simple console-based quiz game written in C++ that loads questions from a text file and asks the user a random selection of questions. The user answers the questions, and at the end, their score is displayed based on how many questions they answered correctly.

## Features

- Loads questions and answers from a text file (`test.txt`).
- Displays a random selection of 10 questions from a total of 26 questions.
- Prompts the user to answer each question and provides feedback on whether their answer is correct.
- Calculates and displays the user's score out of 10.

## Requirements

- C++11 or later
- A file named `test.txt` that contains the questions and answers in a specific format (explained below).
  
## File Format (`test.txt`)

The questions should be stored in a text file named `test.txt` in the following format:

Question text? Answer option 1; Answer option 2; Answer option 3; Answer option 4; Correct answer index (1-based);

### Example:

What is the capital of France? Paris; London; Berlin; Madrid; 1;  
What is 2 + 2? 3; 4; 5; 6; 2;  
What is the capital of France? Paris; London; Berlin; Madrid; 1;

- Each question starts with the question text on its own line.
- The answers for each question are listed on separate lines, with each option followed by a semicolon (`;`).
- The last line contains the index of the correct answer (starting from 1).

## Code Explanation

1. **Questions Structure**: A structure `Questions` is used to store each question's text, a list of answer options, and the index of the correct answer.
   
2. **Loading Questions**: The function `LoadQuestions()` reads the `test.txt` file and loads the questions into a vector of `Questions` structures. It assumes that the file format is consistent with the format described above.
   
3. **Asking Questions**: The function `askQuestion()` displays a question and its possible answers to the user, prompts for an answer, and checks if the answer is correct.

4. **Displaying the Result**: After the quiz ends, the function `displayResult()` calculates and displays the user's score based on how many questions they answered correctly.

5. **Randomization**: The questions are shuffled using `std::random_shuffle` to ensure a different order each time the quiz is played.

6. **Main Function**: The main function:
   - Loads the questions from the file.
   - Shuffles the questions.
   - Asks the user 10 questions from the list.
   - Tracks the number of correct answers and displays the score at the end.

## Example Output
Question 1: What is the capital of France?

Paris  
London  
Berlin  
Madrid  
Your answer (enter the option number in order): 1 Correct!
Question 2: What is 2 + 2?

3  
4  
5  
6  
Your answer (enter the option number in order): 2 Correct!  
...  
You answered correctly 8 out of 10 questions. Your score: 8.0

## Notes

- The program selects 10 random questions from the file. The total number of questions in the file should be at least 10, but the program can handle more questions.
- The quiz will display feedback after each question and calculate the final score at the end.
- The questions and answers should be formatted correctly in the `test.txt` file for the program to function properly.
