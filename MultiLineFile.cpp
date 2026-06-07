#include "MultiLineFile.h"

MultiLineFile::MultiLineFile(const std::string& name, const std::vector<std::string>& lines) : Entry(name), content(lines) {}

void MultiLineFile::display(std::ostream& os) const {
	for (const auto& line : content) {
		os << line << '\n';
	}
}

void MultiLineFile::edit(std::ostream& os) {
	os << "Current content: \n";
	display(os);
	os << "Enter new content (empty line to finish): \n";
	content.clear();
	std::string newLine;
	while (std::getline(std::cin, newLine)) {
		if (newLine.empty()) break;
		content.push_back(newLine);
	}
}
