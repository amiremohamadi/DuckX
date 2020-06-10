#include <duckx.hpp>
#include <iostream>
using namespace std;

int main() {
    duckx::Document doc("my_test.docx");
    doc.open();

    duckx::Paragraph p =
        doc.paragraphs().insert_paragraph_after(L"You can insert text in ");
    p.add_run(L"italic, ", duckx::none);
    p.add_run(L"bold, ", duckx::bold);
    p.add_run(L"underline, ", duckx::strikethrough);
    p.add_run(L"superscript", duckx::superscript);
    p.add_run(L" or ");
    p.add_run(L"subscript, ", duckx::subscript);
    p.add_run(L"small caps, ", duckx::smallcaps);
    p.add_run(L"and shadows, ", duckx::shadow);
    p.add_run(L"and of course ");
    p.add_run(L"combine them.", duckx::bold | duckx::italic | duckx::underline |
                                   duckx::smallcaps);

    doc.save();

    return 0;
}
