/*
 * Under MIT license
 * Author: Amir Mohamadi (@amiremohamadi)
 * DuckX is a free library to work wirh docx files.
*/

#ifndef DUCKX_H
#define DUCKX_H

#include "pugixml/pugixml.hpp"
#include "handle/handle.hpp"

// TODO: Use conatiner-iterator design pattern!

// Run contains runs in a paragraph
class Run {
private:
    // Store the parent node (a paragraph)
    pugi::xml_node parent;
    // And store current node also
    pugi::xml_node current;

public:
    void setParent(pugi::xml_node);

    const pugi::char_t *text();
};

// Paragraph contains a paragraph
// and stores runs
class Paragraph {
private:
    // Store parent node (usually the body node)
    pugi::xml_node parent;
    // And store current node also
    pugi::xml_node current;
    // A paragraph consists of runs
    Run run;

public:
    Paragraph();
    void setParent(pugi::xml_node);

    const Paragraph &next();

    bool hasNext();

    Run &runs();
};

// Document conatins whole the docx file
// and stores paragraphs
class Document {
private:
    const char *directory;
    Paragraph paragraph;
    pugi::xml_document document;
    
public:
    Document();
    Document(const char *);
    void file(const char *);
    void open();

    Paragraph &paragraphs();
};

#endif