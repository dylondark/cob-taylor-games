#include "triviacontroller.h"
#include <random>
#include <algorithm>

TriviaController::TriviaController() {}

/* TriviaController::question TriviaController::loadQuestions()
{
    question questions;

    // Copy file writing code from leadscores in leaderboardhandler

    return questions;
} */

TriviaController::question TriviaController::getQuestion()
{
    // Use the C++ standard library's random device and generator to generate random indices
    static std::random_device rd;
    static std::mt19937 gen(rd());

    // Create a vector to store the indices of the questionVec vector
    static std::vector<int> indices(questionVec.size());
    static int i = 0;

    // Generate the random index
    std::uniform_int_distribution<> dist(0, indices.size() - 1);
    int index = indices[dist(gen)];

    // Remove the chosen index from the indices vector
    indices.erase(indices.begin() + i);

    // If all the indices have been used, regenerate them
    if (i >= indices.size())
    {
        indices.clear();
        for (int j = 0; j < questionVec.size(); ++j)
        {
            indices.push_back(j);
        }
        i = 0;
    }

    // Return the randomly selected question object
    return questionVec[index];
}

/* TriviaController::question TriviaController::loadAnswers()
{
    question answers;

    // Same as above

    return answers;
} */

TriviaController::question TriviaController::getAnswer()
{
    // Use the C++ standard library's random device and generator to generate random indices
    static std::random_device rd;
    static std::mt19937 gen(rd());

    // Create a vector to store the indices of the questionVec vector
    static std::vector<int> indices(answerVec.size());
    static int i = 0;

    // Generate the random index
    std::uniform_int_distribution<> dist(0, indices.size() - 1);
    int index = indices[dist(gen)];

    // Remove the chosen index from the indices vector
    indices.erase(indices.begin() + i);

    // Return the randomly selected answer object
    return answerVec[index];
}
