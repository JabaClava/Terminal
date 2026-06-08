#pragma once
#include "Entry.h"

class Directory : public Entry, 
	public std::enable_shared_from_this<Directory> {

	std::vector<std::shared_ptr<Entry>> children;

public:
	Directory(const std::string& name);
	void addChild(std::shared_ptr<Entry> child);
	void removeChild(const std::string& name);
	std::shared_ptr<Entry> findChild(const std::string& name) const;
	const std::vector<std::shared_ptr<Entry>>& getChildren() const;

	virtual bool isDirectory() const override;
	virtual void display(std::ostream& os) const override;
};
