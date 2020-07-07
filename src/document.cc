/*
 * Under MIT license
 * author : Amir Mohamadi (@amiremohamadi)
 * this file contains all implementation stuffs related to document.hh
 */

#include <duckx/document.hh>
#include <iostream>

// overload pugi_xml writer to use in save method
// we wanna save a bunch of bytes (void *) as char
// this is only becase the inconsistency of zip and xml libraries that we use
// TODO: maybe decelare this inside the document class
struct xml_string_writer : pugi::xml_writer {
    std::string result;

    virtual void write(const void *data, size_t size) {
        result.append(static_cast<const char *>(data), size);
    }
};

// constructs document and set the file path
duckx::Document::Document(std::string directory) { this->directory = directory; }

// set the file path (just set, not opening)
void duckx::Document::file(std::string directory) { this->directory = directory; }

// open the file
void duckx::Document::open() {
    void *buf = NULL;
    size_t bufsize;

    // open file and load "xml" content to the document variable
    zip_t *zip = zip_open(this->directory.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');

    if (zip == NULL) {
        // raise error
        return;
    }

    // open the document file
    // TODO: it would be good to check if this file is exist
    // and in case of not existing raise an exception
    int err = zip_entry_open(zip, "word/document.xml");

    if (err == -1) {
        // raise error
        return;
    }
    // load contents to buffer (as bytes)
    zip_entry_read(zip, &buf, &bufsize);

    // unload the zip file and document.xml
    zip_entry_close(zip);
    zip_close(zip);

    // load contents as string
    this->document.load_buffer(buf, bufsize);
    // set the paragraph
    this->paragraph.set_parent(document.child("w:document").child("w:body"));

    // free the buffer
    free(buf);
}

void duckx::Document::save() const {
    // minizip only supports appending or writing to new files
    // so we must
    // - make a new file
    // - write any new files
    // - copy the old files
    // - delete old docx
    // - rename new file to old file
    // so the performance looks horrible

    // read document buffer
    xml_string_writer writer;
    this->document.print(writer);

    // open file and replace "xml" content
    std::string original_file = this->directory;
    std::string temp_file = this->directory + ".tmp";

    // create the new file
    zip_t *new_zip = zip_open(temp_file.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');

    // write out document.xml
    zip_entry_open(new_zip, "word/document.xml");

    const char *buf = writer.result.c_str();

    zip_entry_write(new_zip, buf, strlen(buf));
    zip_entry_close(new_zip);

    // open the original zip and copy all files which are not replaced by duckX
    zip_t *orig_zip = zip_open(original_file.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');

    // number of entries
    int orig_zip_entry_ct = zip_total_entries(orig_zip);

    // TODO: check if the file is empty (the file is broken)

    // loop and copy each relevant entry in the original zip
    for (int i = 0; i < orig_zip_entry_ct; i++) {

        // open entries one by one
        zip_entry_openbyindex(orig_zip, i);
        const char *name = zip_entry_name(orig_zip);

        // skip copying the original file
        if (std::string(name) != "word/document.xml") {
            // read the old content
            void *entry_buf;
            size_t entry_buf_size;
            zip_entry_read(orig_zip, &entry_buf, &entry_buf_size);

            // write into new zip
            zip_entry_open(new_zip, name);
            zip_entry_write(new_zip, entry_buf, entry_buf_size);

            zip_entry_close(new_zip);
            free(entry_buf);
        }

        // close the entry
        zip_entry_close(orig_zip);
    }

    // close both zip files
    zip_close(orig_zip);
    zip_close(new_zip);

    // remove original zip, rename new to correct name
    remove(original_file.c_str());
    rename(temp_file.c_str(), original_file.c_str());
}

// return the first paragraph
duckx::Paragraph &duckx::Document::paragraphs() {
    this->paragraph.set_parent(document.child("w:document").child("w:body"));
    return this->paragraph;
}

// return the first table in the document
duckx::Table &duckx::Document::tables() {
    this->table.set_parent(document.child("w:document").child("w:body"));
    return this->table;
}
