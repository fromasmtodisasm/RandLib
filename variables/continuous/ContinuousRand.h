#ifndef CONTINUOUSRAND_H
#define CONTINUOUSRAND_H

#include "../RandomVariable.h"

/**
 * @brief The ContinuousRand class
 */
class RANDLIBSHARED_EXPORT ContinuousRand : public RandomVariable<double>
{
public:
    ContinuousRand() : RandomVariable() {}
    virtual ~ContinuousRand() {}

    virtual double f(double x) const = 0;

    void pdf(const QVector<double> &x, QVector<double> &y) const;

    double likelihood(const QVector<double> &sample) const;
    double loglikelihood(const QVector<double> &sample) const;
};

#endif // CONTINUOUSRAND_H