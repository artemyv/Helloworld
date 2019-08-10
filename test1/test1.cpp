#include <iostream>

namespace detail {

inline namespace v1 {
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
		[[gsl::suppress(bounds.3)]]return detail::log_pattern<N>::type::chars;
    }

}
} // namespace detail

int main()
{
    constexpr auto pattern { detail::make_pattern<5>() };

    std::cout << pattern << '\n';
}
