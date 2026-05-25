#include "oper.hpp"

std::string errorCodeToString(StringErrorCode code) {
    switch (code) {
        case StringErrorCode::EMPTY_STRING:        return "EMPTY_STRING";
        case StringErrorCode::INDEX_OUT_OF_RANGE:  return "INDEX_OUT_OF_RANGE";
        case StringErrorCode::MAX_LENGTH_EXCEEDED: return "MAX_LENGTH_EXCEEDED";
        case StringErrorCode::INVALID_DELIMITER:   return "INVALID_DELIMITER";
        case StringErrorCode::SUBSTRING_NOT_FOUND: return "SUBSTRING_NOT_FOUND";
        default:                                   return "UNKNOWN";
    }
}

StringOperationException::StringOperationException(
    const std::string& operation,
    const std::string& message,
    StringErrorCode    code,
    const std::string& input)
    : operation(operation), message(message), input(input), code(code)
{
    fullMessage = "[" + errorCodeToString(code) + "] "
                + "Operation '" + operation + "' failed: "
                + message;
    if (!input.empty())
        fullMessage += " (input: \"" + input + "\")";
}

const char*        StringOperationException::what()         const noexcept { return fullMessage.c_str(); }
const std::string& StringOperationException::getOperation() const          { return operation; }
const std::string& StringOperationException::getMessage()   const          { return message; }
const std::string& StringOperationException::getInput()     const          { return input; }
StringErrorCode    StringOperationException::getCode()      const          { return code; }

void StringOperationException::print() const {
    std::cout << "+-- StringOperationException\n"
              << "|   Operation : " << operation               << "\n"
              << "|   Error     : " << errorCodeToString(code) << "\n"
              << "|   Message   : " << message                 << "\n";
    if (!input.empty())
        std::cout << "|   Input     : \"" << input << "\"\n";
    std::cout << "+--\n";
}

void StringProcessor::checkNotEmpty(const std::string& str, const std::string& op) {
    if (str.empty())
        throw StringOperationException(op, "String must not be empty",
                                       StringErrorCode::EMPTY_STRING, str);
}

void StringProcessor::checkLength(const std::string& str, const std::string& op) {
    if (str.size() > MAX_LENGTH)
        throw StringOperationException(op,
            "String exceeds maximum length of " + std::to_string(MAX_LENGTH),
            StringErrorCode::MAX_LENGTH_EXCEEDED,
            str.substr(0, 30) + "...");
}

std::string StringProcessor::concatenate(const std::string& a, const std::string& b) {
    checkNotEmpty(a, "concatenate");
    checkNotEmpty(b, "concatenate");
    std::string result = a + b;
    checkLength(result, "concatenate");
    return result;
}

std::string StringProcessor::toUpper(const std::string& str) {
    checkNotEmpty(str, "toUpper");
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return result;
}

std::string StringProcessor::toLower(const std::string& str) {
    checkNotEmpty(str, "toLower");
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

char StringProcessor::charAt(const std::string& str, int index) {
    checkNotEmpty(str, "charAt");
    if (index < 0 || index >= (int)str.size())
        throw StringOperationException("charAt",
            "Index " + std::to_string(index) +
            " is out of range for string of length " + std::to_string(str.size()),
            StringErrorCode::INDEX_OUT_OF_RANGE, str);
    return str[index];
}

std::string StringProcessor::substring(const std::string& str, int from, int to) {
    checkNotEmpty(str, "substring");
    if (from < 0 || to > (int)str.size() || from > to)
        throw StringOperationException("substring",
            "Range [" + std::to_string(from) + ", " + std::to_string(to) +
            "] is invalid for string of length " + std::to_string(str.size()),
            StringErrorCode::INDEX_OUT_OF_RANGE, str);
    return str.substr(from, to - from);
}

std::string StringProcessor::replace(const std::string& str,
                                     const std::string& from,
                                     const std::string& to) {
    checkNotEmpty(str,  "replace");
    checkNotEmpty(from, "replace");
    auto pos = str.find(from);
    if (pos == std::string::npos)
        throw StringOperationException("replace",
            "Substring \"" + from + "\" not found",
            StringErrorCode::SUBSTRING_NOT_FOUND, str);
    std::string result = str;
    result.replace(pos, from.size(), to);
    return result;
}

std::vector<std::string> StringProcessor::split(const std::string& str,
                                                  const std::string& delimiter) {
    checkNotEmpty(str, "split");
    if (delimiter.empty())
        throw StringOperationException("split",
            "Delimiter must not be empty",
            StringErrorCode::INVALID_DELIMITER, str);
    std::vector<std::string> tokens;
    std::size_t start = 0, pos;
    while ((pos = str.find(delimiter, start)) != std::string::npos) {
        tokens.push_back(str.substr(start, pos - start));
        start = pos + delimiter.size();
    }
    tokens.push_back(str.substr(start));
    return tokens;
}

std::string StringProcessor::trim(const std::string& str) {
    checkNotEmpty(str, "trim");
    auto start = std::find_if_not(str.begin(), str.end(),
                                  [](unsigned char c){ return std::isspace(c); });
    auto end   = std::find_if_not(str.rbegin(), str.rend(),
                                  [](unsigned char c){ return std::isspace(c); }).base();
    if (start >= end)
        throw StringOperationException("trim",
            "String contains only whitespace",
            StringErrorCode::EMPTY_STRING, str);
    return std::string(start, end);
}

static void section(const std::string& title) {
    std::cout << "\n=== " << title << " ===\n";
}

static void tryOp(const std::string& label, void(*fn)()) {
    std::cout << "\n[TEST] " << label << "\n";
    try {
        fn();
    } catch (const StringOperationException& e) {
        e.print();
    }
}

int main() {
    section("Successful operations");

    tryOp("concatenate(\"Hello\", \" World\")", [] {
        auto r = StringProcessor::concatenate("Hello", " World");
        std::cout << "Result: \"" << r << "\"\n";
    });

    tryOp("toUpper(\"hello world\")", [] {
        auto r = StringProcessor::toUpper("hello world");
        std::cout << "Result: \"" << r << "\"\n";
    });

    tryOp("toLower(\"HELLO WORLD\")", [] {
        auto r = StringProcessor::toLower("HELLO WORLD");
        std::cout << "Result: \"" << r << "\"\n";
    });

    tryOp("charAt(\"Hello\", 1)", [] {
        char c = StringProcessor::charAt("Hello", 1);
        std::cout << "Result: '" << c << "'\n";
    });

    tryOp("substring(\"Hello World\", 0, 5)", [] {
        auto r = StringProcessor::substring("Hello World", 0, 5);
        std::cout << "Result: \"" << r << "\"\n";
    });

    tryOp("replace(\"Hello World\", \"World\", \"C++\")", [] {
        auto r = StringProcessor::replace("Hello World", "World", "C++");
        std::cout << "Result: \"" << r << "\"\n";
    });

    tryOp("split(\"a,b,c,d\", \",\")", [] {
        auto tokens = StringProcessor::split("a,b,c,d", ",");
        std::cout << "Result: [";
        for (std::size_t i = 0; i < tokens.size(); ++i)
            std::cout << "\"" << tokens[i] << "\"" << (i+1<tokens.size() ? ", " : "");
        std::cout << "]\n";
    });

    tryOp("trim(\"  hello  \")", [] {
        auto r = StringProcessor::trim("  hello  ");
        std::cout << "Result: \"" << r << "\"\n";
    });

    section("Error cases");

    tryOp("concatenate(\"\", \"World\") -- EMPTY_STRING", [] {
        StringProcessor::concatenate("", "World");
    });

    tryOp("concatenate(60xA, 60xB) -- MAX_LENGTH_EXCEEDED", [] {
        StringProcessor::concatenate(std::string(60, 'A'), std::string(60, 'B'));
    });

    tryOp("charAt(\"Hi\", 99) -- INDEX_OUT_OF_RANGE", [] {
        StringProcessor::charAt("Hi", 99);
    });

    tryOp("charAt(\"Hi\", -1) -- INDEX_OUT_OF_RANGE", [] {
        StringProcessor::charAt("Hi", -1);
    });

    tryOp("substring(\"Hello\", 3, 1) -- INDEX_OUT_OF_RANGE", [] {
        StringProcessor::substring("Hello", 3, 1);
    });

    tryOp("replace(\"Hello\", \"XYZ\", \"A\") -- SUBSTRING_NOT_FOUND", [] {
        StringProcessor::replace("Hello", "XYZ", "A");
    });

    tryOp("split(\"Hello\", \"\") -- INVALID_DELIMITER", [] {
        StringProcessor::split("Hello", "");
    });

    tryOp("trim(\"   \") -- EMPTY_STRING", [] {
        StringProcessor::trim("   ");
    });

    tryOp("toUpper(\"\") -- EMPTY_STRING", [] {
        StringProcessor::toUpper("");
    });

    return 0;
}