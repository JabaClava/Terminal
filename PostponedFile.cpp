#include "PostponedFile.h"

PostponedFile::PostponedFile(const std::string& name) : Entry(name) {}

void PostponedFile::display(std::ostream& os) const {
	os << '\n';
}

void PostponedFile::edit(std::ostream& os) {
	os << "Enter content (empty line to finish): \n";
	std::string newLine;
	while (std::getline(std::cin, newLine)) {
		if (newLine.empty()) break;
		content.push_back(newLine);
	}

	if (content.empty()) {
		os << "No content provided, file remains empty.\n";
		return;
	}

	if (content.size() > 1) {
		auto file = std::make_shared<MultiLineFile>(getName(), content);
		auto parent = getParent();
		if (parent) {
			parent->removeChild(getName());
			parent->addChild(file);
		}
	}
	else {
		auto file = std::make_shared<SingleLineFile>(getName(), content[0]);
		auto parent = getParent();
		if (parent) {
			parent->removeChild(getName());
			parent->addChild(file);
		}
	}
}
