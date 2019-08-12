#pragma once

#ifndef LOGGER_STREAM_DETAILS_V3
#define LOGGER_STREAM_DETAILS_V3

namespace logger_stream {
namespace detail {
inline namespace v3 {
template <char... S> struct char_list {
  static constexpr const char chars[sizeof...(S) + 1] = {S..., '\0'};
};

template <std::size_t flag> struct log_format {
  static constexpr const char chars[] = {'{', '}'};
  static constexpr const std::size_t size = sizeof(chars);
};

// hex = 1
template <> struct log_format<1> {
  static constexpr const char chars[] = {'{', '0', ':', 'x', '}'};
  static constexpr const std::size_t size = sizeof(chars);
};

template <std::size_t flag, char... S> struct log_pattern {
  using format_seq = log_format<flag>;
  template <typename Indexes> struct apply;
  template <int... I> struct apply<std::index_sequence<I...>> {
    using type = char_list<format_seq::chars[I]..., S...>;
  };

  using type = typename apply<std::make_index_sequence<format_seq::size>>::type;
};

template <std::size_t flag, typename PATTERN, typename F> struct forwarder {
  constexpr explicit forwarder<flag, PATTERN, F>(F &&f) noexcept
      : mf{std::move(f)} {}

  template <typename... Args>
  constexpr decltype(auto) operator()(Args &&... args) const {
    return mf(args...);
  }

private:
  F mf;
};

template <std::size_t flag = 0, typename PATTERN = char_list<>, typename F>
constexpr decltype(auto) make_forwarder(F &&f) noexcept {
  return forwarder<flag, PATTERN, F>(std::forward<F>(f));
}

template <std::size_t flag, typename PATTERN, typename F, typename T>
decltype(auto) operator<<(forwarder<flag, PATTERN, F> &&ap, T &&t);

template <std::size_t flag, char... S, typename F, typename T>
constexpr decltype(auto) operator<<(forwarder<flag, char_list<S...>, F> &&ap,
                                    T &&t) noexcept {
  return make_forwarder<0, log_pattern<flag, S...>::type>(
      [ap = std::forward<forwarder<flag, char_list<S...>, F>>(ap),
       t = std::forward<T>(t)](const char *s, auto &&... a) {
        return ap(s, t, a...);
      });
}

class LogStream {
public:
  LogStream() = default;

  template <std::size_t flag, typename PATTERN, typename F>
  bool operator==(const forwarder<flag, PATTERN, F> &line) noexcept {
    return line(PATTERN::chars);
  }
};
} // namespace v3
} // namespace detail
} // namespace logger_stream
#endif // LOGGER_STREAM_DETAILS_V3
