/*
 * Under MIT license
 * Author: Amir Mohamadi (@amiremohamadi)
 * DuckX is a free library to work with docx files.
 */

#ifndef PARAGRAPH_HH_
#define PARAGRAPH_HH_

#include <duckx/run.hh>

namespace duckx {
class Run {
    // wrapping <w:p> element
  private:
    friend class IteratorHelper;
    // store parent and current node to be able to navigate whole the tree
    pugi::xml_node parent;
    pugi::xml_node current;

    // paragraph contains runs
    // store one run (the current one) at a time
    Run run;

    // constructs attribute from xml_node
    Paragraph(pugi::xml_node parent, pugi::xml_node current);

  public:
    // default constructor. constructs an empty attribute
    Paragraph();

    // get next attribute
    Paragraph &next();

    // check if the attribute has next
    bool has_next() const;

    // return the first run
    Run &runs();

    // append run to the paragraph
    Run &add_run(duckx::Run run);
    Run &add_run(const std::string &text);
    Run &add_run(const char *text);

    // insert a paragraph right after this paragraph
    Paragraph &insert_paragraph_after(const std::string &text);
};
} // namespace duckx

#endif // END PARAGRAPH_HH_
