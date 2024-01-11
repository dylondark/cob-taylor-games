#include "triviacontroller.h"
#include <random>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

TriviaController::TriviaController()
{
    // load question data from files, package into question structs and store in questionVec
    std::ifstream file(questionPath);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        question currentQuestion;
        string temp;
        iss >> temp;
        currentQuestion.m_question = QString(temp.c_str());
        iss >> temp;
        currentQuestion.m_ans1 = QString(temp.c_str());
        iss >> temp;
        currentQuestion.m_ans2 = QString(temp.c_str());
        iss >> temp;
        currentQuestion.m_ans3 = QString(temp.c_str());
        iss >> temp;
        currentQuestion.m_ans4 = QString(temp.c_str());
        iss >> temp;
        currentQuestion.m_img = QString(temp.c_str()); // images will be dynamically loaded when the question is displayed, this will be appended onto imgPath
        questionVec.push_back(currentQuestion);
    }
    file.close();
}

question TriviaController::getQuestion()
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

