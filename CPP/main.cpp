#include <iostream>
#include <unistd.h>
#include <fstream>
#include "admin.cpp"
#include "mainFunction.cpp"
using namespace std;



int main(int argc, char const *argv[])
{
    while (true)
    {
        int optionMode = 0;
        int isTrue = false;

        mainMenu:
        clearTerminal();
        cout << "---Choose Option Mode---\n" << endl;
        cout << "1. Admin" << endl;
        cout << "2. User" << endl;
        cout << "3. Exit\n" << endl;
        cout << "Enter here: ";
        cin >> optionMode;
        if(optionMode == 1)
        {
            clearTerminal();
            while (true)
            {
                //Get admin name
                string mainPassword;
                Admin *admin = new Admin();
                clearTerminal();
                cout << "---Security Check---\n" << endl;
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
                        cout << "---Please Choose an Option---\n" << endl;
                        cout << "1. Create New Admin" << endl;
                        cout << "2. Log In" << endl;
                        cout << "3. Delete an Admin" << endl;
                        cout << "4. Back" << endl;
                        cout << "5. Exit\n" << endl;
                        cout << "Enter here: ";
                        cin >> adminMode;

                        if(adminMode == 1)
                        {

                        }
                        else if (adminMode == 2)
                        {

                        }
                        else if (adminMode == 3)
                        {
                            
                        }
                        else if(adminMode == 4)
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
            /* code */
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
