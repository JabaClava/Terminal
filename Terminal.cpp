#include "Terminal.h"

namespace {
	std::map<std::string, CommandType> commands{ {"help", CommandType::help}, {"exit", CommandType::exit},
		{"ls", CommandType::ls}, {"cd", CommandType::cd}, {"cat", CommandType::cat},
		{"touch", CommandType::touch}, {"mkdir", CommandType::mkdir}, {"rm", CommandType::rm},
		{"restore", CommandType::restore}, {"mv", CommandType::mv}, {"edit", CommandType::edit}
	};
}

Terminal::Terminal(std::ostream& os) : stream(os) {
	root = std::make_shared<Directory>("C:");
	curr = root;
}

void Terminal::help() {
	stream << "Commands:\n"
		<< "  help            - show all commands\n"
		<< "  exit            - exit the program\n"
		<< "  ls              - list contents of current directory\n"
		<< "  cd <dir>        - change directory\n"
		<< "  cat <file>      - display file content\n"
		<< "  touch <file>    - create a file\n"
		<< "  mkdir <dir>     - create a directory\n"
		<< "  rm <name>       - delete file or directory\n"
		<< "  restore <name>  - restore file or directory\n"
		<< "  mv <old> <new>  - rename file or directory\n"
		<< "  edit <file>     - edit file content\n";
}

void Terminal::ls() {
	curr->display(stream);
}

void Terminal::cd(std::string& name) {
	if (name == ".") {
		return;
	}
	if (name == "..") {
		auto parent = curr->getParent();
		if (parent) {
			curr = parent;
		}
		else {
			stream << "At root directory\n";
		}
		return;
	}
	auto child = curr->findChild(name);
	if (child && child->isDirectory() && !child->isHidden()) {
		curr = std::dynamic_pointer_cast<Directory>(child); //Directory and Entry
	}
	else {
		stream << name << " not found\n";
	}
}

void Terminal::cat(std::string& name) {
	if (curr->isDirectory()) {
		stream << "Not a file\n";
		return;
	}
	auto child = curr->findChild(name);
	if (child && !child->isHidden()) {
		child->display(stream);
	}
	else {
		stream << name << " not found\n";
	}
}

void Terminal::touch(std::string& name) {
	if (curr->findChild(name)) {
		stream << "File already exists : " << name << '\n';
		return;
	}
	curr->addChild(std::make_shared<PostponedFile>(name));
	stream << "Created a file: " << name << '\n';
}

void Terminal::mkdir(std::string& name) {
	if (curr->findChild(name)) {
		stream << "Directory already exists : " << name << '\n';
		return;
	}
	curr->addChild(std::make_shared<Directory>(name));
	stream << "Created a directory: " << name << '\n';
}

void Terminal::rm(std::string& name) {
	auto child = curr->findChild(name);
	if (child && !child->isHidden()) {
		child->hide();
		stream << name << " is deleted\n";
	}
	else {
		stream << name << " not found\n";
	}
}

void Terminal::restore(std::string& name) {
	auto child = curr->findChild(name);
	if (child && child->isHidden()) {
		child->restore();
		stream << name << " is restored\n";
	}
	else {
		stream << name << " not found\n";
	}
}

void Terminal::mv(std::string& name, std::string& newName) {
	auto child = curr->findChild(name);
	if (child && !child->isHidden()) {
		if (curr->findChild(newName)) {
			stream << "New name already exists\n";
			return;
		}
		child->setName(newName);
		stream << "Renamed: " << name << " -> " << newName << '\n';
	}
	else {
		stream << name << " not found\n";
	}
}

void Terminal::edit(std::string& name) {
	auto child = curr->findChild(name);
	if (child && !child->isHidden()) {
		child->edit(stream);
	}
	else {
		stream << name << " not found\n";
	}
}

std::vector<std::string> Terminal::parser(std::string line) {
	std::istringstream iss(line);
	std::vector<std::string> args;
	std::string token;
	while (iss >> token) {
		args.push_back(token);
	}
	return args;
}

void Terminal::run() {
	stream << "Terminal is started. Type 'help' for commands.\n";
	std::string line;
	bool if_exit = false;
	while (true) {
		stream << '/' << curr->getName();
		std::getline(std::cin, line);
		std::vector<std::string> args = parser(line);

		if (args.empty()) {
			continue;
		}
		switch (commands[args[0]]) {
		case CommandType::help:
			help();
			break;
		case CommandType::exit:
			stream << "Work is stopped";
			if_exit = true;
			break;
		case CommandType::ls:
			ls();
			break;
		case CommandType::cd:
			if (args.size() == 1) {
				stream << "Enter name directory\n";
				break;
			}
			cd(args[1]);
			break;
		case CommandType::cat:
			if (args.size() == 1) {
				stream << "Enter name file\n";
				break;
			}
			cat(args[1]);
			break;
		case CommandType::touch:
			if (args.size() == 1) {
				stream << "Enter name file\n";
				break;
			}
			touch(args[1]);
			break;
		case CommandType::mkdir:
			if (args.size() == 1) {
				stream << "Enter name directory\n";
				break;
			}
			mkdir(args[1]);
			break;
		case CommandType::rm:
			if (args.size() == 1) {
				stream << "Enter name file\n";
				break;
			}
			rm(args[1]);
			break;
		case CommandType::restore:
			if (args.size() == 1) {
				stream << "Enter name file\n";
				break;
			}
			restore(args[1]);
			break;
		case CommandType::mv:
			if (args.size() == 1) {
				stream << "Enter name and new name file\n";
				break;
			}
			if (args.size() == 2) {
				stream << "Enter new name file\n";
				break;
			}
			mv(args[1], args[2]);
			break;
		case CommandType::edit:
			if (args.size() == 1) {
				stream << "Enter name file\n";
				break;
			}
			edit(args[1]);
			break;
		case CommandType::error:
			stream << "Incorrect command. Try again.\n";
			break;
		}

		args.clear();
		if (if_exit) {
			break;
		}
	}
}