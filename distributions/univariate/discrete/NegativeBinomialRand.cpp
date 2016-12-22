#include "NegativeBinomialRand.h"
#include "../continuous/UniformRand.h"
#include "../continuous/ExponentialRand.h"

template< typename T >
NegativeBinomialRand<T>::NegativeBinomialRand(T number, double probability)
{
    SetParameters(number, probability);
}

template< typename T >
std::string NegativeBinomialRand<T>::Name() const
{
    return "Negative Binomial(" + toStringWithPrecision(GetNumber()) + ", " + toStringWithPrecision(GetProbability()) + ")";
}

template< typename T >
void NegativeBinomialRand<T>::SetValidParameters(T number, double probability)
{
    r = (number > 0) ? number : 1;
    p = (probability > 1.0 || probability < 0.0) ? 0.5 : probability;
}

template< typename T >
void NegativeBinomialRand<T>::SetParameters(T number, double probability)
{
    SetValidParameters(number, probability);
    q = 1.0 - p;
    logP = std::log(p);
    logQ = std::log1p(-p);
    GammaRV.SetParameters(r, p / q);
    qDivP = GammaRV.GetScale();
    pdfCoef = r * logP;
    pdfCoef -= GammaRV.GetLogGammaFunction();

    if (GetIdOfUsedGenerator() == TABLE) {
        /// table method
        table[0] = p;
        double prod = p;
        for (int i = 1; i < tableSize; ++i)
        {
            prod *= q;
            table[i] = table[i - 1] + prod;
        }
    }
}

template< typename T >
double NegativeBinomialRand<T>::P(int k) const
{
    if (k < 0)
        return 0.0;
    double y = std::lgamma(r + k);
    y -= std::lgamma(k + 1);
    y += k * logQ;
    y += pdfCoef;
    return std::exp(y);
}

template< typename T >
double NegativeBinomialRand<T>::F(int k) const
{
    return (k < 0) ? 0.0 : 1.0 - RandMath::regularizedBetaFun(q, k + 1, r);
}

template< >
NegativeBinomialRand<int>::GENERATOR_ID NegativeBinomialRand<int>::GetIdOfUsedGenerator() const
{
    /// if r is small, we use two different generators for two different cases:
    /// if p < 0.08 then the tail is too heavy
    /// (probability to be in main body is less than 0.75),
    /// then we return highest integer less than variate from exponential distribution
    /// otherwise we choose table method
    if (r < 10)
        return (p < 0.08) ? EXPONENTIAL : TABLE;
    return GAMMA_POISSON;
}

template< >
NegativeBinomialRand<double>::GENERATOR_ID NegativeBinomialRand<double>::GetIdOfUsedGenerator() const
{
    return GAMMA_POISSON;
}

template< typename T >
int NegativeBinomialRand<T>::variateThroughGammaPoisson() const
{
    return PoissonRand::Variate(GammaRV.Variate());
}

template<>
int NegativeBinomialRand<int>::variateGeometricByTable() const
{
    double U = UniformRand::StandardVariate();
    /// handle tail by recursion
    if (U > table[tableSize - 1])
        return tableSize + variateGeometricByTable();
    /// handle the main body
    int x = 0;
    while (U > table[x])
        ++x;
    return x;
}

template<>
int NegativeBinomialRand<int>::variateGeometricThroughExponential() const
{
    return std::floor(ExponentialRand::Variate(-logQ));
}

template<>
int NegativeBinomialRand<int>::variateByTable() const
{
    double var = 0;
    for (int i = 0; i < r; ++i) {
        var += variateGeometricByTable();
    }
    return var;
}

template<>
int NegativeBinomialRand<int>::variateThroughExponential() const
{
    double var = 0;
    for (int i = 0; i < r; ++i) {
        var += variateGeometricThroughExponential();
    }
    return var;
}

template<>
int NegativeBinomialRand<double>::Variate() const
{
    return variateThroughGammaPoisson();
}

template<>
int NegativeBinomialRand<int>::Variate() const
{
    GENERATOR_ID genId = GetIdOfUsedGenerator();
    if (genId == TABLE)
        return variateByTable();
    return (genId == EXPONENTIAL) ? variateThroughExponential() : variateThroughGammaPoisson();
}

template<>
void NegativeBinomialRand<double>::Sample(std::vector<int> &outputData) const
{
    for (int &var : outputData)
        var = variateThroughGammaPoisson();
}

template<>
void NegativeBinomialRand<int>::Sample(std::vector<int> &outputData) const
{
    GENERATOR_ID genId = GetIdOfUsedGenerator();
    if (genId == TABLE) {
        for (int & var : outputData)
            var = variateByTable();
    }
    else if (genId == EXPONENTIAL) {
        for (int & var : outputData)
            var = variateThroughExponential();
    }
    else {
        for (int &var : outputData)
            var = variateThroughGammaPoisson();
    }
}

template< typename T >
double NegativeBinomialRand<T>::Mean() const
{
    return qDivP * r;
}

template< typename T >
double NegativeBinomialRand<T>::Variance() const
{
    return qDivP * r / p;
}

template< typename T >
std::complex<double> NegativeBinomialRand<T>::CF(double t) const
{
    if (t == 0)
        return 1;
    std::complex<double> denominator(1.0 - q * std::cos(t), -q * std::sin(t));
    return std::pow(p / denominator, r);
}

template< typename T >
int NegativeBinomialRand<T>::Mode() const
{
    return (r > 1) ? std::floor((r - 1) * qDivP) : 0;
}

template< typename T >
double NegativeBinomialRand<T>::Skewness() const
{
    return (1 + q) / std::sqrt(q * r);
}

template< typename T >
double NegativeBinomialRand<T>::ExcessKurtosis() const
{
    double kurtosis = p / qDivP;
    kurtosis += 6;
    return kurtosis / r;
}


template class NegativeBinomialRand<int>;
template class NegativeBinomialRand<double>;
