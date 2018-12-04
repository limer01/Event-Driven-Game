#ifndef READFILE_H
#define READFILE_H


#include <QString>
#include <vector>

class ReadFile {
public:
    virtual void readFile(std::string , std::vector<QString>* v) = 0;
};

#endif // READFILE_H
