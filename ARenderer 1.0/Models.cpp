#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "Models.h"
#include "ARCommon.h"
namespace ARC {
    namespace Models {
        Model import_obj(std::string path) {
            Model out;

            std::ifstream file(path);
            if (file.is_open()) {

                std::string line;
                while (std::getline(file, line)) {
                    if (line.length() == 0) continue;
                    std::string str(line);
                    std::string buf;
                    std::stringstream ss(str);

                    std::vector<std::string> tokens;

                    while (ss >> buf) tokens.push_back(buf);

                    if (tokens[0] == "v") {
                        out.v.push_back({ std::stod(tokens[1]), std::stod(tokens[2]) , std::stod(tokens[3]) });
                    }
                    else if (tokens[0] == "f") {
                        out.f.push_back(std::vector<int>{std::stoi(tokens[1]) - 1, std::stoi(tokens[2]) - 1, std::stoi(tokens[3]) - 1});
                    }


                }
                file.close();
            }
            return out;
        }
    }
}