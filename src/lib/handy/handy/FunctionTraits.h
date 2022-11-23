#pragma once


#include <tuple>
#include <type_traits>


namespace ad {
namespace handy {


// Base template declaration
/// \attention Does not support std:bind
/// \attention In the case of non-static member functions, the trait "disregard" the implicit this parameter.
template <class>
struct FunctionTraits;


// Free functions' partial specialization
// Also serving as the base definition (all other specilization inherit from it)
template <class T_return, class... VT_args>
struct FunctionTraits<T_return(VT_args...)>
{
    using return_type = T_return;

    using arguments = std::tuple<VT_args...>;

    template <std::size_t N_argIndex>
    using argument_type = std::tuple_element_t<N_argIndex, arguments>;

    static constexpr std::size_t arity = sizeof...(VT_args);
};


// Free function pointers partial specialization
template <class T_return, class... VT_args>
struct FunctionTraits<T_return(*)(VT_args...)> : public FunctionTraits<T_return(VT_args...)>
{};


// Non-const member functions partial specialization
template <class T_class, class T_return, class... VT_args>
struct FunctionTraits<T_return(T_class::*)(VT_args...)> : public FunctionTraits<T_return(VT_args...)>
{};


// Const member functions partial specialization
// (lambda are matched against the main template, which direct them to this partial specialization)
template <class T_class, class T_return, class... VT_args>
struct FunctionTraits<T_return(T_class::*)(VT_args...) const> : public FunctionTraits<T_return(VT_args...)>
{};


// Main template definition, chosen whenever no specialization is matching.
// For the provided T_callable type, it will get the type of its operator().
// This will be selected for lambda, std::function.
/// \attention: Does not work with std::bind, as it seems to have an overloaded operator()
template <class T_callable> 
struct FunctionTraits : FunctionTraits<decltype(&std::remove_reference_t<T_callable>::operator())>
{};


//
// Helpers
//
template <class T_callable>
using FunctionReturn_t = typename FunctionTraits<T_callable>::return_type;

template <class T_callable, std::size_t N_argIndex>
using FunctionArgument_t = typename FunctionTraits<T_callable>::template argument_type<N_argIndex>;

template <class T_callable>
using FunctionArgument_tuple = typename FunctionTraits<T_callable>::arguments;

template <class T_callable>
constexpr std::size_t FunctionArity_v = FunctionTraits<T_callable>::arity;

// Note: Attempt to take the callable by value, but it is limited to constexpr values 
// (excl. function pointers, lambdas, ...)
//template <auto F_callable>
//using FunctionReturn_t = typename FunctionTraits<decltype(F_callable)>::return_type;


} // namespace handy
} // namespace ad
