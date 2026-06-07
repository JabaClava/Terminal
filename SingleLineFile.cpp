#include "SingleLineFile.h"

SingleLineFile::SingleLineFile(const std::string& name, const std::string& line) : Entry(name), content(line) {}

void SingleLineFile::display(std::ostream& os) const {
	os << content << '\n';
}

void SingleLineFile::edit(std::ostream& os) {
    os << "Current content: " << content << '\n';
    os << "Enter new content (single line): \n";
    std::string newLine;
    std::getline(std::cin, newLine);
    content = newLine;
}