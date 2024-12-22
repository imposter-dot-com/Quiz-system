#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<unordered_map>
#include<cstdlib>
#include<string>

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
   Question(int question_id, string question_text, vector<string> options, vector<string> category, int correct_answer, Difficulty difficulty)
        : question_id(question_id), question_text(question_text), options(options), category(category), correct_answer(correct_answer), difficulty(difficulty) {}

    int getId() {return question_id;}
    string getQuestionText(){return question_text;}
    vector<string> getOptions(){return options;}
    int getCorrectAnswer(){return correct_answer;}
    Difficulty getDifficulty(){return difficulty;}
    vector<string> getCategory(){return category;}


    bool hasCategory(string& category){
        return find(category.begin(), category.end(), category) != category.end();
    }


    bool check_answer(){
       return user_answer == correct_answer;
    }

    void display(){
        cout<<"Question: "<<question_text<<endl;
        for(int i = 0; i < options.size(); ++i){
            cout<<i+1<<". "<<options[i]<<endl;
        }
    }

    void SaveToFile(ofstream& file){
        file << question_id << "," << question_text << "," << difficultyToString(difficulty) << "," << correct_answer << ",";

        for(const auto& cat:category){
            file << cat << ",";
        }

        for(const auto& option: options){
            file << option << ",";
        }
        file << "\n";
    }

    static Question loadFromFile(string line){
        istringstream iss(line);
        int id;
        int correct_answer;
        string question_text;
        string difficulty_str;
        string temp;
        vector<string> options;
        vector<string> categories;

        getline(iss, temp, ',');
        id = stoi(temp);
        getline(iss, question_text, ',');
        getline(iss, difficulty_str, ',');
        Difficulty difficulty = stringToDifficulty(difficulty_str);

        getline(iss, temp, ',');
        correct_answer = stoi(temp);

        while(getline(iss, temp, ',')){
            if(temp.empty()){
                break;
            }
            categories.push_back(temp);
        }

        while(getline(iss,temp,',')){
            if(temp.empty()){
                break;
            }
            options.push_back(temp);
        }

        return Question(id, question_text, difficulty, correct_answer, categories, options);
    }
    
};

class Quiz{
    private:
    int quiz_id;
    string title;
    unordered_map <int, Question> questions;
    vector<Question> questions_list;

    public:
    Quiz(int id, string& title) : id(id), title(title){};

    void addQuestion(Question& question){
        question[question.getId()] = question;
        questions_list.push_back(question);
    }

    void saveToFile(string& filename){
        ofstream file(filename);
        if(!file.is_open()){
            cout << "Error opening the file." <<endl;
            return;
        }

        for(const auto& entry : questions){
            entry.second.saveToFile(file);
        }

        file.close();
    }

    void loadFromFile(string& filename){
        ifstream file(filename);
        if(!file.is_open()){
            cout << "Error opening the file!" << endl;
            return;
        }

        string line;
        while(getline(file,line)){
            Question question = Question::loadFromFile(line);
            Questions[question.getID()] = question;
            questions_list.push_back(question);
        }

        file.close();
    }

    void displayQuiz(){
        cout << "Quiz: " << title << endl;
        for(const auto& question: questions_list){
            question.display();
        }
    }

    void removeQuestion(int question_id){
        if(questions.find(question_id) != questions.end()){
            questions.erase(question_id);
            
            for(auto it = questions_list.begin(); it != questions_list.end(); ++it){
                if(it->getID() == question_id){
                    questions_list.erase(it);
                    break;
                }
            }
        }
    }

    void updateQuestion(Question& question){
        questions[question.getId()] = question;
        for(auto& q: questions_list){
            if(q.getId() == question.getId()){
                q = question;
                break;
            }
        }
    }

    vector<Question> getRandomQuestions(string& category, Difficulty difficulty, int num_questions){
        vector<Question> filtered_questions;

        for(const auto& entry: questions){
            const Question& q = entry.second;
            if(q.hasCategory(category) && q.getDifficulty() == difficulty){
                filtered_questions.push_back(q);
            }
        }

        srand(time(0));
        random_shuffle(filtered_questions.begin(), filtered_questions.end());

        if(num_questions > filtered_questions.size()){
            num_questions = filtered_questions.size();
        }

        return vector<Question>(filtered_questions.begin(), filtered_questions.begin() + num_questions);
        
    }

};