#include<iostream>
#include<cmath>
#include<string>

template<typename T>
T input(std::string prompt){
    T inp;
    std::cout<<prompt;
    std::cin>>inp;
    return inp;
}

std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

long long int strToBase256(std::string m){
    long long int ans=0;
    for(int i=0;i<m.length();i++){
        ans=(ans*256)+(unsigned char)m[i];
    }
    return ans;
}
long long int gcd(long long int x,long long int y){
    while(y!=0){
        long long int t =x%y;
        x=y;
        y=t;
    }
    return x;
}
long long int getE(long long int phi){
    long long int e=3;
    while(gcd(e,phi)!=1){
        e+=2;
    }
    return e;
}
long long int getD(long long int phi,long long int e){
    long long int tempP=phi;
    long long int tempR=e;
    long long int val=0;
    long long int n_val=1;
    while(tempR!=0){
        long long int q=tempP/tempR;
        long long int r=tempP%tempR;
        long long int temp_val=val;
        val=n_val;
        n_val=temp_val-q*n_val;
        tempP=tempR;
        tempR=r;

    }

    if(val<0) val=val+phi;
    if(tempR>1) return -1;
    return val;
}
long long int powMod(long long int base,long long int exp,long long int n){
    long long int res=1;
    base=base%n;
    while(exp>0){
        if(exp%2==1){
            res=(long long int)(res*base)%n;
        }
        exp=exp/2;
        base=(base*base)%n;
    }
    return res;
}
long long int RSA_ENC(std::string m,long long int n,long long int e){
    long long int num=strToBase256(m);
    long long int encr=powMod(num,e,n);
    return encr;
}
std::string B64_ENC(std::string message){
    std::string b_string="";
    std::string enc_message="";
    for(int i=0;i<message.length();i++){
        int dec=(int)message[i];
        std::string bnary="";
        while(dec>0){
            int r=dec%2;
            bnary=std::to_string(r)+bnary;
            dec=dec/2;
        }
        for(int j=bnary.length();j<8;j++){
            bnary="0"+bnary;
        }
        b_string=b_string+bnary;
    }
    int count=0;
    while(b_string.length()%6!=0){
        b_string+="0";
        count++;
    }
    for(int i=0;i<b_string.length();i+=6){
        std::string segment=b_string.substr(i,6);
        int num=0;
        for(int j=0;j<segment.length();j++){
            std::string dig(1,segment[j]);
            num+=(std::stoi(dig))*pow(2,segment.length()-j-1);
        }
        enc_message+=base64_chars[num];
    }
    for(int i=0;i<count/2;i++){
        enc_message+="=";
    }
    return enc_message;
}
std::string B64_DEC(std::string message){
    std::string b_string="";
    for(int i=0;i<message.length();i++){
        if(message[i]!='='){
            int num=base64_chars.find(message[i]);
            std::string bnary="";
            while(num>0){
                int r=num%2;
                bnary=std::to_string(r)+bnary;
                num=num/2;
            }
            for(int j=bnary.length();j<6;j++){
                bnary="0"+bnary;
            }
            b_string=b_string +bnary;
        }
    }
    std::string answer;
    for(int i=0;i<b_string.length();i+=8){
        std::string segment=b_string.substr(i,8);
        int num=0;
        for(int j=0;j<segment.length();j++){
            std::string dig(1,segment[j]);
            num+=(std::stoi(dig))*pow(2,segment.length()-j-1);
            
        }
        std::string letter(1,(char)(num));
        answer+=letter;
    }
    return answer;
}
std::string RSA_DEC(long long int encr,long long int d,long long n){
    long long int dec=powMod(encr,d,n);
    std::string ans="";
    while(dec>0){
        ans=char(dec%256)+ans;
        dec=dec/256;
    }
    return ans;
}
int main(){
    long long int n,e;
    std::string message=input<std::string>("Enter the message to encrypt/decrypt:- ");
    std::string command=input<std::string>("Enter the command in Array form:- ");
    int location3=0;
    std::string currentMessage = message;
    
        while(location3<command.length()-1){
            int location1;
            if(location3==0){
                location1=command.find('[');
            }else{
                location1=location3;
            }
            int location2;
            int open=command.find('(',location1+1);
            int close=command.find(')',location1+1);
            int comma=command.find(',',location1+1);
            int end=command.find(']',location1+1);

            if(open!=std::string::npos && open<end && open<comma){
                location2=open;
                location3=close;
            }else{
                location2=command.find(',',location1+1);
                if(location2==std::string::npos || location2>end)
                    location2=end;
                location3=location2;
            }

            std::string cmd=command.substr(location1+1,location2-location1-1);
            std::string arg=command.substr(location2+1,location3-location2-1);
            int brL=command.find(',',location2);
            
            if(cmd=="RSA_ENC"){
                std::string ciphertext="";
                int comma=arg.find(',');
                n=std::stoll(arg.substr(0,comma));
                e=std::stoll(arg.substr(comma + 1));
                
                for(int i=0;i<currentMessage.length();i++){
                    if(i==currentMessage.length()-1){
                        ciphertext+=std::to_string(RSA_ENC(std::string(1,currentMessage[i]),n,e));
                    }else{
                        ciphertext+=std::to_string(RSA_ENC(std::string(1,currentMessage[i]),n,e))+'-';
                    }
                    
                }
                currentMessage=ciphertext;
            }
            if(cmd=="RSA_DEC"){
                std::string result="";
                int comma = arg.find(',');
                n=std::stoll(arg.substr(0, comma));
                long long int d=std::stoll(arg.substr(comma+1));

                int start = 0;

                while (start<currentMessage.length()) {
                    int dash=currentMessage.find('-', start);

                    std::string seg;

                    if (dash == std::string::npos) {
                        seg = currentMessage.substr(start);
                        start = currentMessage.length();
                    } else {
                        seg = currentMessage.substr(start, dash - start);
                        start = dash + 1;
                    }

                    result += RSA_DEC(std::stoll(seg), d, n);
            }

            currentMessage = result;
            }
            if(cmd=="B64_ENC"){
                currentMessage=B64_ENC(currentMessage);
            }
            if (cmd=="B64_DEC") {
                currentMessage=B64_DEC(currentMessage);
            }
            if(cmd!=""){
                std::cout<<"After "<<cmd<<":- "<<currentMessage<<std::endl;
            }
        }
     
    return 0;
}
