#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <limits>
#include "adminAccount.h"
#include "quiz-question.h" 
#include "user.h"

using namespace std;

void clearTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


int main() {
    AdminAccount admin;
    Quiz quiz;
    User user;
    string questionFile = "../CSV-Files/questions.csv";
    string reportFile = "../CSV-Files/report.csv";
    quiz.loadFromFile();

    while (true) {
        int mainOptionMode = 0;

        // Main Menu
        clearTerminal();
        cout << "--- Choose Option Mode ---\n" << endl;
        cout << "1. Admin" << endl;
        cout << "2. User" << endl;
        cout << "3. Exit\n" << endl;
        cout << "Enter here: ";
        cin >> mainOptionMode;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 


        if (mainOptionMode == 1) {
            clearTerminal();

            cout << "--- Admin Login ---\n" << endl;
            admin.login();

            MainMenu:
            while (true) {
                int adminOption = 0;
                clearTerminal();
                cout << "--- Admin Page ---\n" << endl;
                cout << "1. Create New Admin Account" << endl;
                cout << "2. Change Password" << endl;
                cout << "3. Manage Questions" << endl;
                cout << "4. View User Reports" << endl;
                cout << "5. Back to Main Menu" << endl;
                cout << "6. Exit\n" << endl;
                cout << "Enter here: ";
                cin >> adminOption;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

                switch (adminOption) {
                    case 1:
                        admin.createAdminAccount();
                        break;
                    case 2:
                        admin.changePassword();
                        break;
                    case 3: {
                        int questionOption = 0;
                        clearTerminal();
                        cout << "--- Manage Questions ---\n" << endl;
                        cout << "1. Create Question" << endl;
                        cout << "2. Delete Question" << endl;
                        cout << "3. View All Questions" << endl;
                        cout << "4. Update Question" << endl;
                        cout << "5. Back\n" << endl;
                        cout << "Enter here: ";
                        cin >> questionOption;

                        switch (questionOption) {
                            case 1: {
                                // Add a new question
                                Question question = quiz.createQuestionInteractively();
                                quiz.addQuestion(question);
                                cout << "Question added successfully!\n";
                                break;
                            }
                            case 2: {
                                // Delete a question
                                int questionID;
                                cout << "Enter the Question ID to delete: ";
                                cin >> questionID;
                                quiz.removeQuestion(questionID);
                                break;
                            }
                            case 3: {
                                // View all questions
                                quiz.displayAllQuestions(questionFile);
                                
                                cout << "Press Enter to return to the Manage Questions menu..." << endl;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                                cin.get(); // Wait for user to press Enter
                                break;
                            }
                            case 4: {
                                // Update a question
                                while (true) {
                                    int questionID;
                                    cout << "Enter the Question ID to update (or enter -1 to go back): ";
                                    cin >> questionID;

                                    if (questionID == -1) {
                                        break; // Exit the loop and go back to the menu
                                    }

                                    if (!quiz.questionExists(questionID)) {
                                        cout << "Question ID " << questionID << " does not exist. Please try again or enter -1 to go back." << endl;
                                        continue; // Ask for the ID again
                                    }

                                    // If the ID exists, get the updated question details
                                    Question updatedQuestion = quiz.createQuestionInteractively();
                                    updatedQuestion.setId(questionID); // Use the same ID
                                    quiz.updateQuestion(updatedQuestion);
                                    break; // Exit the loop after a successful update
                                }
                                break;
                            }
                            case 5:
                                break;
                            default:
                                cout << "Invalid option!\n";
                        }
                        break;
                    }
                    case 4:   
                        clearTerminal();
                        user.displayReport();
                        cout << "Press Enter to return to the Admin Menu..." << endl;
                        cin.get();
                    case 5:
                        goto MainMenu;
                    case 6:
                        cout << "Exiting program. Goodbye!\n";
                        return 0;
                    default:
                        cout << "Invalid option! Please try again.\n";
                        sleep(2);
                }
            }
        } else if (mainOptionMode == 2) {
            clearTerminal();
            userMenu();
        } else if (mainOptionMode == 3) {
            cout << "Thank you for using the system. Goodbye!\n";
            break;
        } else {
            cout << "Invalid option! Please try again.\n";
        }
    }

    return 0;
}
