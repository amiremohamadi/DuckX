
DuckX
===========

Release v\ |version|

*DuckX* is a C++ library for creating and editing Microsoft Word
(.docx) files.


How to install
--------------
The instructions to install  DuckX

.. code-block:: sh 

    git clone https://github.com/amiremohamadi/DuckX.git
    cd DuckX
    mkdir build
    cd build
    cmake ..
    cmake --build .

Quickstart
--------------
How to start with the DuckX quickly

.. code-block:: cpp

    #include <iostream>
    #include <duckx/duckx.hpp>

    int main() {

        duckx::Document doc("file.docx");   
        doc.open();

        for (auto p : doc.paragraphs())
            for (auto r : p.runs())
                std::cout << r.get_text() << std::endl;

        return 0;
    }


Contact
--------------
Do you have an issue using DuckX?
Feel free to let me know on issue tracker https://github.com/amiremohamadi/duckx/issues.

Licensing
--------------
It is freely available for use under the terms of MIT.
