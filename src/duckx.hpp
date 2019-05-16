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
        Run();
        Run(pugi::xml_node, pugi::xml_node);
        void set_parent(pugi::xml_node);
        void set_current(pugi::xml_node);

        std::string get_text();
        bool set_text(std::string);
        bool set_text(const char *);

        Run &next();
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
        Paragraph(pugi::xml_node, pugi::xml_node);
        void set_parent(pugi::xml_node);
        void set_current(pugi::xml_node);

        Paragraph &next();
        bool has_next();

        Run &runs();
        Run &add_run(std::string);
        Run &add_run(const char*);
        Paragraph &insert_paragraph_after(std::string);
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
