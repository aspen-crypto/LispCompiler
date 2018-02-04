#include <iostream>
#include <vector>

struct token {
    std::string type;
    std::string value;

    std::string toString(){
        return "Type: " + type + "; Value: " + value;
    }
};

std::vector<token> tokenizer(std::string inputCode);


int main() {
    std::string testing = "(add 500 600) sub ()";
    std::vector<token> out = tokenizer(testing);
    for (auto &i : out) {
        std::cout << i.toString() << std::endl;
    }
    return 0;
}

std::vector<token> tokenizer(std::string inputCode){
    std::vector<token> tokens;
    std::string numbers = "123456789";
    for(int i = 0; i < inputCode.length(); i++){
        if(inputCode[i] == '(' || inputCode[i] == ')'){
            token currentToken;
            currentToken.type = "paren";
            currentToken.value = inputCode[i];
            tokens.push_back(currentToken);
        } else if (isdigit(inputCode[i])) {
            token currentToken;
            currentToken.type = "number";
            while (isdigit(inputCode[i])) {
                currentToken.value += inputCode[i];
                i++;
            }
            tokens.push_back(currentToken);
        } else if (isalpha(inputCode[i])){
            token currentToken;
            currentToken.type = "name";
            while(isalpha(inputCode[i])) {
                currentToken.value += inputCode[i];
                i++;
            }
            tokens.push_back(currentToken);
        }
    }
    return tokens;
}