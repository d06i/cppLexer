#include <iostream>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <fstream>

std::unordered_set< std::string > keywords = { "if", "while", "for", "int", "float", "double", "return",  "enum",  "void", "break", "continue" };
std::unordered_set< char > operators = { '+', '-', '*', '/', '!', '&', ';', '=', '<', '>', ',' };
std::unordered_set< char > seperators = { '{', '}', '(', ')', '[', ']' };
std::unordered_set<std::string> doubleOperators = { "==", "!=", "<=", ">=", "++", "--", "&&", "||", "<<", ">>" };

enum Token{
    tok_identifier,
    tok_keywords,
    tok_numbers,
    tok_operators,
    tok_seperators 
};

struct tokenType{
	
    std::string val;
    Token tokenType;
};

std::vector<tokenType> tokens;

void lexer(std::string & source) {

  std::stringstream ss(source);
  std::string temp;
  char c;

  while (ss.get(c)) {
    if (std::isspace(c))
      continue;

    else if (operators.find(c) != operators.end()){
        temp = c;
        char nextChar;
        if ( ss.get(nextChar) ){
            temp += nextChar;
            if ( doubleOperators.find(temp) != doubleOperators.end() ){
                std::cout << "Operator: " << temp << "\n";
                continue; }
         } 
            ss.unget();
            std::cout << "Operator: " << c << "\n"; 
         
          }

    else if (seperators.find(c) != seperators.end())
      std::cout << "Seperator: " << c << "\n";
 
    else if (std::isalpha(c)) {
      temp = c;
      while (ss.get(c) && (std::isalpha(c) || c == '_'))
        temp += c;

      ss.unget(); // putback last character

      if (keywords.find(temp) != keywords.end())
        std::cout << "Keyword: " << temp << "\n";
      else
        std::cout << "Identifier: " << temp << "\n";
    } 
    
    else if (std::isdigit(c)) {
      temp = c;
      while (ss.get(c) && (std::isdigit(c) || c == '.'))
        temp += c;

       ss.unget();

      std::cout << "Number: " << temp << "\n";
    } 
    
    else
      std::cout << "[!] Unknown -> " << c << "\n";

  }
} 

int main() {

  std::string example = R"( float test_f( float q ) {
                             float z_Z = 13; 
                             int z = 12 << 2; 
                             if( z != 54){
                                z = z++;} 
                             return q * z * 2592.44; }
                             
                             )", temp, c;
  
  std::string filename;
  std::cout << "Filename: ";
  std::cin >> filename;

   std::ifstream file( filename );
    if ( !file ){
        std::cout << "File not found!\nExample: " << example << "\n";
        lexer(example);
        return -1;
    }

    while ( std::getline( file, temp ) )
        c += temp; 

   lexer(c); 

  return 0;
}
