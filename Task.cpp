/*
                     Solution of Assignment 3
                            Group A
  Made by
        Name                              ID            Section
        Mohamed Samy Abdelsalam Elsebaey  20200445      12
        Fouad Sayed Fouad Sayed           20200384      12

*/
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
class FloatArray{
protected:
    float *MyArray;
    int MaxArraySize;
    int CurrentArraySize;
public:
    FloatArray(int MaxArraySize){
        this->MaxArraySize=MaxArraySize;
        this->MyArray=new float[MaxArraySize];
        this->CurrentArraySize=0;
    }
    virtual void add(float value){
        if(CurrentArraySize<MaxArraySize){
            this->MyArray[CurrentArraySize]=value;
            CurrentArraySize++;
        }
    }
    friend istream&operator>>(istream &in,FloatArray &obj){
        float FloatValue;
        in>>FloatValue;
        obj.add(FloatValue);
        return in;
    }
    friend ostream&operator<<(ostream &out,const FloatArray &obj){
        out<<obj.CurrentArraySize<<"|\t";
        for(int i=0;i<obj.CurrentArraySize;i++){
            out<<obj.MyArray[i]<<"\t";
        }
        out<<"\n";
        return out;
    }
    ~FloatArray(){
        delete [] MyArray;
    }
};
class SortedArray:public FloatArray{
public:
    SortedArray(int max_array_size): FloatArray(max_array_size){}
    void add(float floatValue) override{
        if(CurrentArraySize<MaxArraySize){
            int i;
            for( i=CurrentArraySize-1;(i>=0 && this->MyArray[i]>floatValue);i--){
                this->MyArray[i+1]=this->MyArray[i];
            }
            this->MyArray[i+1]=floatValue;
            CurrentArraySize++;
        }
    }
};
class FrontArray:public FloatArray{
public:
    FrontArray(int max_array_size): FloatArray(max_array_size){}
    void add(float floatValue) override{
        if(CurrentArraySize<MaxArraySize){
            for(int i=CurrentArraySize-1;(i>=0);i--){
                this->MyArray[i+1]=this->MyArray[i];
            }
            this->MyArray[0]=floatValue;
            CurrentArraySize++;
        }
    }
};
class PositiveArray:public SortedArray{
public:
    PositiveArray(int max_array_size): SortedArray(max_array_size){}
    void add(float floatValue) override{
        if(CurrentArraySize<MaxArraySize){
            if(floatValue>0){
                SortedArray::add(floatValue);
            }
        }
    }
};
class NegativeArray:public SortedArray{
public:
    NegativeArray(int max_array_size): SortedArray(max_array_size){}
    void add(float floatValue) override{
        if(CurrentArraySize<MaxArraySize){
            if(floatValue<0){
                SortedArray::add(floatValue);
            }
        }
    }
};
int main() {
    string inputFileName ;
    cout<<"Enter the name of the input file:"<<"\n";
    cin>>inputFileName;
    ifstream inputFile(inputFileName);
    if(inputFile.fail()){
        cout<<"Failed to open the input file"<<"\n";
        exit(0);
    }
    string outputFileName;
    cout<<"Enter the name of the output file:"<<"\n";
    cin>>outputFileName;
    ofstream outputfile(outputFileName);
    if(outputfile.fail()){
        cout<<"Failed to open the output file"<<"\n";
        exit(0);
    }
    string inputFileLine;
    while(getline(inputFile,inputFileLine)){
        stringstream lineValues(inputFileLine);
        string arrayType;
        int inputFileLineSize;
        lineValues>>arrayType>>inputFileLineSize;
        if(arrayType=="Array"){
            FloatArray * floatArray=new FloatArray(inputFileLineSize);
            for(int i=0;i<inputFileLineSize;i++){
                lineValues>>*floatArray;
            }
            outputfile<<*floatArray;
            delete [] floatArray;
        }else if(arrayType=="Sorted"){
            FloatArray * floatArray=new SortedArray(inputFileLineSize);
            for(int i=0;i<inputFileLineSize;i++){
                lineValues>>*floatArray;
            }
            outputfile<<*floatArray;
            delete [] floatArray;
        }else if(arrayType=="Front"){
            FloatArray * floatArray=new FrontArray(inputFileLineSize);
            for(int i=0;i<inputFileLineSize;i++){
                lineValues>>*floatArray;
            }
            outputfile<<*floatArray;
            delete [] floatArray;
        }else if(arrayType=="Positive"){
            FloatArray * floatArray=new PositiveArray(inputFileLineSize);
            for(int i=0;i<inputFileLineSize;i++){
                lineValues>>*floatArray;
            }
            outputfile<<*floatArray;
            delete [] floatArray;
        }else if(arrayType=="Negative"){
            FloatArray * floatArray=new NegativeArray(inputFileLineSize);
            for(int i=0;i<inputFileLineSize;i++){
                lineValues>>*floatArray;
            }
            outputfile<<*floatArray;
            delete [] floatArray;
        }
    }
    return 0;
}
