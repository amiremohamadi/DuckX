/*
 * Under MIT license
 * author : Amir Mohamadi (@amiremohamadi)
 * this file contains all implementation stuffs related to table.hh
 */

#include <duckx/table.hh>

/* TableCell */
// constructs cell attribute from xml_node
duckx::TableCell::TableCell(pugi::xml_node parent, pugi::xml_node current) {
    this->parent = parent;
    this->current = current;
}

// set current xml node
void duckx::TableCell::set_current(pugi::xml_node node) {
    this->current = node;
    // the child must be updated also
    this->paragraph.set_parent(this->current);
}

// set parent xml node
void duckx::TableCell::set_parent(pugi::xml_node node) {
    this->parent = node;
    this->set_current(this->parent.child("w:tc"));
}

// get next attribute
duckx::TableCell &duckx::TableCell::next() {
    this->set_current(this->current.next_sibling());
    return *this;
}

// check if attribute has next
bool duckx::TableCell::has_next() const { return this->current != 0; }

// return the first paragraph inside the cell
duckx::Paragraph &duckx::TableCell::paragraphs() {
    this->paragraph.parent = this->current;
    return this->paragraph;
}

/* TableRow */
// constructs row attribute from xml_node
duckx::TableRow::TableRow(pugi::xml_node parent, pugi::xml_node current) {
    this->parent = parent;
    this->current = current;
}

// set current xml node
void duckx::TableRow::set_current(pugi::xml_node node) {
    this->set_current(node);
    // also child must be updated
    this->cell.set_parent(this->current);
}

// set parent xml node
void duckx::TableRow::set_parent(pugi::xml_node node) {
    this->parent = node;
    this->set_current(this->parent.child("w:tr"));
}

// get next attribute
duckx::TableRow &duckx::TableRow::next() {
    this->set_current(this->current.next_sibling());
    return *this;
}

// check if the attribute has next
bool duckx::TableRow::has_next() const { return this->current != 0; }

// return first cell in the row
duckx::TableCell &duckx::TableRow::cells() {
    this->cell.parent = this->current;
    return this->cell;
}

/* Table */
// constructs table attribute from xml_node
duckx::Table::Table(pugi::xml_node parent, pugi::xml_node current) {
    this->parent = parent;
    this->current = current;
}

// set current xml node
void duckx::Table::set_current(pugi::xml_node node) {
    this->current = node;
    // the child must be updated also
    this->row.set_parent(this->current);
}

// set parent xml node
void duckx::Table::set_parent(pugi::xml_node node) {
    this->parent = node;
    this->set_current(this->parent.child("w:tbl"));
}

// get next attribute
duckx::Table &duckx::Table::next() {
    this->set_current(this->current.next_sibling());
    return *this;
}

// check if the attribute has next
bool duckx::Table::has_next() const { return this->current != 0; }

// return the first row
duckx::TableRow &duckx::Table::rows() {
    this->row.set_parent(this->current);
    return this->row;
}
