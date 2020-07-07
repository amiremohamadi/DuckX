/*
 * Under MIT license
 * Author: Amir Mohamadi (@amiremohamadi)
 * DuckX is a free library to work with docx files.
 */

#ifndef DOCUMENT_HH_
#define DOCUMENT_HH_

#include <duckx/paragraph.hh>
#include <duckx/table.hh>
#include <pugixml.hpp>
#include <string>
#include <zip.h>

namespace duckx {
class Document {
  private:
    friend class IteratorHelper;
    // store the file path
    std::string directory;

    // document contains paragraphs and tables
    Paragraph paragraph;
    Table table;

    // store document as xml_document
    pugi::xml_document document;

  public:
    // default constructor. constructs an empty document
    Document() = default;
    // constructs document using path to the file
    Document(std::string);

    // set the file path (just set, not opening)
    void file(std::string);

    // open the file
    void open();

    // override the file
    void save() const;

    // return document first paragraph
    Paragraph &paragraphs();

    // return the first table
    Table &tables();
};
} // namespace duckx

#endif // DOCUMENT_HH_
