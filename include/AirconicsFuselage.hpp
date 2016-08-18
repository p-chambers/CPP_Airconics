/*
* @Author: pchambers
* @Date:   2016-08-17 11:57:12
* @Last Modified by:   pchambers
* @Last Modified time: 2016-08-18 14:22:58
*/
#pragma once

#include "AirconicsBase.hpp"


namespace Airconics{

	class Fuselage{
	private:
		double ScaleFactor;

	public:
		// Constructor
		Fuselage();

		// Setters
		void setScaleFactor(double);

		// Getters
		double getScaleFactor();
	};
}
