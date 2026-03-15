#include "InvertedIndex.h"
#include <sstream>
#include <thread>

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {

    docs = input_docs;

    freq_dictionary.clear();

    for (size_t doc_id = 0; doc_id < docs.size(); doc_id++) {

        std::stringstream ss(docs[doc_id]);
        std::string word;

        std::map<std::string, size_t> word_count;

        while (ss >> word)
            word_count[word]++;

        for (auto &pair : word_count) {

            Entry entry;

            entry.doc_id = doc_id;
            entry.count = pair.second;

            freq_dictionary[pair.first].push_back(entry);
        }
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word) {

    if (freq_dictionary.count(word))
        return freq_dictionary[word];

    return {};
}