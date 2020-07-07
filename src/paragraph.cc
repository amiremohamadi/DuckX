/*
 * Under MIT license
 * author : Amir Mohamadi (@amiremohamadi)
 * this file contains all implementation stuffs related to paragraph.hh
 */

#include <duckx/paragraph.hh>

// constructs attribute from xml_node
duckx::Paragraph::Paragraph(pugi::xml_node parent, pugi::xml_node current) {
    this->parent = parent;
    this->current = current;
}

// set current xml node
void duckx::Paragraph::set_current(pugi::xml_node node) {
    this->current = node;
    // child must be updated also
    this->run.set_parent(this->current);
}

// set parent xml node
void duckx::Paragraph::set_parent(pugi::xml_node node) {
    // when parent changes, the child must be updated also
    this->parent = node;
    this->set_current(this->parent.child("w:p"));
}

// get next attribute
duckx::Paragraph &duckx::Paragraph::next() {
    this->set_current(this->current.next_sibling());
    return *this;
}

// checks if the attribute has next
bool duckx::Paragraph::has_next() const { return this->current != 0; }

// return the first run
duckx::Run &duckx::Paragraph::runs() {
    // the run must point to the first run in the current paragraph
    this->run.set_parent(this->current);
    return this->run;
}

// append run to the paragraph (the actual run)
duckx::Run &duckx::Paragraph::add_run(duckx::Run run) {
    duckx::Run *new_run = new duckx::Run(run);
    // set the parent to the current paragraph
    new_run->set_parent(this->current);
    return *new_run;
}

// append run to the paragraph
duckx::Run &duckx::Paragraph::add_run(const std::string &text) {
    return this->add_run(text.c_str());
}

// append run to the paragraph
duckx::Run &duckx::Paragraph::add_run(const char *text) {
    // add new run
    pugi::xml_node new_run = this->current.append_child("w:r");
    pugi::xml_node new_run_text = new_run.append_child("w:t");

    // set the content
    new_run_text.text().set(text);

    // create new run which have a parent points to this paragraph
    return *new Run(this->current, new_run);
}

// insert a paragraph right after this paragraph
duckx::Paragraph &duckx::Paragraph::insert_paragraph_after(const std::string &text) {
    pugi::xml_node new_para = this->parent.insert_child_after("w:p", this->current);

    Paragraph *para = new Paragraph();
    para->set_current(new_para);
    para->add_run(text);

    return *para;
}
