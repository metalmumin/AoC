#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>

inline bool isOpenBracket(const char c)
{
    return c == '(' ||
           c == '[' ||
           c == '{' ||
           c == '<';
}

// Translates opening bracket to closing bracket.
char closingBracket(const char c)
{
    switch(c)
    {
        case '(': return ')'; break;
        case '[': return ']'; break;
        case '{': return '}'; break;
        case '<': return '>'; break;
    }
}

// Find syntax error score for string l.
size_t lineScore(const std::string& l)
{
    std::stack<char> s;
    size_t score = 0;

    for (const auto& c : l)
    {
        // Opening brackets enter the stack
        if (isOpenBracket(c))
        {
            s.push(c);
            continue;
        }

        // Closing brackets pop the stack.
        // c != top() means mismatched bracket, and therefore corruption:
        // "A corrupted line is one where a chunk closes with the wrong character"

        if (s.empty()) break; // if there's no stack, then there's no top(), break.
        char expected = closingBracket(s.top());

        if (c != expected)
        {
            return 0; // corrupt, no score, break
        }

        if(!s.empty())
        {
            // Stack non-empty, continue looking for mismatching brackets.
            s.pop();
        }
    }

    // Reverse the Opening brackets stack.
    std::stack<char> reverse;

    while (!s.empty())
    {
        reverse.push(s.top());
        auto c = closingBracket(s.top());

        switch(c)
        {
            case ')': score = score*5 + 1; break;
            case ']': score = score*5 + 2; break;
            case '}': score = score*5 + 3; break;
            case '>': score = score*5 + 4; break;
        }

        s.pop();
    }

    return score;
}

int main()
{
    std::ifstream in("input.txt");
    size_t total_score = 0;
    std::vector<size_t> scores{};

    // Iterate each line. Detect & discard corrupted lines.
    for (std::string line; std::getline(in,line,'\n');)
    {
        auto score = lineScore(line);
        std::cout << score << std::endl;

        if (score != 0)
            scores.emplace_back(score);
    }

    // Sort scores.
    std::sort(scores.begin(), scores.end());

    // Get middle
    auto mid = scores.size()/2;

    std::cout << "Middle score[" << mid << "]: " << scores.at(mid) << " points." << std::endl;

    return 0;
}
