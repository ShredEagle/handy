#include "catch.hpp"

#include <handy/FunctionTraits.h>
#include <functional>


using namespace ad;
using namespace ad::handy;


namespace {

    float freeFunction(int, int, std::string)
    { return 4.f; }

} // anonymous namespace


const int gInt{5};


SCENARIO("Free function traits.")
{
    // Free function partial specialization
    GIVEN("A free function taking two int, a string, and returning a float.")
    {
        // freeFunction() is declared outside

        THEN("The number of arguments can be queried")
        {
            CHECK(FunctionTraits<decltype(freeFunction)>::arity == 3);
            CHECK(FunctionArity_v<decltype(freeFunction)> == 3);
        }

        THEN("Its arguments and return types are available via FunctionTraits.")
        {
            CHECK(std::is_same_v<
                FunctionTraits<decltype(freeFunction)>::argument_type<0>,
                int>);
            CHECK(std::is_same_v<
                FunctionTraits<decltype(freeFunction)>::argument_type<1>,
                int>);
            CHECK(std::is_same_v<
                FunctionTraits<decltype(freeFunction)>::argument_type<2>,
                std::string>);

            CHECK(std::is_same_v<
                FunctionTraits<decltype(freeFunction)>::return_type,
                float>);
        }
        THEN("Its arguments and return types are available via helpers.")
        {
            CHECK(std::is_same_v<
                FunctionArgument_t<decltype(freeFunction), 0>,
                int>);

            CHECK(std::is_same_v<
                FunctionReturn_t<decltype(freeFunction)>,
                float>);
        }
    }

    // Free function pointer partial specialization
    GIVEN("A pointer to a free function")
    {
        float(*functionPointer)(int, int, std::string);
        using functionPointer_type = float(*)(int, int, std::string);
        auto freeFunctionPtr = freeFunction;

        THEN("The number of arguments can be queried")
        {
            CHECK(FunctionTraits<decltype(functionPointer)>::arity == 3);
            CHECK(FunctionTraits<functionPointer_type>::arity == 3);
            CHECK(FunctionTraits<decltype(freeFunctionPtr)>::arity == 3);
            CHECK(FunctionArity_v<decltype(freeFunction)> == 3);
        }
    }
}


namespace {

    class TestClass
    {
    public:
        void memberFun(double);
        void memberFunConst(double) const;
        static void StaticFun(double);
    };

} // anonymous namespace


SCENARIO("Member functions traits.")
{
    GIVEN("A non-const non-static member function.")
    {
        using function_type = decltype(&TestClass::memberFun);

        THEN("The number of arguments can be queried")
        {
            CHECK(FunctionArity_v<function_type> == 1);
        }

        THEN("The arguments type can be queried")
        {
            CHECK(std::is_same_v<
                FunctionArgument_t<function_type, 0>,
                double>);
        }

        THEN("The return type can be queried")
        {
            CHECK(std::is_same_v<
                FunctionReturn_t<function_type>,
                void>);
        }
    }
    
    GIVEN("A const non-static member function.")
    {
        using function_type = decltype(&TestClass::memberFunConst);

        THEN("The number of arguments can be queried")
        {
            CHECK(FunctionArity_v<function_type> == 1);
        }

        THEN("The arguments type can be queried")
        {
            CHECK(std::is_same_v<
                FunctionArgument_t<function_type, 0>,
                double>);
        }

        THEN("The return type can be queried")
        {
            CHECK(std::is_same_v<
                FunctionReturn_t<function_type>,
                void>);
        }
    }
    
    GIVEN("A static member function.")
    {
        using function_type = decltype(&TestClass::StaticFun);

        THEN("The number of arguments can be queried")
        {
            CHECK(FunctionArity_v<function_type> == 1);
        }

        THEN("The arguments type can be queried")
        {
            CHECK(std::is_same_v<
                FunctionArgument_t<function_type, 0>,
                double>);
        }

        THEN("The return type can be queried")
        {
            CHECK(std::is_same_v<
                FunctionReturn_t<function_type>,
                void>);
        }
    }
}


SCENARIO("Callable traits.")
{
    GIVEN("A lambda function taking a double pointer and return reference to const int.")
    {
        auto lambda = [](double *) -> const int &
        {
            return gInt;
        };

        THEN("The number of arguments can be queried")
        {
            CHECK(FunctionTraits<decltype(lambda)>::arity == 1);
            CHECK(FunctionArity_v<decltype(lambda)> == 1);
        }

        THEN("The return type can be queried")
        {
            CHECK(std::is_same_v<
                typename FunctionTraits<decltype(lambda)>::return_type,
                const int &>);
            CHECK(std::is_same_v<
                FunctionReturn_t<decltype(lambda)>,
                const int &>);
        }
    }

    GIVEN("A std::function taking no parameter and returning a std::pair<int, float>.")
    {
        using function_type = std::function<std::pair<int, float>()>;

        THEN("The number of arguments can be queried")
        {
            CHECK(FunctionTraits<function_type>::arity == 0);
            CHECK(FunctionArity_v<function_type> == 0);
        }

        THEN("The return type can be queried")
        {
            CHECK(std::is_same_v<
                typename FunctionTraits<function_type>::return_type,
                std::pair<int, float>>);
            CHECK(std::is_same_v<
                FunctionReturn_t<function_type>,
                std::pair<int, float>>);
        }
    }

    // The solution does not work with std::bind.
    // Because std::bind seems to have overloaded operator().
    //GIVEN("A std::bind taking a int and returning a float.")
    //{
    //    auto bound = std::bind(&freeFunction, std::placeholders::_1, 5, std::string{"str"});
    //    using bound_type = decltype(bound);

    //    THEN("The number of arguments can be queried")
    //    {
    //        CHECK(FunctionTraits<bound_type>::arity == 1);
    //        CHECK(FunctionArity_v<bound_type> == 1);
    //    }
    //}
}
