#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <string>
std::unordered_map<std::string, std::string> dataMapper;
std::unordered_map<std::string, std::string> variableMapper;
std::vector<std::string> setParserData;
std::vector<std::string> functionHeader;
void refDataset()
{
    dataMapper.insert({"htpl", "#include<stdio.h>\n"});
    dataMapper.insert({"main", "void main(){\n"});
    dataMapper.insert({"log", "printf()"});
    dataMapper.insert({"/log", ";"});
    dataMapper.insert({"/", "}"});
    dataMapper.insert({"in", "int"});
    dataMapper.insert({"ch", "char"});
    dataMapper.insert({"int", "%d"});
    dataMapper.insert({"char", "%c"});
    dataMapper.insert({"take", "scanf()"});
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
void writeCode()
{
    std::ofstream writeFile("output.c");
    for (int i = 0; i < setParserData.size() - 1; i++)
    {
        writeFile << setParserData[i] << "\n";
        if (i == 0)
        {
            for (int k = 0; k < functionHeader.size(); k++)
            {
                writeFile << functionHeader[k] << "\n";
            }
        }
    }
}
std::vector<std::string> fxEval(std::string st)
{
    std::vector<std::string> store;
    std::string newgetData = "";
    for (int i = 0; i < st.length(); i++)
    {
        if (st[i] == '+' || st[i] == '-' || st[i] == '*' || st[i] == '/' || st[i] == '%' || st[i] == '^')
        {
            newgetData += ' ';
            newgetData += st[i];
            newgetData += ' ';
        }
        else
        {
            newgetData += st[i];
        }
    }
    newgetData += ' ';
    std::string helper_st = "";
    for (int i = 0; i < newgetData.length(); i++)
    {
        if (newgetData[i] != ' ')
        {
            helper_st += newgetData[i];
        }
        else
        {
            store.push_back(helper_st);
            helper_st = "";
        }
    }
    return store;
}
void printParser()
{
    std::string string_const = "";
    for (int i = 0; i < setParserData.size(); i++)
    {
        if (setParserData[i] == "printf()")
        {
            int pos;
            std::string formatSpecifiers = "", varNames = "", varName = "";
            std::vector<std::string> expressEval;
            for (int j = 0; j < setParserData[i + 1].size(); j++)
            {
                if (setParserData[i + 1].substr(j, 2) == "${")
                {
                    pos = setParserData[i + 1].substr(j).find('}') + j;
                    varName = setParserData[i + 1].substr(j + 2, pos - (j + 2));
                    expressEval = fxEval(varName);
                    int check = 1;
                    for (int k = 0; k < expressEval.size(); i++)
                    {
                        if (variableMapper.find(expressEval[k]) != variableMapper.end())
                        {
                            formatSpecifiers += variableMapper.find(expressEval[k])->second;
                            varNames += ((varNames == "") ? "" : ",") + varName;
                            check = 0;
                            break;
                        }
                    }
                    if (check == 1)
                    {
                        // Parses anything to string
                        formatSpecifiers += setParserData[i + 1].substr(j, pos - j + 1);
                    }
                    j = pos;
                }
                else
                {
                    formatSpecifiers += setParserData[i + 1][j];
                }
            }
            string_const = setParserData[i].substr(0, 7) + '"' + formatSpecifiers + '"' + ((varNames == "") ? "" : ",") + varNames + ")" + setParserData[i + 2];
            setParserData[i] = string_const;
            setParserData.erase(std::next(setParserData.begin(), i + 1), std::next(setParserData.begin(), i + 3));
        }
        else if (setParserData[i] == "scanf()")
        {
            setParserData[i + 1] += " ";

            std::string formatSpecifiers = "", varNames = "", varName = "";
            for (int j = 0; j < setParserData[i + 1].size(); j++)
            {
                if (setParserData[i + 1][j] != ' ')
                {
                    varName += setParserData[i + 1][j];
                }
                else
                {
                    formatSpecifiers += variableMapper.find(varName)->second + " ";
                    varName = "&" + varName;
                    varNames += ((varNames == "") ? "" : ",") + varName;
                    varName = "";
                }
            }
            string_const = setParserData[i].substr(0, 6) + '"' + formatSpecifiers.substr(0, formatSpecifiers.length() - 1) + '"' + "," + varNames + ')' + ';';
            setParserData[i] = string_const;
            setParserData.erase((setParserData.begin() + i + 1));
        }
    }
}
// Modifying Space Removal Approach
std::string SpaceDebug(std::string getData)
{
    // A 2-pointer approach to remove spaces from both ends inside a tag.
    long long int ptr1 = 0, ptr2 = getData.length() - 1;
    while (getData[ptr1] == ' ' || getData[ptr2] == ' ')
    {
        if (getData[ptr1] == ' ')
            ptr1++;
        if (getData[ptr2] == ' ')
            ptr2--;
    }
    return getData.substr(ptr1, ptr2 - ptr1 + 1);
}
// Getting the arrangement of symbols like '=' or ',' so as to put them in a mapper corectly
std::string arrangeDebugger(std::string getData)
{
    std::string newGetData = "";
    for (int i = 0; i < getData.length(); i++)
    {
        if (getData[i] == '=' || getData[i] == ',')
        {
            newGetData += ' ';
            newGetData += getData[i];
            newGetData += ' ';
        }
        else
        {
            newGetData += getData[i];
        }
    }
    return newGetData;
}
/* A vector based lexer that takes in the type of variable and its name in a map by lexing the whole string in parts*/
void IOparser(std::string getData)
{
    getData = arrangeDebugger(getData);
    std::vector<std::string> tokenContainer;
    std::string ins_string = "";
    for (int i = 0; i < getData.length(); i++)
    {
        if (getData[i] != ' ')
        {
            ins_string += getData[i];
        }
        else
        {
            if (ins_string.length() != 0)
            {
                tokenContainer.push_back(ins_string);
                ins_string = "";
            }
        }
    }
    for (int i = 1; i < tokenContainer.size(); i++)
    {
        if (tokenContainer[i] == "=" || tokenContainer[i] == ",")
        {
            variableMapper.insert({tokenContainer[i - 1], dataMapper.find((dataMapper.find(tokenContainer[0])->second))->second});
        }
    }
}
void Parser(std::string getData)
{
    getData = SpaceDebug(getData);
    if (getData[0] == '<')
    {
        if (getData[getData.length() - 1] == '>' && getData[getData.length() - 2] == '/')
        {
            if (getData.find('f') != std::string::npos && getData[getData.find('f') + 1] == 'x')
            {
                getData = getData.substr(1, getData.length() - 3);
                getData = SpaceDebug(getData);
                std::string ins_string = getData.substr(3, getData.length() - 3) + ";";
                setParserData.push_back(ins_string);
            }
            else if (getData.find('t') != std::string::npos && getData.substr(getData.find('t'), 5) == "throw")
            {
                getData = getData.substr(1, getData.length() - 3);
                getData = SpaceDebug(getData);
                std::string ins_string = "return " + getData.substr(6, getData.length() - 6) + ";";
                setParserData.push_back(ins_string);
            }
            else if (getData[getData.length() - 3] == '/')
            {
                getData = getData.substr(1, getData.length() - 4);
                getData = SpaceDebug(getData) + " ";
                std::vector<std::string> tmp;
                std::string stf = "";

                for (int i = 0; i < getData.length(); i++)
                {
                    if (getData[i] != ' ' && getData[i] != ',')
                    {
                        stf = stf + getData[i];
                    }
                    else
                    {
                        if (stf.length() != 0)
                            tmp.push_back(stf);
                        stf = "";
                    }
                }
                if (tmp[0] == "take")
                {
                    std::string tmpStr = "";
                    setParserData.push_back(dataMapper.find(tmp[0])->second);
                    for (int it = 1; it < tmp.size(); it++)
                    {
                        tmpStr += ((tmpStr == "") ? "" : " ") + tmp[it];
                    }
                    setParserData.push_back(tmpStr);
                }
            }
            else
            {
                /*This defines that we are only working with statements that have a self-closing tag to work with
                    Examples : <in val = 1/> or <in var1 = 3, var2 = 4/>
                */
                getData = getData.substr(1, getData.length() - 3);
                getData = SpaceDebug(getData);
                setParserData.push_back(dataMapper.find(getData.substr(0, 2))->second + getData.substr(2, getData.length() - 2) + ";");
                IOparser(getData + ",");
            }
        }
        else if (getData.find('f') != std::string::npos && getData[getData.find('f') + 1] == 'x')
        {
            getData = getData.substr(1, getData.length() - 2);
            getData = SpaceDebug(getData);
            std::string string_builder = "";
            for (int i = 0; i < getData.length(); i++)
            {
                if (getData[i] == '(' || getData[i] == ')' || getData[i] == ',')
                {
                    string_builder = string_builder + ' ' + getData[i] + ' ';
                }
                else
                {
                    string_builder += getData[i];
                }
            }
            getData = string_builder;
            string_builder = "";
            std::string stf="";
            for(int i=0;i<getData.length();i++){
                if(getData[i]!=' '){
                    string_builder+=getData[i];
                } else {
                    if(string_builder=="in" || string_builder=="ch"){
                        stf+=dataMapper.find(string_builder)->second + ' ';
                    } else if(string_builder=="void"){
                        stf+=string_builder+' ';
                    } else {
                        stf+=string_builder;
                    }
                    string_builder="";
                }
            }
            functionHeader.push_back(stf.substr(2,stf.length()-2)+";");
            stf += "{";
            setParserData.push_back(stf.substr(2,stf.length()-2));
        }
        else if (getData[1] == '%')
        {

            std::vector<std::string> tmp;
            std::string stf = "";
            for (int i = 2; i < getData.length() - 1; i++)
            {
                if (getData[i] != '%')
                {
                    stf = stf + getData[i];
                }
                else
                {
                    break;
                }
            }
            stf = stf + ';';
            setParserData.push_back(stf);
        }
        else if (getData[1] != '/')
        {
            std::string getTag = stripBraces(getData);
            getTag = SpaceDebug(getTag);
            if (dataMapper.find(getTag) != dataMapper.end())
            {
                if (getTag == "log" && getData.substr(getData.length() - 5, 4) == "/log")
                {
                    setParserData.push_back(dataMapper.find(getTag)->second);
                    setParserData.push_back(getData.substr(getData.find('>') + 1, getData.substr(getData.find('>') + 1, getData.length() - (getData.find('>') + 1)).find('<')));
                    setParserData.push_back(";");
                }
                else
                {
                    setParserData.push_back(dataMapper.find(getTag)->second);
                }
            }
        }
        else
        {
            if (getData.substr(2, 3) == "log")
                setParserData.push_back(dataMapper.find("/log")->second);
            else
                setParserData.push_back(dataMapper.find("/")->second);
        }
    }
    else
    {
        if (setParserData[setParserData.size() - 1] == "printf()")
            setParserData.push_back(getData);
        else
            setParserData[setParserData.size() - 1] += (" " + getData);
    }
}

std::string addSpaces(std::string stf, int freq)
{
    for (int i = 0; i < freq; i++)
    {
        stf = "\t" + stf;
    }
    return stf;
}
void conditionalBuilder(std::string parse)
{
    if (parse[parse.length() - 1] != '>')
    {
        parse = parse.substr(2, parse.length() - 2);
        parse = SpaceDebug(parse);
        if (parse.substr(0.4) == "elif")
        {
            std::string sf = "else if";
            parse = sf + parse.substr(4, parse.length() - 4) + "{";
            setParserData.push_back(parse);
        }
        else
        {
            setParserData.push_back(parse + "{");
        }
    }
    else
    {
        setParserData.push_back("}");
    }
}
void iteratorBuilders(std::string parse)
{
    if (parse[parse.length() - 1] != '>')
    {
        parse = parse.substr(2, parse.length() - 2);
        parse = SpaceDebug(parse);
        if (parse[0] == 'f')
        {
            for (int i = 0; i < parse.length(); i++)
            {
                if (parse[i] == ',')
                {
                    parse[i] = ';';
                }
            }
            parse = "for" + parse.substr(1, parse.length() - 1) + "{";
            setParserData.push_back(parse);
        }
        else if (parse[0] == 'w')
        {
            parse = "while" + parse.substr(1, parse.length() - 1) + "{";
            setParserData.push_back(parse);
        }
    }
    else
    {
        setParserData.push_back("}");
    }
}
int main(int argc, char const *argv[])
// int main()
{
    refDataset();
    std::string getSyntax;
    std::ifstream readData(argv[1]);
    // std::ifstream readData("input.html");
    while (getline(readData, getSyntax))
    {
        getSyntax = SpaceDebug(getSyntax);
        if (getSyntax.substr(0, 2) == "<?" || getSyntax.substr(getSyntax.length() - 2, 2) == "?>")
        {
            conditionalBuilder(getSyntax);
        }
        else if (getSyntax.substr(0, 2) == "<#" || getSyntax.substr(getSyntax.length() - 2, 2) == "#>")
        {
            iteratorBuilders(getSyntax);
        }
        else
        {
            Parser(getSyntax);
        }
    }
    printParser();
    writeCode();
    return 0;
}
