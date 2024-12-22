#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

struct Box
{
    string adminName;
    string adminPassword;
    string adminID;
    Box *next;
};

class Admin
{
    private:
        string mainPassowrd = "168168";
    public:
        Box *head, *tail;
        int size;
        Admin() // defalt value
        {
            head = NULL;
            tail = NULL;
            size = 0;
        }

        // Insert
        void insertBegin(string newAdminID, string newAdminName, string newAdminPassword)
        {
            Box *b; 
            b = new Box; // Memory allocaion
            b -> adminName = newAdminName;
            b -> adminPassword = newAdminPassword;
            b -> adminID = newAdminID; 
            b -> next = head;
            head = b; // Make b becoming the head

            if(size == 0)
            {
                tail = b;
            }
            size ++;
        }
        void insertEnd(string newAdminID, string newAdminName, string newAdminPassword)
        {
            Box *b;
            b = new Box;
            b -> adminName = newAdminName;
            b -> adminPassword = newAdminPassword;
            b -> adminID = newAdminID; 
            b -> next = NULL;
            if (size == 0)
            {
                head = b;
                tail = b;
            }
            else
            {
                tail -> next = b;
                tail = b;
            }
            size ++;
        }

// Check for advialable ID and auto set their id
        int getNextAvailableID()
        {
            Box *t = head;
            bool foundIDs[size + 1] = {false}; // Array to track used IDs (1-based indexing)
            int tempID;

            // Mark the IDs that are already in use
            while (t != NULL)
            {
                tempID = stoi(t->adminID);
                if (tempID > 0 && tempID <= size) // Valid range check
                {
                    foundIDs[tempID] = true;
                }
                t = t->next;
            }

            // Find the first missing ID
            for (int i = 1; i <= size; i++)
            {
                if (!foundIDs[i])
                {
                    return i; // Return the first missing ID
                }
            }

            return size + 1; // If no ID is missing, return the next ID in sequence
        }

// Sort by ID
        void sortAdminsByID()
        {
            if (head == NULL || head->next == NULL)
            {
                // List is empty or has only one element, no need to sort
                return;
            }

            // Bubble sort for the linked list
            Box *current, *nextNode;
            string tempID, tempName, tempPassword;

            for (Box *i = head; i != NULL; i = i->next)
            {
                for (Box *j = head; j->next != NULL; j = j->next)
                {
                    // Compare adminID numerically
                    if (stoi(j->adminID) > stoi(j->next->adminID))
                    {
                        // Swap data between nodes
                        tempID = j->adminID;
                        tempName = j->adminName;
                        tempPassword = j->adminPassword;

                        j->adminID = j->next->adminID;
                        j->adminName = j->next->adminName;
                        j->adminPassword = j->next->adminPassword;

                        j->next->adminID = tempID;
                        j->next->adminName = tempName;
                        j->next->adminPassword = tempPassword;
                    }
                }
            }
        }


// Display admin ID and name
        void displayAdmin()
        {
            Box *t;
            t = head;
            cout << "ID,NAME\n" << endl;
            for(int i = 0; i < size; i++)
            {
                cout << t->adminID << ",";
                cout << t->adminName << endl;
                t = t ->next;
            }
            
        }

// Check Name
        bool checkName(string TempAdminName)
        {
            Box *name;
            name = head;
            for(int i = 0; i < size; i++)
            {
                if(TempAdminName == name->adminName)
                {
                    return true;
                }
                if(i == size -1 && TempAdminName != name->adminName)
                {
                    return false;
                }
                name = name->next;
            }
        }
// Check Main Password
        bool checkMainPassowrd(string &inputMainPassword){
            if(mainPassowrd == inputMainPassword)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
// Add admin to file
        void addNewAdmin(fstream &myFile, string fileName, string adminNewID, string adminNewName, string adminNewPassword)
        {
            myFile.open(fileName, ios::app);
            myFile << adminNewID << "," << adminNewName << "," << adminNewPassword << endl;
            myFile.close();
        }
// Gather Admin From file
        bool gatherAdminFile(fstream &myFile, string fileName)
        {
            myFile.open(fileName, ios::in);
            if(myFile.is_open() == true)
            {
                string firstLine;
                string line;
                string tempAdminName;
                string tempAdminPassword;
                string tempAdminID;

                // get the first line of the file
                getline(myFile, firstLine);
                // read the entire file
                while(getline(myFile, line))
                {
                    stringstream ss(line);
                    getline(ss, tempAdminID, ',');
                    getline(ss, tempAdminName, ',');
                    getline(ss, tempAdminPassword, ',');
                    insertEnd(tempAdminID, tempAdminName, tempAdminPassword);
                }
                myFile.close();
                return true;
            }
            else
            {
                return false;
            }             
        } 
};

// int main(int argc, char const *argv[])
// {
//     Admin *admin = new Admin();
//     fstream myfile;
//     string filename = "../CSV-Files/admin.csv";
//     string tempAdminName;
//     string tempAdminPassword;
//     string tempAdminID;
//     string firstline, line;
//     myfile.open(filename, ios::in);

//     getline(myfile, firstline);
//     while(getline(myfile, line))
//     {
//         stringstream ss(line);
//         getline(ss, tempAdminID, ',');
//         getline(ss, tempAdminName, ',');
//         getline(ss, tempAdminPassword, ',');
//         admin->insertEnd(tempAdminID, tempAdminName, tempAdminPassword);
//     }
//     myfile.close();


//     int tempIDA;
//     string tempAdminNameA;
//     cout << "---Creating a new Admin---\n" << endl;
//     cout << "Enter your name: ";
//     cin >> tempAdminNameA;
//     if(admin->checkName(tempAdminNameA) == false)
//     {
//         cout << "false";
//     }
//     else
//     {
//        cout << "true";  
//     }
//     admin->checkName(tempAdminName);

//     return 0;
// }
