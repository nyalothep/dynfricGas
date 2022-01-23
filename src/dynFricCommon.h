#pragma once
#include <cmath>
#include <iostream>
#include <math.h>
#include <vector>
#include <boost/math/special_functions.hpp>
#include <functional>

/**
 * @brief This class contains the common calculation for the sum \f$I\f$.
 * 
 */
class dynFricCommon
{
public:
    
/**
 * @brief Checks whether the given input is a negative integer. This is used to filter out critical inputs for the Gamme functions
 * 
 * @param i The number to be checked
 * @return true The number is critical.
 * @return false The number is uncritical.
 */
bool checkInt(double i);

/**
 * @brief Calculates the prefactor of the sums
 * 
 * @param m Inner sum indice.
 * @param l Outer sum indice.
 * @return long double \f$ (-1)^m \frac{(l-m)!}{(l-m-2)!} \frac{1}{\Gamma((1-l-m)/2)\Gamma(1+(l-m)/2)\Gamma((3-l+m)/2)\Gamma(1+(l+m)/2)} \f$
 */
long double summandPref(int m ,int l);

/**
 * @brief Calculates the sum for \f$ I(\mathcal M) \f$.
 * 
 * @param re Function for the real part of the scattering amplitude \f$ S_{l,l-1}^m\f$.The arguments are l,m.
 * @param im Function for the imaginary part of the scattering amplitude \f$ S_{l,l-1}^m\f$.The arguments are l,m.
 * @param maxL The upper limit \f$ l_{max} \f$ for the outer sum.
 * @return std::pair<long double,long double> calculates \f$\sum_{l=1}^{l_{max}}\sum_{m=-l}^{l-2} (-1)^m \frac{(l-m)!}{(l-m-2)!} \frac{S_{l,l-1}^m-S_{l,l-1}^{m+1*}}{\Gamma((1-l-m)/2)\Gamma(1+(l-m)/2)\Gamma((3-l+m)/2)\Gamma(1+(l+m)/2)} \f$
 */
std::pair<long double,long double> sum(std::function<long double (int,int)> re, std::function<long double (int,int)> im, int maxL);

/**
 * @brief Calculates the sum for either the real or imaginary part of \f$ I(\mathcal M) \f$.
 * 
 * @param func Function for the real or imaginary part of the scattering amplitude \f$ S_{l,l-1}^m\f$.The arguments are l,m.
 * @param maxL The upper limit \f$ l_{max} \f$ for the outer sum.
 * @param realPart If true the function given is assumed to be the real part of the scattering amplitude and Re(I) is calculated. If false then its the imaginary part 
 * @return long double Calculates the real or imaginary part of \f$\sum_{l=1}^{l_{max}}\sum_{m=-l}^{l-2} (-1)^m \frac{(l-m)!}{(l-m-2)!} \frac{S_{l,l-1}^m-S_{l,l-1}^{m+1*}}{\Gamma((1-l-m)/2)\Gamma(1+(l-m)/2)\Gamma((3-l+m)/2)\Gamma(1+(l+m)/2)} \f$
 */
long double sumSingle (std::function<long double (int,int)> func,int maxL, bool realPart);

};
