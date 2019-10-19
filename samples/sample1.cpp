#include <iostream>
#include "../src/duckx.hpp"
using namespace std;

// Print a paragraph and all children runs
void print_paragraph(duckx::Paragraph& p) {
	for (auto r = p.runs(); r.has_next(); r.next()) {
		cout << r.get_text() << endl;
	}
}

int main() {
    duckx::Document doc("my_test.docx");
    doc.open();

	cout << "Paragraph content:" << endl;
    for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
		print_paragraph(p);
    }

	cout << "Table content:" << endl;
	for (auto t = doc.tables(); t.has_next(); t.next()) {
		for (auto tr = t.rows(); tr.has_next(); tr.next()) {
			for (auto tc = tr.cells(); tc.has_next(); tc.next()) {
				for (auto p = tc.paragraphs(); p.has_next(); p.next()) {
					print_paragraph(p);
				}
			}
		}
	}

    return 0;
}
