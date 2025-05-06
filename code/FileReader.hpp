#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <vector>

struct EntityStruct
{
    int value;
    int row;
    int col;

    EntityStruct(int _val, int _row, int _col);
};

class FileReader
{
public:
    static std::vector<std::vector<int>> MapCharger(const std::string& src);

    static std::vector<EntityStruct> EntityCharger(const std::vector<std::vector<int>>& _map);

};

#endif
