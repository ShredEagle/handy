#pragma once


#include <string_view>

namespace ad {
// Note under any additional namespace because it should be very pervasive.

/// \brief Join the convertible-to-string element in interval [aFirst, aLast) with aDelimiter in between.
template <class T_inputIt>
std::string join(T_inputIt aFirst, T_inputIt aLast, std::string_view aDelimiter)
{
    std::string joined;
    if(aFirst != aLast)
    {
        joined += *aFirst;
        while(++aFirst != aLast)
        {
            // no overload for operator+ with string_view as rhs
            // see: https://stackoverflow.com/q/44636549/1027706
            joined.append(aDelimiter);
            joined += *aFirst;
        }
    }
    return joined;
}


/// \brief Join into aOut, using the output operator over the iterated elements.
template <class T_inputIt>
std::ostream & join(std::ostream & aOut, T_inputIt aFirst, T_inputIt aLast, std::string_view aDelimiter)
{
    if(aFirst != aLast)
    {
        aOut << *aFirst;
        while(++aFirst != aLast)
        {
            aOut << aDelimiter << *aFirst;
        }
    }
    return aOut;
}


// Note:
// Functions below are not templated at the moment (compilation times and implementation complexity),
// but they might be if the need arises.

/// \brief Counts occurrences of `aOccurrence` substring within `aString`.
inline std::size_t count(std::string_view aString, std::string_view aOccurrence)
{
    std::size_t count = 0;
    for(std::string_view::size_type pos = aString.find(aOccurrence);
        pos != std::string_view::npos;
        pos = aString.find(aOccurrence, pos + aOccurrence.size()))
    {
        ++count; 
    }
    return count;
}


/// \return a pair {left, tail}
inline std::pair<std::string_view, std::string_view>
lsplit(std::string_view aString, std::string_view aDelimiter)
{
    std::string_view::size_type delimiter = aString.find(aDelimiter);
    std::string_view head = aString.substr(0, delimiter);
    // It is safe for erase second argument to go out of bound
    return {
        head, 
        aString.substr(std::min(head.size() + aDelimiter.size(), aString.size()))
    };
}


/// \return a pair {head, right}
/// \warning right will contain everything from the last occurrence of delimiter to the end.
/// If there is no delimiter present, right will contain the whole `aString`.
inline std::pair<std::string_view, std::string_view>
rsplit(std::string_view aString, std::string_view aDelimiter)
{
    std::string_view::size_type delimiter = aString.rfind(aDelimiter);
    if(delimiter == std::string_view::npos)
    {
        return { 
            "",
            aString
        };
    }
    else
    {
        return {
            aString.substr(0, delimiter), 
            aString.substr(delimiter + aDelimiter.size())
        };
    }
}


} // namespace ad
