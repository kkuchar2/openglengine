#ifndef OPENGL_ENGINEEXCEPTION_H
#define OPENGL_ENGINEEXCEPTION_H

#include <exception>
#include <string>

struct EngineException : public std::exception
{
   std::string s;
    EngineException(std::string ss) : s(ss) {}
   ~EngineException() throw () {} // Updated
   const char* what() const throw() { return s.c_str(); }
};

#endif //OPENGL_ENGINEEXCEPTION_H
