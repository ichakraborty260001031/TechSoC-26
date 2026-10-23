#include"qubit.cpp"
#include<iomanip>
#include<cmath>

class QuantumCircuit{
    public:
        int n;
        Matrix state{1,1};

        Matrix I{2,2};
        Matrix h{2,2};
        Matrix x{2,2};
        Matrix p0{2,2};
        Matrix p1{2,2};
        Matrix y{2,2};
        Matrix z{2,2};

        vector<Qubit> qubits;

    public:
    QuantumCircuit(int n){

        state.setValue(1,1,1);

        I.setValue(1,1,1);I.setValue(1,2,0);I.setValue(2,1,0);I.setValue(2,2,1);
        h.setValue(1,1,1/sqrt(2));h.setValue(1,2,1/sqrt(2));h.setValue(2,1,1/sqrt(2));h.setValue(2,2,-1/sqrt(2));
        x.setValue(1,1,0);x.setValue(1,2,1);x.setValue(2,1,1);x.setValue(2,2,0);
        p0.setValue(1,1,1);p0.setValue(1,2,0);p0.setValue(2,1,0);p0.setValue(2,2,0);
        p1.setValue(1,1,0);p1.setValue(1,2,0);p1.setValue(2,1,0);p1.setValue(2,2,1);
        
        y.setValue(1,1,0.0);y.setValue(1,2,Complex(0.0,-1.0));y.setValue(2,1,Complex(0.0,1.0));y.setValue(2,2,0.0);
        z.setValue(1,1,1.0);z.setValue(1,2,0.0);z.setValue(2,1,0.0);z.setValue(2,2,-1.0);

        this->n=n;
        for(int i=0;i<n;i++){
            Qubit q;
            qubits.push_back(q);
            state=state.tensor(qubits[i].getState());
        }
    }
    void showState() {
        int total = pow(2,n);
        for(int i=0;i<total;i++){
            std::string bitstr="";
            int temp=i;
            double prob=std::norm(state.data[i][0]);
            while(temp>0){
                bitstr=to_string(temp%2)+bitstr;
                temp=temp/2; 
            }
            std::string addstr="";
            for(int i=0;i<n-bitstr.length();i++){
                addstr+="0";
            }
            bitstr=addstr+bitstr;
            std::cout<<std::fixed<<std::setprecision(6);
            std::cout<<"Probability of state |"<<bitstr<<">: "<<prob<<std::endl;
        }
        
        
    }
    Matrix BuildGate(int target,Matrix gate){
        Matrix gateF{1,1};
        gateF.setValue(1,1,1);
        for(int i=0;i<n;i++){
            if(i==target){
                gateF=gateF.tensor(gate);
            }else{
                gateF=gateF.tensor(I);
            }
        }
        return gateF;
    }

    void X(int index){
        Matrix gateF=BuildGate(index,x);
        state=gateF.dotProd(state);
    }
    void Y(int index){
        Matrix gateF=BuildGate(index,y);
        state=gateF.dotProd(state);
    }
    void Z(int index){
        Matrix gateF=BuildGate(index,z);
        state=gateF.dotProd(state);
    }
    void RX(int index,float theta){
        Matrix rx{2,2};
        rx.setValue(1,1,cos(theta/2));
        rx.setValue(2,1,Complex(0.0,-sin(theta/2)));
        rx.setValue(1,2,Complex(0.0,-sin(theta/2)));
        rx.setValue(2,2,cos(theta/2));

        Matrix gateF=BuildGate(index,rx);
        state=gateF.dotProd(state);
    }
    void RY(int index,float theta){
        Matrix ry{2,2};
        ry.setValue(1,1,cos(theta/2));
        ry.setValue(2,1,sin(theta/2));
        ry.setValue(1,2,-sin(theta/2));
        ry.setValue(2,2,cos(theta/2));

        Matrix gateF=BuildGate(index,ry);
        state=gateF.dotProd(state);
    }
    void RZ(int index,float theta){
        Matrix rz{2,2};
        rz.setValue(2,1,0);
        rz.setValue(1,1,Complex(cos(theta/2),-sin(theta/2)));
        rz.setValue(2,2,Complex(cos(theta/2),sin(theta/2)));
        rz.setValue(1,2,0);

        Matrix gateF=BuildGate(index,rz);
        state=gateF.dotProd(state);
    }
    void H(int index){
        Matrix gateF=BuildGate(index,h);
        state=gateF.dotProd(state);
    }
    void CX(int control,int target){
        Matrix part1{1,1};
        part1.setValue(1,1,1);
        Matrix part2{1,1};
        part2.setValue(1,1,1);
        for(int i=0;i<n;i++){
            if(i==control){
                part1=part1.tensor(p0);
                part2=part2.tensor(p1);
            }else if(i==target){
                part1=part1.tensor(I);
                part2=part2.tensor(x);
            }
            else{
                part1=part1.tensor(I);
                part2=part2.tensor(I);
            }
        }
        Matrix gateF=part1+part2;
        state=gateF.dotProd(state);
    }
    void SWAP(int index1,int index2){
        CX(index1,index2);
        CX(index2,index1);
        CX(index1,index2);
    }
    void TOFFOLI(int control1,int control2,int target){
        if(n<3){
            std::cout<<"Warning! Invalid operation.."<<std::endl;
        }
        Matrix fullProj{1,1};fullProj.setValue(1,1,1);
        Matrix tarOp{1,1};tarOp.setValue(1,1,1);
        for(int i=0;i<n;i++){
            if(i==control1 || i==control2){
                fullProj=fullProj.tensor(p1);
                tarOp=tarOp.tensor(I);
            }else if(i==target){
                fullProj=fullProj.tensor(I);
                tarOp=tarOp.tensor(x);
            }else{
                fullProj=fullProj.tensor(I);
                tarOp=tarOp.tensor(I);
            }
        }
        Matrix I2n=Matrix::createDiagonalMatrix(pow(2,n),1);
        Matrix gateF=(I2n+(fullProj.mult(-1)))+fullProj.dotProd(tarOp);
        state=gateF.dotProd(state);
    }
};