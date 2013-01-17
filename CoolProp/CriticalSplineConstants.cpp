#include <iostream>
#include <vector>
#include <string>
#include "CriticalSplineConstants.h"
#include "FluidClass.h"
#include "CPExceptions.h"

void set_critical_spline_constants(Fluid *pFluid)
{

	// This is a map of fluid name to CriticalSplineStruct_T instance
	// Admittedly this is a bit hacky, but it is easier to update the 
	// file separately and at compile times the constants will be pulled into
	// this block
	std::pair<std::string, CriticalSplineStruct_T> name_map_datad[] = {
	
		#include "CriticalSplineConstants_T.h"

	};
	//Now actually construct the map
	std::map<std::string, CriticalSplineStruct_T> name_map(name_map_datad, name_map_datad + sizeof name_map_datad / sizeof name_map_datad[0]);

	std::map<std::string,CriticalSplineStruct_T>::iterator it;
	// Try to find using the map using the official name of the fluid
	it = name_map.find(pFluid->get_name());

	// If it is found the iterator will not be equal to end
	if (it != name_map.end() )
	{
		pFluid->CriticalSpline_T = (*it).second;
	}
	else
	{
		// Didn't work, just filling with infinity
		pFluid->CriticalSpline_T = CriticalSplineStruct_T(_HUGE,_HUGE,_HUGE,_HUGE,_HUGE);
	}

}