
#pragma once

#include <cmath>
#include <iostream>
#include <math.h>
#include <vector>
#include <boost/math/special_functions.hpp>
#include "dynFricCommon.h"
#include <complex>

/**
 * @brief This class calculates the dynamic friction of a rotating pertuber in a gaseaous medium.
 * 
 */
class gas: dynFricCommon
{
private:

public :
/**
 * @brief Returns the real part of the scatering amplitude \f$ S^m_{l,l-1} \f$
 * 
 * @param l Sum indice of the outer sum
 * @param m Sum indice of the inner sum
 * @param Ma Mach number 
 * @return long double \f$ S^m_{l,l-1}=-\frac{\Pi}{2}(j_l(\mathcal M) y_{l-1}(\mathcal M)) \f$ and for m=0 \f$ S^m_{l,l-1}=\frac{\pi}{2(4 l^2-1)} \f$
 */
long double ReS(int l, int m, long double Ma);

/**
 * @brief Returns the imaginary part of the scatering amplitude \f$ S^m_{l,l-1} \f$
 * 
 * @param l Sum indice of the outer sum
 * @param m Sum indice of the inner sum
 * @param Ma Mach number 
 * @return long double \f$ S^m_{l,l-1}=-\frac{\Pi}{2}(j_l(\mathcal M) y_{l-1}(\mathcal M)) \f$
 */
long double ImS(int l,int m,long double Ma);

/**
 * @brief Calculates the function \f$ I(\mathcal M) \f$.
 * 
 * @param maxL Upper limit for the sum
 * @param Ma Max number
 * @return std::pair<long double, long double> (real part, imaginary part)  \f$ I(M)=\sum_{l=1}^{l_{max}}\sum_{m=-l}^{l-2} (-1)^m \frac{k!}{(k-2)!} \frac{S_{l,l-1}^m-S_{l,l-1}^{m+1*}}{\Gamma((1-l-m)/2)\Gamma(1+(l-m)/2)\Gamma((3-l+m)/2)\Gamma(1+(l+m)/2)}\f$
 */
std::complex<long double> Im(int maxL, long double Ma);
/**
 * @brief Calculates the imaginary part of function \f$ I(Ma) \f$.
 * 
 * @param maxL Upper limit for the sum
 * @param Ma Mach number
 * @return long double  The imaginary part ofr \f$ I(M)=\sum_{l=1}^{l_{max}}\sum_{m=-l}^{l-2} (-1)^m \frac{k!}{(k-2)!} \frac{S_{l,l-1}^m-S_{l,l-1}^{m+1*}}{\Gamma((1-l-m)/2)\Gamma(1+(l-m)/2)\Gamma((3-l+m)/2)\Gamma(1+(l+m)/2)}\f$
 */
long double ImI(int maxL, long double Ma);

/**
 * @brief Calculates the real part of the function \f$ I(Ma) \f$ .
 * 
 * @param maxL Upper limit for the sum
 * @param Ma Mach number
 * @return long double The real part ofr \f$ I(M)=\sum_{l=1}^{l_{max}}\sum_{m=-l}^{l-2} (-1)^m \frac{k!}{(k-2)!} \frac{S_{l,l-1}^m-S_{l,l-1}^{m+1*}}{\Gamma((1-l-m)/2)\Gamma(1+(l-m)/2)\Gamma((3-l+m)/2)\Gamma(1+(l+m)/2)}\f$
 */
long double ReI(int maxL, long double Ma);

}; 

