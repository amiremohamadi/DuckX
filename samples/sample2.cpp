#include <iostream>
#include "../src/duckx.hpp"
using namespace std;
using namespace duckx; 

int main() {
    duckx::Document doc("my_test.docx");
    doc.open();

    duckx::Paragraph p = doc.paragraphs().insert_paragraph_after("You can insert text in ");
    p.add_run("italic, ", Run::Italic);
    p.add_run("bold, ", Run::Bold);
    p.add_run("underline, ", Run::Underline);
    p.add_run("strikethrough, ", Run::Strikethrough);
    p.add_run("superscript", Run::Superscript);
    p.add_run(" or ");
    p.add_run("subscript, ", Run::Subscript);
    p.add_run("small caps, ", Run::SmallCaps);
    p.add_run("and shadows, ", Run::Shadow);
    p.add_run("and of course ");
    p.add_run("combine them.", Run::Bold | Run::Italic | duckx::Run::Underline | Run::SmallCaps);
    
    doc.save();

    return 0;
}
