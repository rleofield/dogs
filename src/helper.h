#ifndef BT_HELPER_H
#define BT_HELPER_H

#pragma once



#include <string>

#define LOG(A) writeLog( __LINE__, __FUNCTION__, A )
#define LOGEND(A) writeLog( __LINE__, __FUNCTION__, A, false )
#define LOGBEGIN(A) writeLog( __LINE__, __FUNCTION__, A, false )

unsigned long getTime();
bool writeLog( int line, const char* function, std::string content, bool trim = true );

bool writeFile( const std::string filename, const std::string& content );
std::string readFile( const std::string& filename );

template < class T >
T SanitizeAllWhiteSpaces( const T& ref ) {

   //typedef T                           string;
   //typedef typename T::const_iterator  iterator;
   //typedef typename T::size_type       size_type;

   const T    newEnding( "\n" );
   const T    replaceEnding( "\r\n" );
   T          ret;
   size_t       pos( 0 );

   for( auto it = ref.begin(); it != ref.end(); it++ ) {
      if( *it == replaceEnding[ 0 ] && ref[ pos + 1 ] == replaceEnding[1] ) {
         ret += newEnding;
         it++;
         pos++;
      } else {
         ret += *it;
      }

      pos++;
   }

   return ret;
}

template < class T >
T FindAndReplace( const T& source,
                  const T& find,
                  const T& replace ) {
   size_t i;
   size_t start = 0;
   T ret = source;

   for( ; ( i = ret.find( find, start ) ) != std::string::npos; ) {
      ret.replace( i, find.length(), replace );
      start = i + replace.length();
   }

   return ret;
}

#endif

// EOF
