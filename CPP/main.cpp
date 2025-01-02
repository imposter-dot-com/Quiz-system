#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>
#include "adminAccount.h"
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
        cout << "Welcome to Quiz's system\n";
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
                string mainPassword;
                AdminAccount *admin = new Admin();
                clearTerminal();
                cout << "--- Security Check ---\n" << endl;
                cout << "Enter the password: ";
                cin >> mainPassword;

                bool isCorrect = admin->checkMainPassowrd(mainPassword);
                if (isCorrect)
                {
                    fflush(stdin);
                    clearTerminal();
                    cout << "*** Access Granted ***\n";
                    sleep(1.5);

                    // Initialize quiz system
                    Quiz mainQuiz(1, "Main Quiz"); // Create a default quiz
                    string filename = "quiz_data.csv"; // File to store quiz data
                    mainQuiz.loadFromFile(filename); // Load existing quiz data if any

                    while (true)
                    {
                        int adminOption;
                        clearTerminal();
                        cout << "*** Welcome Admin ***\n" << endl;
                        cout << "=== Please choose an option ===\n" << endl;
                        cout << "1. Create Quiz Question" << endl;
                        cout << "2. Delete Quiz Question" << endl;
                        cout << "3. Update Quiz Title" << endl;
                        cout << "4. Display All Questions" << endl;
                        cout << "5. Back to Main Menu\n" << endl;
                        cout << "Enter here: ";
                        cin >> adminOption;

                        switch(adminOption) {
                            case 1: {
                                // Create new question
                                string questionText, category;
                                vector<string> options;
                                vector<string> categories;
                                int correctAnswer;
                                string difficultyStr;

                                cin.ignore();
                                cout << "Enter question text: ";
                                getline(cin, questionText);

                                cout << "Enter category: ";
                                getline(cin, category);
                                categories.push_back(category);

                                cout << "Enter 4 options:\n";
                                for(int i = 0; i < 4; i++) {
                                    string option;
                                    cout << "Option " << (i+1) << ": ";
                                    getline(cin, option);
                                    options.push_back(option);
                                }

                                cout << "Enter correct answer (1-4): ";
                                cin >> correctAnswer;

                                cout << "Enter difficulty (BEGINNER/INTERMEDIATE/ADVANCED): ";
                                cin >> difficultyStr;

                                Question newQuestion(0, questionText, options, categories, 
                                                   correctAnswer, stringToDifficulty(difficultyStr));
                                mainQuiz.addQuestion(newQuestion);
                                mainQuiz.saveToFile(filename);
                                cout << "Question added successfully!\n";
                                pause();
                                break;
                            }
                            case 2: {
                                // Delete question
                                int questionId;
                                mainQuiz.displayQuiz();
                                cout << "\nEnter question ID to delete: ";
                                cin >> questionId;
                                mainQuiz.removeQuestion(questionId);
                                mainQuiz.saveToFile(filename);
                                cout << "Question deleted successfully!\n";
                                pause();
                                break;
                            }
                            case 3: {
                                // Update quiz title
                                string newTitle;
                                cout << "Enter new quiz title: ";
                                cin.ignore();
                                getline(cin, newTitle);
                                mainQuiz = Quiz(1, newTitle); // Create new quiz with updated title
                                mainQuiz.saveToFile(filename);
                                cout << "Quiz title updated successfully!\n";
                                pause();
                                break;
                            }
                            case 4: {
                                // Display all questions
                                clearTerminal();
                                cout << "=== All Quiz Questions ===\n\n";
                                mainQuiz.displayQuiz();
                                pause();
                                break;
                            }
                            case 5:
                                goto mainMenu;
                            default:
                                cout << "Invalid option!\n";
                                pause();
                        }
                    }
                }
                else
                {
                    cout << "Wrong Password!!" << endl;
                    pause();
                    break;
                }
                delete admin;
            }
        }
        else if (mainOptionMode == 2)
        {
            // User mode implementation here
            cout << "User mode not implemented yet.\n";
            pause();
        }
        else if (mainOptionMode == 3)
        {
            cout << "Thank you for using the Quiz System!\n";
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