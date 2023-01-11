#include "catch.hpp"


#include <handy/StringUtilities.h>

using namespace ad;


SCENARIO("String join.")
{
    GIVEN("A string collection.")
    {
        const std::string collection[] = {
            "alpha",
            "beta",
            "pizza",
        };

        WHEN("The collection is joined with a delimiter.")
        {
            const std::string delimiter = ", ";
            const std::string joined = join(std::begin(collection), std::end(collection), delimiter);

            THEN("There is no end delimiter.")
            {
                CHECK_FALSE(joined.ends_with(delimiter));
                CHECK(joined.ends_with(collection[std::size(collection) - 1]));
            }

            THEN("The joined string is as expected.")
            {
                const std::string expected = "alpha, beta, pizza";
                CHECK(joined == expected);
            }
        }
    }

    GIVEN("An empty string collection.")
    {
        std::vector<std::string> collection;

        WHEN("The collection is joined with a delimiter.")
        {
            const std::string delimiter = ", ";
            const std::string joined = join(std::begin(collection), std::end(collection), delimiter);

            THEN("The result is empty.")
            {
                CHECK(joined.empty());
            }
        }
    }

    GIVEN("An 1 string collection.")
    {
        std::vector<std::string> collection {"One"};
        WHEN("The collection is joined with a delimiter.")
        {
            const std::string delimiter = ", ";
            const std::string joined = join(std::begin(collection), std::end(collection), delimiter);

            THEN("The result is the element of the collection.")
            {
                CHECK(joined == collection.front());
            }
        }
    }
}


SCENARIO("Substring occurrences counting.")
{
    GIVEN("A string with 5 occurrences of a substring.")
    {
        const std::string sub = "ssuubb";
        const std::string message =
         "1" + sub + "other " + sub + sub + " many words " + sub + " many " + sub;

        WHEN("The occurrences are counted.")
        {
            std::size_t counted = count(message, sub);

            THEN("The result is 5.")
            {
                CHECK(counted == 5);
            }
        }

        WHEN("The occurrences of the whole string are counted within itself.")
        {
            std::size_t counted = count(message, message);

            THEN("The result is 1.")
            {
                CHECK(counted == 1);
            }
        }
    }

    GIVEN("A string.")
    {
        const std::string message = "alpha";

        WHEN("The occurrences of substring it does not contain are counted.")
        {
            std::size_t counted = count(message, "beta");

            THEN("The result is 0.")
            {
                CHECK(counted == 0);
            }
        }
    }
}


SCENARIO("String splits.")
{
    GIVEN("A string with multiple occurences of a delimiter.")
    {
        const std::string delim = "--";
        const std::vector<std::string> tokens = {
            "1",
            "2",
            "3",
            "4",
            "5",
        };
        std::string message = join(tokens.begin(), tokens.end(), delim);
        // Sanity check
        REQUIRE(count(message, delim) == tokens.size() - 1);

        WHEN("The string is (left)split once.")
        {
            auto [left, tail] = lsplit(message, delim);
            THEN("Left is the first element.")
            {
                CHECK(left == tokens.front());
            }
            THEN("One delimiter is dropped, the tail is the rest.")
            {
                CHECK(tail == join(tokens.begin() + 1, tokens.end(), delim));
            }
        }

        WHEN("The string is (right)split once.")
        {
            auto [head, right] = rsplit(message, delim);
            THEN("Right is the last element.")
            {
                CHECK(right == tokens.back());
            }
            THEN("Head the the prefix to right, with one delimiter dropped at the end.")
            {
                CHECK(head == join(tokens.begin(), tokens.end() - 1, delim));
            }
        }

        WHEN("The string is recursively (left)split.")
        {
            std::vector<std::string> splits;

            // Equivalent alternative, but writes the operation twice
            //for(auto [left, tail] = lsplit(message, delim);
            //    !left.empty();
            //    std::tie(left, tail) = lsplit(tail, delim))
            std::string_view left, tail{message};
            while(std::tie(left, tail) = lsplit(tail, delim), !left.empty())
            {
                splits.push_back(std::string{left});
            }

            // Sanity check
            REQUIRE(tail.empty());

            THEN("The result is the initial vector of tokens.")
            {
                CHECK(splits == tokens);
            }
        }

        WHEN("The string is recursively (right)split.")
        {
            std::vector<std::string> splits;

            std::string_view head{message}, right;
            while(std::tie(head, right) = rsplit(head, delim), !right.empty())
            {
                splits.push_back(std::string{right});
            }

            // Sanity check
            REQUIRE(head.empty());

            THEN("The result is the reversed initial vector of tokens.")
            {
                CHECK(std::equal(splits.begin(), splits.end(), tokens.rbegin(), tokens.rend()));
            }
        }
    }

    GIVEN("A string.")
    {
        const std::string message = "A string.";

        WHEN("The string is (left)split on a delimiter it does not contain.")
        {
            auto [left, tail] = lsplit(message, "*");

            THEN("Left is the whole string.")
            {
                CHECK(left == message);
            }
            THEN("Tail is empty.")
            {
                CHECK(tail.empty());
            }
        }

        WHEN("The string is (right)split on a delimiter it does not contain.")
        {
            auto [head, right] = rsplit(message, "*");

            THEN("Right is the whole string.")
            {
                CHECK(right == message);
            }
            THEN("Heade is empty.")
            {
                CHECK(head.empty());
            }
        }

        WHEN("The string is (left)split on a its beginning.")
        {
            auto [left, tail] = lsplit(message, "A ");

            THEN("Left is empty.")
            {
                CHECK(left.empty());
            }
            THEN("Tail is the whole string minus beginning.")
            {
                CHECK(tail == message.substr(2));
            }
        }

        WHEN("The string is (right)split on a its beginning.")
        {
            auto [head, right] = rsplit(message, "A ");

            THEN("Right is the whole string minus beginning.")
            {
                CHECK(right == message.substr(2));
            }
            THEN("Head is empty.")
            {
                CHECK(head.empty());
            }
        }

        WHEN("The string is (left)split on a its ending.")
        {
            auto [left, tail] = lsplit(message, ".");

            THEN("Left is the whole string minus ending.")
            {
                CHECK(left == message.substr(0, message.size() - 1));
            }
            THEN("Tail is empty.")
            {
                CHECK(tail.empty());
            }
        }

        WHEN("The string is (right)split on a its ending.")
        {
            auto [head, right] = rsplit(message, ".");

            THEN("Head is the whole string minus ending.")
            {
                CHECK(head == message.substr(0, message.size() - 1));
            }
            THEN("Right is empty.")
            {
                CHECK(right.empty());
            }
        }

        WHEN("The string is (left)split on itself.")
        {
            auto [left, tail] = lsplit(message, message);

            THEN("Left is empty.")
            {
                CHECK(left.empty());
            }
            THEN("Tail is empty.")
            {
                CHECK(tail.empty());
            }
        }

        WHEN("The string is (right)split on itself.")
        {
            auto [head, right] = rsplit(message, message);

            THEN("Head is empty.")
            {
                CHECK(head.empty());
            }
            THEN("Right is empty.")
            {
                CHECK(right.empty());
            }
        }
    }
}