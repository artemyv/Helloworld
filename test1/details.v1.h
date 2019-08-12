#pragma once
#ifndef LOGGER_STREAM_DETAILS_V1
#define LOGGER_STREAM_DETAILS_V1

namespace logger_stream {
namespace detail {
namespace v1 {

template <char... S> struct char_list {
  static constexpr const char chars[sizeof...(S) + 1] = {S..., '\0'};
};

template <size_t N, char... S> struct log_pattern {
  using type = typename log_pattern<N - 1, '{', '}', S...>::type;
};

template <char... S> struct log_pattern<0, S...> {
  using type = char_list<S...>;
};

template <size_t N> constexpr auto make_pattern() {
  [[gsl::suppress(bounds .3)]] return log_pattern<N>::type::chars;
}

template <typename F> struct forwarder {
  constexpr explicit forwarder(F &&f) : mf{std::move(f)} {}

  template <typename... Args>
  constexpr decltype(auto) operator()(Args &&... args) const {
    return mf(args...);
  }

private:
  F mf;
};

template <typename F> constexpr decltype(auto) make_forwarder(F &&f) noexcept {
  return forwarder<F>(std::forward<F>(f));
}

template <typename F, typename T>
decltype(auto) operator<<(forwarder<F> &&ap, T &&t) {
  return make_forwarder(
      [ap = std::forward<forwarder<F>>(ap),
       t = std::forward<T>(t)](auto &&... a) { return ap(t, a...); });
}

class LogStream {
public:
  LogStream() = default;

  template <typename F> bool operator==(const forwarder<F> &line) noexcept {
    return line();
  }
};
} // namespace v1
} // namespace detail
#define LOG_STREAM_CALL_V1(logger, level)                                      \
  logger && logger->should_log(level) &&                                       \
      detail::v1::LogStream() ==                                               \
          detail::v1::make_forwarder(                                          \
              [a_logger = logger, a_level = level](auto &&... a) {             \
                a_logger->log(                                                 \
                    spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION},   \
                    a_level, detail::v1::make_pattern<sizeof...(a)>(),         \
                    std::forward<decltype(a)>(a)...);                          \
                return true;                                                   \
              })
} // namespace logger_stream

#endif // LOGGER_DETAILS_V1
