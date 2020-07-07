/*
 * Under MIT license
 * author : Amir Mohamadi (@amiremohamadi)
 * this file contains all implementation stuffs related to run.hh
 */

#include <duckx/run.hh>

// constructs attribute from xml_node
duckx::Run::Run(pugi::xml_node parent, pugi::xml_node current) {
    this->parent = parent;
    this->current = current;
}

// set current xml node
void duckx::Run::set_current(pugi::xml_node node) { this->current = node; }

// set parent xml node
void duckx::Run::set_parent(pugi::xml_node node) {
    this->parent = node;
    this->set_current(this->parent.child("w:r"));
}

// get attribute text
std::string duckx::Run::get_text() const {
    return this->current.child("w:t").text().get();
}

// set attribute text (std::string)
bool duckx::Run::set_text(const std::string &text) const {
    return this->current.child("w:t").text().set(text.c_str());
}

// set attribute text (c_str)
bool duckx::Run::set_text(const char *text) const {
    return this->current.child("w:t").text().set(text);
}

// get next attribute
duckx::Run &duckx::Run::next() {
    this->set_current(this->current.next_sibling());
    return *this;
}

// check if attribute has next
bool duckx::Run::has_next() const { return this->current != 0; }
