#include<iostream>
#include<vector>
#include <ctime>

using namespace std;

vector<int> sdata;
vector<int> data;

//RANDOM DATA GENERATOR AND OTHER HELPING FUNCTION

void generate_seed_data(int size){
    srand(time(NULL));
    int inp;
    for(int i=0;i<size;i++){
        sdata.push_back(rand()%(10*size)+1);
    }
}

void reset_data(){
    data.clear();
    for(int i=0;i<sdata.size();i++){
        data.push_back(sdata[i]);
    }
}

void print_data(){
    for(int i=0;i<data.size();i++){
        cout<<data[i]<<endl;
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

//selection sort
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

//insertion sort
void insertion_sort(){
   int i,j,sekarang;
   for (i =0;i<data.size();i++) {
       sekarang = data[i];
       j = i-1;
       while (j>=0 && data[j]>sekarang){
           data[j+1]=data[j];
           j=j-1;
       }
       data[j+1] = sekarang;
   }
}

//quick sort
void quick_sort(int left,int right){
    if(left<right){
        int wall=left-1;
        int pivot=(right+left)/2;
        int i=left;
        while(i<right){
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

//merge sort
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
     int banyak;
     cin>>banyak;
    generate_seed_data(banyak);

    reset_data();
    clock_t start,end;
    start=clock();
    selection_sort();
    end=clock();
    print_data();
    cout<<"lama waktu selection sort adalah: "<<(end-start)/(double) CLOCKS_PER_SEC<<" detik"<<endl<<endl;

    reset_data();
    clock_t start2,end2;
    start2=clock();
    insertion_sort();
    end2=clock();
    cout<<"lama waktu insertion sort adalah: "<<(end2-start2)/(double) CLOCKS_PER_SEC<<" detik"<<endl<<endl;

    reset_data();
    clock_t start3,end3;
    start3=clock();
    merge_sort(0,data.size()-1);
    end3=clock();
    cout<<"lama waktu merge sort adalah: "<<(end3-start3)/(double) CLOCKS_PER_SEC<<" detik"<<endl<<endl;

    reset_data();
    clock_t start4,end4;
    start4=clock();
    quick_sort(0,data.size()-1);
    end4=clock();
    cout<<"lama waktu quick sort adalah: "<<(end4-start4)/(double) CLOCKS_PER_SEC<<" detik"<<endl<<endl;
    return 0;
}
