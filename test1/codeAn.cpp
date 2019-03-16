constexpr int add( int x,  int y) noexcept
{
    return x + y;
}

constexpr int mult( int x,  int y) noexcept 
{
    return x * y;
}

constexpr int calc(const int x, const int y, const int z) noexcept
{
    return add(x, mult(y, z));
}
