#ifndef SETS_INCLUDES_GUARD
#define SETS_INCLUDES_GUARD
#include <set>

template<typename T>
std::set<T> set_union(const std::set<T>& s1, const std::set<T>& s2)
{
    std::set<T> ret;
    for(T e : s1)
    {
        ret.insert(e);
    }
    for(T e: s2)
    {
        ret.insert(e);
    }
    return ret;
}

template<typename T>
std::set<T> set_intersection(const std::set<T>& s1, const std::set<T>& s2)
{
    std::set<T> ret;
    for(T e : s1)
    {
        if(s2.count(e))
        {
            ret.insert(e);
        }
    }
    return ret;
}
#endif //SETS_INCLUDES_GUARD
