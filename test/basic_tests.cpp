#include <gtest/gtest.h>
#include <duckx.hpp>

TEST(basic_test, test1) {
    duckx::Document doc("my_test.docx");
    doc.open();

    std::ostringstream ss;

    for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
        for (auto r = p.runs(); r.has_next(); r.next()) {
            ss << r.get_text() << std::endl;
        }
    }

    ASSERT_EQ("This is a test\nokay?\n",ss.str());
}