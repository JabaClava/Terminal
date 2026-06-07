#pragma once
#include "Entry.h"

class MultiLineFile : public Entry {
	std::vector<std::string> content;
public:
	MultiLineFile(const std::string& name, const std::vector<std::string>& lines);
	virtual void display(std::ostream& os) const override;
	virtual void edit(std::ostream& os) override;
};
