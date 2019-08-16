#pragma once
#ifndef LOGGER_STREAM_DETAILS_V2
#define LOGGER_STREAM_DETAILS_V2
#include <cstddef>
#include <utility>

namespace logger_stream
{
namespace detail
{
namespace v2
{

template <std::size_t... f> struct flag_seq
{
    static constexpr const std::size_t values[] = {f...};
    static constexpr const std::size_t size     = sizeof...(f);
    static constexpr const std::size_t last     = values[size - 1];
};

template <typename Seq> struct remove_last
{

    template <typename Indexes> struct apply;

    template <int... I> struct apply<std::index_sequence<I...>>
    {
        using type = flag_seq<Seq::values[I]...>;
    };

    using type = typename apply<std::make_index_sequence<Seq::size - 1>>::type;
};

template <char... S> struct char_list
{
    static constexpr const char chars[sizeof...(S) + 1] = {S..., '\0'};
};

template <std::size_t flag> struct log_format
{
    static constexpr const char        chars[] = {'{', '}'};
    static constexpr const std::size_t size    = sizeof(chars);
};

template <> struct log_format<1>
{
    static constexpr const char        chars[] = {'{', '0', ':', 'x', '}'};
    static constexpr const std::size_t size    = sizeof(chars);
};

template <typename IndexSequence, char... S> struct log_pattern;

template <std::size_t... f, char... S> struct log_pattern<flag_seq<f...>, S...>
{
    using full_seq   = flag_seq<f...>;
    using short_seq  = typename remove_last<full_seq>::type;
    using format_seq = log_format<full_seq::last>;
    template <typename Indexes> struct apply;
    template <int... I> struct apply<std::index_sequence<I...>>
    {
        using type = typename log_pattern<short_seq, S..., format_seq::chars[I]...>::type;
    };

    using type = typename apply<std::make_index_sequence<format_seq::size>>::type;
};
template <char... S> struct log_pattern<flag_seq<>, S...>
{
    using type = char_list<S...>;
};

template <size_t... f>
constexpr auto
make_pattern()
{
    [[gsl::suppress("bounds .3")]] return log_pattern<flag_seq<f...>>::type::chars;
}
} // namespace v2
} // namespace detail
} // namespace logger_stream
#endif // LOGGER_STREAM_DETAILS_V2
