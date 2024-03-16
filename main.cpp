#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Policy{
protected:
    bool isChecked;
public:
    virtual void check(const std::string& string1)=0;
    bool getCheck()const {return isChecked;}
};

class LengthPolicy: public Policy{
private:
    uint16_t minLength, maxLength;
public:
    LengthPolicy(uint16_t min):minLength(min), maxLength(255){}
    LengthPolicy(uint16_t min, uint16_t max):minLength(min), maxLength(max){}
    void check(const std::string& string1) override{
        if(string1.size()<minLength||string1.size()>maxLength) isChecked=false;
        else isChecked=true;
    }
};

class ClassPolicy: public Policy{
    uint16_t minClassCount;
public:
    ClassPolicy(uint16_t minc):minClassCount(minc){}
    void check(const std::string& string1)override{
        int high=0, low=0, number=0, othch=0;
        for (int i=0;i<string1.size();i++){
            if(isupper(string1[i])) high=1;
            else if(islower(string1[i])) low=1;
            if(isalnum(string1[i])&&!isalpha(string1[i])) number=1;
            else if(!isalnum(string1[i])) othch=1;
        }
        if(minClassCount<=(high+low+number+othch)) isChecked=true;
        else isChecked=false;
    }
};

class IncludePolicy: public Policy{
private:
    char characterType;
public:
    IncludePolicy(char c):characterType(c){}
    void check(const std::string& string1) override{
        int ck=0;
        if (characterType=='a')
            for(int i=0; i<string1.size();i++){
                if(islower(string1[i])) ck=1;
            }
        else if (characterType=='A')
            for(int i=0; i<string1.size();i++){
                if(isupper(string1[i])) ck=1;
            }
        else if (characterType=='0')
            for(int i=0; i<string1.size();i++){
                if(isalnum(string1[i])&&!isalpha(string1[i])) ck=1;
            }
        else if (characterType=='$')
            for(int i=0; i<string1.size();i++){
                if(!isalnum(string1[i])) ck=1;
            }
        if(ck==1) isChecked=true;
        else isChecked=false;
    }
};

class NotIncludePolicy: public Policy{
private:
    char characterType;
public:
    NotIncludePolicy(char c): characterType(c){}
    void check(const std::string& string1) override{
        int ck=0;
        if (characterType=='a')
            for(int i=0; i<string1.size();i++){
                if(islower(string1[i])) ck=1;
            }
        else if (characterType=='A')
            for(int i=0; i<string1.size();i++){
                if(isupper(string1[i])) ck=1;
            }
        else if (characterType=='0')
            for(int i=0; i<string1.size();i++){
                if(isalnum(string1[i])&&!isalpha(string1[i])) ck=1;
            }
        else if (characterType=='$')
            for(int i=0; i<string1.size();i++){
                if(!isalnum(string1[i])) ck=1;
            }
        if(ck==1) isChecked=false;
        else isChecked=true;
    }
};

class RepetitionPolicy: public Policy{
    uint16_t maxCount;
public:
    RepetitionPolicy(uint16_t max):maxCount(max){}
    void check(const std::string& string1) override{
        int tru=0;
        for(int i=0; i<string1.size()-1;i++){
            int nmb_rep=1;
            for(int j=i+1;j<string1.size();j++){
                if(string1[i]==string1[j]) {
                    nmb_rep += 1;
                }else break;
            }
            if(nmb_rep>maxCount){
                isChecked=false;
                tru=1;
                break;
            }
        }
        if(tru==0) isChecked=true;
    }
};

class ConsecutivePolicy: public Policy{
    uint16_t maxCount;
public:
    ConsecutivePolicy(uint16_t max): maxCount(max){}
    void check(const std::string& string1) override{
        int tru=0;
        for(int i=0;i<string1.size()-1;i++){
            int asc=(char)string1[i];
            int nm_rep=1;
            for (int j=i+1;j<string1.size();j++){
                asc+=1;
                if((char)string1[j]==asc){
                    nm_rep+=1;
                }else break;
            }
            if(nm_rep>maxCount) {
                isChecked=false;
                tru=1;
                break;
            }
        }
        if(tru==0) isChecked=true;
    }
};
std::string checkPassword(const std::string string2, std::vector<Policy*> pol){
    for(int i=0;i<pol.size();i++){
        pol[i]->check(string2);
        if(!pol[i]->getCheck()) return "NOK";
    }
    return "OK";
}
int main() {
    unsigned int n;
    std::cin>>n;
    std::vector <Policy*> policies;
    uint16_t value, max_val;
    char c;
    for(int i=0; i<n;i++){
        std::string str;
        std::cin>>str;
        if(str=="length"){
            int l_rep=0;
            cin>>value;
            if(getchar()==' '){
                cin>>max_val;
                policies.push_back(new LengthPolicy(value,max_val));
            }
            else policies.push_back(new LengthPolicy(value));
        }
        else if(str=="class"){
            std::cin>>value;
            policies.push_back(new ClassPolicy(value));
        }
        else if(str=="include"){
            std::cin>>c;
            policies.push_back(new IncludePolicy(c));
        }
        else if(str=="ninclude"){
            std::cin>>c;
            policies.push_back(new NotIncludePolicy(c));
        }
        else if(str=="repetition"){
            std::cin>> value;
            policies.push_back(new RepetitionPolicy(value));
        }
        else if(str=="consecutive"){
            std::cin>>value;
            policies.push_back(new ConsecutivePolicy(value));
        }
    }
    std::vector<std::string> passwords;
    std::string pass;
    while(std::cin>>pass) passwords.push_back(pass);
    for(int i=0;i<passwords.size();i++){
        std::cout<< checkPassword(passwords[i], policies);
        std::cout<<std::endl;
    }
    return 0;
}
