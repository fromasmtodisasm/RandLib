#include "RademacherRand.h"
#include "BernoulliRand.h"

RademacherRand::RademacherRand()
{
}

std::string RademacherRand::Name() const
{
    return "Rademacher";
}

double RademacherRand::P(int k) const
{
    return std::abs(k) == 1 ? 0.5 : 0.0;
}

double RademacherRand::F(int k) const
{
    if (k < -1)
        return 0;
    return (k < 1) ? 0.5 : 1.0;
}

int RademacherRand::Variate() const
{
    return BernoulliRand::StandardVariate() ? 1 : -1;
}

double RademacherRand::Mean() const
{
    return 0;
}

double RademacherRand::Variance() const
{
    return 1;
}

std::complex<double> RademacherRand::CF(double t) const
{
    return std::cos(t);
}

double RademacherRand::Median() const
{
    return 0.0;
}

int RademacherRand::Mode() const
{
    /// any from {-1, 1}
    return Variate();
}

double RademacherRand::Skewness() const
{
    return 0.0;
}

double RademacherRand::ExcessKurtosis() const
{
    return -2.0;
}

double RademacherRand::Entropy()
{
    return M_LN2;
}
