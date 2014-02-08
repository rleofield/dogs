
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

#include <boost/algorithm/string/trim.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>

#include "helper.h"

#include <time.h>

static boost::mutex MUTEX; //boost mutex

/// \return The clock cycle in milliseconds
unsigned long getTime() {
   clock_t time = clock();
   time *= 1000;
   time /= CLOCKS_PER_SEC;
   return time;
}

bool writeFile( const std::string filename, const std::string& content ) {

   std::ofstream ofs( filename.c_str(), std::ios::out | std::ios::binary );

   if( ofs.is_open() ) {
      ofs << content;
      return true;

   } else {
      return false;
   }
}

std::string readFile( const std::string& filename ) {

   std::ifstream ifs( filename.c_str(), std::ios::in );
   std::string data;

   if( ifs.is_open() ) {

      char c = 0;

      while( !ifs.eof() ) {
         c = ifs.get();

         if( ifs.good() ) {
            data.push_back( c );
         }
      }
   }

   return data;
}

bool writeLog( int line, const char* function, std::string content, bool trim ) {

   std::stringstream ss;

   // time
   ss.width( 6 );
   ss << getTime() << " ms T:0x";

   // thread
   ss.fill( '0' );
   ss.width( 6 );
   ss << boost::this_thread::get_id();

   // line
   ss.fill( ' ' );
   ss << " L:";
   ss.width( 4 );
   ss.setf( std::ios::right );
   ss << line << " F:";

   // function
   ss.width( 20 );
   ss.setf( std::ios::left );
   ss << function << " : ";

   // beautify
   std::string alignment = std::string( ss.str().size(), ' ' );
   std::string formatted = trim ? boost::trim_right_copy( content ) : content;
   formatted = SanitizeAllWhiteSpaces<std::string>( formatted );
   formatted = FindAndReplace( formatted, std::string( "\n" ), std::string( "\n" ) + alignment );

   ss << formatted << std::endl;

   // write to logfile
   {
      boost::lock_guard<boost::mutex> lock( MUTEX );

      std::ofstream ofs( "boost_threads.log", std::ios::out | std::ios::app );

      if( ofs.is_open() ) {

         // 2 newlines at start
         static bool start = false;

         if( !start ) {
            ofs << "\n\n";
            start = true;
         }

         ofs << ss.str();

         return true;

      } else {
         return false;
      }
   }
}

