#pragma once
#include "Entry.h"
#include "SingleLineFile.h"
#include "MultiLineFile.h"
#include "Directory.h"

class PostponedFile : public Entry {
	std::vector<std::string> content;
public:
	PostponedFile(const std::string& name);
	virtual void display(std::ostream& os) const override;
	virtual void edit(std::ostream& os) override;
};