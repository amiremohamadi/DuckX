/*
 * Under MIT license
 * Author: Amir Mohamadi (@amiremohamadi)
 * This file read contents from docx file without any changes!

 * The purpose is to pass contents to the analyzer and separate file handling
 * from the analyzer.
*/

#include "handle.hpp"

Handle::Handle(const char *directory) {
    // Open the docx file (it's like a zip file!)
    int err = 0;
    zip *z = zip_open(directory, 0, &err);

    // This file contain contents
    // TODO: this variable must find the path from a rel file
    const char *name = "word/document.xml";
    struct zip_stat z_st;
    zip_stat_init(&z_st);
    zip_stat(z, name, 0, &z_st);
    

    char *contents = new char[z_st.size];

    // Try to open xml file
    zip_file *f;
    if ((f=zip_fopen(z, name, 0)) == NULL) {
        fprintf(stderr, "Error! Couldn't open the file:(\n");
        return;
    }

    // Read contents from the file
    zip_fread(f, contents, z_st.size);
    zip_fclose(f);
    zip_close(z);

    this->content = contents;
}

char *Handle::getContent() {
    return this->content;
}