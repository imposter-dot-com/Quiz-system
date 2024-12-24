#include <iostream>
#include <unistd.h>
#include <fstream>
#include "admin.cpp"
#include "mainFunction.cpp"
#include "user.cpp"
#include "quiz-question.h"
using namespace std;

int main(int argc, char const *argv[])
{
    while (true)
    {
        int optionMode = 0;
        int isTrue = false;
        int selected = 0;
        int newselected = 0;

    mainMenu:
        clearTerminal();
        cout << "---Choose Option Mode---\n"
             << endl;
        cout << "1. Admin" << endl;
        cout << "2. User" << endl;
        cout << "3. Exit\n"
             << endl;
        cout << "Enter here: ";
        cin >> optionMode;
        if (optionMode == 1)
        {
            clearTerminal();
            while (true)
            {
                // Get admin name
                string mainPassword;
                Admin *admin = new Admin();
                clearTerminal();
                cout << "---Security Check---\n"
                     << endl;
                cout << "Enter the password: ";
                cin >> mainPassword;

                // remove the end character of mainPassword
                mainPassword.pop_back();
                bool isCorrect = admin->checkMainPassowrd(mainPassword);
                if (isCorrect == true)
                {
                    clearTerminal();
                    cout << "*** Access Granted ***";
                    sleep(2);
                    while (true)
                    {
                        // Choose an option
                        string adminFileName = "admin.csv";
                        fstream adminFile;
                        int adminMode;
                        clearTerminal();
                        cout << "---Please Choose an Option---\n"
                             << endl;
                        cout << "1. Create New Admin" << endl;
                        cout << "2. Log In" << endl;
                        cout << "3. Delete an Admin" << endl;
                        cout << "4. Back" << endl;
                        cout << "5. Exit\n"
                             << endl;
                        cout << "Enter here: ";
                        cin >> adminMode;

                        if (adminMode == 1)
                        {
                        }
                        else if (adminMode == 2)
                        {
                        }
                        else if (adminMode == 3)
                        {
                        }
                        else if (adminMode == 4)
                        {
                            goto mainMenu;
                        }
                        else if (adminMode == 5)
                        {
                            return 0;
                        }
                        else
                        {
                            cout << "Invalid option!!" << endl;
                            cout << "Press ENTER to continue...";
                            fflush(stdin);
                            cin.get();
                        }
                    }
                }
                else
                {
                    cout << "Invalid Password" << endl;
                    cout << "Press ENTER to continue...";
                    fflush(stdin);
                    cin.get();
                    break;
                }
            }
        }
        else if (optionMode == 2)
        {
            clearTerminal();
            while (true)
            {
                cout << "---Please Choose an Option---\n"
                     << endl;
                cout << "1. Sign In" << endl;
                cout << "2. Create New Account" << endl;
                cout << "3. Exit\n"
                     << endl;
                cout << "Enter here: ";

                cin >> selected;

                if (selected == 1)
                {
                    clearTerminal();
                    while (true)
                    {
                        string inputUsername;
                        string inputpassword;
                        cout << "---Login in with username---\n"
                             << endl;
                        cout << "Enter username: ";
                        cin >> inputUsername;
                        cout << "Enter password: ";
                        cin >> inputpassword;
                        User *user = new User(inputUsername, inputpassword);

                        bool isAuth = user->userValidation();

                        if (isAuth)
                        {
                            clearTerminal();
                            cout << "*** Access Granted ***";
                            sleep(1);
                            while (true)
                            {
                                clearTerminal();
                                int quizSelected;
                                cout << "---Please choose a quiz---\n";
                                cout << "1. Data Structure and Algorithm" << endl;
                                cout << "2. Web Design" << endl;
                                cout << "3. AI" << endl;
                                cout << "4. Data Science \n"
                                     << endl;
                                cout << "Enter here: ";
                                cin >> quizSelected;

                                if (quizSelected == 1 || quizSelected == 2 || quizSelected == 3 || quizSelected == 4)
                                {
                                    clearTerminal();
                                    while (true)
                                    {
                                        int quizChoice = 0;
                                        cout << "---Please select--- \n"
                                             << endl;
                                        cout << "1. Take a quiz" << endl;
                                        cout << "2. Get quiz history \n"
                                             << endl;
                                        cout << "Enter here:";
                                        cin >> quizChoice;

                                        // Quiz *quiz = new Quiz(quizSelected);

                                        if (quizChoice == 1)
                                        {
                                            // quiz.take_quiz();
                                            cout << "take quiz";
                                        }
                                        else if (quizChoice == 2)
                                        {
                                            // quiz.generate_history();
                                            cout << "history";
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            clearTerminal();
                            cout << "Username or password is incorrect \n \n";
                        }
                    }
                }
                else if (selected == 2)
                {
                    clearTerminal();
                    while (true)
                    {
                        string newUsername;
                        string password;
                        bool isDone;
                        cout << "---Create New Account---\n"
                             << endl;
                        cout << "Enter new username: ";
                        cin >> newUsername;
                        cout << "Enter password: ";
                        cin >> password;
                        User *userNew = new User(newUsername, password);

                        isDone = userNew->addNewUsername();

                        if (isDone)
                        {
                            clearTerminal();
                            cout << "New user has been added successfully. \n"
                                 << endl;
                            sleep(2);
                            while (true)
                            {
                                clearTerminal();
                                int quizSelected;
                                cout << "---Please choose a quiz---\n";
                                cout << "1. Data Structure and Algorithm" << endl;
                                cout << "2. Web Design" << endl;
                                cout << "3. AI" << endl;
                                cout << "4. Data Science \n"
                                     << endl;
                                cout << "Enter here: ";
                                cin >> quizSelected;

                                if (quizSelected == 1 || quizSelected == 2 || quizSelected == 3 || quizSelected == 4)
                                {
                                    clearTerminal();
                                    while (true)
                                    {
                                        int quizChoice = 0;
                                        cout << "---Please select--- \n"
                                             << endl;
                                        cout << "1. Take a quiz" << endl;
                                        cout << "2. Get quiz history \n"
                                             << endl;
                                        cout << "Enter here:";
                                        cin >> quizChoice;

                                        // Quiz *quiz = new Quiz(quizSelected);

                                        if (quizChoice == 1)
                                        {
                                            // quiz.take_quiz();
                                            cout << "take quiz";
                                        }
                                        else if (quizChoice == 2)
                                        {
                                            // quiz.generate_history();
                                            cout << "history";
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            clearTerminal();
                            cout << "Username already exists. Please enter another username \n \n";
                        }
                    }
                }
                else if (selected == 3)
                {
                    break;
                }
                else
                {
                    cout << "Invalid selection!" << endl;
                }
            }
        }
        else if (optionMode == 3)
        {
            break;
        }
        else
        {
            cout << "Invalid option!!" << endl;
            cout << "Press ENTER to continue...";
            fflush(stdin);
            cin.get();
        }
    }
    return 0;
}
