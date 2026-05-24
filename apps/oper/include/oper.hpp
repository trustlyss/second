#pragma once

#include <exception>
#include <string>
#include <iostream>
#include <vector>

enum class StringErrorCode {
    EMPTY_STRING,
    NULL_STRING,
    INDEX_OUT_OF_RANGE,
    MAX_LENGTH_EXCEEDED,
    INVALID_DELIMITER,
    SUBSTRING_NOT_FOUND,
    INVALID_ENCODING
};

std::string errorCodeToString(StringErrorCode code);


class StringOperationException : public std::exception {
public:
    StringOperationException(const std::string& operation,
                             const std::string& message,
                             StringErrorCode    code,
                             const std::string& input = "");

    const char* what()          const noexcept override;

    const std::string& getOperation() const;
    const std::string& getMessage()   const;
    const std::string& getInput()     const;
    StringErrorCode    getCode()      const;

    void print() const;

private:
    std::string     operation;
    std::string     message;
    std::string     input;
    StringErrorCode code;
    std::string     fullMessage;
};


class StringProcessor {
public:
    static const std::size_t MAX_LENGTH = 100;

    static std::string concatenate(const std::string& a, const std::string& b);
    static std::string toUpper(const std::string& str);
    static std::string toLower(const std::string& str);
    static char        charAt(const std::string& str, int index);
    static std::string substring(const std::string& str, int from, int to);
    static std::string replace(const std::string& str,
                               const std::string& from,
                               const std::string& to);
    static std::vector<std::string> split(const std::string& str,
                                          const std::string& delimiter);
    static std::string trim(const std::string& str);

private:
    static void checkNotEmpty(const std::string& str, const std::string& op);
    static void checkLength  (const std::string& str, const std::string& op);
};

#include <vector>