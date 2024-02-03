#ifndef SCORES_H
#define SCORES_H

#include <string>
#include <fstream>
#include <vector>

struct Score
{
    Score(const std::string& name, int score)
            :m_name{name}, m_score{score}
    {
    }

    int m_score{};
    std::string m_name{};
};

class Scores
{
public:
    Scores(const char* scoresFilePath)
            :m_scoresFilePath{scoresFilePath}
    {
    }

    void updateScores(const std::vector<Score>& newScores);

private:
    std::vector<Score> parseScores(std::fstream& scoreFile);
    void saveScores(const std::vector<Score>& scores,
                    const char* scoreFilePath);

private:
    std::vector<Score> m_scores{};
    const char* m_scoresFilePath{};
};
#endif //SCORES_H
