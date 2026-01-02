#pragma once

#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <string>
#include <tuple>
#include <variant>
#include <iostream>
#include <stdexcept>

#include "../Core/Types.hpp"

/* Next steps:
 *     user-defined formatting, as define a Foo struct and how to handle it in the to_string_any;
 *     user-defined format rules, as in user define a "%{foo}" that prints the type of the value;
 *     
 *     format rules:
 *     - '\d' = placement {word}
 *     - format("%{1}%{0}", "abc", "123") -->  "123abc"
 * 
 *     - 'a' = align {number} {left} {center} {right} {spacing character}
 *     - format("%{a}", 10, "", 33, "", " ")             -->  "    33    "
 *     - format("%{a}", 12, "<3", "hello!", ":B", " - ") -->  "<3 - hello! - :B"
 *     - format("%{a}", 5, "A", "B", "C", "()")          -->  "A()B()C"
 *
 *     - 'r' = repeat {number} {word}
 *     - format("%{r}", 5, 33)  -->  "3333333333"
 *     - format("%{r}", 4, 'a') -->  "aaaa"
 *     
 *     - '-' = reverse {word}
 *     - format("%{-}", "abc")        -->  "cba"
 *     - format("%{-}", 13)           -->  "31"
 *     - format("%{-}", "sucafrisex") -->  "xesirfacus"
 */

namespace WSDC {

namespace Format {


template <std::size_t I = 0, typename... Ts>
std::variant<Ts...> tuple_runtime_get(std::size_t index, const std::tuple<Ts...>& tup) {
    using ReturnType = std::variant<Ts...>;
    constexpr std::size_t N = sizeof...(Ts);

    if constexpr (I < N) {
        if (index == I) {
            return ReturnType(std::in_place_index<I>, std::get<I>(tup));
        } else {
            return WSDC::Format::tuple_runtime_get<I + 1, Ts...>(index, tup);
        }
    } else {
        throw std::out_of_range("tuple_runtime_get: index out of range");
    }
}


template <typename T>
constexpr std::string to_string_any(const T& value) {
    if constexpr (std::is_same_v<T, std::string>) {
        return value;
    } else if constexpr (std::is_same_v<T, const char*>) {
        return std::string(value);
    } else if constexpr (std::is_same_v<T, char*>) {
        return std::string(value);
    } else if constexpr (std::is_same_v<T, char>) {
        return std::string("") + value;
    } else if constexpr (std::is_convertible_v<T, std::string>) {
        return std::string(value);
    } else if constexpr (std::is_arithmetic_v<T>) {
        return std::to_string(value);
    } else {
        throw std::runtime_error("not printable");
    }
}


template <typename... Types>
constexpr std::string format(const std::string& fmt, const Types&... args) {
    std::string ret;
    auto arguments = std::make_tuple( args... );
    std::size_t arg_index = 0;

    for (std::size_t i = 0; i < fmt.size(); ++i) {
        if (fmt[i] == '$' && i + 2 < fmt.size() && fmt[i+1] == '{') {
            auto variant_value = WSDC::Format::tuple_runtime_get(arg_index, arguments);

            if (fmt[i+2] != '}') {
                if (fmt[i+3] != '}') {
                    throw std::runtime_error("format call not closed");
                }
                
                switch(fmt[i+2]) {
                    case '^':
                        std::visit([&ret](const auto& value) {
                            ret += to_string_any(sizeof(value));
                        }, variant_value);
                        break;
                    default:
                        throw std::runtime_error(WSDC::Format::format("format command \'${}\' not found", fmt[i+2]));
                }
                i += 3;
            } else {
                std::visit([&ret](const auto& value) {
                    ret += WSDC::Format::to_string_any(value);
                }, variant_value);
                i += 2;
            }
            ++arg_index;
            continue;
        }
        ret.push_back(fmt[i]);
    }
    return ret;
}

inline std::string format(const std::string& fmt) {
    return fmt;
}

template <typename... Args>
void format_p(std::string& fmt, Args... args) {
    const auto cpy = fmt;
    fmt = WSDC::Format::format(cpy, args...);
}


} // namespace Format

} // namespace WSDC
