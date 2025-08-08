#include <iostream>
#include <string>
#include <vector>
#include <cmath>
//Tokenxxxxxx
struct Token {
  std::string type;
  std::string val;
};
std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << "{ type: " << token.type << ", val: " << token.val << " }";
    return os;
}
//tokenxxxxxx
const std::string numbers="1234567890."; 
const std::string operators="+-/*^";
//definitions
std::vector<Token> level1(std::vector<Token> tokens);
std::vector<Token> level2(std::vector<Token> tokens);
std::vector<Token> level3(std::vector<Token> tokens);
std::vector<Token> negate(std::vector<Token>tokens);
float parser(std::vector<Token> tokens);
//
//Lexerxxxxxx
std::vector<Token> lexer(std::string line){
  int i=0;
  char c=line[i];
  std::vector<Token> tokens;
  while(i<line.length()){
    c=line[i];
    if (numbers.find(c)!=std::string::npos) {
      std::string str="";
      while(numbers.find(c)!=std::string::npos && i<line.length()){
        str+=c;
        i++;
        c=line[i];
      }
      tokens.push_back(Token{"num",str});
    }
    else if(operators.find(c)!=std::string::npos){
      i++;
      tokens.push_back(Token{"op",std::string(1,c)});
      c=line[i];
    }
    else if(c=='('){
        std::string str="";
        int n=1;
        int j=i;
        j++;
        c=line[j];
        while(n>0){
            str+=c;
            j++;
            c=line[j];
            if(c=='('){n++;}
            else if(c==')'){n--;}
        }
       
        float res=parser(lexer(str));
        line.replace(i,str.size()+2,std::to_string(res));
    }
    else{
      i++;
      c=line[i];
    }
  }
  return tokens;
}
//lexerxxxxxx

//Parserxxxxxx
float parser(std::vector<Token> tokens){
 tokens=negate(tokens);
 
 
 for (const Token& token : tokens) {
    std::cout << token << std::endl;
}
 
 tokens=level3(tokens);
 tokens= level2(tokens);
 tokens= level1(tokens);
 std::cout<<tokens[0].val<<"\n";
 return std::stof(tokens[0].val);
}
//parseexxxxxx
//Level1xxxxxx
std::vector<Token> level1(std::vector<Token> tokens){
  for(int i=0;i<tokens.size();i++){
    if(tokens[i].val=="+"){
      float left=std::stof(tokens[i-1].val);
      float right =std::stof(tokens[i+1].val);
      float res =left+right;
      tokens.erase(tokens.begin()+i-1);
      i--;
      tokens.erase(tokens.begin()+i+1);
     // i--;
      tokens[i].type="op";
      tokens[i].val=std::to_string(res);

    }
    if(tokens[i].val=="-"){
      float left=std::stof(tokens[i-1].val);
      float right =std::stof(tokens[i+1].val);
      float res =left-right;
      tokens.erase(tokens.begin()+i-1);
      i--;
      tokens.erase(tokens.begin()+i+1);
      tokens[i].type="op";
      tokens[i].val=std::to_string(res);
    }
  }
  return tokens;
}
//Level1xxxxxx
//Level2xxxxxx
std::vector<Token> level2(std::vector<Token> tokens){
 for(int i=0;i<tokens.size();i++){
  if(tokens[i].val=="*"){
   float left=std::stof(tokens[i-1].val);
   float right=std::stof(tokens[i+1].val);
   float res=left*right;
   tokens.erase(tokens.begin()+i-1);
   i--;
   tokens.erase(tokens.begin()+i+1);
   tokens[i].type="num";
   tokens[i].val=std::to_string(res);
  }
  if(tokens[i].val=="/"){
   float left=std::stof(tokens[i-1].val);
   float right=std::stof(tokens[i+1].val);
   float res=left/right;
   tokens.erase(tokens.begin()+i-1);
   i--;
   tokens.erase(tokens.begin()+i+1);
   tokens[i].type="num";
   tokens[i].val=std::to_string(res);
  }
 }
 return tokens;
}
//level2xxxxxx
//Level3xxxxxx
std::vector<Token> level3(std::vector<Token> tokens){
 for(int i=0;i<tokens.size();i++){
  if(tokens[i].val=="^"){
   float left=std::stof(tokens[i-1].val);
   float right=std::stof(tokens[i+1].val);
   float res=std::pow(left,right);
   tokens.erase(tokens.begin()+i-1);
   i--;
   tokens.erase(tokens.begin()+i+1);
   tokens[i].type="num";
   tokens[i].val=std::to_string(res);
  }
 }
 return tokens;
}
//level3xxxxxx
//Negatexxxxxxx
std::vector<Token> negate(std::vector<Token>tokens){
 for(int i=0;i<tokens.size();i++){
  if(tokens[i].val=="-"){
   if(i>0){
    if(tokens[i-1].type!="num"){
     tokens[i+1].val="-"+tokens[i+1].val;
     tokens.erase(tokens.begin()+i);
     i--;
    }
   }
   else{
    if(tokens[0].val=="-"){
     tokens[i+1].val="-"+tokens[i+1].val;
     tokens.erase(tokens.begin());
     i--;
    }
   }
  }
 }
 return tokens;
}
//negatexxxxxxx
std::string code ="1-4*3/2^1.5";
//main functionxxxxxx
int main2(){
 std::cout<<"calc>";
 std::cin>>code;
 std::vector<Token> tokens = lexer(code);
for (const Token& token : tokens) {
    std::cout << token << std::endl;
}
std::cout<<parser(tokens)<<std::endl; 
  return 0;
}
int main(){
 std::cout<<"this programm runs calculator \nit has + - / * ^\nit allows prantheses\nit allows negative number\nno charcters like abcd only numbers and operators\nthis calc assums you are smart so dont do charcters or anything stupid\n";
 while(true){
  main2();
 }
 return 0;
}
