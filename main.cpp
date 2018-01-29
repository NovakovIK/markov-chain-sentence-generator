#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <random>


template<typename Iter>
Iter randomSelect(Iter begin, Iter end)
{
    static std::random_device randomDevice;
    static std::default_random_engine engine(randomDevice());
    std::uniform_int_distribution<> distribution(0, static_cast<int>(std::distance(begin, end)) - 1);
    std::advance(begin, distribution(engine));
    return begin;
}

std::vector<std::string> readWords(const std::string &path)
{
    std::ifstream text(path);
    if (!text.is_open())
    {
        std::cerr << "Fail to open text file." << std::endl;
    }
    else
    {
        std::vector<std::string> words;
        while(!text.eof())
        {
            std::string word;
            getline(text, word, ' ');
            words.push_back(word);
        }
        return words;
    }
}

std::string generateSentence(const std::string &path, size_t numberOfWords)
{
    auto words = readWords(path);
    std::map<std::string, std::vector<std::string>> map;

    for (auto i = words.begin(); i != words.end() - 1; ++i)
    {
        map[*i].push_back(*(i + 1));
    }

    std::string result = *randomSelect(words.begin(), words.end());

    std::string current = result;
    std::string next;


    for (int i = 0; i < numberOfWords; ++i)
    {
        next = *randomSelect(map[current].begin(), map[current].end());
        result += ' ' + next;
        current = next;
    }

    return result;
}

int main()
{
    std::cout << generateSentence("text", 10) << std::endl;
}