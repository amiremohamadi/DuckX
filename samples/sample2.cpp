#include <iostream>
#include "duckx.hpp"
using namespace std;

int main() {
	duckx::Document doc("my_test.docx");
	doc.open();

	for (auto p = doc.paragraphs(); p.has_next(); p.next()) {
		for (auto r = p.runs(); r.has_next(); r.next()) {
			cout << r.get_text() << endl;
		}
	}

	duckx::Paragraph p =
		doc.paragraphs().append("You can insert text in ");
	p.add_run("italic, ", duckx::italic);
	p.add_run("bold, ", duckx::bold);
	p.add_run("underline, ", duckx::underline);
	p.add_run("emphasis, ", duckx::emphasis);
	p.add_run("superscript", duckx::superscript);
	p.add_run("strikethrough, ", duckx::strikethrough);
	p.add_run("doublestrikethrough", duckx::doublestrikethrough);
	p.add_run("relief", duckx::relief);
	p.add_run("intaglio", duckx::intaglio);
	p.add_run("hide", duckx::hide);
	p.add_run("hollow", duckx::hollow);
	p.add_run("allcaps", duckx::allcaps);
	p.add_run(" or ");
	p.add_run("subscript, ", duckx::subscript);
	p.add_run("small caps, ", duckx::smallcaps);
	p.add_run("and shadows, ", duckx::shadow);
	p.add_run("and of course ");
	p.add_run("combine them.", duckx::bold | duckx::italic | duckx::underline |
		duckx::smallcaps);

	//     if (p.has_next())
	//     {
	//         p = p.next();
	//     }
	//     p.add_run("and of course ");
	//     p.add_run("combine them.", duckx::bold | duckx::italic | duckx::underline |
	//         duckx::smallcaps);

	//     for (auto t = doc.tables(); t.has_next(); t.next())
	//     {
	//         auto row = t.rows();
	//         for (int i = 0; i < 6; i++)
	//         {
	//             row = row.add();
	//             int cN = 0;
	//             for (auto cell = row.cells(); cell.has_next(); cell.next())
	//             {
	//                 char szT[32];
	//                 sprintf(szT, "r%d,c%d", i, cN);
	//                 auto p = cell.paragraphs().set_text(szT);
	//                 cN++;
	//             }
	//         }
	//     }
	//     auto t = doc.tables().add();
	//     auto row = t.rows();
	//     for (int i = 0; i < 6; i++)
	//     {
	//         row = row.add();
	//         auto cel = row.cells();
	//         for (int j = 0; j < 4; j++)
	//         {
	//             cel = cel.add();
	//             char szT[32];
	//             sprintf(szT, "r%d,c%d", i, j);
	//             cel.paragraphs().set_text(szT);
	//         }
	//     }
	auto t = doc.tables();
	t.resize(3, 2);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			char szT[32];
			sprintf(szT, "r%d,c%d", i, j);
			t.set_text(i, j, szT);
		}
	}
	//     doc.clean();
	doc.save();

	return 0;
}
