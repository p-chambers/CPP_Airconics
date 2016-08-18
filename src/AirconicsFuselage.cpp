/*
* @Author: pchambers
* @Date:   2016-08-17 11:56:49
* @Last Modified by:   pchambers
* @Last Modified time: 2016-08-18 14:23:26
*/
#include <iostream>

#include "AirconicsFuselage.hpp"
#include "AirconicsBase.hpp"

namespace Airconics{

	Fuselage::Fuselage(){
		std::cout << "Constructing Fuselage" << std::endl;
		ScaleFactor = 0;
	}

	double Fuselage::getScaleFactor(){
		return ScaleFactor;
	}
}
