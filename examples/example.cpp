#include "../src/smpl_IGES.hpp"
#include <vector>
#include <string>

int main() {
	/*
		In this example, a quadratic B-spline surface representing the standard Wigley hull
			for (L,B,T) = (1,0.1,0.0625) is saved to IGES format
	*/

	/* Input */

	double L = 1;
	double B = 0.1;
	double T = 0.0625;

	std::string filename = "Wigley.igs";

	/* constructing surface */

	std::vector<double> knotsU = { 0,0,0,1,1,1 };// knot vector in U-direction

	std::vector<double> knotsV = { 0,0,0,1,1,1 };// knot vector in V-direction

	std::vector<std::vector<std::vector<double>>> control_points =//9 control points of surface all initialized to zero
		std::vector<std::vector<std::vector<double>>>(3, std::vector<std::vector<double>>(3, std::vector<double>(3,0)));

	control_points.at(0).at(0) = { -L / 2,0,0 };
	control_points.at(0).at(1) = { -L / 2,0,T / 2 };
	control_points.at(0).at(2) = { -L / 2,0,T };

	control_points.at(1).at(0) = { 0,B,0 };
	control_points.at(1).at(1) = { 0,B,T / 2 };
	control_points.at(1).at(2) = { 0,0,T };

	control_points.at(2).at(0) = { L / 2,0,0 };
	control_points.at(2).at(1) = { L / 2,0,T / 2 };
	control_points.at(2).at(2) = { L / 2,0,T };

	/* saving to igs */

	bspln_to_iges(filename, knotsU, knotsV, control_points);

	return 0;
}