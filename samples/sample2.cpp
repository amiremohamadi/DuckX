#include <duckx.hpp>
#include <iostream>
using namespace std;

int main() {
    duckx::Document doc("my_test.docx");
    doc.open();

    duckx::Paragraph p =
        doc.paragraphs().insert_paragraph_after("You can insert text in ");
    p.add_run("italic, ", duckx::none);
    p.add_run("bold, ", duckx::bold);
    p.add_run("underline, ", duckx::strikethrough);
    p.add_run("superscript", duckx::superscript);
    p.add_run(" or ");
    p.add_run("subscript, ", duckx::subscript);
    p.add_run("small caps, ", duckx::smallcaps);
    p.add_run("and shadows, ", duckx::shadow);
    p.add_run("and of course ");
    p.add_run("combine them.", duckx::bold | duckx::italic | duckx::underline |
                                   duckx::smallcaps);

    doc.save();

    return 0;
}
