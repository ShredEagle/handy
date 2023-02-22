#pragma once


#include <memory>
#include <string>

#include <cctype>


namespace ad {
namespace handy {


namespace detail {

    // see: https://stackoverflow.com/a/14530993/1027706
    void decodeUrl(char *dst, const char *src)
    {
        char a, b;
        while (*src) {
                if ((*src == '%') &&
                    ((a = src[1]) && (b = src[2])) &&
                    (std::isxdigit(a) && std::isxdigit(b))) {
                        if (a >= 'a')
                                a -= 'a'-'A';
                        if (a >= 'A')
                                a -= ('A' - 10);
                        else
                                a -= '0';
                        if (b >= 'a')
                                b -= 'a'-'A';
                        if (b >= 'A')
                                b -= ('A' - 10);
                        else
                                b -= '0';
                        *dst++ = 16*a+b;
                        src+=3;
                } else if (*src == '+') {
                        *dst++ = ' ';
                        src++;
                } else {
                        *dst++ = *src++;
                }
        }
        *dst++ = '\0';
    }

} // namespace detail


/// \brief Decode an url encoded string.
std::string decodeUrl(std::string_view aUrlEncoded)
{
    // The decoded string cannot be longer than the url encoded string.
    std::unique_ptr<char[]> destination{new char[aUrlEncoded.size() + 1]};
    detail::decodeUrl(destination.get(), aUrlEncoded.data());
    return {destination.get()};
}

} // namespace handy
} // namespace ad
