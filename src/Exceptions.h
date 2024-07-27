#pragma once
#include <exception>
#include <string>

class FatalException : public std::exception
{
public:
    explicit FatalException(const char* message) : mMessage(message), mErrorCode(0) {}
    FatalException(const char* message, int errorCode) : mMessage(message), mErrorCode(errorCode) {}
    [[nodiscard]] const char * what() const noexcept override { return mMessage; }

    [[nodiscard]] int getErrorCode() const { return mErrorCode; }
    void setErrorCode(int errorCode) { mErrorCode = errorCode; }
private:
    const char *mMessage;
    int mErrorCode;
};

class NonFatalException : public std::exception
{
public:
    explicit NonFatalException(const char* message) : mMessage(message), mErrorCode(0) {}
    NonFatalException(const char* message, int errorCode) : mMessage(message), mErrorCode(errorCode) {}
    [[nodiscard]] const char * what() const noexcept override { return mMessage; }

    [[nodiscard]] int getErrorCode() const { return mErrorCode; }
    void setErrorCode(int errorCode) { mErrorCode = errorCode; }

private:
    const char *mMessage;
    int mErrorCode;
};

