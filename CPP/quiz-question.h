#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<unordered_map>
#include<cstdlib>
#include<string>
#include<algorithm>
#include<set>
#include<random>

using namespace std;

enum Difficulty{
    BEGINNER,
    INTERMEDIATE,
    ADVANCED
};

string difficultyToString(Difficulty difficulty){
    switch(difficulty){
        case BEGINNER:
            return "BEGINNER";
            break;
        case INTERMEDIATE:
            return "INTERMEDIATE";
            break;
        case ADVANCED:
            return "ADVANCED";
            break;
        default:
            return "UNKNOWN";
            break;
    }
}

Difficulty stringToDifficulty(string& str){
    if(str=="BEGINNER"){
        return BEGINNER;
    }
    if(str=="INTERMEDIATE"){
        return INTERMEDIATE;
    }
    if(str=="ADVANCED"){
        return ADVANCED;
    }
    return BEGINNER;
}

class Question{
    private:
    int question_id;
    string question_text;
    vector <string> options;
    int correct_answer;
    string category;
    Difficulty difficulty;

    public:
     Question()
        : question_id(0), question_text(""), correct_answer(0), difficulty(BEGINNER) {}


    Question(int question_id, string question_text, vector<string> options, string category, int correct_answer, Difficulty difficulty)
        : question_id(question_id), question_text(question_text), options(options), category(category), correct_answer(correct_answer), difficulty(difficulty) {}

    int getId() const{return question_id;}
    string getQuestionText()const{return question_text;}
    vector<string> getOptions() const{return options;}
    int getCorrectAnswer() const{return correct_answer;}
    Difficulty getDifficulty() const{return difficulty;}
    string getCategory() const{return category;}
    
    void setId(int id) { question_id = id; }

    bool hasCategory(const string& cat) const {
    return !cat.empty() && category == cat;
    }


    void feedback(int user_answers) const {
    if (user_answers < 1 || user_answers > options.size()) {
        cout << "Invalid answer. Please provide a number between 1 and " << options.size() << "." << endl;
        return;
    }

    if (user_answers == correct_answer) {
        cout << "Correct answer!" << endl;
    } else {
        cout << "Incorrect answer. The correct answer is " << correct_answer << endl;
    }
}

    void display() const{
        cout<<"Question: "<<question_text<<endl;
        for(int i = 0; i < options.size(); ++i){
            cout<<i+1<<". "<<options[i]<<endl;
        }
    }

    void saveQuestionsToFile(ofstream& file) const{

        file << question_id << "," << question_text << "," 
        << difficultyToString(difficulty) << "," 
        << correct_answer << "," 
        << category << ",";

    for (size_t i = 0; i < options.size(); ++i) {
        file << options[i];
        if (i < options.size() - 1) file << ","; 
    }
    file << "\n";

    }

   static Question loadQuestionFromFile(const string& line) {
    istringstream iss(line);
    int id, correct_answer;
    string question_text, difficulty_str, temp;
    string category;
    vector<string> options;

    // Parse ID
    if (!getline(iss, temp, ',')) return Question();  // Return an empty Question on failure
    try {
        id = stoi(temp);
    } catch (const invalid_argument&) {
        cout << "Invalid ID format in line: " << line << endl;
        return Question(); // Return an empty Question on failure
    }

    // Parse Question Text
    if (!getline(iss, question_text, ',')) return Question();

    // Parse Difficulty
    if (!getline(iss, difficulty_str, ',')) return Question();
    Difficulty difficulty = stringToDifficulty(difficulty_str);

    // Parse Correct Answer Index
    if (!getline(iss, temp, ',')) return Question();
    try {
        correct_answer = stoi(temp);
    } catch (const invalid_argument&) {
        cout << "Invalid correct answer format in line: " << line << endl;
        return Question(); // Return an empty Question on failure
    }

    // Parse Category (assumes single category)
    if (!getline(iss, category, ',')) return Question();

    // Parse Options
    while (getline(iss, temp, ',')) {
        options.push_back(temp);
    }

    if (options.empty() || correct_answer < 1 || correct_answer > options.size()) {
        cout << "Warning: Question with ID " << id << " has invalid data." << endl;
        return Question(); 
    }

    return Question(id, question_text, options, category, correct_answer, difficulty);
}

    
};

class Quiz{
    private:
    int quiz_id;
    string title;
    unordered_map <int, Question> questions;
    int last_question_id=0;
    set<int> available_ids;


    public:

    bool questionExists(int question_id) const {
    return questions.find(question_id) != questions.end();
    }

   void addQuestion(Question& question) {
    string filename = "../CSV-Files/questions.csv";
    int question_id;

    // Check available IDs first
    if (!available_ids.empty()) {
        question_id = *available_ids.begin();
        available_ids.erase(available_ids.begin());
    } else {
        question_id = ++last_question_id; 
    }

    Question new_question(question_id, question.getQuestionText(), question.getOptions(), question.getCategory(), question.getCorrectAnswer(), question.getDifficulty());
    questions[question_id] = new_question;

    saveToFile(filename);  
    }
    
    void removeQuestion(int question_id) {
    if (questions.find(question_id) != questions.end()) {
        available_ids.insert(question_id);  // Add ID to available IDs
        questions.erase(question_id);  
        cout << "Question deleted successfully." <<endl;
        saveToFile("../CSV-Files/questions.csv"); // Save after removing
    } else {
        cout << "Question not found." << endl;
    }
}

    void updateQuestion(const Question& updatedQuestion) {
    int question_id = updatedQuestion.getId();
    if (questions.find(question_id) == questions.end()) {
        cout << "Question ID " << question_id << " does not exist. Cannot update." << endl;

        return; 
    }

    questions[question_id] = updatedQuestion;
    saveToFile("../CSV-Files/questions.csv");
}


   void saveToFile(const string& filename) {
    // Read existing content to preserve the header
    ifstream infile(filename);
    string header;

    if (infile.is_open()) {
        getline(infile, header);  // Read the header
        infile.close();
    } else {
        cout << "Error opening the file." << endl;
        return;
    }

    // Open the file for writing (will overwrite content)
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening the file for writing." << endl;
        return;
    }

    // Write the header back to the file
    file << header << endl;

    // Write all questions
    for (const auto& entry : questions) {
        entry.second.saveQuestionsToFile(file);
    }

    file.close();
}

   void loadFromFile() {
        ifstream file("../CSV-Files/questions.csv");
        if (!file.is_open()) {
            cout << "Error opening the file!" << endl;
            return;
        }

        string line;

        getline(file, line);

        while (getline(file, line)) {
            Question question = Question::loadQuestionFromFile(line);
            questions[question.getId()] = question;

            
            if (question.getId() > last_question_id) {
                last_question_id = question.getId();
            }
        }

        file.close();
    }


   void displayAllQuestions(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open file!" << endl;
        return;
    }

    string line;
    cout << "--- All Questions ---" << endl;
    // Skip the header line
    getline(file, line);

    while (getline(file, line)) {
        Question question = Question::loadQuestionFromFile(line);
        if (question.getId() != 0) { // Ensure valid question was loaded
            cout << "----------------------------------------" << endl;
            cout << "ID: " << question.getId() << endl;
            cout << "Question: " << question.getQuestionText() << endl;
            cout << "Category: " << question.getCategory() << endl;
            cout << "Difficulty: " << difficultyToString(question.getDifficulty()) << endl;
            const auto& options = question.getOptions();
            for (size_t i = 0; i < options.size(); ++i) {
                cout << i + 1 << ". " << options[i] << endl;
            }
            cout << "Correct Answer: " << question.getCorrectAnswer() << endl;
        }
    }
    cout << "----------------------------------------" << endl;

    file.close();
    }

    Question createQuestionInteractively() {
    string questionText, category;
    vector<string> options;
    int correctAnswer, difficultyLevel;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter the question text: ";
    getline(cin, questionText);

    cout << "Enter the category: ";
    getline(cin, category);

    cout << "Enter the difficulty level (1: BEGINNER, 2: INTERMEDIATE, 3: ADVANCED): ";
    cin >> difficultyLevel;
    while (difficultyLevel < 1 || difficultyLevel > 3) {
        cout << "Invalid difficulty level. Please enter 1, 2, or 3: ";
        cin >> difficultyLevel;
    }
    Difficulty difficulty = static_cast<Difficulty>(difficultyLevel - 1);

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    cout << "Enter the options (type 'done' when finished):\n";
    string option;
    while (true) {
        cout << "Option " << options.size() + 1 << ": ";
        getline(cin, option);
        if (option == "done") break;
        options.push_back(option);
    }

    cout << "Enter the number of the correct answer (1-" << options.size() << "): ";
    cin >> correctAnswer;
    while (correctAnswer < 1 || correctAnswer > static_cast<int>(options.size())) {
        cout << "Invalid choice. Enter a number between 1 and " << options.size() << ": ";
        cin >> correctAnswer;
    }

    return Question(-1, questionText, options, category, correctAnswer, difficulty);
    }


    void displayQuiz(){
        
       cout << "Quiz: " << title << endl;
       for(const auto& entry: questions){
            entry.second.display();
       }
    }

    unordered_map<int, Question> getQuestions() const{
        return questions;
    }

    vector<Question> getRandomQuestions(const string& category, Difficulty difficulty, int num_questions) {
    vector<Question> filtered_questions;

    cout << "Filtering questions for category: " << category
         << ", difficulty: " << difficultyToString(difficulty) << endl;

    for (const auto& entry : questions) {
        const Question& q = entry.second;
        if (q.getCategory() == category && q.getDifficulty() == difficulty) {
            filtered_questions.push_back(q);
        }
    }

    if (filtered_questions.empty()) {
        cout << "No questions match the criteria." << endl;
        return {};  
    }


    random_device rd;
    mt19937 gen(rd());
    shuffle(filtered_questions.begin(), filtered_questions.end(), gen);

    // Adjust the number of questions to return
    if (num_questions > filtered_questions.size()) {
        cout << "Not enough questions available. Returning all " << filtered_questions.size() << " questions.\n";
        return filtered_questions;
    }

    return vector<Question>(filtered_questions.begin(), filtered_questions.begin() + num_questions);
}

};
