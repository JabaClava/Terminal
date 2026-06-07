#pragma once
#include "PostponedFile.h"
#include <sstream>
#include <map>

enum class CommandType {
	error, help, exit, ls, cd, cat, touch, mkdir, rm, restore, mv, edit
};

class Terminal {
	std::ostream& stream;
	std::shared_ptr<Directory> root;
	std::shared_ptr<Directory> curr;
	void help();
	void ls();
	void cd(std::string& name);
	void cat(std::string& name);
	void touch(std::string& name);
	void mkdir(std::string& name);
	void rm(std::string& name);
	void restore(std::string& name);
	void mv(std::string& name, std::string& newName);
	void edit(std::string& name);
	std::vector<std::string> parser(std::string line);
public:
	Terminal(std::ostream& os);
	void run();
};
