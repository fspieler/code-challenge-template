#ifndef CCCT_TRIE_INCLUDES_GUARD
#define CCCT_TRIE_INCLUDES_GUARD
#include <ccct_debug.h>
#include <string>
#include <map>
#include <vector>

class Trie
{
public:
  typedef std::map<char,Trie> TMap;
private:
  int _count;
  std::string _str;
  bool _is_empty_word;
  bool _is_full_word;
  TMap _map;
  Trie(TMap&&);
public:
  Trie() :
    _count(),
    _str(),
    _is_empty_word(false),
    _is_full_word(false),
    _map()
  { }
  ~Trie(){}
  friend std::ostream& operator<<(std::ostream&, const Trie&);
  Trie& add_string(const std::string&);
  void next_letters(std::vector<char>&, const std::string&) const;
  std::ostream& print
    (
     std::ostream& os,
     bool indent=false,
     int level=0
    ) const;
};

std::ostream& operator<<(std::ostream& os, const Trie& t)
{
  return t.print(os);
}
#include <ccct_trie.hpp>

#endif // CCCT_TRIE_INCLUDES_GUARD
