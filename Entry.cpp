#include "Entry.h"

Entry::Entry(const std::string& name) : name(name), parent(nullptr), hidden(false) {}

std::string Entry::getName() const {
	return name;
}

void Entry::setName(const std::string& newName) {
	name = newName;
}

void Entry::display(std::ostream& os) const {};

void Entry::edit(std::ostream& os) {
	os << "Error: cannot edit a directory\n";
}

bool Entry::isDirectory() const { 
	return false; 
}

bool Entry::isHidden() const { 
	return hidden; 
}

void Entry::hide() { 
	hidden = true; 
}

void Entry::restore() { 
	hidden = false; 
}

std::shared_ptr<Directory> Entry::getParent() const {
	return parent; 
}

void Entry::setParent(std::shared_ptr<Directory> p) {
	parent = p; 
}