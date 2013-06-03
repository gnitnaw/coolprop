#ifndef MIXTURES_H
#define MIXTURES_H

#include "Helmholtz.h"
#include "FluidClass.h"

typedef std::vector<std::vector<double> > STLMatrix;





/// An abstract base class for the reducing function to allow for
/// Lemmon-Jacobsen, GERG, or other reducing function to yield the
/// reducing parameters \f$ \bar\rho_r \f$ and \f$ T_r \f$
class ReducingFunction
{
public:
	virtual double Tr(std::vector<double> x) = 0;
	virtual double dTr_dxi(std::vector<double> x, int i) = 0;
	virtual double rhorbar(std::vector<double> x) = 0;
	virtual double drhorbar_dxi(std::vector<double> x, int i) = 0;
};

/// The Reducing parameter model used by the GERG-2004 and GERG-2008 
/// formulations
class GERGReducingFunction
{
protected:
	STLMatrix beta_v; /// \f$ \beta_{v,ij} \f$ from GERG-2008
	STLMatrix gamma_v; /// \f$ \gamma_{v,ij} \f$ from GERG-2008
	STLMatrix beta_T; /// \f$ \beta_{T,ij} \f$ from GERG-2008
	STLMatrix gamma_T; /// \f$ \gamma_{T,ij} \f$ from GERG-2008
	std::vector<Fluid *> pFluids; /// List of pointers to fluids
public:
	GERGReducingFunction(std::vector<Fluid *> pFluids, STLMatrix beta_v, STLMatrix gamma_v, STLMatrix beta_T, STLMatrix gamma_T)
	{
		this->pFluids = pFluids;
		this->beta_v = beta_v;
		this->gamma_v = gamma_v;
		this->beta_T = beta_T;
		this->gamma_T = gamma_T;
	};
	double Tr(std::vector<double> x);
	double dTr_dxi(std::vector<double> x, int i);
	double rhorbar(std::vector<double> x);
	double drhorbar_dxi(std::vector<double> x, int i);
};








/// The ABC for departure functions for the excess part of the Helmholtz energy
class DepartureFunction
{
protected:
	STLMatrix F; /// The \f$ F_{ij} \f$ matrix
public:
	DepartureFunction(){};
	/// Instantiator for the ABC for the DepartureFunction
	DepartureFunction(std::vector<Fluid *> pFluids);
	
	/// The excess Helmholtz energy of the binary pair
	/// Pure-virtual function (must be implemented in derived class
	virtual double phir(double tau, double delta, std::vector<double> x) = 0;
	virtual double dphir_dDelta(double tau, double delta, std::vector<double> x) = 0;
	//virtual double dphir_dxi(double tau, double delta, std::vector<double> x, int i) = 0;
};

class GERGDepartureFunction : DepartureFunction
{
protected:
	phir_power phi1;
	phir_GERG_gaussian phi2;
public:
	GERGDepartureFunction(STLMatrix F);
	double phir(double tau, double delta, std::vector<double> x);
	double dphir_dDelta(double tau, double delta, std::vector<double> x);
	//double dphir_dxi(double tau, double delta, std::vector<double> x, int i);
};

class IdealMixture
{
protected:
	std::vector<Fluid*> pFluids;
public:
	IdealMixture(std::vector<Fluid*> pFluids);
	double dphir_dDelta(double tau, double delta, std::vector<double> x);
};












class Mixture
{
protected:
	std::vector<Fluid *> pFluids;
public:
	Mixture(std::vector<Fluid *> pFluids);
	double dphir_dDelta(double tau, double delta, std::vector<double> x);
};

#endif