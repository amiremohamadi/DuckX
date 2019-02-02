/*
 * Under MIT license
 * Author: Amir Mohamadi (@amiremohamadi)
 * This file read contents from docx file without any changes!

 * The purpose is to pass contents to the analyzer and separate file handling
 * from the analyzer.
*/

#ifndef HANDLE_H
#define HANDLE_H

#include <zip.h>

class Handle {
private:
    char *content;

public:
    Handle(const char *);
    char *getContent();
};

#endif