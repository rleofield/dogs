#ifndef DALMATINER_H
#define DALMATINER_H


#include "dog.h"

// class 'Dalmatiner', a special 'Dog', overwrites 'run' from Dog
class Dalmatiner: public Dog {

public:

   void run()const {
      std::string s( "Dalmatiner is running" );
      out( s );
   }


};

#endif // DALMATINER_H
