#include <cstdlib>
#include <exception>


enum class ErrorCode {
    SUCCESS = 0,
    MALLOC_ERROR = 1,
    UNEXPECTED_NULLPTR = 2,
    UNEXPECTED_CHAR = 3,
    INDEX_OUT_OF_BOUNDS = 4,
    EMPTY_ARRAY = 5,
    NEGATIVE_SIZE_DIFFERENCE = 6
};


class Exception : public std::exception
{
private:
    std::string message;
    ErrorCode code;
public:
    Exception( ErrorCode code ) : code( code ) {
        switch ( code ) {
            case ErrorCode::SUCCESS:
                this->message = "Success!";
                break;
            case ErrorCode::MALLOC_ERROR:
                this->message = "Error. Unable to allocate memory.";
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
                this->message = "Error. Size cannot negative.";
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

template <typename T>
class ResultInfo
{
public:
	static ResultInfo<T> Value(T value)             { return ResultInfo(value); }
	static ResultInfo<T> Error(const Exception& ex) { return ResultInfo(ex); }
private:
    T value;
    Exception ex;
    bool isOk;
public:
    ResultInfo( T value ) :             value( value ), ex( Exception(ErrorCode::SUCCESS) ), isOk( true ) {}
    ResultInfo( const Exception& ex ) : value{},        ex( ex ),                            isOk( false ) {}
public:
    T& getValue() { 
        if ( this->isOk ) {
            return this->value;
        } else {
            throw this->ex;
        }
    }
    Exception GetException() const {
        if (!this->isOk) {
            return this->ex;
        } else {
            throw std::logic_error("Result is ok — no exception to return.");
        }
    }
    bool IsOk() const { return this->isOk; }
public:
    template <typename V>
    ResultInfo<V> Map( V (*f)(T&)) {
        if ( this->isOk ) {
            try {
                V res = f( this->value );
                return ResultInfo<V>::Value( res );
            } catch ( const Exception& ex ) {
                return ResultInfo<V>::Error( ex );
            }
        } else {
            return ResultInfo<V>::Error( this->ex );
        }
    }
};

template <>
class ResultInfo<void> 
{
public:
    static ResultInfo<void> Value()                    { return ResultInfo(); }
    static ResultInfo<void> Error(const Exception& ex) { return ResultInfo(ex); }
private:
    Exception ex;
    bool isOk;
public:
    ResultInfo() :                      ex( Exception(ErrorCode::SUCCESS) ), isOk( true ) {}
    ResultInfo( const Exception& ex ) : ex( ex ),                            isOk( false ) {}
public:
    void getValue() {
        if ( !this->isOk ) {
            throw this->ex;
        }
    }
    Exception GetException() const {
        if (!this->isOk) {
            return this->ex;
        } else {
            throw std::logic_error("Result is ok — no exception to return.");
        }
    }
    bool IsOk() const { return this->isOk; }
public:
    template <typename V>
    ResultInfo<V> Map( V (*f)() ) {
        if ( this->isOk ) {
            try {
                V res = f();
                return ResultInfo<V>::Value( res );
            } catch ( const Exception& ex ) {
                return ResultInfo<V>::Error( ex );
            }
        } else {
            return ResultInfo<V>::Error( this->ex );
        }
    }
};