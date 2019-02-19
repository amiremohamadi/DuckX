#include <iostream>
#include <"duckx.hpp">
using namespace std;

int main() {
    Document doc("my_test.docx");
    doc.open();

    for (auto p = doc.paragraphs(); p.hasNext(); p.next()) {
        for (auto r = p.runs(); r.hasNext(); r.next()) {
            cout << r.text() << endl;
        }
    }

    return 0;
}