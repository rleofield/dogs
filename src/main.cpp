/* --------------------------------------------------------------------------
    Copyright 2012 by Richard Albrecht
    richard.albrecht@rleofield.de

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ------------------------------------------------------------------------------
*/

#include <iostream>
#include <string>
#include <typeinfo>

#include "dog.h"
#include "animal.h"
#include "dalmatiner.h"
using namespace std;

/*
examples for virtual functions
in
animal.h
dog.h
dalmatiner.h

*/


namespace{
   void out( string s ) {
      cout << s << endl;
   }

}






// functions, using pointers of Dog, Animal , ...
void useAnimal( Animal const& animal ) {
   string s = string( "in useAnimal, Type: " ) + typeid( animal ).name() ;
   out( s );

   // output depends from type of 't' instance
   animal.run();
}

void useDog( Dog const& dog ) {
   string s = std::string( "in useDog By Reference,  Type: " ) + typeid( dog ).name() ;
   out( s );

   // output depends from type of 't' instance
   dog.run();
}
void useDogByValue( Dog byValueDog ) {
   string s = std::string( "in useDog by Value,  Type: " ) + typeid( byValueDog ).name() ;
   out( s );

   // output is really from 'Dog'
   byValueDog.run();
}
void useDalmatiner( Dalmatiner const& dalmatiner ) {
   string s = std::string( "in useDalmatiner, Type: " ) + typeid( dalmatiner ).name();
   out( s );

   // output is a 'Dalmatiner'
   dalmatiner.run();
}



int main() {

   // create one instance and get the pointer to base class
   Dalmatiner dalmatinerInstance;
   Animal& animal = dalmatinerInstance;
   Dog&  dog  = dalmatinerInstance;

   out( "" );
   useAnimal( animal ); // calls Dalmatiner
   //useDog(animal); // compiler error
   //useDalmatiner(animal); // compiler error

   out( "use the 'Dog' by value" );
   useDogByValue( dog ); // calls Dog, Instance is an Dalmatiner, but Function use only the Dog
   out( "" );

   out( "now use the Dog" );
   useAnimal( dog ); // works, Dalmatiner is used
   useDog( dog );  // works, Dalmatiner is used
   //useDalmatiner(dog); // compiler error

   return 0;
}

