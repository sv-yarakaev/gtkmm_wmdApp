//
// Created by sv.yarakaev on 25.06.2020.
//

#include "utils.h"


//������!!!111111
//��� ��� ������!
std::string exec(const char *cmd) {
    std::array<char, 128> buffer = {0};
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}