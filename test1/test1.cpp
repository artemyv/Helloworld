#include <iostream>

namespace detail {

namespace v1 {
    template <char... S>
    struct char_list {
        static constexpr const char chars[sizeof...(S) + 1] = { S..., '\0' };
    };

    template <char... S>
    constexpr const char char_list<S...>::chars[sizeof...(S) + 1];

    template <size_t N, char... S>
    struct log_pattern {
        using type = typename log_pattern<N - 1, '{', '}', S...>::type;
    };

    template <char... S>
    struct log_pattern<0, S...> {
        using type = char_list<S...>;
    };

    template <size_t N>
    constexpr auto make_pattern()
    {
        [[gsl::suppress(bounds .3)]] return detail::log_pattern<N>::type::chars;
    }

}
/*
inline namespace v2 {
    template <char... S>
    struct char_list {
        static constexpr const char chars[sizeof...(S) + 1] = { S..., '\0' };
    };

    template <char... S>
    constexpr const char char_list<S...>::chars[sizeof...(S) + 1];

    template <std::size_t N, std::size_t... I>
    constexpr auto
    remove_last_impl(const int (&a)[N], std::index_sequence<I...>) -> int (&)[N - 1]
    {
        return { { a[I]... } };
    }

    template <std::size_t N>
    constexpr auto remove_last(const int (&a)[N]) -> int (&)[N - 1]
    {
        return remove_last_impl(a, std::make_index_sequence<N - 1> {});
    }

    template <size_t N, const int (&flags)[N], char... S>
    struct log_pattern {
        if constexpr (N > 1) {
            using type = typename log_pattern<N - 1, remove_last(flags), S..., '{', '}'>::type;
        } else {
            using type = char_list<S..., '{', '}'>;
        }
    };

    template <size_t N, template constexpr auto make_pattern(const int (&flags)[N])
    {
        [[gsl::suppress(bounds .3)]] return detail::log_pattern<N, flags>::type::chars;
    }

}
*/
namespace v3 {
    template <size_t N>
    class log_pattern {
        char content[2 * N + 1] = {};
        size_t real_size { 0 };

    public:
        constexpr log_pattern() noexcept
        {
            for (size_t i { 0 }; i < N; ++i) {
                content[2 * i] = '{';
                content[2 * i + 1] = '}';
            }
            content[2 * N] = 0;
        }
        constexpr const char* get() const noexcept
        {
            return content;
        }
    };

    template <char... S>
    struct char_list {
        static constexpr const char chars[sizeof...(S) + 1] = { S..., '\0' };
    };

    template <size_t N>
    constexpr auto make_pattern()
    {
        static constexpr detail::log_pattern<N> p;
        [[gsl::suppress(bounds .3)]] return p.get();
    }

}
inline namespace v4 {

    template <std::size_t...>
    struct flags {
    };

    template <typename IndexSequence>
    struct remove_last;

    template <std::size_t... f>
    struct remove_last<flags<f...>> {
        static constexpr std::size_t values[] = { f... };

        template <typename sq>
        struct apply;
        template <int... I>
        struct apply<std::index_sequence<I...>> {
            using type = flags<values[I]...>;
        };

        using type = typename apply<std::make_index_sequence<sizeof...(f) - 1>>::type;
    };
}
} // namespace detail

int main()noexcept
{
    using type = detail::flags<0, 1, 2, 3, 0>;
    using pattern = detail::remove_last<type>::type;

    static_assert(std::is_same<pattern, detail::flags<0, 1, 2, 3>>::value, "!");
}
