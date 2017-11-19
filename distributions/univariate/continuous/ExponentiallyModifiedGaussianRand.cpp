#include "ExponentiallyModifiedGaussianRand.h"

ExponentiallyModifiedGaussianRand::ExponentiallyModifiedGaussianRand(double location, double variance, double rate)
{
    SetParameters(location, variance, rate);
}

String ExponentiallyModifiedGaussianRand::Name() const
{
    return "Exponentially modified Gaussian(" + this->toStringWithPrecision(GetLocation()) + ", "
                                              + this->toStringWithPrecision(X.Variance()) + ", "
                                              + this->toStringWithPrecision(GetRate()) + ")";
}

void ExponentiallyModifiedGaussianRand::SetParameters(double location, double variance, double rate)
{
    if (variance <= 0)
        throw std::invalid_argument("Exponentially modified Gaussian distribution: variance should be positive");
    if (rate <= 0)
        throw std::invalid_argument("Exponentially modified Gaussian distribution: rate should be positive");

    X.SetLocation(location);
    X.SetVariance(variance);
    Y.SetRate(rate);

    double mu = X.GetLocation();
    double sigma = X.GetScale();
    double beta = Y.GetRate();
    double var = sigma * sigma;
    a = 0.5 * beta * var;
    c = mu + a;
    a += c;
    b = M_SQRT1_2 / sigma;
    v = beta * sigma;
}

double ExponentiallyModifiedGaussianRand::f(const double & x) const
{
    double lambda = Y.GetRate();
    double y = a - x;
    y *= b;
    y = std::erfc(y);
    y *= 0.5 * lambda;
    double exponent = c - x;
    exponent *= lambda;
    exponent = std::exp(exponent);
    return y * exponent;
}

double ExponentiallyModifiedGaussianRand::logf(const double & x) const
{
    double lambda = Y.GetRate();
    double y = a - x;
    y *= b;
    y = std::erfc(y);
    y *= 0.5 * lambda;
    double exponent = c - x;
    exponent *= lambda;
    return std::log(y) + exponent;
}

double ExponentiallyModifiedGaussianRand::F(const double & x) const
{
    double u = Y.GetRate() * (x - X.GetLocation());
    double y = X.F(x);
    double exponent = -u + 0.5 * v * v;
    exponent = std::exp(exponent);
    exponent *= X.F(x - v * X.GetScale());
    return y - exponent;
}

double ExponentiallyModifiedGaussianRand::S(const double & x) const
{
    double u = Y.GetRate() * (x - X.GetLocation());
    double y = X.S(x);
    double exponent = -u + 0.5 * v * v;
    exponent = std::exp(exponent);
    exponent *= X.F(x - v * X.GetScale());
    return y + exponent;
}

double ExponentiallyModifiedGaussianRand::Variate() const
{
    return X.Variate() + Y.Variate();
}

double ExponentiallyModifiedGaussianRand::StandardVariate(RandGenerator &randGenerator)
{
    return NormalRand::StandardVariate(randGenerator) + ExponentialRand::StandardVariate(randGenerator);
}

void ExponentiallyModifiedGaussianRand::Reseed(unsigned long seed) const
{
    X.Reseed(seed);
    Y.Reseed(seed + 1);
}

long double ExponentiallyModifiedGaussianRand::Mean() const
{
    return X.Mean() + Y.Mean();
}

long double ExponentiallyModifiedGaussianRand::Variance() const
{
    return X.Variance() + Y.Variance();
}

std::complex<double> ExponentiallyModifiedGaussianRand::CFImpl(double t) const
{
    return X.CF(t) * Y.CF(t);
}

long double ExponentiallyModifiedGaussianRand::Skewness() const
{
    long double sigma = X.GetScale();
    long double lambda = Y.GetRate();
    long double tmp = 1.0 / (sigma * lambda);
    long double tmpSq = tmp * tmp;
    long double y = 1.0 + tmpSq;
    y = y * y * y;
    y = std::sqrt(y);
    y = tmpSq * tmp / y;
    return y + y;
}

long double ExponentiallyModifiedGaussianRand::ExcessKurtosis() const
{
    long double sigma = X.GetScale();
    long double lambda = Y.GetRate();
    long double tmp = 1.0 / (sigma * lambda);
    tmp *= tmp;
    long double numerator = 1.0 + 2.0 * tmp + 3.0 * tmp * tmp;
    long double denominator = 1.0 + tmp;
    denominator *= denominator;
    long double y = numerator / denominator - 1.0;
    return 3.0 * y;
}

