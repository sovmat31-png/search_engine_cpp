#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"

int main() {

    ConverterJSON converter;

    auto docs = converter.GetTextDocuments();

    InvertedIndex index;

    index.UpdateDocumentBase(docs);

    SearchServer server(index);

    auto requests = converter.GetRequests();

    int limit = converter.GetResponsesLimit();

    auto results = server.search(requests, limit);

    std::vector<std::vector<std::pair<int,float>>> answers;

    for (auto &res : results) {

        std::vector<std::pair<int,float>> v;

        for (auto &r : res)
            v.push_back(std::make_pair((int)r.doc_id, r.rank));

        answers.push_back(v);
    }

    converter.putAnswers(answers);

}