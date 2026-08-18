#include<iostream>
using namespace std;
int main(){
    //Setting Up the Basic Input Interface...
    int c;
    cout<<"Enter Storage Capacity:- ";
    cin>>c;
    cout<<"Enter no. of Containers:- ";
    int n;
    cin>>n;
    if(n>1000){
        cout<<"No. of Containers Should be less than 1000";
    }else{
    float wei_sum=0;
    //Initialising Max and Min to Infinity(Or the limiting integer values)
    float max_wei=INT_MIN;   //-999999
    float min_wei=INT_MAX;   //9999999
    //Looping through all the Weights
    for(int i=0;i<n;i++){
        float temp;
        cout<<"Enter weight "<<i+1<<" of "<<n<<": ";
        cin>>temp;
        wei_sum+=temp;
        if(temp>max_wei){
            max_wei=temp;
        }
        if(temp<min_wei){
            min_wei=temp;
        }
    }
    //Analysis and Display
    cout<<"Total Shipment Weight: "<<wei_sum<<endl;
    cout<<"Average Container Weight: "<<(float)wei_sum/n<<endl;
    cout<<"Heaviest Container: "<<max_wei<<endl;
    cout<<"Lightest Container: "<<min_wei<<endl;
    if(wei_sum>=200){
        cout<<"Classification: Heavy"<<endl;
    }else{
        cout<<"Classification: Light"<<endl;
    }
    cout<<"Port Capacity: "<<c<<endl;
    if(wei_sum>c){
        cout<<"Status: Shipment exceeds port capacity."<<endl;
    }else{
        cout<<"Status: Shipment can be uploaded."<<endl;
    }
    return 0;
}
}