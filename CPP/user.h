#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<string>
#include<iomanip>
using namespace std;

string current_username;

struct userScore {
    string username;
    int score;
    double accuracy; 
    Difficulty difficulty;

    
    userScore(string u, int s, double a, Difficulty d)
        : username(u), score(s), accuracy(a), difficulty(d) {}

    userScore() : username(""), score(0), accuracy(0.0), difficulty(BEGINNER) {}
};


class User{
    private:
    string email;
    string username;
    string password;

    public:

    User() : email(""), username(""), password("") {};

    User(string& email, string& username, string& password) : email(email), username(username), password(password) {};

    static bool isUsernameAvailable(const string& username) {
    ifstream file("../CSV-Files/user.csv");
    if (!file.is_open()) {
        cout << "Error opening the file."<<endl;
    }

    string line;
    while (getline(file, line)) { 
        stringstream ss(line);
        string email, user, password;

        
        getline(ss, email, ',');  
        getline(ss, user, ',');  
        getline(ss, password, ','); 

        
        if (user == username) {
            file.close();
            return false; 
        }
    }

    file.close();
    return true;  
}

static bool isEmailAvailable(const string& input_email) {
    ifstream file("../CSV-Files/user.csv");
    if (!file.is_open()) {
        cout << "Error opening the file."<<endl;
    }

    string line;
    while (getline(file, line)) { 
        stringstream ss(line);
        string email, user, password;

        
        getline(ss, email, ',');  
        getline(ss, user, ',');  
        getline(ss, password, ','); 

        
        if (email == input_email) {
            file.close();
            return false; 
        }
    }

    file.close();
    return true;  
}



void createAccountUser() {
    ofstream file("../CSV-Files/user.csv", ios::app); 
    if (!file.is_open()) {
        cout << "Error opening the file." << endl;
        return;
    }

    file.seekp(0, ios::end);
    if (file.tellp() == 0) {
        file << "Email,Username,Password" << endl;  
    }

    string email;
    string username;
    string password;
    string confirmPassword;

    
    do {
        cout << "Enter your email: ";
        cin >> email;
        if (email.find('@') == string::npos) {
            cout << "Invalid email address. Please enter a valid email address." << endl;
        }
        while(!isEmailAvailable(email)){
            cout << "Email already exists. Please enter a different email address." << endl;
            cout << "Enter your email: ";
            cin >> email;
        }
    } while (email.find('@') == string::npos);


    cout << "Enter your username: ";
    cin >> username;
    while (!isUsernameAvailable(username)) {
        cout << "Username is taken. Please choose a different one: ";
        cin >> username;
    }

    
    cout << "Enter your password: ";
    cin >> password;

    
    do {
        cout << "Confirm your password: ";
        cin >> confirmPassword;
        if (confirmPassword != password) {
            cout << "Passwords do not match. Please try again." << endl;
        }
    } while (confirmPassword != password);

    
    file << email << "," << username << "," << password << endl;

    cout << "Account created successfully!" << endl;

    
    file.close();
}


   void userLogin(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening the file." << endl;
        return;
    }

    string username, password;
    bool loggedIn = false; 

    do {
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;

        string line;
        getline(file, line); // Skip header
        loggedIn = false; 

        while (getline(file, line)) {
            stringstream ss(line);
            string email, stored_username, stored_password;

            getline(ss, email, ',');
            getline(ss, stored_username, ',');
            getline(ss, stored_password, ',');

            if (username == stored_username && password == stored_password) {
                current_username = username; 
                cout << "Login successful." << endl;
                loggedIn = true; 
                break;
            }
        }

        if (!loggedIn) {
            cout << "Invalid username or password. Please try again." << endl;
            cout << "Would you like to try again? (1 for Yes, 0 for No): ";
            int choice;
            cin >> choice;
            if (choice == 0) {
                cout << "Exiting login." << endl;
                break; 
            }
            
        }
    } while (!loggedIn); 

    file.close();
}



   void bubbleSort(vector<userScore>& leaderboard) {
    bool swapped;
    int n = leaderboard.size();
    
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (leaderboard[j].score < leaderboard[j + 1].score) {
                swap(leaderboard[j], leaderboard[j + 1]);
                swapped = true;
            }
            //if scores are equal, sort by accuracy
            else if (leaderboard[j].score == leaderboard[j + 1].score && 
                       leaderboard[j].accuracy < leaderboard[j + 1].accuracy) {
                swap(leaderboard[j], leaderboard[j + 1]);
                swapped = true;
            }
        }
        
        if (!swapped) break; 
        }
    }


    void viewOwnHistory(const string& username) {
    ifstream file("../CSV-Files/report.csv");
    if (!file.is_open()) {
        cout << "Error opening the file." << endl;
        return;
    }

    string line;
    bool foundUser = false;
    vector<string> allAttempts; // To store all attempts for the user

    while (getline(file, line)) {
        string user, score_str, accuracy_str, difficulty_str, quiz_attempts;

        if (line.find("User: ") != string::npos) {
            istringstream iss(line);
            iss.ignore(6); 
            getline(iss, user);

            getline(file, line);
            if (line.find("Score: ") != string::npos) {
                istringstream scoreStream(line);
                scoreStream.ignore(7); 
                getline(scoreStream, score_str); 
            }

            getline(file, line);
            if (line.find("Accuracy: ") != string::npos) {
                istringstream accuracyStream(line);
                accuracyStream.ignore(10);
                getline(accuracyStream, accuracy_str); 
            }

            getline(file, line);
            if (line.find("Difficulty: ") != string::npos) {
                istringstream difficultyStream(line);
                difficultyStream.ignore(12); 
                getline(difficultyStream, difficulty_str); 
            }

            getline(file,line);
            getline(file, line); 
            if (line.find("Quiz Attempt Details:") != string::npos) {
                while (getline(file, line)) {
                    if (line == "--------------------------------------------------") {
                        break; 
                    }
                    quiz_attempts += line + "\n"; 
                }
            }

            if (user == username) {
                foundUser = true;
                allAttempts.push_back("Score: " + score_str + "\n" +
                                      "Accuracy: " + accuracy_str + "\n" +
                                      "Difficulty: " + difficulty_str + "\n" +
                                      "Quiz Attempts:\n" + quiz_attempts);
            }
        }
    }

    // Print all attempts for the user
    if (foundUser) {
        cout << "\n--- History for " << username << " ---\n";
        for (const auto& attempt : allAttempts) {
            cout << attempt << endl;
        }
    } else {
        cout << "No history found for user: " << username << endl;
    }

    file.close();
}


    void viewLeaderboard() {
        ifstream file("../CSV-Files/report.csv");
        if (!file.is_open()) {
            cout << "Error opening the file." << endl;
            return;
        }

        vector<userScore> leaderboard;
        string line;

        while (getline(file, line)) {
            if (line.empty()) continue;  // Skip empty lines

            string username;
            int score = 0;
            double accuracy = 0.0;
            string difficulty_str;

            // Check if the line starts with "User:"
            if (line.find("User: ") == 0) {
                username = line.substr(6);  // Extract username
                
                // Read the next lines for score, accuracy, and difficulty
                getline(file, line); // Score line
                if (line.find("Score: ") != string::npos) {
                    stringstream scoreStream(line);
                    string temp;
                    scoreStream >> temp >> score;  // Extract score
                }

                getline(file, line); 
                if (line.find("Accuracy: ") != string::npos) {
                    stringstream accuracyStream(line);
                    string temp;
                    accuracyStream >> temp >> accuracy;  
                    accuracyStream.ignore(numeric_limits<streamsize>::max(), '%'); 
                }

                getline(file, line);
                if (line.find("Difficulty: ") != string::npos) {
                    string temp;
                    stringstream difficultyStream(line);
                    difficultyStream >> temp >> difficulty_str;  
                }

                Difficulty difficulty;
                if (difficulty_str == "BEGINNER") {
                    difficulty = BEGINNER;
                } else if (difficulty_str == "INTERMEDIATE") {
                    difficulty = INTERMEDIATE;
                } else if (difficulty_str == "ADVANCED") {
                    difficulty = ADVANCED;
                } else {
                    cout << "Invalid difficulty level: " << difficulty_str << endl;
                    continue;  
                }

                leaderboard.emplace_back(username, score, accuracy, difficulty);
            }
        }

        file.close();

        // Separate leaderboard by difficulty
        vector<userScore> beginner, intermediate, advanced;

        for (const auto& entry : leaderboard) {
            switch (entry.difficulty) {
                case BEGINNER: beginner.push_back(entry); break;
                case INTERMEDIATE: intermediate.push_back(entry); break;
                case ADVANCED: advanced.push_back(entry); break;
            }
        }

        // Sort each leaderboard using bubbleSort
        bubbleSort(beginner);
        bubbleSort(intermediate);
        bubbleSort(advanced);

        // Output the leaderboard
        cout << "Leaderboard by Difficulty:\n";

        auto printLeaderboard = [](const vector<userScore>& scores, const string& title) {
            cout << "\n--- " << title << " ---\n";
            int top = min(10, (int)scores.size());
            for (int i = 0; i < top; ++i) {
                cout << i + 1 << ". " << scores[i].username 
                    << " | Score: " << scores[i].score
                    << " | Accuracy: " << fixed << setprecision(2) << scores[i].accuracy << "%" << endl;
            }
        };

        printLeaderboard(beginner, "Beginner");
        printLeaderboard(intermediate, "Intermediate");
        printLeaderboard(advanced, "Advanced");
    }

    void afterLogin() {
    int pick;

    do {
    cout << "\n\n";
    cout << "---------------------"<<endl;
    cout << "Welcome to the quiz system! What would you like to do?" << endl;
    cout << "1. Start Quiz" << endl;
    cout << "2. View Leaderboard" << endl;
    cout << "3. View own's history" << endl;
    cout << "4. Exit" << endl;
    cout << "---------------------";
    cout << "\n\n";
        cout << "Enter your choice: ";
        cin >> pick;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 


        switch (pick) {
            case 1: {
                string category;
                int category_input;

                cout << "Pick your preferred category: \n";
                cout << "1. Literature\n";
                cout << "2. History\n";
                cout << "3. Science\n";
                cout << "4. Math\n";
                cout << "5. Programming\n";
                cout << "6. Geography\n";

                do {
                    cout << "Enter your preferred category (1-6): ";
                    cin >> category_input;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a number between 1 and 6.\n";
                        continue;
                    }

                    switch (category_input) {
                        case 1: category = "Literature"; break;
                        case 2: category = "History"; break;
                        case 3: category = "Science"; break;
                        case 4: category = "Math"; break;
                        case 5: category = "Programming"; break;
                        case 6: category = "Geography"; break;
                        default:
                            cout << "Invalid input. Please try again.\n";
                            category_input = 0;
                    }
                } while (category_input == 0);

                int difficulty_input;
                cout << "Enter your preferred difficulty (1 = BEGINNER, 2 = INTERMEDIATE, 3 = ADVANCED): ";
                cin >> difficulty_input;

                Difficulty difficulty;
                if (difficulty_input == 1) {
                    difficulty = BEGINNER;
                } else if (difficulty_input == 2) {
                    difficulty = INTERMEDIATE;
                } else if (difficulty_input == 3) {
                    difficulty = ADVANCED;
                } else {
                    cout << "Invalid difficulty. Defaulting to BEGINNER." << endl;
                    difficulty = BEGINNER;
                }

                
                startQuiz(category, difficulty);
                cout << "Press Enter to continue...";
                cin.get();
                break;
            }

            case 2:
                viewLeaderboard();
                cout << "Press Enter to continue...";
                cin.get();
                break;

            case 3:
                viewOwnHistory(current_username);
                cout << "Press Enter to continue...";
                cin.get();
                break;

            case 4:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice." << endl;
        }
    } while (pick != 4);
}

int setTimer(Difficulty difficulty){
    int timer;
        switch(difficulty){
            case BEGINNER:
            timer = 80;
            break;
            case INTERMEDIATE:
            timer = 120;
            break;
            case ADVANCED:
            timer = 150;
            break;
            default:
            timer = 80;
            break;
        }
        return timer;
    }

    void displayReport() {
    ifstream file("../CSV-Files/report.csv"); 
    if (!file.is_open()) {
        cout << "Error: Unable to open the report file.\n";
        return;
    }

    string line;
    bool isFirstLine = true;

    cout << "\n========== Quiz Report ==========\n";
    cout << "\n\n\n";

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        if (isFirstLine) {
            cout << line << "\n";
            cout << string(50, '=') << "\n"; 
            isFirstLine = false;
        } else if (line.find("User, Score, Accuracy, Difficulty") != string::npos) {
            cout << "\n" << line << "\n";
            cout << string(50, '-') << "\n"; 
        } else if (line.find("Question:") != string::npos) {
            cout << line << "\n"; 
        } else if (line.find("Correct answer:") != string::npos) {
            cout << line << "\n";
            cout << string(25, '-') << "\n"; 
        } else {
            cout << line << "\n";
        }
    }

    file.close();
    cout << "\n========== End of Report ==========\n";
}




void startQuiz(string category, Difficulty difficulty) {
    Quiz quiz;
    quiz.loadFromFile();

    int num_questions;
    switch (difficulty) {
        case BEGINNER: num_questions = 5; break;
        case INTERMEDIATE: num_questions = 10; break;
        case ADVANCED: num_questions = 15; break;
        default: num_questions = 10; break;
    }

    vector<Question> randomized_questions = quiz.getRandomQuestions(category, difficulty, num_questions);
    if (randomized_questions.empty()) {
        cout << "No questions found for the specified category and difficulty!" << endl;
        return;
    }

    int timer = setTimer(difficulty);
    time_t start_time = time(0);
    time_t end_time = start_time + timer;
    int correct_answers = 0;

    cout << "You have " << timer << " seconds to complete the quiz.\n\n";

    for (size_t i = 0; i < randomized_questions.size(); ++i) {
        if (time(0) > end_time) {
            cout << "Time's up!\n";
            break;
        }

        const auto& question = randomized_questions[i];
        cout << "Question " << i + 1 << ": " << question.getQuestionText() << endl;

        const auto& options = question.getOptions();
        for (size_t j = 0; j < options.size(); ++j) {
            cout << "  " << j + 1 << ". " << options[j] << endl;
        }

        int user_answer = 0;
        while (true) {
            cout << "Your answer (1-" << options.size() << "): ";
            cin >> user_answer;

            if (cin.fail() || user_answer < 1 || user_answer > options.size()) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "Invalid input. Please enter a number between 1 and " << options.size() << ".\n";
            } else {
                break;
            }
        }

        if (user_answer == question.getCorrectAnswer()) {
            ++correct_answers;
        }

        question.feedback(user_answer);
    }

    int score = correct_answers;
    int total_questions = randomized_questions.size();
    double accuracy = (double)score / randomized_questions.size() * 100.0;

    cout << "\nQuiz Complete!\n";
    cout << "Your Score: " << score << " out of " << total_questions << "\n";
    cout << "Accuracy: " << accuracy << "%\n";

    stringstream ss;
    ss << "Quiz Attempt Details:\n";
    ss << "Category: " << category << endl;

    for (const auto& question : randomized_questions) {
        ss << "Question: " << question.getQuestionText() << "\n";

        const auto& options = question.getOptions();
        for (size_t i = 0; i < options.size(); ++i) {
            ss << "  " << i + 1 << ". " << options[i] << endl;
        }

        if (question.getCorrectAnswer() >= 1 && question.getCorrectAnswer() <= options.size()) {
            ss << "Correct answer: "
               << options[question.getCorrectAnswer() - 1] << endl;
        } else {
            ss << "Correct answer: Invalid Index\n";
        }

        ss << "-------------------------\n";
    }

    string quiz_report = ss.str();

    vector<string> quiz_attempts;
    quiz_attempts.push_back(quiz_report);

    storeReport(current_username, score, accuracy, difficulty, quiz_attempts, total_questions);
}


    void storeReport(const string& username, int score, double accuracy, Difficulty difficulty, const vector<string>& quiz_attempts, int total_questions) {
    ofstream report_file("../CSV-Files/report.csv", ios::app); 
    if (!report_file.is_open()) {
        cerr << "Error: Could not open the report file!" << endl;
        return;
    }

    report_file << "User: " << username << endl;
    report_file << "Score: " << score << " / " << total_questions << endl;
    report_file << "Accuracy: " << accuracy << "%" << endl;
    report_file << "Difficulty: " << difficultyToString(difficulty) << endl;
    report_file << string(50, '-') << "\n";

    for (const auto& attempt : quiz_attempts) {
        report_file << attempt << "\n";
        report_file << string(50, '-') << "\n";
    }

    report_file << "------------------------------------------\n";
    report_file.close();
    }


    
};

   void userMenu() {
    User user;
    string filename = "../CSV-Files/user.csv";

    int choice;
    cout << "------User Menu-------"<<endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    cout << "\n\n\n";

    do {
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                user.createAccountUser();
                int proceed;
                cout << "Would you like to proceed? (1 for yes, 2 for no): ";
                cin >> proceed;
                if (proceed == 1) {
                    user.afterLogin();
                } else if (proceed == 2) {
                    cout << "Returning to menu..." << endl;
                } else {
                    cout << "Invalid option. Returning to menu..." << endl;
                }
                break;

            case 2:
                user.userLogin(filename);
                user.afterLogin();
                break;

            case 3:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
        }
    } while (choice != 3);
}
