#include "duckx.hpp"

#include <cctype>
#include "zip.h"

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

void duckx::TableCell::resize(int nCol)
{
    current = parent.child("w:tc");
    if (current == NULL)
    {
        current = parent.append_child("w:tc");
    }
    paragraph.add(current);

    pugi::xml_node cur = current;
    int nC = 0;
    while (current != NULL)
    {
        nC++;
        current = current.next_sibling();
    }

    int i;
    for (i = nC; i < nCol; i++)
    {
        pugi::xml_node added = parent.append_copy(cur);
        TableCell tc(parent, added);
    }
    for (i = nCol; i < nC; i++)
    {
        parent.remove_child(parent.last_child());
    }
}

void duckx::TableCell::add()
{
    pugi::xml_node added = parent.append_copy(current);
    TableCell tc(parent, added);
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

void duckx::TableRow::resize(int nRow, int nCol)
{
    this->current = this->parent.child("w:tr");
    if (current == NULL)
    {
        current = parent.append_child("w:tr");
    }
    cell.set_parent(this->current);
    cell.resize(nCol);

    pugi::xml_node cur = current;
    int nR = 0;
    while (current != NULL)
    {
        if (nR < nRow)
        {
            cells().resize(nCol);
        }
        nR++;
        current = current.next_sibling();
    }

    int i;
    for (i = nR; i < nRow; i++)
    {
        pugi::xml_node added = parent.append_copy(cur);
        TableRow tr(parent, added);
    }
    for (i = nRow; i < nR; i++)
    {
        parent.remove_child(parent.last_child());
    }
}

void duckx::TableRow::add()
{
    pugi::xml_node added = parent.append_copy(current);
    TableRow tr(parent, added);
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

void duckx::Table::resize(int nRow, int nCol)
{
    current = parent.child("w:tbl");
    if (current == NULL)
    {
        current = parent.append_child("w:tbl");
    }
    row.set_parent(current);

    if (nRow > 0 && nCol > 0)
    {
        row.resize(nRow, nCol);
    }
}

void duckx::Table::set_current(pugi::xml_node node) { this->current = node; }

duckx::Table &duckx::Table::append()
{
    if (current == NULL)
    {
        current = parent.append_child("w:tbl");
        row.set_parent(current);
        return *this;
    }
    else
    {
        pugi::xml_node added = parent.append_copy(current);
        Table t(parent, added);
        return t;
    }
}

void duckx::Table::set_text(int nRow, int nCol, const char *lpszText)
{
    TableRow &tr = rows();
    int i;
    for (i = 0; i < nRow; i++)
    {
        if (tr.has_next())
        {
            tr.next();
        }
    }

    TableCell &tc = tr.cells();
    for (i = 0; i < nCol; i++)
    {
        if (tc.has_next())
        {
            tc.next();
        }
    }
    tc.paragraphs().set_text(lpszText);
}

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

    if (f & duckx::emphasis)
        meta.append_child("w:em").append_attribute("w:val").set_value("dot");

    if (f & duckx::strikethrough)
        meta.append_child("w:strike")
        .append_attribute("w:val")
        .set_value("true");

    if (f & duckx::doublestrikethrough)
        meta.append_child("w:dstrike")
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
    else if (f & duckx::allcaps)
        meta.append_child("w:caps")
        .append_attribute("w:val")
        .set_value("true");

    if (f & duckx::relief)
        meta.append_child("w:emboss")
        .append_attribute("w:val")
        .set_value("true");
    else if (f & duckx::intaglio)
        meta.append_child("w:imprint")
        .append_attribute("w:val")
        .set_value("true");

    if (f & duckx::hide)
        meta.append_child("w:vanish")
        .append_attribute("w:val")
        .set_value("true");

    if (f & duckx::hollow)
        meta.append_child("w:outline")
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
                                         duckx::formatting_flag f)
{
    if (current == NULL)
    {
        current = parent.append_child("w:p");
        add_run(text, f);
        return *this;
    }
    else
    {
        pugi::xml_node new_para =
            this->parent.insert_child_after("w:p", this->current);

        Paragraph *p = new Paragraph();
        p->set_current(new_para);
        p->add_run(text, f);
        return *p;
    }
}

bool duckx::Paragraph::set_text(const char *lpszT, duckx::formatting_flag f)
{
    if (current == NULL)
    {
        current = parent.append_child("w:p");
        run.set_parent(current);
    }
    if (run.has_next())
    {
        run.set_text(lpszT);
    }
    else
    {
        add_run(lpszT, f);
    }
    return true;
}

void duckx::Paragraph::add(pugi::xml_node node)
{
    parent = node;
    current = parent.child("w:p");
    if (current == NULL)
    {
        current = parent.append_child("w:p");
    }
    run.set_parent(current);
}

duckx::Document::Document() {
    // TODO: this function must be removed!
    this->directory = "";
}

duckx::Document::Document(std::string directory) {
    this->directory = directory;
}

void duckx::Document::file(std::string directory) {
    this->directory = directory;
}

void duckx::Document::open() {
    void *buf = NULL;
    size_t bufsize;

    // Open file and load "xml" content to the document variable
    zip_t *zip =
        zip_open(this->directory.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');

    zip_entry_open(zip, "word/document.xml");
    zip_entry_read(zip, &buf, &bufsize);

    zip_entry_close(zip);
    zip_close(zip);

    this->document.load_buffer(buf, bufsize);

    free(buf);

    this->paragraph.set_parent(document.child("w:document").child("w:body"));
}

void duckx::Document::save() const {
    // minizip only supports appending or writing to new files
    // so we must
    // - make a new file
    // - write any new files
    // - copy the old files
    // - delete old docx
    // - rename new file to old file

    // Read document buffer
    xml_string_writer writer;
    this->document.print(writer);

    // Open file and replace "xml" content

    std::string original_file = this->directory;
    std::string temp_file = this->directory + ".tmp";

    // Create the new file
    zip_t *new_zip =
        zip_open(temp_file.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');

    // Write out document.xml
    zip_entry_open(new_zip, "word/document.xml");

    const char *buf = writer.result.c_str();

    zip_entry_write(new_zip, buf, strlen(buf));
    zip_entry_close(new_zip);

    // Open the original zip and copy all files which are not replaced by duckX
    zip_t *orig_zip =
        zip_open(original_file.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');

    // Loop & copy each relevant entry in the original zip
    int orig_zip_entry_ct = zip_total_entries(orig_zip);
    for (int i = 0; i < orig_zip_entry_ct; i++) {
        zip_entry_openbyindex(orig_zip, i);
        const char *name = zip_entry_name(orig_zip);

        // Skip copying the original file
        if (std::string(name) != std::string("word/document.xml")) {
            // Read the old content
            void *entry_buf;
            size_t entry_buf_size;
            zip_entry_read(orig_zip, &entry_buf, &entry_buf_size);

            // Write into new zip
            zip_entry_open(new_zip, name);
            zip_entry_write(new_zip, entry_buf, entry_buf_size);
            zip_entry_close(new_zip);

            free(entry_buf);
        }

        zip_entry_close(orig_zip);
    }

    // Close both zips
    zip_close(orig_zip);
    zip_close(new_zip);

    // Remove original zip, rename new to correct name
    remove(original_file.c_str());
    rename(temp_file.c_str(), original_file.c_str());
}

void duckx::Document::clear()
{
    pugi::xml_node body = document.child("w:document").child("w:body");
    while (body.remove_child("w:p"));
    while (body.remove_child("w:tbl"));
}

duckx::Paragraph &duckx::Document::paragraphs() {
    this->paragraph.set_parent(document.child("w:document").child("w:body"));
    return this->paragraph;
}

duckx::Table &duckx::Document::tables() {
    this->table.set_parent(document.child("w:document").child("w:body"));
    return this->table;
}
