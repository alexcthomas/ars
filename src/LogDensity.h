/*
 * LogDensityDup.h
 *
 *  Created on: Oct 2, 2013
 *      Author: hoblitz
 */

#ifndef LOGDENSITY_H_
#define LOGDENSITY_H_

#include <math.h>

class LogDensity {
public:
    virtual double pdf(const double x) =0;
    virtual double pdfDeriv(const double x) =0;
	virtual std::tuple<double, double> getInit() =0;
};

class GammaDistribution : public LogDensity {
private:
    double m_alpha, m_beta;
public:
    GammaDistribution(const double alpha, const double beta) {
		m_alpha = alpha;
		m_beta = beta;
		if (alpha <= 1.0)
			throw std::exception("A Gamma distribution with shape parameter less than one is not log-convex, so adaptive rejection sampling will not work.");
		if (beta <= 0.0)
			throw std::exception("Invalid rate parameter for a Gamma distribution");
    };
    double pdf(const double x) {
        return (m_alpha - 1.0) * log(x) - x * m_beta;
    };
    double pdfDeriv(const double x) {
        return (m_alpha - 1.0) / x - m_beta;
    };
	std::tuple<double, double> getInit() {
		double mode = (m_alpha - 1.0) / m_beta;
		double sd = sqrt(m_alpha) / m_beta;
		
		if (m_alpha <= 5.83)
			return std::make_tuple(mode / 2.0, mode + sd);

		return std::make_tuple(mode - sd, mode + sd);
	};

};

class WeibullDistribution : public LogDensity {
private:
	double m_lamda, m_k;
public:
	WeibullDistribution(const double lamda, const double k) {
		m_k = k;
		m_lamda = lamda;
		if (k <= 1.0)
			throw std::exception("A Weibull distribution with shape parameter less than one is not log-convex, so adaptive rejection sampling will not work.");
		if (lamda <= 0.0)
			throw std::exception("Invalid rate parameter for a Weibull distribution");
    }
    double pdf(const double x) {
        return (m_k - 1.0) * log(x) - pow(x / m_lamda, m_k);
    };
    double pdfDeriv(const double x) {
        return (m_k - 1.0) / x - m_k * pow(x / m_lamda, m_k - 1.0) / m_lamda;
	};
	std::tuple<double, double> getInit() {
		double mode = m_lamda * pow((m_k - 1.0)/m_k, 1.0 / m_k);

		return std::make_tuple(mode / 2.0, mode + m_lamda);
	};

};


#endif /* LOGDENSITY_H_ */
