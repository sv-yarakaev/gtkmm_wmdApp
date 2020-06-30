//
// Created by sv.yarakaev on 29.06.2020.
//

#include "redir_output.h"

RedirOutput::RedirOutput() {
    if (pipe(m_handles.data()) < 0) {
        exit(1);
    }
}

RedirOutput::~RedirOutput() {
    close(m_handles.at(0));
    close(m_handles.at(1));
}

std::string RedirOutput::read() {
    std::array<char, 256> buf ={0};
    std::size_t bytes= ::read(m_handles.at(0), buf.data(), buf.size());

    if (bytes > 0) {
        return {buf.data(), bytes};
    }
    return {};
}

void RedirOutput::redirect() {
    dup2(m_handles.at(1), STDOUT_FILENO);
    close(m_handles.at(0));
    close(m_handles.at(1));
}





