#ifndef WORD_H
#define WORD_H

#include <string>

class Word {
private:
    std::string secretWord;//要猜的字
    std::string revealedWord; //hidden word

public:
    Word(const std::string& word){ //配合CM去选择字
        secretWord = word; 
        revealedWord = std::string(word.length(), '_'); 
    }
    bool checkGuess(char guess){//检查猜测的字
        bool found = false; //？？
        for (size_t i = 0; i < secretWord.length(); i++) {//对每个index检测是否正确
            if (tolower(secretWord[i]) == tolower(guess)) { //猜对显示对应的字
                revealedWord[i] = secretWord[i];
                found = true; //？？
            }
        }
        return found;
    }
    bool isFullyGuessed() const{ //猜测单词正确
        return secretWord == revealedWord;
    }
    std::string getRevealedWord() const{//获取最新状态
        return revealedWord;
    }
    std::string getSecretWord() const{//获取最新状态
        return secretWord;
    }
};

#endif
