#pragma once

#include <vector>
#include <string>
#include <utility>
#include "nlohmann/json.hpp"

class ConverterJSON {
public:
    std::vector<std::string> GetTextDocuments();
    int GetResponsesLimit();
    std::vector<std::string> GetRequests();
    void putAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers);
};