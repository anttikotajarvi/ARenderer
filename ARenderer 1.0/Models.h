#pragma once
#include <fstream>
#include <string>
#include <iostream>

#include "ARCommon.h"
namespace ARC {
	namespace Models {
		struct Model {
			std::vector<Point> v;
			std::vector<std::vector<int>> f;
		};
		Model import_obj(std::string path);
	};
};
