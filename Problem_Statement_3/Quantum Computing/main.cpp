#include<iostream>
#include"simulator.cpp"
#include<string>
#include<vector>

template<typename T>
T input(std::string prompt);

int main(){

    int n=input<int>("Enter the no. of Qubits in Your Circuit:- ");
    QuantumCircuit circ(n);
    std::cout<<"Initial State: "<<std::endl;
    circ.showState();
    int count=0;
    int choice=1;
    do{
        count++;
        std::cout<<"Command set "<<count<<std::endl;
        std::string command=input<std::string>("Enter the commands in Array form:- ");
        int location3=0;
        while(location3!=command.length()-2){
            int location1;
            if(location3==0){
                location1=command.find('[');
            }else{
                location1=command.find(',',location3);
            }
            int location2=command.find('(',location1);
            location3=command.find(')',location2);

            std::string cmd=command.substr(location1+1,location2-location1-1);
            std::string arg=command.substr(location2+1,location3-location2-1);
            if(cmd=="H"){
                circ.H(stoi(arg));
                std::cout<<std::endl<<"After "<<cmd<<": "<<std::endl;
                circ.showState();
            }else if(cmd=="X"){
                circ.X(stoi(arg));
                std::cout<<std::endl<<"After "<<cmd<<": "<<std::endl;
                circ.showState();
            }
            else if(cmd=="Y"){
                circ.Y(stoi(arg));
                std::cout<<std::endl<<"After "<<cmd<<": "<<std::endl;
                circ.showState();
            }
            else if(cmd=="Z"){
                circ.Z(stoi(arg));
                std::cout<<std::endl<<"After "<<cmd<<": "<<std::endl;
                circ.showState();
            }else if(cmd=="CX"){
                circ.CX((int)arg[0]-(int)'0',(int)arg[2]-(int)'0');
                std::cout<<std::endl<<"After "<<cmd<<": "<<std::endl;
                circ.showState();
            }else if(cmd=="RX" || cmd== "RY" || cmd=="RZ") {
                int pos = arg.find(',');
                int index =std::stoi(arg.substr(0,pos));
                float theta = std::stof(arg.substr(pos+1));
    
                if (cmd == "RX") circ.RX(index, theta);
                else if (cmd == "RY") circ.RY(index, theta);
                else if (cmd == "RZ") circ.RZ(index, theta);
    
                std::cout<<std::endl<<"After "<<cmd<<": "<<std::endl;
                circ.showState();
            }else if(cmd=="SWAP"){
                circ.SWAP((int)arg[0]-(int)'0',(int)arg[2]-(int)'0');
                std::cout<<std::endl<<"After "<<cmd<<": "<<std::endl;
                circ.showState();
            }
            else if(cmd=="TOFFOLI"){
                circ.TOFFOLI((int)arg[0]-(int)'0',(int)arg[2]-(int)'0',(int)arg[4]-(int)'0');
                std::cout<<std::endl<<"After "<<cmd<<": "<<std::endl;
                circ.showState();
            }
        }
        choice=input<int>("Enter 1 to continue; anything else to exit:- ");
    }while(choice==1);
    return 0;

}

template<typename T>
T input(std::string prompt){
    T inp;
    std::cout<<prompt;
    std::cin>>inp;
    return inp;
}

