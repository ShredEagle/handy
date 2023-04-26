#pragma once


#include <platform/Filesystem.h>

#include <initializer_list>
#include <optional>
#include <vector>


namespace ad {
namespace resource {

/// \brief Constructed from a list of prefixes,
///  it looks for a given asset in each prefix in order, until found.
class ResourceFinder
{
public:
    ResourceFinder(std::initializer_list<filesystem::path> aPrefixes) :
        mPrefixes{aPrefixes}
    {}

    template <std::input_iterator T_inputIterator> 
    ResourceFinder(T_inputIterator aFirst, T_inputIterator aLast) :
        mPrefixes{aFirst, aLast}
    {}

    std::optional<filesystem::path> find(const filesystem::path & aAsset) const;

    filesystem::path pathFor(const filesystem::path & aAsset) const;

private:
    std::vector<filesystem::path> mPrefixes;
};


inline std::optional<filesystem::path> ResourceFinder::find(const filesystem::path &aAsset) const
{
    for (const auto & prefix : mPrefixes)
    {
        auto candidate = prefix / aAsset;
        if (exists(candidate))
        {
            return candidate;
        }
    }
    return std::nullopt;
}


inline filesystem::path ResourceFinder::pathFor(const filesystem::path & aAsset) const
{
    if(std::optional<filesystem::path> found = find(aAsset); found)
    {
        return *found;
    }
    else
    {
        throw std::invalid_argument{
            "ResourceFinder cannot find a path for resource '" + aAsset.string() + "'."};
    }
}

} // namespace resource
} // namespace ad
