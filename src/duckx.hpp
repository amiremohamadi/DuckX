/*
 * Under MIT license
 * Author: Amir Mohamadi (@amiremohamadi)
 * DuckX is a free library to work wirh docx files.
*/

#ifndef DUCKX_H
#define DUCKX_H

#include <stdlib.h>
#include <string>

#include "pugixml.hpp"
#include "zip.h"


// TODO: Use conatiner-iterator design pattern!

namespace duckx {
    // Run contains runs in a paragraph
    class Run {
    private:
        // Store the parent node (a paragraph)
        pugi::xml_node parent;
        // And store current node also
        pugi::xml_node current;

    public:
        void set_parent(pugi::xml_node);

        const pugi::char_t *text();

        const Run &next();
        
        bool has_next();

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
        void set_parent(pugi::xml_node);

        const Paragraph &next();

        bool has_next();

        Run &runs();
    };

    // Document conatins whole the docx file
    // and stores paragraphs
    class Document {
    private:
        std::string directory;
        Paragraph paragraph;
        pugi::xml_document document;

    public:
        Document();
        Document(std::string);
        void file(std::string);
        void open();
        void save();

        Paragraph &paragraphs();
    };
}

#endif