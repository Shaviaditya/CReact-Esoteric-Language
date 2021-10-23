#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <string>
#include <time.h>
std::unordered_map<std::string, std::string> dataMapper;
std::unordered_map<std::string, std::string> variableMapper;
std::vector<std::string> setParserData;
std::vector<std::string> functionHeader;
std::vector<std::string> headers;
std::vector<std::string> var_keeper;
std::unordered_map<std::string, std::string> vector_counter;
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
            for (int j = 0; j < headers.size(); j++)
            {
                writeFile << (headers[j]) << "\n";
            }
            for (int j = 0; j < functionHeader.size(); j++)
            {
                writeFile << functionHeader[j] << "\n";
            }
            for (int j = 0; j < var_keeper.size(); j++)
            {
                writeFile << (var_keeper[j]) << "\n";
            }
        }
    }
}
std::vector<std::string> fxEval(std::string st)
{
    std::string newgetData;
    std::vector<std::string> store;
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
                    for (int i = 0; i < expressEval.size(); i++)
                    {
                        if (variableMapper.find(expressEval[i]) != variableMapper.end())
                        {
                            formatSpecifiers += variableMapper.find(expressEval[i])->second;
                            varNames += ((varNames == "") ? "" : ",") + varName;
                            check = 0;
                            break;
                        }
                    }
                    if (check == 1)
                    {
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
                {
                    std::string ins_string = getData.substr(3, getData.length() - 3) + ";";
                    setParserData.push_back(ins_string);
                }
            }
            else if (getData.find('t') != std::string::npos && getData.substr(getData.find('t'), 5) == "throw")
            {
                // std::cout<<getData.length()<<"\n";
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
            std::string stf = "";
            for (int i = 0; i < getData.length(); i++)
            {
                if (getData[i] != ' ')
                {
                    string_builder += getData[i];
                }
                else
                {
                    if (string_builder == "in" || string_builder == "ch")
                    {
                        stf += dataMapper.find(string_builder)->second + ' ';
                    }
                    else if (string_builder == "void")
                    {
                        stf += string_builder + ' ';
                    }
                    else
                    {
                        stf += string_builder;
                    }
                    string_builder = "";
                }
            }
            functionHeader.push_back(stf.substr(2, stf.length() - 2) + ";");
            stf += "{";
            setParserData.push_back(stf.substr(2, stf.length() - 2));
        }
        else if (getData[1] == '%')
        {
            if (getData.find('[') == std::string::npos)
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
            else
            {
                int c1 = 0, c2 = 0;
                getData = getData.substr(2, getData.length() - 4);
                getData = SpaceDebug(getData);
                std::string p1 = SpaceDebug(getData.substr(0, getData.find('=')));
                std::string p2 = SpaceDebug(getData.substr(getData.find('=') + 1, getData.length() - getData.find('=') - 1));
                if (p1.find('[') != std::string::npos && p1.find(']') != std::string::npos)
                {
                    std::string var_name = p1.substr(0, p1.find('['));
                    std::string val = p1.substr(p1.find('[') + 1, p1.find(']') - p1.find('[') - 1);
                    p1 = "*(" + var_name + "+" + val + ")";
                }
                if (p2.find('[') != std::string::npos && p2.find(']') != std::string::npos)
                {
                    std::string var_name2 = p2.substr(0, p2.find('['));
                    std::string val2 = p2.substr(p2.find('[') + 1, p2.find(']') - p2.find('[') - 1);
                    p2 = "*(" + var_name2 + "+" + val2 + ")";
                }
                setParserData.push_back(p1 + " = " + p2 + ";");
            }
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
            if (getData.substr(0, 3) == "<fx")
            {
                std::string ins_string = getData.substr(4, getData.length() - 5);
                ins_string = SpaceDebug(ins_string);
                ins_string = dataMapper.find(ins_string.substr(0, 2))->second + " " + ins_string.substr(3, ins_string.length() - 3);
                functionHeader.push_back(ins_string + ";");
                setParserData.push_back(ins_string + "{");
            }
            else if (getData.substr(2, 3) == "log")
            {
                setParserData.push_back(dataMapper.find("/log")->second);
            }
            else
            {
                setParserData.push_back(dataMapper.find("/")->second);
            }
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
void conditionalBuilder(std::string parse)
{
    if (parse[parse.length() - 1] != '>')
    {
        parse = parse.substr(2, parse.length() - 2);
        parse = SpaceDebug(parse);
        if (parse.substr(0, 2) == "if")
        {
            parse = parse + "{";
            setParserData.push_back(parse);
        }
        else if (parse.substr(0, 4) == "elif")
        {
            std::string sf = "else if";
            parse = sf + parse.substr(4, parse.length() - 4) + "{";
            setParserData.push_back(parse);
        }
        else
        {
            parse = "else {";
            setParserData.push_back(parse);
        }
    }
    else
    {
        std::string stf = "}";
        setParserData.push_back(stf);
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
            for (int i = 1; i < parse.length(); i++)
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
        std::string stf = "}";
        setParserData.push_back(stf);
    }
}
void memoryPlay(std::string getData)
{
    getData = getData.substr(2, getData.length() - 4);
    // std::cout<<getData<<"\n";
    getData = SpaceDebug(getData);
    if (getData.substr(0, 6) == "stream")
    {
        headers.push_back("#include<stdlib.h>");
        headers.push_back("#define predefsz 2");
        std::string _datatype = getData.substr(getData.find('(') + 1, getData.find(')') - getData.find('(') - 1);
        if (_datatype == "in")
        {
            srand(time(0));
            std::string varRect = SpaceDebug(getData.substr(getData.find(')') + 1, getData.length() - getData.find(')') - 1));
            std::string sizeDef = varRect + std::to_string(rand()).substr(0, 3);
            std::string ins_var = "c" + std::to_string(rand()).substr(0, 3);
            vector_counter.insert({varRect, ins_var});
            vector_counter.insert({ins_var, sizeDef});
            functionHeader.push_back("int " + ins_var + "= 0;");
            setParserData.push_back("int " + sizeDef + " = " + "predefsz;");
            std::string instance1 = dataMapper.find(_datatype)->second + " " + '*' + varRect + " = (int*)malloc(sizeof(int)*" + sizeDef + ");";
            setParserData.push_back(instance1);
            if (var_keeper.empty())
            {
                std::string ins_var1;
                std::ifstream readFile("./modules/memoryalloc.txt");
                while (getline(readFile, ins_var1))
                {
                    var_keeper.push_back(ins_var1);
                }
            }
        }
    }
    else
    {
        if (getData.substr(getData.find('.') + 1, 4) == "plus")
        {

            std::string ins_var = getData.substr(0, getData.find('.')) + "=" + "checkout(" + vector_counter.find(getData.substr(0, getData.find('.')))->second + ",&" + vector_counter.find(vector_counter.find(getData.substr(0, getData.find('.')))->second)->second + "," + getData.substr(0, getData.find('.')) + ");\n";
            std::string ins_var3 = "*(" + getData.substr(0, getData.find('.')) + "+" + vector_counter.find(getData.substr(0, getData.find('.')))->second + "++)=" + getData.substr(getData.find('(') + 1, getData.find(')') - getData.find('(') - 1) + ";";
            setParserData.push_back(ins_var + ins_var3);
        }
        else if (getData.substr(getData.find('.') + 1, 5) == "minus")
        {
            setParserData.push_back(vector_counter.find(getData.substr(0, getData.find('.')))->second + "--" + ';');
        }
        else if (getData.substr(getData.find('.') + 1, 4) == "show")
        {
            setParserData.push_back("show(" + getData.substr(0, getData.find('.')) + "," + vector_counter.find(getData.substr(0, getData.find('.')))->second + ");");
        }
    }
}
// int main(int argc, char const *argv[])
int main()
{
    refDataset();
    std::string getSyntax;
    // std::ifstream readData(argv[1]);
    std::ifstream readData("input.html");
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
        else if (getSyntax.substr(0, 2) == "<<")
        {
            memoryPlay(getSyntax);
        }
        else
        {
            Parser(getSyntax);
        }
    }
    for (auto it : setParserData)
    {
        std::cout << it << "\n";
    }
    printParser();
    for (auto it : setParserData)
    {
        std::cout << it << "\n\n";
    }
    writeCode();
    return 0;
}
