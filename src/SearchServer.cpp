#include "SearchServer.h"
#include <sstream>
#include <map>
#include <algorithm>

std::vector<std::vector<RelativeIndex>> SearchServer::search(
        const std::vector<std::string>& queries_input,
        int responses_limit)
{

    std::vector<std::vector<RelativeIndex>> results;

    for (const auto& query : queries_input) {

        std::stringstream ss(query);
        std::string word;

        std::map<size_t, float> doc_relevance;

        // считаем абсолютную релевантность
        while (ss >> word) {

            auto entries = _index.GetWordCount(word);

            for (const auto& entry : entries) {
                doc_relevance[entry.doc_id] += entry.count;
            }
        }

        // ищем максимум
        float max_relevance = 0;

        for (auto& doc : doc_relevance) {
            if (doc.second > max_relevance)
                max_relevance = doc.second;
        }

        std::vector<RelativeIndex> relative;

        // считаем относительную релевантность
        for (auto& doc : doc_relevance) {

            RelativeIndex ri;

            ri.doc_id = doc.first;
            ri.rank = doc.second / max_relevance;

            relative.push_back(ri);
        }

        // сортировка
        std::sort(relative.begin(), relative.end(),
                  [](const RelativeIndex& a, const RelativeIndex& b) {
                      return a.rank > b.rank;
                  });

        // ограничение max_responses
        if (relative.size() > responses_limit)
            relative.resize(responses_limit);

        results.push_back(relative);
    }

    return results;
}