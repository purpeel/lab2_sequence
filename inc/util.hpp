#ifndef UTILITY_H
#define UTILITY_H

#include <cstdlib>
#include <exception>

class Exception : public std::exception
{
private:
    std::string message;
    std::exception& ex;
    void throwSelf() {
        throw this->ex;
    }
public:
    enum class ErrorCode {
        SUCCESS = 0,
        UNEXPECTED_NULLPTR = 2,
        UNEXPECTED_CHAR = 3,
        INDEX_OUT_OF_BOUNDS = 4,
        EMPTY_ARRAY = 5,
        NEGATIVE_SIZE_DIFFERENCE = 6
    };
    Exception( std::exception ex ) : {
        this->ex = ex;
        this->throwSelf();
        catch( std::bad_alloc& ex ) {
            this->message = "Error. Unable to allocate memory.";
        }

        catch( ... ) {
            this->message = "Unknown error.";
        }
    }
    Exception( ErrorCode code ) : {
        this->ex = std::exception();
        switch ( code ) {
        case ErrorCode::SUCCESS:
            this->message = "Success!";
            break;
        case ErrorCode::UNEXPECTED_NULLPTR:
            this->message = "Error. Provided data contains null-pointer.";
            break;
        case ErrorCode::UNEXPECTED_CHAR:
            this->message = "Error. Invalid input, expected digits.";
            break;
        case ErrorCode::INDEX_OUT_OF_BOUNDS:
            this->message = "Error. Index out of bounds.";
            break;
        case ErrorCode::EMPTY_ARRAY:
            this->message = "Error. Unable to delete from empty sequence.";
            break;
        case ErrorCode::NEGATIVE_SIZE_DIFFERENCE:
            this->message = "Error. Size difference cannot be negative.";
            break;
        default:
            this->message = "Unknown error.";
            break;
        }
    }
public: 
    const char* what() const noexcept override {
        return this->message.c_str();
    }
    ErrorCode getCode() const noexcept {
        return this->code;
    }
};

#endif