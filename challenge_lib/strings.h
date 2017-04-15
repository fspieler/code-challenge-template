#ifndef STRINGS_INCLUDES_GUARD
#define STRINGS_INCLUDES_GUARD
#include <vector>
#include <string>
#include <sstream>

const std::string WHITESPACE = " \t\n";

template<typename T>
std::string toString(const T& obj){
    std::ostringstream oss;
    oss << obj;
    return oss.str();
}

std::vector<std::string> split(
    const std::string& input,
    const std::string& tokens=WHITESPACE,
    bool includeEmptyTokens=false
)
{
    using namespace std;
    vector<string> ret;
    int tokenIdx = -1;
    for(int i = 0; i < (int)input.size(); ++i)
    {
        char c = input[i];
        if(tokens.find(c) != tokens.npos)
        {
            if(i > tokenIdx+1 || includeEmptyTokens)
            {
                ret.push_back(input.substr(tokenIdx+1, i-tokenIdx-1));
            }
            tokenIdx = i;
        }
    }
    if(tokenIdx != (int)input.size()-1 || includeEmptyTokens)
    {
        ret.push_back(input.substr(tokenIdx+1, input.size()-tokenIdx-1));
    }

    return ret;
}

template<typename T>
std::string join(std::vector<T>& vec, const std::string& str=" ")
{
    std::ostringstream oss;
    bool first = true;
    for(auto e : vec)
    {
        if(first)
        {
            first = false;
        }
        else{
            oss << str;
        }
        oss << e;
    }
    return oss.str();
}
#endif // STRINGS_INCLUDES_GUARD
