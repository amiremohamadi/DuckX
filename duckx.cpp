#include "duckx.hpp"

void Run::setParent(pugi::xml_node node) {
    this->parent = node;
    this->current = this->parent.child("w:r");
}

const pugi::char_t *Run::text() {
    return this->current.child("w:t").text().get();
}


Paragraph::Paragraph() {}

void Paragraph::setParent(pugi::xml_node node) {
    this->parent = node;
    this->current = this->parent.child("w:p");
    
    this->run.setParent(
        this->current
    );
}

const Paragraph &Paragraph::next() {
    this->current = this->current.next_sibling();
    this->run.setParent(this->current);
    return *this;
}

bool Paragraph::hasNext() {
    return this->current != 0;
}

Run &Paragraph::runs() {
    return this->run;
}


Document::Document() {
    // TODO: this function must be removed!
    this->directory = "";
}

Document::Document(const char *directory) {
    this->directory = directory;

    Handle handle(this->directory);
    document.load_string(
        handle.getContent()
    );

    this->paragraph.setParent(
        document.child("w:document").child("w:body")
    );
}

void Document::file(char *directory) {
    this->directory = directory;
    
    Handle handle(directory);
    document.load_string(
        handle.getContent()
    );
}

Paragraph &Document::paragraphs() {
    return this->paragraph;
}