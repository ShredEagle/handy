#pragma once

#include <functional>
#include <iostream>
#include <type_traits>


namespace ad {


class [[nodiscard]] Guard
{
    // So it can disable the Guard
    template <class> friend class ResourceGuard;

public:
    typedef std::function<void(void)> release_fun;

    Guard(release_fun aReleaser) :
        mReleaser(std::move(aReleaser))
    {}

    // Non-copyable
    Guard(const Guard &) = delete;
    Guard & operator=(const Guard &) = delete;

    // Movable
    Guard(Guard && aOther) :
        mReleaser{std::move(aOther.mReleaser)}
    {
        aOther.mReleaser = &Guard::turnOff;
    }

    Guard & operator=(Guard && aOther)
    {
        mReleaser(); // Call current releaser before taking the releaser from aOther.
        mReleaser = std::move(aOther.mReleaser);
        aOther.mReleaser = &Guard::turnOff;
        return *this;
    }

    ~Guard()
    {
        try
        {
            mReleaser();
        }
        catch(...)
        {
            std::cerr << "Catastrophic failure: guard release threw an exception"
                      << std::endl;
        }
    }

private:
    static void turnOff()
    {}

    release_fun mReleaser;
};

template <class T>
class [[nodiscard]] ResourceGuard
{
public:
    typedef std::function<void(T &)> release_fun;

    ResourceGuard(T aResource, release_fun aReleaser):
        mResource{std::move(aResource)},
        // Note: bind a copy, not a reference. Otherwise move sematic would lead to UB.
        mGuard{std::bind(aReleaser, mResource)}
    {}

    // Movable
    ResourceGuard(ResourceGuard && aOther) = default;
    ResourceGuard & operator=(ResourceGuard &&) = default;

    /*implicit*/ operator const T& () const
    {
        return mResource;
    }

    const T & get() const
    {
        return mResource;
    }

    /// \brief Allows to change the resource managed by the ResourceGuard.
    ///
    /// The previous resource will be released.
    void resetResource(T aResource, release_fun aReleaser)
    {
        mResource = std::move(aResource);
        mGuard = Guard{std::bind(aReleaser, mResource)};
    }

    /// \brief Release ownership of the resource.
    T release()
    {
        T resource; // Default constructed resource to replace mResource
        std::swap(mResource, resource);
        mGuard.mReleaser = Guard::turnOff; 
        return resource;
    }

private:
    T mResource;
    Guard mGuard;
};

template <class T>
ResourceGuard<T> guard(T aResource, typename ResourceGuard<T>::release_fun aReleaser) {
    return ResourceGuard<T>(std::move(aResource), std::move(aReleaser));
}


} // namespace ad
