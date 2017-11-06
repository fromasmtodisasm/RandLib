#ifndef DISCRETEBIVARIATEDISTRIBUTION_H
#define DISCRETEBIVARIATEDISTRIBUTION_H

#include "BivariateDistribution.h"
#include "../univariate/discrete/DiscreteDistribution.h"

/**
 * @brief The DiscreteBivariateDistribution class <BR>
 * Abstract class for all bivariate probability distributions
 * with marginal discrete distributions
 */
template < class T1, class T2 >
class RANDLIBSHARED_EXPORT DiscreteBivariateDistribution : public BivariateDistribution< T1, T2, IntPair >
{
    static_assert(std::is_base_of<DiscreteDistribution, T1>::value, "T1 must be a descendant of DiscreteDistribution");
    static_assert(std::is_base_of<DiscreteDistribution, T2>::value, "T2 must be a descendant of DiscreteDistribution");

protected:
    DiscreteBivariateDistribution() {}
    virtual ~DiscreteBivariateDistribution() {}

public:
    virtual double P(const IntPair &point) const = 0;
    virtual double logP(const IntPair &point) const = 0;
};


#endif // DISCRETEBIVARIATEDISTRIBUTION_H
