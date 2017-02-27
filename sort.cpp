#include<iostream>
#include<vector>
#include <ctime>

using namespace std;

vector<int> data;

//RANDOM DATA GENERATOR AND OTHER HELPING FUNCTION

void generate_data(int size){
    srand(time(NULL));
    int inp;
    for(int i=0;i<size;i++){
        data.push_back(rand()%10000+1);
    }
}

void print_data(){
    for(int i=0;i<data.size();i++){
        cout<<data[i]<<" ";
    }
    cout<<endl;
}

bool is_sorted(){
    bool urut=true;
    for(int i=0;i<data.size()-1 && urut;i++){
        if(data[i]>data[i+1])
            urut=false;
    }
    return urut;
}

void swap(int i,int j){
    int temp=data[j];
    data[j]=data[i];
    data[i]=temp;
}


//MULAI BAGIAN SORTING
void selection_sort(){
    for(int i=0;i<data.size();i++){
        //pertama cari maksium
        int current_min=INT32_MAX;
        int current_min_id=i;
        for(int j=i;j<data.size();j++){
            if(data[j]<current_min){
                current_min=data[j];
                current_min_id=j;
            }
        }
        swap(i,current_min_id);
    }
}

void insertion_sort(){
    for(int i=0;i<data.size();i++){
        int j=i;
        while(j>0 && data[j]<data[j-1]){
            swap(j,j-1);
            j--;
        }
    }
}

void quick_sort(int left,int right){
    if(left<right){
        int wall=left-1;
        int pivot=right;
        int i=left;
        while(i<pivot){
            if(data[i]<data[pivot]){
                wall++;
                swap(i,wall);
            }
            i++;
        }
        swap(pivot,wall+1);
        quick_sort(left,wall);
        quick_sort(wall+2,right);
    }
}

void merge_sort(int left,int right){
    if(left<right){
        int mid=(left+right)/2;
        merge_sort(left,mid);
        merge_sort(mid+1,right);

        int* joined=new int[right-left+1];
        int joined_idx=0;
        int first_array_idx=left;
        int second_array_idx=mid+1;

        while(first_array_idx<=mid || second_array_idx<=right){
            if(first_array_idx==mid+1){
                //joined.push_back(data[second_array_idx]);
                joined[joined_idx++]=data[second_array_idx];
                second_array_idx++;
            }
            
            else if(second_array_idx==right+1){
                //joined.push_back(data[first_array_idx]);
                joined[joined_idx++]=data[first_array_idx];
                first_array_idx++;
            }

            else if(data[first_array_idx]<data[second_array_idx]){
                //joined.push_back(data[first_array_idx]);
                joined[joined_idx++]=data[first_array_idx];
                first_array_idx++;
            }

            else{
                //joined.push_back(data[second_array_idx]);
                joined[joined_idx++]=data[second_array_idx];
                second_array_idx++;
            }          
        }
         for(int i=left;i<=right;i++){
                data[i]=joined[i-left];
            }
         delete [] joined;
    }
}


//MAIN PROGRAM

int main(){
    generate_data(1000000);
    // print_data();

    clock_t start,end;
    start=clock();
    insertion_sort();
    end=clock();
    cout<<"lama waktu adalah: "<<(end-start)/(double) CLOCKS_PER_SEC<<endl<<endl;

    // print_data();
    if(is_sorted()){
        cout<<"array telah di sort";
    } 
    return 0;
}
