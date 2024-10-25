#pragma once

#include <array>
#include <type_traits>


namespace ad {


namespace detail
{

    template <class T, unsigned N = std::rank<T>::value>
    struct combined_extents_impl :
        public std::integral_constant<std::size_t,
                                      std::extent<T, N-1>::value * combined_extents_impl<T, N-1>::value>
    {};

    /// \todo Fix for ad::math types (for which it will wrongly return 1)
    template <class T>
    struct combined_extents_impl<T, 0> : public std::integral_constant<std::size_t, 1>
    {
        static_assert(std::is_array<T>::value || std::is_arithmetic<T>::value,
                      "Only arithmetic types or arrays at the moment.");
    };


    template <class T_element, std::size_t N_size, std::size_t... VN_indices>
    std::array<T_element, N_size> make_filled_array_impl(
        std::index_sequence<VN_indices...>,
        T_element aValue)
    {
        return {{
            (VN_indices, aValue)...
        }};
    }

} // namespace detail



/// @brief Construct an array of N_size elements, filled with `aValue`.
/// @tparam T_element Array element type.
/// @tparam N_size Array size.
template <class T_element, std::size_t N_size>
std::array<T_element, N_size> make_filled_array(T_element aValue)
{
    return detail::make_filled_array_impl<T_element, N_size>(
        std::make_index_sequence<N_size>{},
        aValue);
}



/// \brief Combines all dimensions in an array (the total number of elements stored)
/// \return 1 for scalar types !
template <class T>
struct combined_extents : public detail::combined_extents_impl<T>
{};

template <class T>
static constexpr std::size_t combined_extents_v = combined_extents<T>::value;


template <class T, typename = void>
struct scalar
{};

template <class T>
struct scalar<T, std::enable_if_t<std::is_arithmetic<T>::value>>
{
    typedef T type;
};

template <class T>
struct scalar<T[]>
{
    typedef typename scalar<T>::type type;
};

template <class T, std::size_t N>
struct scalar<T[N]>
{
    typedef typename scalar<T>::type type;
};

template <class T>
using scalar_t = typename scalar<T>::type;

} // namespace ad
