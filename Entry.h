#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <vector>

class Directory;

class Entry {
	std::string name;
	std::shared_ptr<Directory> parent;
	bool hidden;
public:
	Entry(const std::string& name);
	virtual std::string getName() const;
	virtual void setName(const std::string& newName);
	virtual void hide();
	virtual void restore();
	virtual bool isHidden() const;

	virtual void display(std::ostream& os) const;
	virtual void edit(std::ostream& os);
	virtual bool isDirectory() const;
	virtual std::shared_ptr<Directory> getParent() const;
	virtual void setParent(std::shared_ptr<Directory> p);
};
