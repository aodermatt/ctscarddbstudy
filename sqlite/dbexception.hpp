#ifndef DBEXCEPTION_HPP
#define DBEXCEPTION_HPP

#include "oosqlite3.hpp"
#include <iostream>

#define DB_CATCH_EXCEPTION_CLAUSE \
    catch (CppSQLite3Exception& e) \
    { \
        std::cerr << e.errorCode() << ":" << e.errorMessage() << std::endl; \
    }


#endif // DBEXCEPTION_HPP


