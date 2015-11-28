Trie::Trie(TMap&& map) :
  _count(1),
  _str(),
  _map(map)
{}

Trie& Trie::add_string(const std::string& s)
{
  auto move_suffix_to_intermediate_node =
    [](Trie& t, int index) -> Trie&
  {
    int length = t._str.size() - index;
    if(length < 0)
    {
      return t;
    }
    t._is_full_word = false;
    auto new_str = t._str.substr(index, length);
    auto new_map = std::move(t._map);
    t._str = t._str.substr(0,index);
    Trie& newTrie = t._map[new_str[0]];
    newTrie.add_string(new_str.substr(1,new_str.size()-1));
    newTrie._map = std::move(new_map);
    newTrie._count = t._count - 1;
    return t;
  };

  this->_count++;
  if(!s.size()){
    _is_empty_word=true;
    return *this;
  }
  if(!_str.size())
  {
    if(_map.size())
    {
      _map[s[0]].add_string(s.substr(1,s.size()-1));
    }
    else
    {
      _str = s;
      _is_full_word=true;
    }
    return *this;
  }

  int common_index=-1;
  for
    (
      size_t i = 0;
      i < s.size() && i < _str.size();
      ++i
    )
  {
    if(s[i] == _str[i])
    {
      common_index=i;
    }
    else break;
  }

  if(common_index >= 0)
  {
    int start= common_index+1;
    int length1 = _str.size() - start;
    if(length1>0)
    {
      move_suffix_to_intermediate_node(*this,start);
    }
    int length2 = s.size() - start;
    if(length2>0)
    {
      length2--;
      std::string new_entry = s.substr(start+1, length2);
      _map[s[start]].add_string(new_entry);
    }
    _str = _str.substr(0,start);
  }
  else
  {
    move_suffix_to_intermediate_node(*this,0);
    _map[s[0]].add_string(s.substr(1,s.size()-1));
  }

  return *this;
}

void Trie::next_letters(std::vector<char>& vc, const std::string& s) const
{
  if(s.size() < _str.size())
  {
    vc.push_back(_str[s.size()]);
    return;
  }
  else if(s.size() == _str.size())
  {
    for(auto& kv : _map)
    {
      vc.push_back(kv.first);
    }
    return;
  } else // s.size() > _str.size()
  {
    for(size_t i = 0; i < s.size() && i < _str.size(); ++i)
    {
      if(s[i] != _str[i]) return;
    }
    auto it = _map.find(s[_str.size()]);
    if(it == _map.end()) return;
    std::string new_str = s.substr(_str.size()+1, s.size()-_str.size());
    _map.at(s[_str.size()]).next_letters(vc, new_str);
  }
}

std::ostream& Trie::print
  (
   std::ostream& os,
   bool indent,
   int level
  ) const
{
  std::string newline = indent ? "\n" : ", ";
  std::string outer_indent;
  int temp = level;
  while(temp-->0)
  {
    outer_indent+="\t";
  }
  std::string inner_indent = indent ? outer_indent + '\t' : "";
  os << "{ trie " << newline;

  os << inner_indent << "count: " << _count << newline;
  os << inner_indent << "is empty a word?: " << (_is_empty_word?"true":"false") << newline;
  os << inner_indent << "is full a word?: " << (_is_full_word?"true":"false") << newline;
  if(_str.size() >= 1)
  {
    os << inner_indent << "base string: \"" << _str << '\"' << newline;
  }
  if(_map.size() >= 1)
  {
    for(auto &kv : _map)
    {
      os << inner_indent << kv.first << ": ";
      kv.second.print(os,indent,indent?level+1:0);
    }
  }
  os << outer_indent << "}" << newline;
  return os;
}
