
//ADD-ONS to the fundamental system
#include<iostream>
#include<vector>
#include <climits>
#include<map>
#include<fstream>
using namespace std;

//---------------MY SORTING ALGORTIHM FUNCTION-----------------

void merge(vector<int> &seq,int p,int q,int r){
    int n1=q-p+1;
    int n2=r-q;
    vector<int> l1(n1+1);
    vector<int> l2(n2+1);
    for(int i=0;i<n1;i++){
        l1[i]=seq[p+i];
    }
    for(int j=0;j<n2;j++){
        l2[j]=seq[q+j+1];
    }
    l1[n1]=999999;
    l2[n2]=999999;
    int i=0;
    int j=0;
    for(int k=p;k<=r;k++){
        if(l1[i]<=l2[j]){
            seq[k]=l1[i];
            i++;
        }else{
            seq[k]=l2[j];
            j++;
        }
    }
}
void merge_sort(vector<int> &seq,int p,int r){
    int q=(p+r)/2;
    if(q>p){
        merge_sort(seq,p,q);
    }
    if(r>q+1){
        merge_sort(seq,q+1,r);
    }
    merge(seq,p,q,r);
}

//----------------MAIN CODE----------------
int main(){
    int choice=0;
    //----------------SETTING UP THE INTRO MENU--------------
    string data;
    cout<<"Hello and Welcome to Smart Cargo Terminal!!"<<endl;

    while(choice!=3){
        data="";
        cout<<endl<<"What do you want to do?"<<endl;
        cout<<"For Processing a Shipment By Entering Data now, Enter 1..."<<endl;
        cout<<"For Processing Shipment Data From a File, Enter 2..."<<endl;
        cout<<"To Exit,Enter 3.."<<endl<<endl;
        cout<<"What do You Choose?"<<endl;
        cin>>choice;
        if(choice==3){
            break;
        }
        //-----------BUILDING MENU LOGIC----------------
        int c = 0;
        int n = 0;
        int wei_sum=0;
        int max_wei=INT_MIN;
        int min_wei=INT_MAX;
        vector<int> weights;        //PREPARING A VECTOR FOR STORING THE WEIGHTS..
        multimap<int,int> list;     //MAP FOR SEARCHING LATER...
        
        if(choice==1){
            //------------CHOICE-1--------------
            cout<<"Enter Storage Capacity:- ";
            cin>>c;
            cout<<"Enter no. of Containers:- ";
            cin>>n;
            if(n>1000){
                cout<<"No. of Containers Should be less than 1000"<<endl;
                continue;
            }else{
                for(int i=0;i<n;i++){
                    int temp;
                    cout<<"Enter weight "<<i+1<<" of "<<n<<": ";
                    cin>>temp;
                    weights.push_back(temp);
                    list.insert({temp,i+1});
                }
            }
        }else if(choice==2){
            //--------INPUT FROM FILE--------
            cout<<"Enter Storage Capacity: "<<endl;
            cin>>c;
            string name;
            cout<<"Enter the name of the File..."<<endl;
            cin>>name;
            ifstream file(name);
            int temp;
            file>>n; 
            int i=0;
            while(file>>temp){
                weights.push_back(temp);
                list.insert({temp,i+1});
                i++;
            }
            cout<<"File Successfully Loaded and Data Stored.."<<endl<<endl;
        }

        for(int i=0;i<n;i++){
            wei_sum+=weights[i];
            if(weights[i]>max_wei){
                max_wei=weights[i];
            }
            if(weights[i]<min_wei){
                min_wei=weights[i];
            }
        }
        cout<<"Total Shipment Weight: "<<wei_sum<<endl;
        data+="Total Shipment Weight: "+to_string(wei_sum)+"\n";
        cout<<"Average Container Weight: "<<(float)wei_sum/n<<endl;
        data+="Average Container Weight: "+to_string((float)wei_sum/n)+"\n";
        cout<<"Heaviest Container: "<<max_wei<<endl;
        data+="Heaviest Container: "+to_string(max_wei)+"\n";
        cout<<"Lightest Container: "<<min_wei<<endl;
        data+="Lightest Container: "+to_string(min_wei)+"\n";
        if(wei_sum>=200){
            cout<<"Classification: Heavy"<<endl;
            data+="Classification: Heavy\n";
        }else{
            cout<<"Classification: Light"<<endl;
            data+="Classification: Light\n";
        }
        cout<<"Port Capacity: "<<c<<endl;
        if(wei_sum>c){
            cout<<"Status: Shipment exceeds port capacity."<<endl;
        }else{
            cout<<"Status: Shipment can be uploaded."<<endl;
        }
        cout<<endl;
        
        int choice2=0;
        //--------BUILDING ANOTHER MENU OF EXTRA FEATURES---------
        while(choice2!=6){
            cout<<"What do you want to do next?"<<endl<<endl;
            cout<<"To Display container weights in sorted order, Enter 1..."<<endl;
            cout<<"To Display a Bar Chart of Your Weights, Enter 2..."<<endl;
            cout<<"To Save this Report, Enter 3..."<<endl;
            cout<<"To Search for a container by weight,Enter 4..."<<endl;
            cout<<"To Find the Kth Heaviest Container, Enter 5..."<<endl;
            cout<<"If you dont want anything Extra, Enter 6..."<<endl;
            cout<<"What do you Choose?"<<endl;
            cin>>choice2;
            
            if(choice2==1){
                //-----SORTING--------
                merge_sort(weights,0,n-1);
                cout<<endl<<"Sorted Weights are:- ";
                for(int i=0;i<weights.size();i++){
                    cout<<weights[i]<<" ";
                }
                cout<<endl;
            }else if(choice2==2){
                //---------BAR CHART----------
                cout<<"Container Weight Bar Chart: "<<endl<<endl<<endl;
                for(int i=0;i<n;i++){
                    int w=weights[i]/5;
                    if(weights[i]%5!=0){
                        w+=1;
                    }
                    cout<<"Container "<<i+1<<"("<<weights[i]<<"): ";
                    for(int j=0;j<w;j++){
                        cout<<"*";
                    }
                    cout<<endl;
                }
                cout<<endl<<"(Where Each * Represents 5 units)"<<endl;
            }else if(choice2==3){
                //-------SAVING REPORT IN FILE---------
                string name;
                cout<<"Whats the Name of the file You Want?"<<endl;
                cin>>name;
                ofstream file(name);
                file<<data;
                cout<<"File successfully saved as "<<name<<endl;
                file.close();
            }else if(choice2==4){
                //-----SEARCHING CONTAINER BY WEIGHT-------
                int w;
                cout<<"Enter the Weight of the Container:- "<<endl;
                cin>>w;
                auto cont=list.find(w);
                if (cont!=list.end()) {
                    cout <<"Container "<<cont->second<<endl<<endl;
                }else {
                    cout <<"Container not found!"<<endl<<endl;
                }
            }else if(choice2==5){
                //-------SEARCHING KTH HEAVIEST CONTAINER--------
                merge_sort(weights,0,n-1);
                int k;
                cout<<"Enter K for the Kth Heaviest Container.."<<endl;
                cin>>k;
                if(k>n){
                    cout<<"Invalid input: Only "<<n<<" containers exist."<<endl;
                }
                else if(k<=0){
                    cout<<"Must have atleast one container.."<<endl;
                }
                else{
                    cout<<k<<"th Heaviest Container has weight:- "<<weights[n-k]<<endl;
                }
            }else if(choice2==6){
                break;
            }
        }
    }

    cout<<endl<<"Thank You For Choosing Smart Cargo Terminal! We Wish to Serve you Again! ";
    return 0;
}