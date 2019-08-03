#pragma once

constexpr int mul(int left, int right)
{
	return left * right;
}

template <class T, int nom = 1, int denom = 1>
class Aggregator
{
	T m_value;

public:
	explicit constexpr Aggregator(T t) : m_value(t) {}

	template<int right_nom, int right_denom>
	constexpr auto add(const Aggregator<T, right_nom, right_denom>& right) const
	{
		return Aggregator<T, nom*right_denom + right_nom * denom, right_denom*denom>
			(normalize(nom*right_denom, m_value, right_nom *denom, right.m_value));
	}

	constexpr auto multiply (int right) const
	{
		return Aggregator<T, mul(nom,right), denom>(m_value);
	}

	constexpr auto divide(int right) const
	{
		return Aggregator<T, nom, mul(denom,right)>(m_value );
	}
	constexpr const T& get() const
	{
		static_assert(nom == denom, "Not pure value");
		return m_value;
	}
};

template <class T, int nom, int denom>
constexpr auto operator+(const Aggregator<T, nom, denom>& left, const T& right)
{
	return left.add (Aggregator{ right });
}

template <class T, int nom, int denom, int right_nom, int right_denom>
constexpr auto operator+(const Aggregator<T, nom, denom>& left, const Aggregator<T, right_nom, right_denom>& right)
{
	return  left.add( right );
}


template <class T, int nom, int denom>
constexpr auto operator *(const Aggregator<T, nom, denom>& left, int right)
{
	return left.multiply(right);
}

template <class T, int nom, int denom>
constexpr auto operator /(const Aggregator<T, nom, denom>& left, int right)
{
	return left.divide(right);
}
