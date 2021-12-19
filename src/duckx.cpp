#include "duckx.hpp"

#include <cctype>

// Hack on pugixml
// We need to write xml to std string (or char *)
// So overload the write function
struct xml_string_writer : pugi::xml_writer {
    std::string result;

    virtual void write(const void *data, size_t size) {
        result.append(static_cast<const char *>(data), size);
    }
};

duckx::Run::Run() {}

duckx::Run::Run(pugi::xml_node parent, pugi::xml_node current) {
    this->set_parent(parent);
    this->set_current(current);
}

void duckx::Run::set_parent(pugi::xml_node node) {
    this->parent = node;
    this->current = this->parent.child("w:r");
}

void duckx::Run::set_current(pugi::xml_node node) { this->current = node; }

std::string duckx::Run::get_text() const {
    return this->current.child("w:t").text().get();
}

bool duckx::Run::set_text(const std::string &text) const {
    return this->current.child("w:t").text().set(text.c_str());
}

bool duckx::Run::set_text(const char *text) const {
    return this->current.child("w:t").text().set(text);
}

duckx::Run &duckx::Run::next() {
    this->current = this->current.next_sibling();
    return *this;
}

bool duckx::Run::has_next() const { return this->current != 0; }

// Table cells
duckx::TableCell::TableCell() {}

duckx::TableCell::TableCell(pugi::xml_node parent, pugi::xml_node current) {
    this->set_parent(parent);
    this->set_current(current);
}

void duckx::TableCell::set_parent(pugi::xml_node node) {
    this->parent = node;
    this->current = this->parent.child("w:tc");

    this->paragraph.set_parent(this->current);
}

void duckx::TableCell::set_current(pugi::xml_node node) {
    this->current = node;
}

bool duckx::TableCell::has_next() const { return this->current != 0; }

duckx::TableCell &duckx::TableCell::next() {
    this->current = this->current.next_sibling();
    return *this;
}

duckx::Paragraph &duckx::TableCell::paragraphs() {
    this->paragraph.set_parent(this->current);
    return this->paragraph;
}

// Table rows
duckx::TableRow::TableRow() {}

duckx::TableRow::TableRow(pugi::xml_node parent, pugi::xml_node current) {
    this->set_parent(parent);
    this->set_current(current);
}

void duckx::TableRow::set_parent(pugi::xml_node node) {
    this->parent = node;
    this->current = this->parent.child("w:tr");

    this->cell.set_parent(this->current);
}

void duckx::TableRow::set_current(pugi::xml_node node) { this->current = node; }

duckx::TableRow &duckx::TableRow::next() {
    this->current = this->current.next_sibling();
    return *this;
}

duckx::TableCell &duckx::TableRow::cells() {
    this->cell.set_parent(this->current);
    return this->cell;
}

bool duckx::TableRow::has_next() const { return this->current != 0; }

// Tables
duckx::Table::Table() {}

duckx::Table::Table(pugi::xml_node parent, pugi::xml_node current) {
    this->set_parent(parent);
    this->set_current(current);
}

void duckx::Table::set_parent(pugi::xml_node node) {
    this->parent = node;
    this->current = this->parent.child("w:tbl");

    this->row.set_parent(this->current);
}

bool duckx::Table::has_next() const { return this->current != 0; }

duckx::Table &duckx::Table::next() {
    this->current = this->current.next_sibling();
    this->row.set_parent(this->current);
    return *this;
}

void duckx::Table::set_current(pugi::xml_node node) { this->current = node; }

duckx::TableRow &duckx::Table::rows() {
    this->row.set_parent(this->current);
    return this->row;
}

duckx::Paragraph::Paragraph() {}

duckx::Paragraph::Paragraph(pugi::xml_node parent, pugi::xml_node current) {
    this->set_parent(parent);
    this->set_current(current);
}

void duckx::Paragraph::set_parent(pugi::xml_node node) {
    this->parent = node;
    this->current = this->parent.child("w:p");

    this->run.set_parent(this->current);
}

void duckx::Paragraph::set_current(pugi::xml_node node) {
    this->current = node;
}

duckx::Paragraph &duckx::Paragraph::next() {
    this->current = this->current.next_sibling();
    this->run.set_parent(this->current);
    return *this;
}

bool duckx::Paragraph::has_next() const { return this->current != 0; }

duckx::Run &duckx::Paragraph::runs() {
    this->run.set_parent(this->current);
    return this->run;
}

duckx::Run &duckx::Paragraph::add_run(const std::string &text,
                                      duckx::formatting_flag f) {
    return this->add_run(text.c_str(), f);
}

duckx::Run &duckx::Paragraph::add_run(const char *text,
                                      duckx::formatting_flag f) {
    // Add new run
    pugi::xml_node new_run = this->current.append_child("w:r");
    // Insert meta to new run
    pugi::xml_node meta = new_run.append_child("w:rPr");

    if (f & duckx::bold)
        meta.append_child("w:b");

    if (f & duckx::italic)
        meta.append_child("w:i");

    if (f & duckx::underline)
        meta.append_child("w:u").append_attribute("w:val").set_value("single");

    if (f & duckx::strikethrough)
        meta.append_child("w:strike")
            .append_attribute("w:val")
            .set_value("true");

    if (f & duckx::superscript)
        meta.append_child("w:vertAlign")
            .append_attribute("w:val")
            .set_value("superscript");
    else if (f & duckx::subscript)
        meta.append_child("w:vertAlign")
            .append_attribute("w:val")
            .set_value("subscript");

    if (f & duckx::smallcaps)
        meta.append_child("w:smallCaps")
            .append_attribute("w:val")
            .set_value("true");

    if (f & duckx::shadow)
        meta.append_child("w:shadow")
            .append_attribute("w:val")
            .set_value("true");

    pugi::xml_node new_run_text = new_run.append_child("w:t");
    // If the run starts or ends with whitespace characters, preserve them using
    // the xml:space attribute
    if (*text != 0 && (isspace(text[0]) || isspace(text[strlen(text) - 1])))
        new_run_text.append_attribute("xml:space").set_value("preserve");
    new_run_text.text().set(text);

    return *new Run(this->current, new_run);
}

duckx::Paragraph &
duckx::Paragraph::insert_paragraph_after(const std::string &text,
                                         duckx::formatting_flag f) {
    pugi::xml_node new_para =
        this->parent.insert_child_after("w:p", this->current);

    Paragraph *p = new Paragraph();
    p->set_current(new_para);
    p->add_run(text, f);

    return *p;
}

// TODO: this function must be removed!
duckx::Document::Document() : mode{MODE::FILE}, directory{""} { }

duckx::Document::Document(std::string directory) : mode{MODE::FILE}, directory{directory} { }

duckx::Document::Document(char* zipBuf, size_t len) : mode{MODE::BUFFER}, buf{zipBuf}, bufLen{len} { }

void duckx::Document::file(std::string directory) {
    this->mode = MODE::FILE;
    this->directory = directory;
}

void duckx::Document::buffer(char* zipBuf, size_t len) {
    this->mode = MODE::BUFFER;
    this->buf = zipBuf;
    this->bufLen = len;
}

duckx::Document::~Document() {
    //makes double free or corruption
    //if (zip != NULL) zip_close(zip);
}

void duckx::Document::close() {
    if (zip != NULL) zip_close(zip);
    zip = NULL;
    this->saveWriters.clear();
}

void duckx::Document::open() {
    if (this->mode != MODE::FILE && this->mode != MODE::BUFFER) throw "Unknown mode error, specify file or buffer";

    // Open file and load "xml" content to the document variable
    //if (zip != NULL) zip_close(zip);
    zip = this->mode == MODE::FILE ? 
        zip_open(this->directory.c_str(), ZIP_CREATE, NULL) : /*this->mode == MODE::BUFFER*/
        zip_open_from_source(zip_source_buffer_create(this->buf, this->bufLen, 0, &zipError), 0, &zipError) ;
    docFile = zip_fopen(zip, "word/document.xml", 0);
    if (!docFile) throw "Something's wrong with the document";
    struct zip_stat sb;
    zip_stat(zip, "word/document.xml", 0, &sb);
    size_t bufSize = sb.size;
    void* docBuf = malloc(bufSize);
    zip_fread(docFile, docBuf, bufSize);
    this->document.load_buffer(docBuf, bufSize);


    free(docBuf);
    zip_fclose(docFile);

    this->paragraph.set_parent(document.child("w:document").child("w:body"));

}

void duckx::Document::save(const char* dst) {
    using namespace std;
    if (this->mode != MODE::FILE && this->mode != MODE::BUFFER) throw "Unknown mode error, specify file or buffer";

    if (mode == MODE::BUFFER && dst == NULL) throw "Specify destination path"; 

    //see comment in include/duckx.hpp about writers
    /*xml_string_writer writer; 
    this->document.print(writer);
    char* newBuf = writer.result.c_str();*/


    if (dst == NULL) {
        auto writer = make_shared<xml_string_writer>();
        this->saveWriters.push_back(writer);
        this->document.print(*writer);
        const char* newBuf = writer->result.c_str();
        auto source = zip_source_buffer_create(newBuf, strlen(newBuf), 0, &zipError);
        auto idx = zip_name_locate(zip, "word/document.xml", 0);
        zip_replace(zip, idx, source);
    }
    else {
        xml_string_writer writer; 
        this->document.print(writer);
        const char* newBuf = writer.result.c_str();
        zip_t* dstZip = zip_open(dst, ZIP_CREATE /*| ZIP_TRUNCATE*/, errorp);
        for (int i = 0; i < zip_get_num_entries(zip, 0); ++i) {
            auto name = zip_get_name(zip, i, 0);
            if (string(name) != "word/document.xml") {
                auto file = zip_fopen_index(zip, i, /*ZIP_FL_COMPRESSED*/ 0); //TODO unnecessary decompression + compression, need to think of workaround 
                struct zip_stat sb;
                zip_stat(zip, name, 0, &sb);
                auto fsize = /*sb.comp_size*/ sb.size;
                auto tmpBuf = malloc(fsize);
                DEBUG(zip_fread(file, tmpBuf, fsize));
                auto source = zip_source_buffer_create(tmpBuf, fsize, 1, &zipError);
                DEBUG(source);
                DEBUG(zip_file_add(dstZip, name, source, ZIP_FL_OVERWRITE));
                zip_fclose(file);
            }
        }
        auto source = zip_source_buffer_create(newBuf, strlen(newBuf), 0, &zipError);
        zip_file_add(dstZip, "word/document.xml", source, ZIP_FL_OVERWRITE);
        zip_close(dstZip);
    }
}

duckx::Paragraph &duckx::Document::paragraphs() {
    this->paragraph.set_parent(document.child("w:document").child("w:body"));
    return this->paragraph;
}

duckx::Table &duckx::Document::tables() {
    this->table.set_parent(document.child("w:document").child("w:body"));
    return this->table;
}
