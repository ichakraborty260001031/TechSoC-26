#include"matrix.cpp"
class Qubit {
    Matrix zero{2,1};
    Matrix one{2,1};
    Matrix state{2,1};
    
    public:
    double a=1;
    double b=0;
    Qubit(){
        zero.setValue(1,1,1);
        one.setValue(2,1,1); 
        state=zero.mult(a) + one.mult(b);
    }
    Matrix getState(){
        state=zero.mult(a) + one.mult(b);
        return state;
    }
};