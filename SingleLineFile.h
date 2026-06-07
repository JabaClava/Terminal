#pragma once
#include "Entry.h"

class SingleLineFile : public Entry {
	std::string content;
public:
	SingleLineFile(const std::string& name, const std::string& line);
	virtual void display(std::ostream& os) const override;
	virtual void edit(std::ostream& os) override;
};
