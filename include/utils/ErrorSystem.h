#pragma once
#include <exception>
#include <iostream>

#define THROW_EXCEPTION(Error) throw AppException(Error, #Error);
#define INIT_ERROR 0 
#define CREATE_WIN_ERROR 1
#define GLAD_ERROR 2
#define FILE_NOT_FOUND_ERROR 3
#define EMPTY_FILE_ERROR 4
#define SHADER_ERROR 5

class AppException : public std::exception
{
public:
    AppException(const int& ErrorCode, const char* ErrorType)
    {
        std::cout << "Error " << ErrorCode << " : " << ErrorType << std::endl;
    }
};