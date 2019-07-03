#include "duckx.hpp"

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

void duckx::Run::set_current(pugi::xml_node node) {
    this->current = node;
}


std::string duckx::Run::get_text() {
    return this->current.child("w:t").text().get();
}

bool duckx::Run::set_text(const std::string &text) {
    return this->current.child("w:t").text().set(text.c_str());
}

bool duckx::Run::set_text(const char *text) {
    return this->current.child("w:t").text().set(text);
}

duckx::Run &duckx::Run::next() {
    this->current = this->current.next_sibling();
    return *this;
}

bool duckx::Run::has_next() {
    return this->current != 0;
}

duckx::Paragraph::Paragraph() {}

duckx::Paragraph::Paragraph(pugi::xml_node parent, pugi::xml_node current) {
    this->set_parent(parent);
    this->set_current(current);
}

void duckx::Paragraph::set_parent(pugi::xml_node node) {
    this->parent = node;
    this->current = this->parent.child("w:p");

    this->run.set_parent(
            this->current
    );
}

void duckx::Paragraph::set_current(pugi::xml_node node) {
    this->current = node;
}

duckx::Paragraph &duckx::Paragraph::next() {
    this->current = this->current.next_sibling();
    this->run.set_parent(this->current);
    return *this;
}

bool duckx::Paragraph::has_next() {
    return this->current != 0;
}

duckx::Run &duckx::Paragraph::runs() {
    this->run.set_parent(
            this->current
    );
    return this->run;
}

duckx::Run &duckx::Paragraph::add_run(const std::string &text) {
    return this->add_run(text.c_str());
}

duckx::Run &duckx::Paragraph::add_run(const char *text) {
    // Add new run
    pugi::xml_node new_run = this->current.append_child("w:r");
    // Insert meta to new run
    new_run.append_child("w:rPr");
    pugi::xml_node new_run_text = new_run.append_child("w:t");
    new_run_text.text().set(text);

    return *new Run(this->current, new_run);
}

duckx::Paragraph &duckx::Paragraph::insert_paragraph_after(const std::string &text) {
    pugi::xml_node new_para = this->parent.insert_child_after("w:p", this->current);

    Paragraph *p = new Paragraph();
    p->set_current(new_para);
    p->add_run(text);

    return *p;
}


duckx::Document::Document() {
    // TODO: this function must be removed!
    this->directory = "";
}

duckx::Document::Document(const std::string &directory) {
    this->directory = directory;
}

void duckx::Document::file(const std::string &directory) {
    this->directory = directory;
}

void duckx::Document::open() {
    void *buf = NULL;
    int err = 0;
    zip_t *zip = zip_open(this->directory.c_str(), ZIP_RDONLY, &err);
    if (zip == nullptr) {
        return;
    }
    zip_stat_t st;
    zip_stat_init(&st);
    zip_stat(zip, "word/document.xml", 0, &st);
    zip_file_t *zfile = zip_fopen_index(zip, st.index, 0);
    buf = malloc(st.size);
    zip_fread(zfile, buf, st.size);
    zip_fclose(zfile);
    this->document.load_string(
            (char *) buf
    );

    free(buf);
    zip_close(zip);
    this->paragraph.set_parent(
            document.child("w:document").child("w:body")
    );
}

void duckx::Document::save() {
    // Open file and replace "xml" content
    int err = 0;
    zip_t *zip = zip_open(this->directory.c_str(), 0, &err);
    if (zip == nullptr) {
        return;
    }
    zip_stat_t st;
    zip_stat_init(&st);
    zip_stat(zip, "word/document.xml", 0, &st);

    xml_string_writer writer;
    this->document.print(writer);

    const char *buf = writer.result.c_str();
    zip_error_t error = {0};
    zip_source_t *source = zip_source_buffer_create(buf, writer.result.length(), 0, &error);
    zip_file_replace(zip, st.index, source, ZIP_FL_OVERWRITE | ZIP_FL_ENC_UTF_8);
    zip_source_close(source);
    zip_close(zip);
}

duckx::Paragraph &duckx::Document::paragraphs() {
    this->paragraph.set_parent(
            document.child("w:document").child("w:body")
    );
    return this->paragraph;
}