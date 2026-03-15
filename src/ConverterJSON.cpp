#include <iostream>
#include "ConverterJSON.h"

using json = nlohmann::json;

std::vector<std::string> ConverterJSON::GetTextDocuments() {

    std::ifstream file("config.json");

    if (!file.is_open())
        throw std::runtime_error("config file is missing");

    json config;
    file >> config;

    if (config["config"].empty())
        throw std::runtime_error("config file is empty");

    std::vector<std::string> docs;

    for (auto &path : config["files"]) {

        std::ifstream doc(path);

        if (!doc.is_open()) {
            std::cout << "file not found: " << path << std::endl;
            continue;
        }

        std::string content(
            (std::istreambuf_iterator<char>(doc)),
            std::istreambuf_iterator<char>()
        );

        docs.push_back(content);
    }

    return docs;
}

int ConverterJSON::GetResponsesLimit() {

    std::ifstream file("config.json");

    json config;
    file >> config;

    if (config["config"].contains("max_responses"))
        return config["config"]["max_responses"];

    return 5;
}

std::vector<std::string> ConverterJSON::GetRequests() {

    std::ifstream file("requests.json");

    json requests;
    file >> requests;

    std::vector<std::string> result;

    for (auto &req : requests["requests"])
        result.push_back(req);

    return result;
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers) {

    json result;
    result["answers"] = json::object();

    for (int i = 0; i < answers.size(); i++) {

        std::string req = "request" + std::string(3 - std::to_string(i+1).length(), '0') + std::to_string(i+1);

        if (answers[i].empty()) {
            result["answers"][req]["result"] = false;
            continue;
        }

        result["answers"][req]["result"] = true;

        for (auto &ans : answers[i]) {

            json elem;

            elem["docid"] = ans.first;
            elem["rank"] = ans.second;

            result["answers"][req]["relevance"].push_back(elem);
        }
    }

    std::ofstream out("answers.json");

    out << result.dump(4);
}