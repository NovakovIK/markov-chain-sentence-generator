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

std::string generateSentence(const std::string &path, size_t numberOfWords, size_t order)
{
    if (order < 2)
    {
        std::cerr << "Order must be more then 2.";
        return std::string();
    }
    auto words = readWords(path);
    std::vector<std::string> ngrams;
    for (auto i = words.begin(); i < words.end(); ++i)
    {
        std::string ngram;
        for (int j = 0; j < order - 1; ++j)
        {
            ngram += *(i + j) + ' ';
        }
        ngrams.push_back(ngram);
    }

    std::map<std::string, std::vector<std::string>> map;

    for (auto i = ngrams.begin(); i != ngrams.end() - 1; ++i)
    {
        map[*i].push_back(*(i + 1));
    }


    for (auto &i : ngrams)
    {
        std::cout << i << ':' << std::endl;
        for (auto &j : map[i])
        {
            std::cout << "\t\t" << j << std::endl;
        }
    }

    std::string result = *randomSelect(ngrams.begin(), ngrams.end());

    std::string current = result;
    std::string next;


    for (int i = 0; i < numberOfWords; ++i)
    {
        next = *randomSelect(map[current].begin(), map[current].end());
        result += next;
        current = next;
    }

    return result;
}

int main()
{
    std::cout << generateSentence("text", 10, 2) << std::endl;
}