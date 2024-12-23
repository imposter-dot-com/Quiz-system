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
    vector <string> category;
    Difficulty difficulty;

    public:
     Question()
        : question_id(0), question_text(""), correct_answer(0), difficulty(BEGINNER) {}


    Question(int question_id, string question_text, vector<string> options, vector<string> category, int correct_answer, Difficulty difficulty)
        : question_id(question_id), question_text(question_text), options(options), category(category), correct_answer(correct_answer), difficulty(difficulty) {}

    int getId() const{return question_id;}
    string getQuestionText()const{return question_text;}
    vector<string> getOptions() const{return options;}
    int getCorrectAnswer() const{return correct_answer;}
    Difficulty getDifficulty() const{return difficulty;}
    vector<string> getCategory() const{return category;}


    bool hasCategory (string& cat) const{
        return find(category.begin(), category.end(), cat) != category.end();
    }

    void feedback(int user_answers) const{
        if(user_answers == correct_answer){
            cout<<"Correct answer!"<<endl;
        }
        else{
            cout<<"Incorrect answer. The correct answer is "<<correct_answer<<endl;
            }
    }

    void display() const{
        cout<<"Question: "<<question_text<<endl;
        for(int i = 0; i < options.size(); ++i){
            cout<<i+1<<". "<<options[i]<<endl;
        }
    }

    void SaveToFile(ofstream& file) const{
        file << question_id << "," << question_text << "," << difficultyToString(difficulty) << "," << correct_answer << ",";

        for(const auto& cat:category){
            file << cat << ",";
        }

        for(const auto& option: options){
            file << option << ",";
        }
        file << "\n";
    }

   static Question loadFromFile(const string& line) {
    istringstream iss(line);
    int id, correct_answer;
    string question_text, difficulty_str, temp;
    vector<string> options, categories;

    getline(iss, temp, ',');  
    id = stoi(temp);
    getline(iss, question_text, ','); 
    getline(iss, difficulty_str, ',');
    Difficulty difficulty = stringToDifficulty(difficulty_str);

    getline(iss, temp, ',');    
    correct_answer = stoi(temp);

    while (getline(iss, temp, ',')) {
        if (temp.empty()) break;
        categories.push_back(temp);
    }

    while (getline(iss, temp, ',')) {
        if (temp.empty()) break;
        options.push_back(temp);
    }

    return Question(id, question_text, options, categories, correct_answer, difficulty);
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
    Quiz(int quiz_id, const string& title) : quiz_id(quiz_id), title(title){};

    void addQuestion(Question& question){
        int question_id;
        if (!available_ids.empty()) {
            question_id = *available_ids.begin();
            available_ids.erase(available_ids.begin());
        } else {
            question_id = ++last_question_id;
        }

        Question new_question(question_id, question.getQuestionText(), question.getOptions(), question.getCategory(), question.getCorrectAnswer(), question.getDifficulty());
        questions[question_id] = new_question;
    }
    
    void removeQuestion(int question_id) {
        if (questions.find(question_id) == questions.end()) {
            cout << "Question not found." << endl;
            return;
        }
        available_ids.insert(question_id);
        questions.erase(question_id);
    }

    void updateQuestion(const Question& question) {
        int question_id = question.getId();
        if (questions.find(question_id) != questions.end()) {
            questions[question_id] = question;
            cout << "Question updated successfully." << endl;
        } else {
            cout << "Question with ID " << question_id << " not found." << endl;
        }
    }

    void saveToFile(string& filename){
        ofstream file(filename);
        if(!file.is_open()){
            cout << "Error opening the file." <<endl;
            return;
        }

        for(const auto& entry : questions){
            entry.second.SaveToFile(file);
        }

        file.close();
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening the file!" << endl;
            return;
        }

        string line;
        getline(file,line);
        while (getline(file, line)) {
            Question question = Question::loadFromFile(line);
            questions[question.getId()] = question;

            
            if (question.getId() > last_question_id) {
                last_question_id = question.getId();
            }
        }

        file.close();
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

    vector<Question> getRandomQuestions(string& category, Difficulty difficulty, int num_questions){
        vector<Question> filtered_questions;

        for(const auto& entry: questions){
            const Question& q = entry.second;
            if(q.hasCategory(category) && q.getDifficulty() == difficulty){
                filtered_questions.push_back(q);
            }
        }

        shuffle(filtered_questions.begin(), filtered_questions.end(), default_random_engine(time(0)));

        if(num_questions > filtered_questions.size()){
            num_questions = filtered_questions.size();
        }

        return vector<Question>(filtered_questions.begin(), filtered_questions.begin() + num_questions);
        
    }

};