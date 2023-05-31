#pragma once


#include <atomic>


namespace ad {


/// \brief Hackish class, intended to compose movable types with atomic data members.
/// \warning This is dangerous, for e.g. if a thread is using the moved from atomic
/// to synchronise with a thread already using the moved to atomic (i.e. sync is lost)
/// Yet this is useful if the move is only part of an initialization process.
template <class T>
struct MovableAtomic : public std::atomic<T>
{
    using std::atomic<T>::atomic;
    using std::atomic<T>::operator=;

    MovableAtomic(MovableAtomic && aOther) :
        std::atomic<T>{aOther.load()}
    {};
};


template <class T>
struct CopyableAtomic : public std::atomic<T>
{
    using std::atomic<T>::atomic;
    using std::atomic<T>::operator=;

    CopyableAtomic(CopyableAtomic & aOther) :
        std::atomic<T>{aOther.load()}
    {};
};


} // namespace ad