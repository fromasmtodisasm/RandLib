#ifndef SingularDistribution_H
#define SingularDistribution_H

#include "../UnivariateProbabilityDistribution.h"

/**
 * @brief The SingularDistribution class
 */
class RANDLIBSHARED_EXPORT SingularDistribution : public UnivariateProbabilityDistribution<double>
{
public:
    SingularDistribution();
    virtual ~SingularDistribution() {}

private:
    double Hazard(double) const override;
    double Mode() const override;
    double ExpectedValue(const std::function<double (double)> &, double) const override;
    double ExpectedValue(const std::function<double (double)> &funPtr, double minPoint, double maxPoint) const override;
    double Likelihood(const std::vector<double> &Sample) const override;
    double LogLikelihood(const std::vector<double> &Sample) const override;
};


#endif // SingularDistribution_H
