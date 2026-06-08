#include "Directory.h"
#include <algorithm>

Directory::Directory(const std::string& name) : Entry(name) {}
bool Directory::isDirectory() const {
	return true;
}
void Directory::display(std::ostream& os) const {
    for (auto child : children) {
        if (!child->isHidden()) {
            if (child->isDirectory()) {
                os << '-' << child->getName() << '\n';
            }
            else {
                os << child->getName() << '\n';
            }
        }
    }
}
void Directory::addChild(std::shared_ptr<Entry> child) {
    child->setParent(shared_from_this());
    children.push_back(child);
}
void Directory::removeChild(const std::string& name) {
    auto it = std::find(children.begin(), children.end(), findChild(name));
    if (it != children.end()) {
        children.erase(it);
    }
}
std::shared_ptr<Entry> Directory::findChild(const std::string& name) const {
    for (auto child : children) {
        if (child->getName() == name) {
            return child;
        }
    }
    return nullptr;
}

const std::vector<std::shared_ptr<Entry>>& Directory::getChildren() const {
    return children;
}