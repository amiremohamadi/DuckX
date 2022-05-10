/*
 * Under MIT license
 * Author: Amir Mohamadi (@amiremohamadi)
 * DuckX is a free library to work with docx files.
 */

#ifndef DUCKX_H
#define DUCKX_H

#include <cstdio>
#include <stdlib.h>
#include <string>

#include <constants.hpp>
#include <duckxiterator.hpp>
#include <pugixml.hpp>
#include <vector>

#ifdef _WIN32
#ifdef duckx_EXPORTS
#define DUCKX_EXPORT __declspec(dllexport)
#else
#define DUCKX_EXPORT __declspec(dllimport)
#endif
#else
#define DUCKX_EXPORT
#endif

// TODO: Use container-iterator design pattern!

namespace duckx {
#define make_rgb(r, g, b) ((((unsigned char)r)<<16)|(((unsigned char)g)<<8)|((unsigned char)b))

struct MediaObject
{
    char    szName[24]; // media name saved into `word\media` directory
    std::vector<char> content; // media content
};

class Document;
// Run contains runs in a paragraph
class DUCKX_EXPORT Run {
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
    inline bool set_text(const std::string &t) const { return set_text(t.c_str()); };
    bool set_text(const char *) const;
    bool add_picture(Document &doc, const char *lpszPath, int w, int h);

    Run &next();
    bool has_next() const;
};

// Paragraph contains a paragraph
// and stores runs
class DUCKX_EXPORT Paragraph {
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
    inline Run &add_run(const std::string &t, duckx::formatting_flag f = duckx::none, unsigned char nFontSize = 0, const std::string &strFontName = std::string(), int nColor = 0) { return add_run(t.c_str(),f, nFontSize, strFontName.data(), nColor); };
    Run &add_run(const char *, duckx::formatting_flag = duckx::none, unsigned char nFontSize = 0, const char *pszFontName = NULL, int nColor = 0);
    inline Paragraph &append(const std::string &t, duckx::formatting_flag f = duckx::none, unsigned char nFontSize = 0, const std::string &strFontName = std::string(), int nColor = 0) { return append(t.c_str(), f, nFontSize, strFontName.data(), nColor); };
    Paragraph &append(const char *, duckx::formatting_flag = duckx::none, unsigned char nFontSize = 0, const char *pszFontName = NULL, int nColor = 0);
    Paragraph &set_alignment(paragraph_alignment a = duckx::align_left, bool bNew = true, unsigned char indent = 0, unsigned char font_size = 10);
    inline bool set_text(const std::string &t, duckx::formatting_flag f = duckx::none) { return set_text(t.c_str(), f); };
    bool set_text(const char *, duckx::formatting_flag = duckx::none, int nColor = 0);
    void add(pugi::xml_node);
};

// TableCell contains one or more paragraphs
class DUCKX_EXPORT TableCell {
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
    void resize(int nCol = 1);
    void mergeCol(int nSpanCol = 2);
    void mergeRow(bool bStart = false);
    void add();
    void setBackGroundColor(int nColor);

private:
    int getWidth(pugi::xml_node cell);
};

// TableRow consists of one or more TableCells
class DUCKX_EXPORT TableRow {
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
    void resize(int nRow = 1, int nCol = 1);
    void merge(int nStartRow = 1, int nStartCol = 1, int nSpanRow = 1, int nSpanCol = 2);
    void add();
};

// Table consists of one or more TableRow objects
class DUCKX_EXPORT Table {
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

    Table &append(bool bNew = true);
    Table &next();
    bool has_next() const;
    void resize(int nRow = 1, int nCol = 1);
    void merge(int nStartRow = 1, int nStartCol = 1, int nSpanRow = 1, int nSpanCol = 2);
    void set_text(int nRow, int nCol, const char *lpszText, paragraph_alignment a = duckx::align_left, int nBackGroundColor = 0, int nTextColor = 0, unsigned char nFontSize = 0, const char *pszFontName = NULL, duckx::formatting_flag = duckx::none);

    TableRow &rows();
};

// Document contains whole the docx file
// and stores paragraphs
class DUCKX_EXPORT Document {
  private:
    friend class IteratorHelper;
    std::string directory;
    Paragraph paragraph;
    Table table;
    pugi::xml_document document;//`word/document.xml`
    pugi::xml_document _doc_rels; //`word/_rels/document.xml.rels`
    std::vector<MediaObject> _medias;

  public:
    Document();
    Document(std::string);
    void file(std::string);
    bool open();
    bool save() const;
    void clear();
    inline pugi::xml_document& get_doc_rels() { return _doc_rels; };
    std::vector<MediaObject>& medias() { return _medias; };

	Paragraph &paragraphs();
	Table &tables();
};
} // namespace duckx

#endif
