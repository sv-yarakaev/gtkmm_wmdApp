//
// Created by sv.yarakaev on 29.06.2020.
//

#ifndef WINDOWAPP_REDIR_OUTPUT_H
#define WINDOWAPP_REDIR_OUTPUT_H
#include <string>
#include <unistd.h>
#include <sys/wait.h>

#include <array>
#include <iostream>
#include <string_view>


class RedirOutput {
private:
    std::array<int,  2> m_handles;
public:
    RedirOutput();
    ~RedirOutput();

    std::string read();

    void redirect();

};


#endif //WINDOWAPP_REDIR_OUTPUT_H
