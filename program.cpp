#include <iostream>
#include <vector>
#include <string>
#include<iostream>
#include "string.h"
#include <fstream>
#include "ReadDataSet.h"



using namespace std;
class DefaultIO {
public:
    virtual string input() = 0;
    virtual void input(float* f) = 0;
    virtual void input(string data) = 0;
    virtual void output(string data) = 0;

    void readAndFile(string fileName){
        ofstream out(fileName);
        string s = "";
        while((s = input()) != "done"){
            out<<s<<endl;
        }
        out.close();
    }


};

class StandardIO : public DefaultIO {
public:
    void input(string data) {
        std::cin >> data;
    }

    void output(string data) {
        std::cout << data << std::endl;
    }
};

class SocketIO : public DefaultIO {
public:
    void input(std::string &data) {
        // code for reading data from socket
    }

    void output(std::string &data) {
        // code for sending data to socket
    }
};


struct CurrentState{
    int k;
    string distMetric;
    vector<vector<string>> fileContent; //read file
    //separate data to vector -> label
    map<vector<double>, string> mappedData = classified.createMapOfData(fileContent);

    CurrentState(){
        k = 5;
        distMetric = "AUC";
    }
};






class Command {

protected:
    DefaultIO* m_dio;
public:
    const string m_description;
    Command(DefaultIO* dio, const string description): m_dio(dio), m_description(description){}
    virtual void execute(CurrentState* CurrentState) = 0;
    virtual ~Command(){}
};

class UploadCommand : public Command {
public:
    UploadCommand(DefaultIO* dio) : Command(dio, "upload an unclassified csv data file") {}
    virtual void execute(CurrentState* CurrentState) {
        string file_path;

        m_dio -> output("Please upload your local train CSV file.\n");
        m_dio -> input(file_path);
        m_dio->output("Upload complete.\n");

        m_dio -> output("Please upload your local train CSV file.\n");
        m_dio -> input(file_path);
        m_dio->output("Upload complete.\n");
    }
};

class SettingsCommand : public Command {
    DefaultIO* dio;
public:
    SettingsCommand(DefaultIO* dio) : Command(dio, "algorithm settings") {}
    void execute(CurrentState* CurrentState) {
        // NEED TO CREATE STRUCT OF CURRENT STATE OF THE ALGORITHM
        int k = CurrentState->k;
        string dist = CurrentState->distMetric;
        m_dio ->output("The current KNN parameters are: K = " + to_string(k) + ", distance metric = " + dist);
        string newParameters;
        m_dio ->input(newParameters);//NEED TO CHECK VALIDATION. IF "ENTER", DON'T DO ANYTHING
        CurrentState->k = 5;
        CurrentState ->distMetric = "";

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
}

