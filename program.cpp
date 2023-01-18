#include <iostream>
#include <vector>

class DefaultIO {
public:
    virtual void input() = 0;
    virtual void output() = 0;
};

class StandardIO : public DefaultIO {
public:
    void input() {
        std::cout << "Input data from standard input" << std::endl;
    }

    void output() {
        std::cout << "Output data to standard output" << std::endl;
    }
};

class SocketIO : public DefaultIO {
public:
    void input() {
        std::cout << "Input data from socket" << std::endl;
    }

    void output() {
        std::cout << "Output data to socket" << std::endl;
    }
};

class Command {
public:
    virtual void execute() = 0;
};

class UploadCommand : public Command {
    DefaultIO& io;
public:
    UploadCommand(DefaultIO& io) : io(io) {}
    void execute() {
        std::cout << "Uploading unclassified csv data file" << std::endl;
        io.input();
    }
};

class SettingsCommand : public Command {
    DefaultIO& io;
public:
    SettingsCommand(DefaultIO& io) : io(io) {}
    void execute() {
        std::cout << "Setting algorithm parameters" << std::endl;
        io.input();
    }
};

class ClassifyCommand : public Command {
    DefaultIO& io;
public:
    ClassifyCommand(DefaultIO& io) : io(io) {}
    void execute() {
        std::cout << "Classifying data" << std::endl;
        io.output();
    }
};

class ResultsCommand : public Command {
    DefaultIO& io;
public:
    ResultsCommand(DefaultIO& io) : io(io) {}
    void execute() {
        std::cout << "Displaying results" << std::endl;
        io.output();
    }
};

class DownloadCommand : public Command {
    DefaultIO& io;
public:
    DownloadCommand(DefaultIO& io) : io(io) {}
    void execute() {
        std::cout << "Downloading results" << std::endl;
        io.output();
    }
};

class ExitCommand : public Command {
public:
    void execute() {
        std::cout << "Exiting program" << std::endl;
    }
};

class CLI {
    std::vector<Command*> commands;
    DefaultIO& io;
public:
    CLI(DefaultIO& io) : io(io) {
        commands.push_back(new UploadCommand(io));
        commands.push_back(new SettingsCommand(io));
        commands.push_back(new ClassifyCommand(io));
        commands.push_back(new ResultsCommand(io));
        commands.push_back(new DownloadCommand(io));
        commands.push_back(new ExitCommand());
    }

    ~CLI() {
        for (auto command: commands) {
            delete command;
        }
    }

    void start() {
        while (true) {
            std::cout << "Welcome to the KNN Classifier Server. Please choose an option:" << std::endl;
            std::cout << "1. upload an unclassified csv data file" << std::endl;
            std::cout << "2. algorithm settings" << std::endl;
            std::cout << "3. classify data" << std::endl;
            std::cout << "4. display results" << std::endl;
            std::cout << "5. download results" << std::endl;
            std::cout << "6. Exit" << std::endl;

            int choice;
            std::cin >> choice;
            if (choice == 6) {
                break;
            }
            else if (choice >= 1 && choice <= 5) {
                commands[choice - 1]->execute();
            }
            else {
                std::cout << "Invalid choice" << std::endl;
            }
        }
    }

