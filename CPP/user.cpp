#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <string>
// #include "quiz-question.h"
using namespace std;

class User
{
public:
    string username;
    string password;
    bool isExist;
    float accuracy;
    int score;
    int timer;
    vector<string> quiz_attempts;

    User(string username, string password) : username(username), isExist(false), password(password), score(0), accuracy(0), timer(60) {};

    bool userValidation()

    {
        ifstream file("../CSV-Files/user.csv");
        string line;
        if (!file.is_open())
        {
            cout << "Failed to open file!" << endl;
        }

        bool isFirstLine = true; // To skip the header row

        while (getline(file, line))
        {
            if (isFirstLine)
            { // Skip the header
                isFirstLine = false;
                continue;
            }

            stringstream ss(line);
            string id, name, userpassword;

            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, userpassword);

            if (name == username)
            {
                isExist = true;
            }
            // Compare with the target username
            if (name == username && userpassword == password)
            {
                file.close();
                return true; // Username found
            }
        }

        file.close();
        return false; // Username not found
    }

    bool addNewUsername()
    {
        userValidation();
        if (isExist)
        {
            return false;
        }

        // Open file for reading to find the last ID
        ifstream inFile("../CSV-Files/user.csv");
        if (!inFile.is_open())
        {
            cout << "Error: Could not open file for reading!" << endl;
            return false;
        }

        string line, lastLine;
        while (getline(inFile, line))
        {
            if (!line.empty())
            {
                lastLine = line; // Save the last non-empty line
            }
        }
        inFile.close();

        int newID = 1; // Default ID if file is empty or invalid
        if (!lastLine.empty())
        {
            stringstream ss(lastLine);
            string idStr;
            getline(ss, idStr, ','); // Get the first value (ID)
            try
            {
                newID = stoi(idStr) + 1; // Increment ID
            }
            catch (...)
            {
                newID = 1; // Fallback if conversion fails
            }
        }

        // Check if the last character is a newline before appending
        inFile.open("../CSV-Files/user.csv", ios::in | ios::binary);
        char lastChar = '\n'; // Default to newline if file is empty
        if (inFile.is_open())
        {
            inFile.seekg(-1, ios::end);
            inFile.get(lastChar);
            inFile.close();
        }

        ofstream outFile("../CSV-Files/user.csv", ios::app);
        if (!outFile.is_open())
        {
            cout << "Error: Could not open file for writing!" << endl;
            return false;
        }

        if (lastChar != '\n')
        {
            outFile << '\n'; // Ensure there's a newline before appending
        }

        // Append the new entry
        outFile << newID << "," << username << "," << password << endl;
        outFile.close();

        return true;
    }

    // void setTimer(Difficulty difficulty)
    // {
    //     switch (difficulty)
    //     {
    //     case BEGINNER:
    //         timer = 80;
    //         break;
    //     case INTERMEDIATE:
    //         timer = 120;
    //         break;
    //     case ADVANCED:
    //         timer = 150;
    //         break;
    //     default:
    //         timer = 60;
    //         break;
    //     }
    // }

    // void take_quiz(Quiz &quiz, string category, Difficulty difficulty, int num_questions)
    // {

    //     switch (difficulty)
    //     {
    //     case BEGINNER:
    //         num_questions = 10;
    //         break;
    //     case INTERMEDIATE:
    //         num_questions = 25;
    //         break;
    //     case ADVANCED:
    //         num_questions = 20;
    //         break;
    //     default:
    //         num_questions = 10;
    //         break;
    //     }

    //     setTimer(difficulty);
    //     vector<Question> randomized_questions = quiz.getRandomQuestions(category, difficulty, num_questions);
    //     int correct_answers = 0;
    //     time_t start_time = time(0);
    //     time_t end_time = start_time + timer;

    //     cout << "You have " << timer << " seconds to complete the quiz.\n";

    //     while (time(0) > end_time)
    //     {
    //         for (size_t i = 0; i < randomized_questions.size(); ++i)
    //         {
    //             const auto &question = randomized_questions[i];
    //             cout << "Question " << i + 1 << ": " << question.getQuestionText() << endl;
    //             const auto &options = question.getOptions();
    //             for (size_t j = 0; j < options.size(); ++j)
    //             {
    //                 cout << "  " << j + 1 << ". " << options[j] << endl;
    //             }

    //             int user_answer;
    //             cout << "Your answer (1-4): ";
    //             cin >> user_answer;

    //             if (user_answer == question.getCorrectAnswer())
    //             {
    //                 ++correct_answers;
    //             }

    //             question.feedback(user_answer);
    //         }

    //         if (time(0) > end_time)
    //         {
    //             cout << "Time's up!\n";
    //             break;
    //         }
    //     }

    //     score = correct_answers;
    //     accuracy = (double)score / randomized_questions.size() * 100;

    //     cout << "\nQuiz Complete!\n";
    //     cout << "Your Score: " << score << " out of " << randomized_questions.size() << "\n";
    //     cout << "Accuracy: " << accuracy << "%\n";

    //     cout << "\nDetailed Report:\n";
    //     for (const auto &question : randomized_questions)
    //     {
    //         cout << "Question: " << question.getQuestionText() << "\n";
    //         const auto &options = question.getOptions();
    //         for (size_t i = 0; i < options.size(); ++i)
    //         {
    //             cout << "  " << i + 1 << ". " << options[i] << endl;
    //         }
    //         cout << "Correct Answer: " << options[question.getCorrectAnswer() - 1] << endl;
    //         cout << "----------------------\n";
    //     }

    //     stringstream ss;
    //     ss << "Category: " << category << ", Difficulty: " << difficultyToString(difficulty)
    //        << ", Score: " << score << ", Accuracy: " << accuracy << "%" << endl;

    //     for (const auto &question : randomized_questions)
    //     {
    //         ss << "Question: " << question.getQuestionText() << "\n";
    //         const auto &options = question.getOptions();
    //         for (size_t i = 0; i < options.size(); ++i)
    //         {
    //             ss << "  " << i + 1 << ". " << options[i] << endl;
    //         }
    //         ss << "Correct Answer: " << options[question.getCorrectAnswer() - 1] << endl;
    //         ss << "----------------------\n";
    //     }

    //     quiz_attempts.push_back(ss.str());
    // }
};
