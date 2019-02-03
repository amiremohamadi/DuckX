<p align="center"><img src="https://github.com/amiremohamadi/DuckX/blob/master/img/logo.png" width="380"></p>

# DuckX

**DuckX** is a library for creation of Office docx files

> DuckX helps you to work with docx files quickly in C++.

## Status ##

- Documents (docx) [Word]
	- Read

## Quick Start

Here's an example of how to use duckx to read a docx file; It opens a docx file named **file.docx** and goes over paragraphs and runs and prints them:
```c++
#include <iostream>
#include "duckx.hpp"

int main() {
    Document doc("file.docx");    

    for (auto p = doc.paragraphs(); p.hasNext() ; p.next()) {
        std::cout << p.runs().text() << std::endl;
    }
}
```
* [Examples](https://github.com/amiremohamadi/DuckX/tree/master/samples)


## Requirements ##

- [libzip](https://github.com/nih-at/libzip)
- [pugixml](https://github.com/zeux/pugixml)


### Licensing

This library is available to anybody free of charge, under the terms of MIT License (see LICENSE.md).
