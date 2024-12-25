#include "tempQuizQuestion.h"

Question::Question(int question_id, const string& question_text, const vector<string>& options, 
                  const vector<string>& category, int correct_answer, Difficulty difficulty)
    : question_id(question_id),
      question_text(question_text),
      options(options),
      correct_answer(correct_answer),
      category(category),
      difficulty(difficulty) {}