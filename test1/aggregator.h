#pragma once

template <class T>
class Aggregator
{
	int m_nom;
	int m_denom;
	T m_value;
	constexpr Aggregator(T t, int nom, int denom) : m_nom(nom), m_denom(denom), m_value(t) {}

public:
	explicit constexpr Aggregator(T t) : m_nom(1), m_denom(1),m_value(t) {}

	constexpr auto add(const Aggregator<T>& right) const
	{
		return Aggregator<T>
			(normalize(m_nom*right.m_denom, m_value, right.m_nom *m_denom, right.m_value), m_nom*right.m_denom + right.m_nom *m_denom, right.m_denom*m_denom );
	}

	constexpr auto multiply (int right) const
	{
		return Aggregator<T>(m_value, m_nom*right, m_denom);
	}

	constexpr auto divide(int right) const
	{
		return Aggregator<T>(m_value, m_nom, m_denom*right);
	}
	constexpr const T& get() const
	{
		static_assert(m_nom == m_denom, "Not pure value");
		return m_value;
	}
};

template <class T>
constexpr auto operator+(const Aggregator<T>& left, const T& right)
{
	return left.add (Aggregator{ right });
}

template <class T>
constexpr auto operator+(const Aggregator<T>& left, const Aggregator<T>& right)
{
	return  left.add( right );
}


template <class T>
constexpr auto operator *(const Aggregator<T>& left, int right)
{
	return left.multiply(right);
}

template <class T>
constexpr auto operator /(const Aggregator<T>& left, int right)
{
	return left.divide(right);
}
