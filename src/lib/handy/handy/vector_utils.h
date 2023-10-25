#pragma once

#include <array>
#include <vector>

namespace ad {

    template <class T_element>
    std::size_t getStoredSize(const std::vector<T_element> & aVector)
    {
        return sizeof(T_element) * aVector.size();
    }

    
    // see: https://stackoverflow.com/a/42915152/1027706
    template <class T_element, std::size_t N_length>
    std::vector<T_element> makeVector(std::array<T_element, N_length> aElements)
    {
        return std::vector<T_element>{
            std::make_move_iterator(std::begin(aElements)),
            std::make_move_iterator(std::end(aElements)),
        };
    }


    /// @brief Helper to initialize a vector from a "list" of value, accepting move-only types
    /// @note Because std::vector ctor taking std::initializer_list<> 
    /// does not allow to initialize a vector of move-only type
    /// @see https://stackoverflow.com/a/8468817/1027706
    template <class... VT_element>
    auto makeVector(VT_element &&... vaElements)
    {
        return makeVector(std::to_array({std::forward<VT_element>(vaElements)...}));
    }

} // namespace ad
