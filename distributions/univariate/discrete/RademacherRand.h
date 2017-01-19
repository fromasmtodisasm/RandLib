#ifndef RADEMACHERRAND_H
#define RADEMACHERRAND_H

#include "DiscreteDistribution.h"
#include "../BasicRandGenerator.h"

/**
 * @brief The RademacherRand class
 *
 * P(X = k) = 0.5 * 1_{|k| = 1}
 *
 * Notation: X ~ Rademacher
 *
 * Related distributions:
 * If Y ~ Bernoulli(0.5), then 2Y - 1 ~ Rademacher
 */
class RANDLIBSHARED_EXPORT RademacherRand : public DiscreteDistribution
{
public:
    RademacherRand();
    std::string Name() const override;
    SUPPORT_TYPE SupportType() const override { return FINITE_T; }
    int MinValue() const override { return -1; }
    int MaxValue() const override { return 1; }

    double P(int k) const override;
    double F(int k) const override;
    int Variate() const override;

    double Mean() const override;
    double Variance() const override;
    double Median() const override;
    int Mode() const override;
    double Skewness() const override;
    double ExcessKurtosis() const override;

    std::complex<double> CFImpl(double t) const override;

    double Entropy();
};

#endif // RADEMACHERRAND_H
