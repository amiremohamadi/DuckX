/*
 * Under MIT license
 * Author: Amir Mohamadi (@amiremohamadi)
 * DuckX is a free library to work with docx files.
 */

#ifndef DUCKX_H
#define DUCKX_H

#include <bits/stdc++.h>
#include <cstdio>
#include <stdlib.h>
#include <string>

#include <constants.hpp>
#include <duckxiterator.hpp>
#include <pugixml.hpp>
#include <zip.h>

#define PROD

#ifndef PROD
#define DEBUG(x) cout << "[DEBUG] " << #x << ": " << (x) << endl;
#else
#define DEBUG
#endif

// TODO: Use container-iterator design pattern!

struct xml_string_writer;


namespace duckx {
// Run contains runs in a paragraph
class Run {
  private:
    friend class IteratorHelper;
    // Store the parent node (a paragraph)
    pugi::xml_node parent;
    // And store current node also
    pugi::xml_node current;

  public:
    Run();
    Run(pugi::xml_node, pugi::xml_node);
    void set_parent(pugi::xml_node);
    void set_current(pugi::xml_node);

    std::string get_text() const;
    bool set_text(const std::string &) const;
    bool set_text(const char *) const;

    Run &next();
    bool has_next() const;
};

// Paragraph contains a paragraph
// and stores runs
class Paragraph {
  private:
    friend class IteratorHelper;
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
    bool has_next() const;

    Run &runs();
    Run &add_run(const std::string &, duckx::formatting_flag = duckx::none);
    Run &add_run(const char *, duckx::formatting_flag = duckx::none);
    Paragraph &insert_paragraph_after(const std::string &,
                                      duckx::formatting_flag = duckx::none);
};

// TableCell contains one or more paragraphs
class TableCell {
  private:
    friend class IteratorHelper;
    pugi::xml_node parent;
    pugi::xml_node current;

    Paragraph paragraph;

  public:
    TableCell();
    TableCell(pugi::xml_node, pugi::xml_node);

    void set_parent(pugi::xml_node);
    void set_current(pugi::xml_node);

    Paragraph &paragraphs();

    TableCell &next();
    bool has_next() const;
};

// TableRow consists of one or more TableCells
class TableRow {
    friend class IteratorHelper;
    pugi::xml_node parent;
    pugi::xml_node current;

    TableCell cell;

  public:
    TableRow();
    TableRow(pugi::xml_node, pugi::xml_node);
    void set_parent(pugi::xml_node);
    void set_current(pugi::xml_node);

    TableCell &cells();

    bool has_next() const;
    TableRow &next();
};

// Table consists of one or more TableRow objects
class Table {
  private:
    friend class IteratorHelper;
    pugi::xml_node parent;
    pugi::xml_node current;

    TableRow row;

  public:
    Table();
    Table(pugi::xml_node, pugi::xml_node);
    void set_parent(pugi::xml_node);
    void set_current(pugi::xml_node);

    Table &next();
    bool has_next() const;

    TableRow &rows();
};

enum class MODE {
    FILE,
    BUFFER,
};

// Document contains whole the docx file
// and stores paragraphs
class Document {
  private:
    friend class IteratorHelper;
    std::string directory;
    MODE mode;
    Paragraph paragraph;
    Table table;
    pugi::xml_document document;
    zip_error_t zipError;
    int *errorp;
    zip_file_t* docFile = NULL;
    zip_t* zip = NULL;
    char* buf;
    size_t bufLen;
    //the only way I know to write to zip is wait for zip_close, 
    //so we need to keep writers in order to flush it's contents to actual file
    std::vector<std::shared_ptr<xml_string_writer>> saveWriters; 

  public:
    Document();
    ~Document();
    Document(std::string);
    Document(char*, size_t);
    void file(std::string);
    void buffer(char*, size_t);
    void open();
    void close();
    void save(const char* dst = NULL);
    //void save(const char*) const;

    Paragraph &paragraphs();
    Table &tables();
};
} // namespace duckx

#endif
