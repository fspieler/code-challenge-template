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
  int _empty_count;
  int _full_count;
  std::string _str;
  bool _is_empty_word;
  bool _is_full_word;
  TMap _map;
  const Trie* _navigate_to_trie(const Trie& t, const std::string& str, int& index);
  void _autocomplete_helper(std::vector<std::pair<std::string, int> >& wordCounts, const std::string& prefix, const Trie& t);
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
  void autocomplete_words(std::vector<std::string>&, const std::string&, int limit=5) const;
  std::ostream& print
    (
     std::ostream& os,
     bool indent=true,
     int level=0
    ) const;
};

std::ostream& operator<<(std::ostream& os, const Trie& t)
{
  return t.print(os);
}
#include <ccct_trie.hpp>

#endif // CCCT_TRIE_INCLUDES_GUARD
