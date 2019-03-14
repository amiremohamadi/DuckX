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
#include <string>

class Handle {
private:
    char *content;
    std::string directory;

public:
    Handle(std::string);

    char *getContent();
    void replaceFile(std::string);
};

#endif