#include "UniformDiscreteRand.h"


UniformDiscreteRand::UniformDiscreteRand(int minValue, int maxValue)
{
    setBoundaries(minValue, maxValue);
}

void UniformDiscreteRand::setBoundaries(int minValue, int maxValue)
{
    a = minValue;
    b = maxValue;

    if (b < a)
        swapBoundaries();

    n = b - a + 1;
    nInv = 1.0 / n;
}

void UniformDiscreteRand::swapBoundaries()
{
    a += b;
    b -= a;
    a += b;
    b = -b;
}

double UniformDiscreteRand::P(int k) const
{
    if (k < a || k > b)
        return 0;
    return nInv;
}

double UniformDiscreteRand::F(double x) const
{
    return nInv * (std::floor(x) - a + 1);
}

int UniformDiscreteRand::variate()
{
    /// If we use modulo instead it would always return odd-even-odd-... values
    double rv = .5 + (signed)BasicRandGenerator::getRand() * BasicRandGenerator::maxInv(); /// ~ U(0,1)
    rv *= (n - 1); /// ~ U(0, b - a)
    return std::round(rv + a); /// ~ U(a, b)
}
