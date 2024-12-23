#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>
#include "quiz-question.h"
#include "admin.cpp"
#include "mainFunction.cpp"
using namespace std;



int main(int argc, char const *argv[])
{
    while (true)
    {
        int mainOptionMode = 0;
        int isTrue = false;

        mainMenu:
        clearTerminal();
        cout << "--- Choose Option Mode ---\n" << endl;
        cout << "1. Admin" << endl;
        cout << "2. User" << endl;
        cout << "3. Exit\n" << endl;
        cout << "Enter here: ";
        cin >> mainOptionMode;
        if(mainOptionMode == 1)
        {
            clearTerminal();
            while (true)
            {
                //Get admin name
                string mainPassword;
                Admin *admin = new Admin();
                clearTerminal();
                cout << "--- Security Check ---\n" << endl;
                cout << "Enter the password: ";
                cin >> mainPassword;

                // remove the end character of mainPassword
                bool isCorrect = admin->checkMainPassowrd(mainPassword);
                if (isCorrect == true)
                {
                    fflush(stdin);
                    clearTerminal();
                    cout << "*** Access Granted ***";
                    sleep(1.5);
                while (true)
                    {
                        int loginOption;
                        clearTerminal();
                        cout << "*** Welcome ***\n"  << endl;
                        cout << "=== Please choose an option ===\n" << endl;
                        cout << "1. Create Quiz" << endl;
                        cout << "2. Delete Quiz" << endl;
                        cout << "3. Update Quiz" << endl;
                        cout << "4. Back\n" << endl;
                        cout << "Enter here: ";
                        cin >> loginOption;
                        if (loginOption == 1)
                        {
                            // Create Quiz
                            clearTerminal();
                            int quizID;
                            string quizTitle;
                            cout << "--- Create Quiz ---\n" << endl;
                            cout << "Enter Quiz ID: ";
                            cin >> quizID;
                            cout << "Enter Quiz Title: ";
                            cin.ignore();
                            getline(cin, quizTitle);

                            Quiz quiz(quizID, quizTitle);

                            int numQuestions;
                            cout << "How many questions do you want to add? ";
                            cin >> numQuestions;

                            for (int i = 0; i < numQuestions; i++)
                            {
                                clearTerminal();
                                cout << "--- Add Question " << (i + 1) << " ---\n" << endl;
                                int questionID;
                                string questionText;
                                int correctAnswer;
                                vector<string> options;
                                vector<string> categories;
                                string tempOption;

                                cout << "Enter Question ID: ";
                                cin >> questionID;
                                cin.ignore();
                                cout << "Enter Question Text: ";
                                getline(cin, questionText);

                                for (int j = 0; j < 4; j++)
                                {
                                    cout << "Enter Option " << (j + 1) << ": ";
                                    getline(cin, tempOption);
                                    options.push_back(tempOption);
                                }

                                cout << "Enter the number of the correct option (1-4): ";
                                cin >> correctAnswer;

                                cin.ignore();
                                string category;
                                cout << "Enter Question Category: ";
                                getline(cin, category);
                                categories.push_back(category);

                                int difficultyInput;
                                cout << "Select Difficulty (1 = BEGINNER, 2 = INTERMEDIATE, 3 = ADVANCED): ";
                                cin >> difficultyInput;
                                Difficulty difficulty = static_cast<Difficulty>(difficultyInput - 1);

                                Question question(questionID, questionText, options, categories, correctAnswer - 1, difficulty);
                                quiz.addQuestion(question);
                            }

                            string filename = "../CSV-Files/quiz_" + to_string(quizID) + ".csv";
                            quiz.saveToFile(filename);
                            cout << "\nQuiz created and saved successfully." << endl;
                            pause();
                        }
                        else if (loginOption == 2)
                        {
                            // Delete Quiz
                            clearTerminal();
                            int quizID;
                            cout << "--- Delete Quiz ---\n" << endl;
                            cout << "Enter Quiz ID: ";
                            cin >> quizID;
                            string filename = "../CSV-Files/quiz_" + to_string(quizID) + ".csv";
                            if (remove(filename.c_str()) == 0)
                            {
                                cout << "Quiz deleted successfully." << endl;
                            }
                            else
                            {
                                cout << "Error: Quiz not found." << endl;
                            }
                            pause();
                        }
                        else if (loginOption == 3)
                        {
                            // // Update Quiz
                            // clearTerminal();
                            // int quizID;
                            // cout << "--- Update Quiz ---\n" << endl;
                            // cout << "Enter Quiz ID: ";
                            // cin >> quizID;
                            // string filename = "../CSV-Files/quiz_" + to_string(quizID) + ".csv";

                            // Quiz quiz(quizID, "");
                            // quiz.loadFromFile(filename);

                            // int questionID;
                            // cout << "Enter Question ID to update: ";
                            // cin >> questionID;

                            // for (auto& question : quiz.getRandomQuestions("", BEGINNER, quiz.getQuestions().size()))
                            // {
                            //     if (question.getId() == questionID)
                            //     {
                            //         clearTerminal();
                            //         cout << "--- Update Question ---\n" << endl;
                            //         int correctAnswer;
                            //         vector<string> options;
                            //         string tempOption;

                            //         cin.ignore();
                            //         cout << "Enter updated Question Text: ";
                            //         getline(cin, question.getQuestionText());

                            //         for (int j = 0; j < 4; j++)
                            //         {
                            //             cout << "Enter updated Option " << (j + 1) << ": ";
                            //             getline(cin, tempOption);
                            //             options.push_back(tempOption);
                            //         }

                            //         cout << "Enter the updated number of the correct option (1-4): ";
                            //         cin >> correctAnswer;
                            //         question.getCorrectAnswer() = correctAnswer - 1;

                            //         quiz.updateQuestion(question);
                            //         quiz.saveToFile(filename);

                            //         cout << "Question updated successfully." << endl;
                            //         pause();
                            //         break;
                            //     }
                            // }
                        }                                            
                        else if (loginOption == 4)
                        {
                            break;
                        }
                        else
                        {
                            cout << "Wrong Input!!" << endl;
                            sleep(2);
                        }
                    }                    
                    
                }
                else
                {
                    cout << "Wrong Password!!" << endl;
                    pause();
                    break;
                }
                
            }
        }
        else if (mainOptionMode == 2)
        {
            /* code */
        }
        else if (mainOptionMode == 3)
        {
            break;
        }
        else
        {
            cout << "Invalid option!!" << endl;
            pause();
        }
    }

    return 0;
}
