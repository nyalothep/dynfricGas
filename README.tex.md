Dynamical friction acting on circularly moving perturbers
===========================================================================

Preface
===========================================================================
This code is made public in conjecture with the paper 
["Analytic solution to the dynamical friction acting on circularly moving perturbers" by Vincent Desjacques, Adi Nusser and Robin Bühler](https://arxiv.org/abs/2111.07366) and it can be used to reproduce results presented in their. 
If this code is used, we ask kindly to cite the paper.

 ![Example for I(M) with comparison to simulations](IM.png)
 ![Shows I(M) for different M summed up to different values of l_max ](Convergence.png)

Introduction
===========================================================================
If a perturber moves through a homogeneous and isotropic gaseos material, its gravitational field will introduce inisotropies into the distribution of the gaseos medium, which than will have a net gravitational effect on the perturber
itself. This effect is called dynamical friction. In this work we focus specifically on dynamical friction of a perturber on a circular motion.
In the following we are going to give a short summary of the calculations, for a more detailed version the reader is referred to the paper.

The gaseous medium is described by an average density \f$\bar\rho_g\f$ and its soundspeed \f$c_s\f$, while the perturber by its mass \f$M\f$ and its circular motion in the x-y plane with the angular velocity \f$\Omega>0\f$ and the 
radius \f$r_0\f$. We define the Mach number \f$\mathcal M\equiv v_p/c_s\f$, where the velocity of the perturber is given by \f$v_p\equiv r_0\Omega \f$, it is going the be defining parameter of all the function given in this code. The motion of the perturber is described by \f$\vec r_p(t)=r_0(\cos \Omega t \hat x +\sin \Omega t \hat y)\f$, then we can express the reaction of the gaseos medium as its fractional overdensity \f$\alpha\f$ via the Green's function:
\f[ \alpha(\vec u,t)=\frac{G M}{c_s^2}\int_{-\infty}^\infty\mathrm{d}\tau h(t-\tau)\frac{\delta^d(\tau-\frac{1}{c_s}|\vec r_p(t) +\vec u -\vec r_p(t-\tau )|}{|\vec r_p(t) +\vec u -\vec r_p(t-\tau )|}\f]
here \f$\vec u\f$ is the three-dimensional separation vector between an arbitrary point, where we want to calculate the overdensity at and the position of the perturber at the time \f$t\f$, and \f$ h(t)\f$ is either 0 or 1 depending whether the perturber is on or off. Representing the Green's function with its Fourier transformation and inserting it into the formula for the dynamical friction
\f[\vec F_{DF}(t)=G M\bar \rho_g \int \mathrm{d}^3u \frac{\vec u}{u^3} \alpha(\vec u,t) \f]
we can use spherical harmonics to decompose the force into helicity modes. From there on we can further simiplify our solution and show that it can be expressed as
\f[\vec F_{DF}(t)=-4\pi \left(\frac{G M}{\Omega r_0}\right)^2\bar \rho_g \left(\Re(I(\mathcal M)) \hat r(t)+\Im (I(\mathcal M))\hat \phi(t)\right) \f]
with
\f[ I(\mathcal M)=\mathcal M^2\sum_{l=1}^{\infty}\sum_{m=-l}^{l-2} (-1)^m \frac{(l-m)!}{(l-m-2)!} \frac{S_{l,l-1}^m-S_{l,l-1}^{m+1*}}{\Gamma((1-l-m)/2)\Gamma(1+(l-m)/2)\Gamma((3-l+m)/2)\Gamma(1+(l+m)/2)} \f]
and the scattering amplitude
\f[S_{l,l-1}^m=\int \frac{\mathrm{d}\omega}{2\pi}\int_{-\infty}^{\infty}\mathrm{d}\tau(t-\tau)e^{i(m\Omega-\omega)\tau}c_s^2\int_0^\infty \mathrm d k k \frac{j_l(k r_0)j_{l-1}(k r_0) }{c_s^2 k^2-(w+i \epsilon)} \f].
If we assume steady state \f$ h(t)=1 \f$, then this further simplifies and we can compute for \f$ m\neq 0 \f$
\f[S_{l,l-1}^m=\frac{i \pi}{2}j_l(m \mathcal M) h^{(1)}_{l-1}(m \mathcal M) \f]
and simply for \f$ m=0 \f$
\f[ S_{l,l-1}^0=\frac{\pi}{2(4l^2-1)} \f].
This code provides functions for \f$I(\mathcal M)\f$ and \f$S_{l,l-1}^m\f$ in the steady state case.

Prerequisites
===========================================================================
The following libaries are necessary to run the code:
- [Boost](https://www.boost.org/)
- [OpenMp](https://www.openmp.org/)(optional, accelerates calculations)
- [Doxygen](https://www.doxygen.nl/index.html)(optional, generates documentation)

Usage
===========================================================================
The code can be compiled with:
```console
    make main
```    
then the executable can be run with
```shell
    ./dynfric
```
. This will produce \f$I(\mathcal M)\f$ for the Machnumbers \f$\mathcal M=[0.5, 0.9, 2.0, 4.0, 6.0] \f$ summed up to \f$ l_{max}\f$ from 1 to 800. If other output is desired, then its up to the user to edit the 'src\main.cpp'.
If Doxygen is installed, then the documentation can be created
```shell
    make doc
```
Temporary files generated during compilation can be deleted with
```shell
    make clean
```
Using
```shell
    make distclean
```
will revert the directory to its originial state. This does not remove any files the user added themself.
