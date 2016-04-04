#include "ProbabilityDistribution.h"
#include <sstream>      // std::ostringstream
#include <iomanip>      // std::setprecision

template < typename T >
ProbabilityDistribution<T>::ProbabilityDistribution()
{
}

template < typename T >
std::string ProbabilityDistribution<T>::toStringWithPrecision(const double a_value, const int n)
{
    std::ostringstream out;
    out << std::setprecision(n) << a_value;
    return out.str();
}

template < typename T >
void ProbabilityDistribution<T>::sample(std::vector<T> &outputData) const
{
    for (T &var : outputData)
        var = variate();
}

template < typename T >
void ProbabilityDistribution<T>::cdf(const std::vector<T> &x, std::vector<double> &y) const
{
    size_t size = x.size();
    if (size > y.size())
        return;
    for (size_t i = 0; i != size; ++i)
        y[i] = F(x[i]);
}

template class ProbabilityDistribution<double>;
template class ProbabilityDistribution<DoublePair>;
template class ProbabilityDistribution< std::vector<double> >;
