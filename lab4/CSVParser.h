#ifndef CSV_CSVPARSER_H
#define CSV_CSVPARSER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>
#include <vector>
#include <iterator>

template<std::size_t> struct Size {};

template <class Tuple, size_t Pos, typename Ch, typename Tr>
std::basic_ostream<Ch, Tr> &print_tuple(std::basic_ostream<Ch, Tr>& os, const Tuple& t, Size<Pos> ) {
    os << std::get< std::tuple_size<Tuple>::value - Pos >(t) << ", ";
    return print_tuple(os, t, Size<Pos - 1>());
}

template <typename Tuple, typename Ch, typename Tr>
std::basic_ostream<Ch, Tr> &print_tuple(std::basic_ostream<Ch, Tr>& os, const Tuple& t, Size<1> ) {
    return os << std::get<std::tuple_size<Tuple>::value - 1>(t);
}

template <typename... Args, typename Ch, typename Tr>
std::basic_ostream<Ch, Tr> &operator<< (std::basic_ostream<Ch, Tr>& os, const std::tuple<Args...> &t) {
    os << "(";
    return print_tuple(os, t, Size<sizeof...(Args)>()) << ")";
}

template <typename T>
void ReadTupleElement(std::istringstream& in, T& value) {
    in >> value;
}

template <>
void ReadTupleElement(std::istringstream& in, std::string& value) {
    value = in.str();
}

std::string GetToken(std::istringstream &line, char lineDelim, char quote, unsigned int &tokenLength) {
    std::string result;
    tokenLength = 0;
    bool IsInQuotes = false;
    while(line.good())
    {
        char c = line.get();
        ++tokenLength;
        if (!IsInQuotes && c == quote)
        {
            IsInQuotes = true;
        }
        else if (IsInQuotes && c == quote)
        {
            if (line.peek() == quote)
            {
                result += static_cast<char>(line.get());
                ++tokenLength;
            }
            else
            {
                IsInQuotes = false;
            }
        }
        else if (!IsInQuotes && c == lineDelim)
        {
            return result;
        }
        else
        {
            result += c;
        }
    }
    return result;
}

template <typename Tuple, size_t Pos>
void GetElements(std::istringstream &lineStream, Tuple &t, Size<Pos>, char lineDelim,
        char quote, unsigned int &symbolErrorNum) {
    unsigned int tokenLength;
    std::string nextToken = GetToken(lineStream, lineDelim, quote, tokenLength);
    std::istringstream tokenStream(nextToken);
    tokenStream.exceptions(std::ios::failbit | std::ios::badbit);
    ReadTupleElement(tokenStream, std::get<std::tuple_size<Tuple>::value - Pos>(t));
    symbolErrorNum += tokenLength;
    GetElements(lineStream, t, Size<Pos - 1>(), lineDelim, quote, symbolErrorNum);
}

template <typename Tuple>
void GetElements(std::istringstream &ss, Tuple &t, Size<0>, char lineDelim,
        char quote, unsigned int &symbolErrorNum) {}

template <typename...Args>
bool GetTuple(const std::string &line, char lineDelim, char quote,
        std::tuple<Args...> &tuple, unsigned int &symbolErrorNum) {
    std::istringstream lineStream(line);
    symbolErrorNum = 1;
    try {
        GetElements(lineStream, tuple, Size<sizeof...(Args)>(), lineDelim, quote, symbolErrorNum);
    }
    catch (std::ios::failure &e) {
        return false;
    }
    return true;
}

std::string GetLine(std::ifstream &file, char textDelim, char quote) {
    std::string result;
    bool IsInQuotes = false;
    while(file.good())
    {
        char c = file.get();
        if (c == '\377') {
            break;
        }
        if (!IsInQuotes && c == quote)
        {
            result += c;
            IsInQuotes = true;
        }
        else if (IsInQuotes && c == quote)
        {
            result += c;
            if (file.peek() == quote)
            {
                result += static_cast<char>(file.get());
            }
            else
            {
                IsInQuotes = false;
            }
        }
        else if (!IsInQuotes && c == textDelim)
        {
            return result;
        }
        else
        {
            result += c;
        }
    }
    return result;
}

template <typename... Args>
class CSVParser {
        std::vector<std::tuple<Args...>> tuples;
    public:
        CSVParser(std::ifstream &file, int skipLinesCount, char textDelim = '\n', char lineDelim = ',', char quote = '"') {
            std::string nextLine;
            unsigned int lineNum = 0;
            for (int i = 0; i < skipLinesCount; ++i) {
                nextLine = GetLine(file, textDelim, quote);
                ++lineNum;
            }
            while(file.good()) {
                std::tuple<Args...> nextTuple;
                nextLine = GetLine(file, textDelim, quote);
                ++lineNum;
                unsigned int symbolErrorNum;
                if (GetTuple(nextLine, lineDelim, quote, nextTuple, symbolErrorNum)) {
                    tuples.push_back(nextTuple);
                }
                else {
                    std::cout << "Parsing error: " << "line " << lineNum << ", position " << symbolErrorNum << std::endl;
                    break;
                }
            }
        }
        auto begin() {
            return tuples.begin();
        }
        auto end() {
            return tuples.end();
        }
};


#endif //CSV_CSVPARSER_H
