#pragma once

template <class T>
class Aggregator
{
	int _num;
	int _denom;
	T _value;
	constexpr Aggregator(T t, int num, int denom) : _num(num), _denom(denom), _value(t) {}

public:
	explicit constexpr Aggregator(T t) : _num(1), _denom(1),_value(t) {}

	constexpr auto add(const Aggregator<T>& right) const
	{
		return Aggregator<T>
			(normalize(_num*right._denom, _value, right._num *_denom, right._value), _num*right._denom + right._num *_denom, right._denom*_denom );
	}

	constexpr auto multiply (int right) const
	{
		return Aggregator<T>(_value, _num*right, _denom);
	}

	constexpr auto divide(int right) const
	{
		return Aggregator<T>(_value, _num, _denom*right);
	}
	constexpr const T& get() const
	{
		static_assert(_num == _denom, "Not pure value");
		return _value;
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
