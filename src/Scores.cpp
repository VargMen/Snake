#include "Scores.hpp"

#include <algorithm>

void Scores::updateScores(const std::vector<Score>& newScores)
{
    if(newScores.empty())
        return;

    std::fstream scoreFile{ m_scoresFilePath };

    std::vector<Score> previousScores { parseScores(scoreFile) };

    for(const auto& score: newScores)
    {
        auto it { std::find_if(previousScores.begin(), previousScores.end(),
                               [score](const Score& prevScore)
                               {return score.m_name == prevScore.m_name; })
        };

        if (it != previousScores.end())
        {
            if(score.m_score > it->m_score)
                it->m_score = score.m_score;
        }
        else
        {
            previousScores.push_back(score);
        }
    }

    std::sort(previousScores.begin(), previousScores.end(),
              [](const Score& score_1, const Score& score_2)
              {return score_1.m_score > score_2.m_score; });

    scoreFile.close();

    saveScores(previousScores, m_scoresFilePath);

    scoreFile.close();
}

std::vector<Score> Scores::parseScores(std::fstream& scoreFile)
{
    std::vector<Score> scores{};
    std::string line;

    while (std::getline(scoreFile, line))
    {
        size_t colonIndex { line.find(':') };
        if(colonIndex != std::string::npos)
        {
            std::string name { line.substr(2, colonIndex - 2) };
            int score { stoi(line.substr(colonIndex + 2)) };
            scores.emplace_back(name, score);
        }
    }

    return scores;
}

void Scores::saveScores(const std::vector<Score>& scores,
                const char* scoreFilePath)
{
    std::ofstream scoresFile{ scoreFilePath, std::ios::out | std::ios::trunc };

    int i {1};
    for(const auto& score: scores)
    {
        scoresFile << i << '.' << score.m_name << ": " << score.m_score << std::endl;
        ++i;
    }
}
