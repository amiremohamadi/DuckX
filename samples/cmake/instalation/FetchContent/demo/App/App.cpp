#include <iostream>
#include <duckx.hpp>

int main(){
    try
    {
        duckx::Document doc("../../../../my_test.dock");
        doc.open();
        //for (auto p : doc.paragraphs())
            //for (auto r : p.runs())
                //std::cout << r.get_text() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}