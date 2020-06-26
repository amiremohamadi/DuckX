/*
 * Under MIT license
 * Author: Amir Mohamadi (@amiremohamadi)
 * DuckX is a free library to work with docx files.
 */

#ifndef RUN_HH_
#define RUN_HH_

namespace duckx {
class Run {
    // wrapping <w:r> element
  private:
    friend class IteratorHelper;
    friend class Paragraph;
    // store parent and current node to be able to navigate whole the tree
    pugi::xml_node parent;
    pugi::xml_node current;

    // constructs attribute from xml_node
    Run(pugi::xml_node parent, pugi::xml_node current);

  public:
    // default constructor. constructs an empty attribute
    Run();

    // get attribute text
    std::string get_text() const;

    // set attribute text
    bool set_text(const std::string &text) const;
    bool set_text(const char *text) const;

    // get next attribute
    Run &next();

    // check if attribute has next
    bool has_next() const;
};
} // namespace duckx

#endif // END RUN_HH_
