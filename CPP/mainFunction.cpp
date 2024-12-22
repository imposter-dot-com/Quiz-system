#include <iostream>
#include <fstream>
using namespace std;

void clearTerminal()
{
    cout << "\033[2J\033[1;1H"; // clear terminal
}



// File Check Functions
bool isFileAppend(fstream &myFile, const string &fileName)
{
    myFile.open(fileName, ios::app);
    if(myFile.is_open())
    {
        return false;
    }
    else
    {
        myFile.close();
        return true;
    }
}

bool isFileWrite(fstream &myFile, const string &fileName)
{
    myFile.open(fileName, ios::out);
    if(myFile.is_open())
    {
        return false;
    }
    else
    {
        myFile.close();
        return true;
    }
}

bool isFileRead(fstream &myFile, const string &fileName)
{
    myFile.open(fileName, ios::in);
    if(myFile.is_open())
    {
        myFile.close();
        return false;
    }
    else
    {
        return true;
    }
}

void pause()
{
    cout << "Press ENTER to continue...";
    fflush(stdin);
    cin.get();
                        
}


// int main(int argc, char const *argv[])
// {

//     return 0;
// }
