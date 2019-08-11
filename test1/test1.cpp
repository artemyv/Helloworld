#include <iostream>

namespace detail {

namespace v1 {
template <char... S> struct char_list {
  static constexpr const char chars[sizeof...(S) + 1] = {S..., '\0'};
};

template <char... S>
constexpr const char char_list<S...>::chars[sizeof...(S) + 1];

template <size_t N, char... S> struct log_pattern {
  using type = typename log_pattern<N - 1, '{', '}', S...>::type;
};

template <char... S> struct log_pattern<0, S...> {
  using type = char_list<S...>;
};

template <size_t N> constexpr auto make_pattern() {
  [[gsl::suppress(bounds .3)]] return detail::log_pattern<N>::type::chars;
}

} // namespace v1
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
    remove_last_impl(const int (&a)[N], std::index_sequence<I...>) -> int (&)[N
- 1]
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
            using type = typename log_pattern<N - 1, remove_last(flags), S...,
'{', '}'>::type; } else { using type = char_list<S..., '{', '}'>;
        }
    };

    template <size_t N, template constexpr auto make_pattern(const int
(&flags)[N])
    {
        [[gsl::suppress(bounds .3)]] return detail::log_pattern<N,
flags>::type::chars;
    }

}
*/
namespace v3 {
template <size_t N> class log_pattern {
  char content[2 * N + 1] = {};
  size_t real_size{0};

public:
  constexpr log_pattern() noexcept {
    for (size_t i{0}; i < N; ++i) {
      content[2 * i] = '{';
      content[2 * i + 1] = '}';
    }
    content[2 * N] = 0;
  }
  constexpr const char *get() const noexcept { return content; }
};

template <char... S> struct char_list {
  static constexpr const char chars[sizeof...(S) + 1] = {S..., '\0'};
};

template <size_t N> constexpr auto make_pattern() {
  static constexpr detail::log_pattern<N> p;
  [[gsl::suppress(bounds .3)]] return p.get();
}

} // namespace v3
inline namespace v4 {

template <std::size_t... f> struct flag_seq {
  static constexpr std::size_t values[] = {f...};
  static constexpr std::size_t size = sizeof...(f);
};

template <typename Seq> struct remove_last {

  template <typename Indexes> struct apply;

  template <int... I> struct apply<std::index_sequence<I...>> {
    using type = flag_seq<Seq::values[I]...>;
  };

  using type = typename apply<std::make_index_sequence<Seq::size - 1>>::type;
};

template <char... S> struct char_list {
  static constexpr const char chars[sizeof...(S) + 1] = {S..., '\0'};
};

template <typename IndexSequence, char... S> struct log_pattern;

template <std::size_t... f, char... S>
struct log_pattern<flag_seq<f...>, S...> {
  using full_seq = typename flag_seq<f...>;
  using short_seq = typename remove_last<full_seq>::type;
  using type = typename log_pattern<short_seq, S..., '{', '}'>::type;
};
template <char... S> struct log_pattern<flag_seq<>, S...> {
  using type = char_list<S...>;
};

// template <size_t... f> constexpr auto make_pattern() {
//	[[gsl::suppress(bounds .3)]] return
// detail::log_pattern<flags<f...>>::type::chars;
//}

} // namespace v4
} // namespace detail

int main() {
  using type = detail::flag_seq<0, 1,0,0>;
  using type2 = detail::log_pattern<type>::type;

  std::cout << type2::chars << '\n';
}
