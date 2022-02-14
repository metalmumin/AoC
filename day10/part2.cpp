#include <iostream>
#include <fstream>
#include <string>
#include <stack>

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
    std::stack<char> orphaned;
    size_t score = 0;

    for (const auto& c : l)
    {
        // Opening brackets enter the stack
        if (isOpenBracket(c))
        {
            //std::cout << c << " enters the stack" << std::endl;
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
            switch(c)
            {
                case ')': score += 3;     break;
                case ']': score += 57;    break;
                case '}': score += 1197;  break;
                case '>': score += 25137; break;
            }

            //std::cout << "Expected " << expected << ", but found " << c << " instead." << std::endl;

            return score;
        }

        if(!s.empty())
        {
            // Stack non-empty, continue looking for mismatching brackets.
            s.pop();
        }
        else
        {
            // Stack empty. Line incomplete. Add orphaned bracket, and continue iterating..
            orphaned.push(c);
            std::cout << "Orphaned " << c << " pushed to stack." << std::endl;
/*
            while(!stack.empty())
            {
                char expected_incomplete = closingBracket(s.top());

                switch(c)
                {
                    case ')': score += score*5 + 1; break;
                    case ']': score += score*5 + 2; break;
                    case '}': score += score*5 + 3; break;
                    case '>': score += score*5 + 4; break;
                }
            }

            return 0;
*/
        }
    }

    return false;
}

int main()
{
    std::ifstream in("input.txt");
    size_t total_score = 0;

    // Iterate each line. Detect & discard corrupted lines.
    for (std::string line; std::getline(in,line,'\n');)
    {
//        std::cout << line << std::endl;
        total_score += lineScore(line);
    }

    std::cout << "Score: " << total_score << " points." << std::endl;

    return 0;
}
