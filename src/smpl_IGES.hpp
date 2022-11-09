#ifndef SMPL_IGES_HPP
#define SMPL_IGES_HPP
#include <fstream>
#include <vector>
#include <string>

template<typename scalar = double>
bool bspln_to_iges(
	std::string filename,
	std::vector<scalar> knotsU,
	std::vector<scalar> knotsV,
	std::vector<std::vector<std::vector<scalar>>> cps
);

template<typename scalar = double>
bool bspln_to_iges(
	std::string filename,
	std::vector<scalar> knotsU,
	std::vector<scalar> knotsV, 
	std::vector<std::vector<std::vector<scalar>>> cps
	) {
	/*
		Description: Writes the B-spline surface defined by knotsU, knotsV, cps, to
			'filename' in IGES format.

		Input:
			- filename: the name of the file to write the B-Spline in IGES format. filename must include filename
				extension. In example filename == "example.iges" or filename == "example.txt"

			- knotsU: knotsU.at(i) = ith knot in U direction

			- knotsV: knotsV.at(i) = ith knot in V direction

			- cps:
				cps.at(i).at(j) = (ith,jth) control point
				cps.at(i).at(j).at(0) = X component
				cps.at(i).at(j).at(1) = Y component
				cps.at(i).at(j).at(2) = Z component
		Output:
			- true:
				successfully wrote B-Spline to filename
			- false:
				error occured
	*/

	/* initialization */

	int Mu = cps.size();// number of control points in U direction
	int Mv = cps.at(0).size();// number of control points in V direction

	int nU = knotsU.size() - Mu - 1;// degree in U direction
	int nV = knotsV.size() - Mv - 1;// degree in V direction

	if (nU < 1 || nV < 1) return false;

	std::fstream file;

	file.open(filename, std::ios::out);

	std::vector<std::string> P;// Parameter Data section
		// P.at(i) = ith row of Parameter Data section without last 8 characters

	auto spaces = [](int Nspace) {
		//lambda expression to return the string of Nspace spaces
		//ie spaces(3) -> "   "
		std::string out = "";
		for (int i = 0;i < Nspace;i++)out += " ";
		return out;
	};

	/* write Start and Global sections */

	file << spaces(72) << "S      1";
	file << "\n";

	file << spaces(72) << "G      1";
	file << "\n";

	/* construct Parameter Data section */

	// Type, Degrees and Flags
	P.push_back("128," + std::to_string(Mu-1) + "," + std::to_string(Mv-1) + ","
		+ std::to_string(nU) + "," + std::to_string(nV)
		+ ",1,1,1,0,0,");

	P.at(0) = P.at(0) + spaces(71 - P.at(0).length());//adding extra spaces (see IGES)

	// U knots
	for (int i = 0;i < knotsU.size(); i++) {
		P.push_back(std::to_string(knotsU.at(i)) + "," + spaces(70 - std::to_string(knotsU.at(i)).length()));
	}

	// V knots
	for (int i = 0;i < knotsV.size(); i++) {
		P.push_back(std::to_string(knotsV.at(i)) + "," + spaces(70 - std::to_string(knotsV.at(i)).length()));
	}

	// weights
	for (int i = 0;i < Mu * Mv;i++) {
		P.push_back("1," + spaces(69));
	}

	// control points
	for (int j = 0; j < cps.at(0).size(); j++) {
		for (int i = 0;i < cps.size();i++) {
			P.push_back(std::to_string(cps.at(i).at(j).at(0)) + "," + spaces(70 - std::to_string(cps.at(i).at(j).at(0)).length()));
			P.push_back(std::to_string(cps.at(i).at(j).at(1)) + "," + spaces(70 - std::to_string(cps.at(i).at(j).at(1)).length()));
			if (i == (cps.size() - 1) && j == (cps.at(i).size() - 1)) {
				P.push_back(std::to_string(cps.at(i).at(j).at(2)) + ";" + spaces(70 - std::to_string(cps.at(i).at(j).at(2)).length()));
			}
			else {
				P.push_back(std::to_string(cps.at(i).at(j).at(2)) + "," + spaces(70 - std::to_string(cps.at(i).at(j).at(2)).length()));
			}
		}
	}

	/* write Data Entry section */

	file << spaces(5) + "128" 
		+ spaces(7) + "1" 
		+ spaces(7) + "0" 
		+ spaces(7) + "1" 
		+ spaces(7) + "0" 
		+ spaces(7) + "0" 
		+ spaces(7) + "0"
		+ spaces(7) + "0"
		+ spaces(7) + "1"
		+ "D      1";
	file << std::endl;

	file << spaces(5) + "128"
		+ spaces(7) + "0"
		+ spaces(7) + "1"
		+ spaces(8 - std::to_string(P.size()).length()) + std::to_string(P.size())//number of lines in P
		+ spaces(7) + "0"
		+ spaces(7) + "0"
		+ spaces(7) + "0"
		+ spaces(7) + "0"
		+ spaces(7) + "0"
		+ "D      2";
	file << std::endl;

	/* write Parameter Data section */

	for (int i = 0; i < P.size();i++) {
		file << P.at(i) << "1P" + spaces(7 - std::to_string(i+1).size()) + std::to_string(i+1) << std::endl;
	}

	/* write Terminate section */

	file << "S" + spaces(6) + "1"
		+ "G      1"
	    + "D      2" 
		+ "P" + spaces(7 - std::to_string(P.size()).length()) + std::to_string(P.size())
		+ spaces(40)
		+ "T      1";

	file.close();
	return true;
}

#endif // SMPL_IGES_HPP
