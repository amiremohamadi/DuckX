#include <sstream>
#include <duckx.hpp>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("checks contents of sample.docx") {
    duckx::Document doc("sample.docx");
    doc.open();

    std::ostringstream ss;

    for (duckx::Paragraph p = doc.paragraphs(); p.has_next(); p.next()) {
        for (duckx::Run r = p.runs(); r.has_next(); r.next()) {
            ss << r.get_text() << std::endl;
        }
    }

    CHECK_EQ("This is a test\nokay?\n", ss.str());
}
