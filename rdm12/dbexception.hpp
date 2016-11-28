#ifndef DBEXCEPTION_HPP
#define DBEXCEPTION_HPP

// Raima generated include
#include "rdm.h"
#include "cardsdb_api.h"

#define DB_CATCH_EXCEPTION_CLAUSE \
   catch (const RDM_CPP::rdm_exception& ex) \
   { \
       std::cerr << "rdm exception caught - reason: " << ex.what() << std::endl; \
   }


#endif // DBEXCEPTION_HPP


