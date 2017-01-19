﻿#include "CauchyRand.h"
#include "UniformRand.h"

CauchyRand::CauchyRand(double location, double scale)
    : StableRand(1, 0, scale, location)
{
}

std::string CauchyRand::Name() const
{
    return "Cauchy(" + toStringWithPrecision(GetLocation()) + ", " + toStringWithPrecision(GetScale()) + ")";
}

double CauchyRand::f(double x) const
{
    return StableRand::pdfCauchy(x);
}

double CauchyRand::F(double x) const
{
    return StableRand::cdfCauchy(x);
}

double CauchyRand::Variate() const
{
    return mu + sigma * StandardVariate();
}

double CauchyRand::Variate(double location, double scale)
{
    return location + scale * StandardVariate();
}

double CauchyRand::StandardVariate()
{
    double x, y;
    do {
        x = UniformRand::Variate(-1, 1);
        y = UniformRand::Variate(-1, 1);
    } while (y == 0.0 || x * x + y * y > 1.0);
    return x / y;
}
    
std::complex<double> CauchyRand::CFImpl(double t) const
{
    std::complex<double> x(-sigma * std::fabs(t), mu * t);
    return std::exp(x);
}

double CauchyRand::quantileImpl(double p) const
{
    return mu - sigma / std::tan(M_PI * p);
}

double CauchyRand::quantileImpl1m(double p) const
{
    return mu + sigma / std::tan(M_PI * p);
}

double CauchyRand::Entropy() const
{
    return std::log(4 * sigma * M_PI);
}
