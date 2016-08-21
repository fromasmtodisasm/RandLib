#ifndef DISCRETE_DISTRIBUTION_H
#define DISCRETE_DISTRIBUTION_H

#include "../UnivariateProbabilityDistribution.h"

/**
 *@brief The DiscreteDistribution class
 */
class RANDLIBSHARED_EXPORT DiscreteDistribution : public virtual UnivariateProbabilityDistribution<int>
{
public:
    DiscreteDistribution() {}
    virtual ~DiscreteDistribution() {}

    /**
     * @brief P
     * probability to Get x
     * @param x
     * @return
     */
    virtual double P(int x) const = 0;

    /**
     * @brief ProbabilityMassFunction
     * fill vector y by P(x)
     * @param x
     * @param y
     */
    void ProbabilityMassFunction(const std::vector<int> &x, std::vector<double> &y) const;

    int Mode() const override;

private:
    double quantileImpl(double p) const override;
    double quantileImpl1m(double p) const override;

public:
    double Hazard(double x) const override;

    double ExpectedValue(const std::function<double (double)> &funPtr, int minPoint, int maxPoint) const override;
    double ExpectedValue(const std::function<double (double)> &funPtr, double startPoint) const override;

    double Likelihood(const std::vector<int> &Sample) const override;
    double LogLikelihood(const std::vector<int> &Sample) const override;
};

#endif // DISCRETE_DISTRIBUTION_H
