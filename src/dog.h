#ifndef DOG_H
#define DOG_H

#include <string>

#include "animal.h"

// class Dog implements 'run'
class Dog: public Animal {

public:
   void out( std::string s )const {
      std::cout << s << std::endl;
   }

   void run()const {
      std::string s( "Dog is running" );
      out( s );
   }


};

#endif // DOG_H
