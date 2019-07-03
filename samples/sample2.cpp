#include <iostream>
#include "../src/duckx.hpp"

using namespace std;

int main() {
    duckx::Document doc("../samples/my_test2.docx");
    doc.open();
    auto paragraph = doc.paragraphs();
    paragraph.add_run("Hello!");
    paragraph.add_run("你好!");
    doc.save();
    return 0;
}