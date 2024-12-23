// #include <iostream>
// #include <unistd.h>
// #include <fstream>
// #include <string>
// #include <sstream>
// #include "quiz-question.h"
// #include "admin.cpp"
// #include "mainFunction.cpp"
// using namespace std;



// int main(int argc, char const *argv[])
// {
//     while (true)
//     {
//         int mainOptionMode = 0;
//         int isTrue = false;

//         mainMenu:
//         clearTerminal();
//         cout << "--- Choose Option Mode ---\n" << endl;
//         cout << "1. Admin" << endl;
//         cout << "2. User" << endl;
//         cout << "3. Exit\n" << endl;
//         cout << "Enter here: ";
//         cin >> mainOptionMode;
//         if(mainOptionMode == 1)
//         {
//             clearTerminal();
//             while (true)
//             {
//                 //Get admin name
//                 string mainPassword;
//                 Admin *admin = new Admin();
//                 clearTerminal();
//                 cout << "--- Security Check ---\n" << endl;
//                 cout << "Enter the password: ";
//                 cin >> mainPassword;

//                 // remove the end character of mainPassword
//                 bool isCorrect = admin->checkMainPassowrd(mainPassword);
//                 if (isCorrect == true)
//                 {
//                     fflush(stdin);
//                     clearTerminal();
//                     cout << "*** Access Granted ***";
//                     sleep(1.5);
//                     string adminFileName = "../CSV-Files/admin.csv";
//                     fstream adminFile;
//                     if(admin->gatherAdminFile(adminFile, adminFileName) == false)
//                     {
//                         cout << "Can't Open File";
//                         sleep(1.5);
//                         break;
//                     }
//                     while (true)
//                     {
//                         // Choose an option
//                         // Gather all the info from admin file
//                         int adminMode;
//                         clearTerminal();
//                         cout << "--- Please Choose an Option ---\n" << endl;
//                         cout << "1. Create a New Admin" << endl;
//                         cout << "2. Delete an Admin" << endl;
//                         cout << "3. Display All Admins" << endl;
//                         cout << "4. Log In" << endl;
//                         cout << "5. Back" << endl;
//                         cout << "6. Exit\n" << endl;
//                         cout << "Enter here: ";
//                         cin >> adminMode;

//                         // Create a new admin
//                         if(adminMode == 1)
//                         {
                            
//                             while (true)
//                             {
//                                 /* code */
//                                 string newAdminName;
//                                 int tempID;
//                                 clearTerminal();
//                                 cout << "--- Creating a new Admin ---\n" << endl;
//                                 cout << "Enter your name: ";
//                                 cin >> newAdminName;
//                                 if(admin->checkName(newAdminName) == false)
//                                 {
//                                     int tempID = admin->getNextAvailableID();
//                                     string strTempID = to_string(tempID);
//                                     string newAdminPassword;
//                                     // enter password
//                                     clearTerminal();
//                                     cout << "--- Creating a new Admin ---\n" << endl;
//                                     cout << "Enter your password: ";
//                                     cin >> newAdminPassword;

//                                     // Add the entered element in the linked list
//                                     admin->insertEnd(strTempID, newAdminName, newAdminPassword);
                                    
//                                     // Add the the info to the file
//                                     admin->addNewAdmin(adminFile, adminFileName, strTempID, newAdminName, newAdminPassword);
//                                     adminFile.close();
//                                     clearTerminal();
//                                     cout << "*** New admin have been created successfully ***";
//                                     sleep(1.5);
//                                     break;
//                                 }
                                
//                                 else
//                                 {
//                                     cout << "Name Already Taken!" << endl;
//                                     sleep(2);
//                                 }
//                             }

//                         }

//                         // Delete an admin
//                         else if (adminMode == 2)
//                         {
//                             while (true)
//                             {
                                
//                                 string delAdminID;
//                                 string delAdminPassword;
//                                 clearTerminal();
//                                 cout << "--- Deleting an Admin ---\n" << endl;
//                                 cout << "Enter the admin ID: ";
//                                 cin >> delAdminID;
//                                 if(admin->checkAdminID(delAdminID) == true)
//                                 {
//                                     clearTerminal();
//                                     cout << "--- Deleting an Admin ---\n" << endl;
//                                     cout << "Enter the admin password: ";
//                                     cin >> delAdminPassword;
//                                     if(admin->checkAdminPassword(delAdminID, delAdminPassword) == true)
//                                     {
//                                         while(true)
//                                         {
//                                             int delOption;
//                                             clearTerminal();
//                                             cout << "Are you sure to delete this admin?" << endl;
//                                             cout << "1. Yes" << endl;
//                                             cout << "2. No" << endl;
//                                             cout << "Enter here: ";
//                                             cin >> delOption;
//                                             if(delOption == 1)
//                                             {
//                                                 admin->removeAdminFromFile(delAdminID);
//                                                 sleep(4);
//                                                 break;
//                                             }
//                                             else if (delOption == 2)
//                                             {
//                                                 break;
//                                             }
//                                             else
//                                             {
//                                                 cout << "Wrong Input!!" << endl;
//                                                 sleep(2);
//                                             }
//                                         }
//                                     }
//                                     else
//                                     {
//                                         cout << "Wrong Password!!" << endl;
//                                         sleep(2);
//                                         break;
//                                     }
//                                     break;
//                                 }
//                                 else
//                                 {
//                                     clearTerminal();
//                                     cout << "ID is not in the file" << endl;
//                                     sleep(2);
//                                     break;
//                                 }
//                             }
//                         }
//                         // Dispay all admins
//                         else if (adminMode == 3)
//                         {
//                             clearTerminal();
//                             cout << "--- Display All Admins ---" << endl;
//                             admin->displayAdmin();
//                             pause();
//                         }
//                         // Login
//                         else if (adminMode == 4)
//                         {
//                             while (true)
//                             {
//                                 clearTerminal();
//                                 string loginID;
//                                 cout << "--- Login --- \n" << endl;
//                                 cout << "Enter your ID: ";
//                                 cin >> loginID;
//                                 if(admin->checkAdminID(loginID) == true)
//                                 {
//                                     clearTerminal();
//                                     string loginPassword;
//                                     cout << "--- Login --- \n" << endl;
//                                     cout << "Enter your password: ";
//                                     cin >> loginPassword;
//                                     if (admin->checkAdminPassword(loginID, loginPassword) == true)
//                                     {
//                                         clearTerminal();
//                                         cout << "*** Login Sucessfully ***";
//                                         sleep(2);
//                                         while (true)
//                                         {
//                                             int loginOption;
//                                             clearTerminal();
//                                             cout << "*** Welcome ***\n"  << endl;
//                                             cout << "=== Please choose an option ===\n" << endl;
//                                             cout << "1. Create Quiz" << endl;
//                                             cout << "2. Delete Quiz" << endl;
//                                             cout << "3. Update Quiz" << endl;
//                                             cout << "4. Back\n" << endl;
//                                             cout << "Enter here: ";
//                                             cin >> loginOption;
//                                             if (loginOption == 1)
//                                             {
//                                                 // Create Quiz
//                                                 clearTerminal();
//                                                 int quizID;
//                                                 string quizTitle;
//                                                 cout << "--- Create Quiz ---\n" << endl;
//                                                 cout << "Enter Quiz ID: ";
//                                                 cin >> quizID;
//                                                 cout << "Enter Quiz Title: ";
//                                                 cin.ignore();
//                                                 getline(cin, quizTitle);

//                                                 Quiz quiz(quizID, quizTitle);

//                                                 int numQuestions;
//                                                 cout << "How many questions do you want to add? ";
//                                                 cin >> numQuestions;

//                                                 for (int i = 0; i < numQuestions; i++)
//                                                 {
//                                                     clearTerminal();
//                                                     cout << "--- Add Question " << (i + 1) << " ---\n" << endl;
//                                                     int questionID;
//                                                     string questionText;
//                                                     int correctAnswer;
//                                                     vector<string> options;
//                                                     vector<string> categories;
//                                                     string tempOption;

//                                                     cout << "Enter Question ID: ";
//                                                     cin >> questionID;
//                                                     cin.ignore();
//                                                     cout << "Enter Question Text: ";
//                                                     getline(cin, questionText);

//                                                     for (int j = 0; j < 4; j++)
//                                                     {
//                                                         cout << "Enter Option " << (j + 1) << ": ";
//                                                         getline(cin, tempOption);
//                                                         options.push_back(tempOption);
//                                                     }

//                                                     cout << "Enter the number of the correct option (1-4): ";
//                                                     cin >> correctAnswer;

//                                                     cin.ignore();
//                                                     string category;
//                                                     cout << "Enter Question Category: ";
//                                                     getline(cin, category);
//                                                     categories.push_back(category);

//                                                     int difficultyInput;
//                                                     cout << "Select Difficulty (1 = BEGINNER, 2 = INTERMEDIATE, 3 = ADVANCED): ";
//                                                     cin >> difficultyInput;
//                                                     Difficulty difficulty = static_cast<Difficulty>(difficultyInput - 1);

//                                                     Question question(questionID, questionText, options, categories, correctAnswer - 1, difficulty);
//                                                     quiz.addQuestion(question);
//                                                 }

//                                                 string filename = "../CSV-Files/quiz_" + to_string(quizID) + ".csv";
//                                                 quiz.saveToFile(filename);
//                                                 cout << "\nQuiz created and saved successfully." << endl;
//                                                 pause();
//                                             }
//                                             else if (loginOption == 2)
//                                             {
//                                                 // Delete Quiz
//                                                 clearTerminal();
//                                                 int quizID;
//                                                 cout << "--- Delete Quiz ---\n" << endl;
//                                                 cout << "Enter Quiz ID: ";
//                                                 cin >> quizID;
//                                                 string filename = "../CSV-Files/quiz_" + to_string(quizID) + ".csv";
//                                                 if (remove(filename.c_str()) == 0)
//                                                 {
//                                                     cout << "Quiz deleted successfully." << endl;
//                                                 }
//                                                 else
//                                                 {
//                                                     cout << "Error: Quiz not found." << endl;
//                                                 }
//                                                 pause();
//                                             }
//                                             else if (loginOption == 3)
//                                             {
//                                                 // Update Quiz
//                                                 clearTerminal();
//                                                 int quizID;
//                                                 cout << "--- Update Quiz ---\n" << endl;
//                                                 cout << "Enter Quiz ID: ";
//                                                 cin >> quizID;
//                                                 string filename = "../CSV-Files/quiz_" + to_string(quizID) + ".csv";

//                                                 Quiz quiz(quizID, "");
//                                                 quiz.loadFromFile(filename);

//                                                 int questionID;
//                                                 cout << "Enter Question ID to update: ";
//                                                 cin >> questionID;

//                                                 for (auto& question : quiz.getRandomQuestions("", BEGINNER, quiz.getQuestions().size()))
//                                                 {
//                                                     if (question.getId() == questionID)
//                                                     {
//                                                         clearTerminal();
//                                                         cout << "--- Update Question ---\n" << endl;
//                                                         int correctAnswer;
//                                                         vector<string> options;
//                                                         string tempOption;

//                                                         cin.ignore();
//                                                         cout << "Enter updated Question Text: ";
//                                                         getline(cin, question.getQuestionText());

//                                                         for (int j = 0; j < 4; j++)
//                                                         {
//                                                             cout << "Enter updated Option " << (j + 1) << ": ";
//                                                             getline(cin, tempOption);
//                                                             options.push_back(tempOption);
//                                                         }

//                                                         cout << "Enter the updated number of the correct option (1-4): ";
//                                                         cin >> correctAnswer;
//                                                         question.getCorrectAnswer() = correctAnswer - 1;

//                                                         quiz.updateQuestion(question);
//                                                         quiz.saveToFile(filename);

//                                                         cout << "Question updated successfully." << endl;
//                                                         pause();
//                                                         break;
//                                                     }
//                                                 }
//                                             }                                            
//                                             else if (loginOption == 4)
//                                             {
//                                                 break;
//                                             }
//                                             else
//                                             {
//                                                 cout << "Wrong Input!!" << endl;
//                                                 sleep(2);
//                                             }
//                                         }
//                                         break;
//                                     }
//                                     else
//                                     {
//                                         cout << "Wrong Password!!" << endl;
//                                         sleep(2);
//                                         break;
//                                     }
//                                 }
//                                 else
//                                 {
//                                     cout << "Wrong ID!!" << endl;
//                                     sleep(2);
//                                     break;
//                                 }
//                             }
                            
//                         }
//                         else if(adminMode == 5)
//                         {
//                             clearTerminal();
//                             cout << "*** Exit Admin Mode ***";
//                             sleep(2);
//                             goto mainMenu;
//                         }
//                         else if (adminMode == 6)
//                         {
//                             return 0;
//                         }
//                         else
//                         {
//                             cout << "Invalid option!!" << endl;
//                             pause();
//                         }
//                     }
                    
//                 }
//                 else
//                 {
//                     cout << "Wrong Password!!" << endl;
//                     pause();
//                     break;
//                 }
                
//             }
//         }
//         else if (mainOptionMode == 2)
//         {
//             /* code */
//         }
//         else if (mainOptionMode == 3)
//         {
//             break;
//         }
//         else
//         {
//             cout << "Invalid option!!" << endl;
//             pause();
//         }
//     }

//     return 0;
// }
