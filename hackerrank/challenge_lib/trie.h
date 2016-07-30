#ifndef TRIE_INCLUDES_GUARD
#define TRIE_INCLUDES_GUARD
#include <debug.h>
#include <string>
#include <sstream>
#include <map>
#include <vector>

class Trie
{
  std::map<char,Trie> _map;
  bool _isWord;
  size_t _count;
public:
  Trie() :
    _isWord(false),
    _count(0)
  {}
  void addWord(const std::string& str)
  {
    _count++;
    if(str.size() == 0)
    {
      _isWord = true;
      return;
    }
    _map[str[0]].addWord(str.substr(1,str.size()-1));
  }
private:
  void completionHelper(std::vector<std::string>& ret, const std::string& prefix)
  {
    if(_isWord)
    {
      ret.push_back(prefix);
    }
    for(auto p : _map)
    {
      std::get<1>(p).completionHelper(ret, prefix + std::get<0>(p));
    }
  }
public:
  std::vector<std::string> findCompletions(const std::string& prefix)
  {
    std::vector<std::string> ret;
    auto currentNode = this;
    for(size_t i = 0; i < prefix.size(); ++i)
    {
      currentNode = &currentNode->_map[prefix[i]];
    }
    currentNode->completionHelper(ret, prefix);
    return ret;
  }

  void print(size_t indentation=0)
  {
    std::ostringstream oss;
    size_t tempIndentation = indentation;
    while(tempIndentation-->0)
    {
      oss << "\t";
    }
    std::string indent = oss.str();
    std::cout << indent << "{" << std::endl;
    if(_isWord)
    {
      std::cout << indent << "full word" << std::endl;
    }
    for(auto p : _map)
    {
      std::cout << indent << std::get<0>(p) << ":" << std::endl;
      std::get<1>(p).print(indentation+1);
    }
    std::cout << indent << "}" << std::endl;
  }

};
#endif // TRIE_INCLUDES_GUARD
