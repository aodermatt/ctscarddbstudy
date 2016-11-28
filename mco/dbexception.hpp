#ifndef DBEXCEPTION_HPP
#define DBEXCEPTION_HPP

// I don't know if McObject (mco) throws an exceptions or not 

#define DB_CATCH_EXCEPTION_CLAUSE \
   catch (const char * ex) \
   { \
       std::cerr << "rdm exception caught - reason: " << ex << std::endl; \
   }


#endif // DBEXCEPTION_HPP


