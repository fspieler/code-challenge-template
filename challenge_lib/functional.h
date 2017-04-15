#ifndef FUNCTIONAL_INCLUDES_GUARD
#define FUNCTIONAL_INCLUDES_GUARD
#include <vector>
#include <set>
#include <functional>
template<typename T>
std::pair<std::vector<T>, std::vector<T> > filter(
    const std::vector<T>& input,
    std::function<bool(T)> predicate
)
{
    std::pair<std::vector<T>, std::vector<T> > ret;
    for(const T& e : input)
    {
        if(predicate(e))
        {
            std::get<0>(ret).push_back(e);
        }
        else
        {
            std::get<1>(ret).push_back(e);
        }
    }
    return ret;
}

template<typename T>
std::pair<std::set<T>, std::set<T> > filter(
    const std::set<T>& input,
    std::function<bool(T)> predicate
)
{
    std::pair<std::set<T>, std::set<T> > ret;
    for(const T& e : input)
    {
        if(predicate(e))
        {
            std::get<0>(ret).insert(e);
        }
        else
        {
            std::get<1>(ret).insert(e);
        }
    }
    return ret;
}

template<typename T, typename U>
void foreach(
    const std::vector<T>& input,
    std::function<U(T)> f
)
{
    for(const auto& e : input)
    {
        f(e);
    }
}

template<typename T, typename U>
std::vector<U> each(
    const std::vector<T>& input,
    std::function<U(T)> f
)
{
    std::vector<U> ret;
    for(const auto& e : input)
    {
        ret.push_back(f(e));
    }
    return ret;
}

template<typename T, typename U>
std::set<U> each(
    const std::set<T>& input,
    std::function<U(T)> f
)
{
    std::set<U> ret;
    for(const auto& e : input)
    {
        ret.insert(f(e));
    }
    return ret;
}

template<typename T, typename U>
U foldleft(
        const std::vector<T>& input,
        std::function<U(T,U)> f,
        U initial
)
{
    U ret = initial;
    for(const auto& e : input)
    {
        ret = f(e,ret);
    }
    return ret;
}

template<typename T>
T sumall(const std::vector<T>& input)
{
    return foldleft<T,T>(input,[](T e, T sum)
    {
        return e + sum;
    }, 0);
}

template<typename T>
T productall(const std::vector<T>& input)
{
    return foldleft<T,T>(input,[](T e, T product)
    {
        return e * product;
    }, 1);
}
#endif // FUNCTIONAL_INCLUDES_GUARD
