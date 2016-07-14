#ifndef TRIE_INCLUDES_GUARD
#define TRIE_INCLUDES_GUARD
#include <debug.h>
#include <string>
#include <map>
#include <vector>

class Trie;
namespace trie_helper {
  Trie& move_suffix_to_intermediate_node(Trie& t, int index);
}

class Trie
{
public:
  typedef std::map<char,Trie> TMap;
private:
  size_t _count;
  size_t _empty_count;
  size_t _full_count;
  std::string _str;
  bool _is_empty_word;
  bool _is_full_word;
  TMap _map;
  void _autocomplete_helper(std::vector<std::pair<std::string, int> >& wordCounts, const std::string& prefix, const Trie& t) const;
  Trie(TMap&&);
  friend Trie& trie_helper::move_suffix_to_intermediate_node(Trie& t, int index);
public:
  const Trie* _navigate_to_trie(const std::string& str, int& index) const;
  Trie() :
    _count(0),
    _empty_count(0),
    _full_count(0),
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
#include <trie.hpp>

#endif // TRIE_INCLUDES_GUARD
