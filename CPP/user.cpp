#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

class user
{
public:
    int score;

    User(const std::string &name) : name(name), score(0) {}

    void take_quiz(Quiz &quiz)
    {
        int correct_count = 0;
        auto selected_questions = quiz.get_random_questions();

        clock_t start = clock();

        for (const auto &question : selected_questions)
        {
            std::cout << question.question_text << "\n";
            for (size_t i = 0; i < question.options.size(); ++i)
            {
                std::cout << i + 1 << ". " << question.options[i] << "\n";
            }
            int user_answer;
            std::cout << "Your answer: ";
            std::cin >> user_answer;
            if (question.check_answer(user_answer - 1))
            {
                ++correct_count;
            }
        }

        clock_t end = clock();

        double time_taken = double(end - start) / CLOCKS_PER_SEC;

        score = correct_count * 10;
        quiz_attempts.push_back(quiz.id);
        std::cout << "You scored: " << score << "\n";
        std::cout << "Total time spending: " << time_taken << "\n";

        void generate_report()
        {
            std::cout << "User: " << name << "\n";
            std::cout << "Score: " << score << "\n";
        };
    }
};

