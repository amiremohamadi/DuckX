#include <iostream>
#include <string>
#include "../duckx.hpp"


int main() {
    Document doc("my_test.docx");
    

    for (auto p = doc.paragraphs(); p.hasNext() ; p.next()) {
        std::cout << p.runs().text() << std::endl;
    }

    return 0;
}