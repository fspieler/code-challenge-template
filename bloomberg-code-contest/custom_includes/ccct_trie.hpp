Trie::Trie(std::string&& base_str, TMap&& map) :
  _count(1),
  _str(base_str),
  _is_empty_word(false),
  _map(map)
{}

Trie& Trie::add_string(const std::string& s)
{
  auto move_suffix_to_intermediate_node =
    [](Trie& t, int index) -> Trie&
  {
    auto length = t._str.size() - index;
    auto new_str = t._str.substr(index, length);
    auto new_map = std::move(t._map);
    t._str = t._str.substr(0,index);
    t._map[new_str[0]]=Trie(new_str.substr(1,new_str.size()-1),std::move(new_map));
    return t;
  };

  if(!s.size()) return *this;;
  this->_count++;
  if(!_str.size())
  {
    if(_map.size())
    {
      _map[s[0]].add_string(s.substr(1,s.size()-1));
    }
    else
    {
      _str = s;
    }
    return *this;
  }
  std::string common;

  DEBUG(s);
  DEBUG(_str);

  for
    (
      size_t i = 0;
      i < s.size() && i < _str.size();
      ++i
    )
  {
    if(s[i] == _str[i])
    {
      common+=s[i];
    }
    else break;
  }

  DEBUG(common);

  if(common.size() > 0)
  {
    int start= common.size() + 1;
    int length1 = _str.size() - common.size() - 1;
    if(length1>0)
    {
      DEBUG(length1);
      move_suffix_to_intermediate_node(*this,common.size());
    }
    int length2 = s.size() - common.size() - 1;
    if(length2>0)
    {
      DEBUG(length2);
      std::string new_entry = s.substr(start, length2);
      _map[s[common.size()]].add_string(new_entry);
    }
    _str = common;
  }
  else
  {
    move_suffix_to_intermediate_node(*this,0);
    _map[s[0]].add_string(s.substr(1,s.size()-1));
  }

  return *this;
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
