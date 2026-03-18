#include "ConverterJSON.h"
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

// Получить список документов
std::vector<std::string> ConverterJSON::GetTextDocuments() {
    std::ifstream file("config.json");

    if (!file.is_open()) {
        throw std::runtime_error("config.json is missing");
    }

    json config;
    file >> config;

    std::vector<std::string> result;

    if (config.contains("files")) {
        for (const auto& file_path : config["files"]) {
            std::ifstream doc(file_path);

            if (!doc.is_open()) {
                throw std::runtime_error("Document file is missing: " + file_path.get<std::string>());
            }

            std::string content(
                (std::istreambuf_iterator<char>(doc)),
                std::istreambuf_iterator<char>()
            );

            result.push_back(content);
        }
    }

    return result;
}

// Получить количество ответов
int ConverterJSON::GetResponsesLimit() {
    std::ifstream file("config.json");

    if (!file.is_open()) {
        throw std::runtime_error("config.json is missing");
    }

    json config;
    file >> config;

    if (config.contains("config") && config["config"].contains("max_responses")) {
        return config["config"]["max_responses"];
    }

    return 5; // значение по умолчанию
}

// Получить запросы
std::vector<std::string> ConverterJSON::GetRequests() {
    std::ifstream file("requests.json");

    if (!file.is_open()) {
        throw std::runtime_error("requests.json is missing");
    }

    json requests_json;
    file >> requests_json;

    std::vector<std::string> requests;

    if (requests_json.contains("requests")) {
        for (const auto& req : requests_json["requests"]) {
            requests.push_back(req);
        }
    }

    return requests;
}

// Записать ответы
void ConverterJSON::putAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers) {
    std::ofstream out("answers.json");

    if (!out.is_open()) {
        throw std::runtime_error("Cannot open answers.json for writing");
    }

    json result;
    result["answers"] = json::object();

    for (size_t i = 0; i < answers.size(); ++i) {
        std::string request_id = "request" + std::string(3 - std::to_string(i + 1).length(), '0') + std::to_string(i + 1);

        if (answers[i].empty()) {
            result["answers"][request_id]["result"] = false;
        } else {
            result["answers"][request_id]["result"] = true;
            result["answers"][request_id]["relevance"] = json::array();

            for (const auto& [docid, rank] : answers[i]) {
                result["answers"][request_id]["relevance"].push_back({
                    {"docid", docid},
                    {"rank", rank}
                });
            }
        }
    }

    out << result.dump(4);

if (!out) {
    throw std::runtime_error("Error writing to answers.json");
}
}