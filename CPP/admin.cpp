#include <iostream>
#include <string.h>
using namespace std;

struct Box
{
    string adminName;
    string adminPassword;
    int adminID;
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
        void insertBegin(string newAdminName, string newAdminPassword, int newAdminID)
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
        void insertEnd(string newAdminName, string newAdminPassword, int newAdminID)
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

        void displayAdmin()
        {
            Box *t;
            t = head;

            for(int i = 0; i < size; i++)
            {
                cout << t->adminName<< " ";
                t = t ->next;
            }
            
        }
        bool checkName()
        {
            Box *name;
            name = head;
            if(name == NULL)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        bool checkMainPassowrd(string inputMainPassword){
            int isTrue = mainPassowrd.compare(inputMainPassword);
            if(isTrue == 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
};