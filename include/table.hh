/*
 * Under MIT license
 * Author: Amir Mohamadi (@amiremohamadi)
 * DuckX is a free library to work with docx files.
 */

#ifndef TABLE_HH_
#define TABLE_HH_

namespace duckx {
class TableCell {
  private:
    friend class IteratorHelper;

    // store parent and current node to be able to nvigate whole the tree
    pugi::xml_node parent;
    pugi::xml_node current;

    // table cell contains paragraphs
    Paragraph paragraph;

    // constructs attribute from xml_node
    TableCell(pugi::xml_node, pugi::xml_node);

  public:
    // default constructor. constructs an empty attribute
    TableCell();

    // get next attribute
    TableCell &next();

    // check if attribute has next
    bool has_next() const;

    // return the first paragraph inside the cell
    Paragraph &paragraphs();
};

class TableRow {
    friend class IteratorHelper;
    // sotre parent and current node to be able to navigate whole the tree
    pugi::xml_node parent;
    pugi::xml_node current;

    // each row contains cell
    TableCell cell;

    // constructs attribute from xml_node
    TableRow(pugi::xml_node, pugi::xml_node);

  public:
    // default constructor. constructs an empty attribute
    TableRow();

    // get next attribute
    TableRow &next();

    // check if attribute has next
    bool has_next() const;

    // return first cell in the row
    TableCell &cells();
};

class Table {
  private:
    friend class IteratorHelper;
    // store parent and current node to be able to navigate whole the tree
    pugi::xml_node parent;
    pugi::xml_node current;

    // table contains rows
    TableRow row;

    // constructs attribute from xml_node
    Table(pugi::xml_node, pugi::xml_node);

  public:
    // default const. constructs an empty attribute
    Table();

    // get next attribute
    Table &next();

    // check if attribute has next
    bool has_next() const;

    // return the first row
    TableRow &rows();
};
} // namespace duckx

#endif // TABLE_HH_
