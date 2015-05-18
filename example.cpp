/// Shaun Harker
/// Sample Program for SQLambda
/// 2015-05-18

#include <iostream>
#include <exception>
#include <cmath>
#include <cstdint>

#include "sqlambda.h"

using namespace sqlite;

int main ( void ) {
  int64_t N = 1000000;
  try {
    // Open a database. Create if does not exist.
    database db("dbfile.db");
    // Create a table "user" in database
    db . exec ( "create table if not exists test (name Integer, data Real);" );
    // Begin a transaction
    db . exec ( "begin;" );
    // Create a prepared statement for insertion
    statement prepped = db . prepare ( "insert into test (name, data) values (?, ?);" );
    // Insert N rows into table "user"
    for ( int64_t i = 0; i < N; ++ i ) 
      prepped . bind ( i, std::sqrt((double)i) ) . exec ();
    // Commit the transaction
    db . exec ( "end;" );
    // Create a prepared statement for selection
    prepped = db . prepare ( "select * from test where data < 8.0;");
    // Process the results using a lambda expression
    prepped . forEach ( [] (int name, double data) {
      std::cout << "Name: " << name << "\t Data: " << data << "\n";
    });
  }
  catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
