#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
std::unordered_map<std::string, std::string> dataMapper;
std::vector<std::string> setParserData;
void refDataset()
{
    dataMapper.insert({"htpl", "#include<stdio.h>\n"});
    dataMapper.insert({"main", "void main(){\n"});
    dataMapper.insert({"log", "printf()"});
    dataMapper.insert({"/", "}"});
    dataMapper.insert({"/log",";"});
}
void writeCode(){
    std::ofstream writeFile("output.c");
    for(int i=0;i<setParserData.size()-1;i++){
        writeFile<<setParserData[i]<<"\n";
    }
}
std::string removeFrontSpaces(std::string getData)
{
    for (int i = 0; i < getData.length(); i++)
    {
        if (getData[i] != ' ')
        {
            getData = getData.substr(i, getData.length() - i);
            break;
        }
    }
    return getData;
}
std::string stripBraces(std::string getData)
{
    return getData.substr(1, getData.find('>') - 1);
}
void printParser(){
    std::string string_const="";
    for(int i=0;i<setParserData.size();i++){
        if(setParserData[i]=="printf()"){
            string_const = setParserData[i].substr(0,7) + '"' + setParserData[i + 1] + '"' + ")" + setParserData[i + 2];
            setParserData[i] = string_const;
            setParserData.erase(std::next(setParserData.begin(),i+1),std::next(setParserData.begin(),i+3));
        }
    }
}
void Parser(std::string getData){
    getData = removeFrontSpaces(getData);
    if(getData[0]=='<'){
        if (getData[1] != '/'){
            std::string getTag = stripBraces(getData);
            if (dataMapper.find(getTag) != dataMapper.end()){
                setParserData.push_back(dataMapper.find(getTag)->second);
            }
        } else {
            if (getData.substr(2, 3) == "log")
                setParserData.push_back(dataMapper.find("/log")->second);
            else
                setParserData.push_back(dataMapper.find("/")->second);
        }
    } else {
        if (setParserData[setParserData.size() - 1] == "printf()")
            setParserData.push_back(getData);
        else
            setParserData[setParserData.size()-1]+=(" "+getData);
    }
}
int main(int argc, char const *argv[]){
    refDataset();
    std::string getSyntax;
    std::ifstream readData(argv[1]);
    while (getline(readData, getSyntax)){
        Parser(getSyntax);
    }
    printParser();
    writeCode();
}