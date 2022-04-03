#include<bits/stdc++.h>
using namespace std;
class Bucket{
    public:
    int localDepth;
    int bucketCapacity;
    vector<int> keys;
    Bucket(int localDepth,int bucketCapacity){
       this->localDepth= localDepth;
       this->bucketCapacity = bucketCapacity;
    }
};
class HashTable{
    int bucketCapacity;
    int globalDepth;
    int numBuckets;
    int numDirectory;
    vector<int> directory;
    vector<Bucket> buckets;
    // The hashing function
    int hash(int x){
        int h = 0;
        int pow = 1;
        for(int i=0; i<globalDepth; i++){
            int bit  = (1<<i & x)?1:0;
            h+=pow*bit;
            pow*=2;
        }
        return h;
    }
    public:
    HashTable(int globalDepth, int bucketCapacity){
        this->bucketCapacity = bucketCapacity;
        this->globalDepth = globalDepth;
        this->numDirectory = (1<<globalDepth);
        this->numBuckets = (1<<globalDepth);
        for(int i=0; i<numBuckets; i++){
            buckets.push_back(Bucket(globalDepth,bucketCapacity));
        }
        for(int i=0; i<numDirectory; i++){
            directory.push_back(i);
        }
    }
    void insertKey(int x){
        if(globalDepth<20){
            int dirIndex = hash(x);
            int idx = directory[dirIndex];
            if(buckets[idx].keys.size()<bucketCapacity){
                buckets[idx].keys.push_back(x);
            }else{
                /*
                    Now there are two possible cases
                    1. local depth of the bucket that is going to split is less than the global depth
                    2. local depth of the current bucket is equals to the global depth
                    -- in case-1 we have to just split the bucket and store all increase the local depth by 1
                    -- in case-2 we have to dotwo things
                    a) split the bucket and store all increase the local depth by 1
                    b) double the size of directory
                */
                if(buckets[idx].localDepth==globalDepth){
                    for(int i=0; i<numDirectory; i++){
                        directory.push_back(directory[i]);
                    }
                    globalDepth++;
                    numDirectory = (1<<globalDepth);
                }
                vector<int> temp;
                for(int i=0; i<bucketCapacity; i++){
                    temp.push_back(buckets[idx].keys[bucketCapacity-1-i]);
                    buckets[idx].keys.pop_back();
                    buckets[idx];
                }
                temp.push_back(x);
                buckets[idx].localDepth++;
                buckets.push_back(Bucket(buckets[idx].localDepth,bucketCapacity));
                if(buckets[idx].localDepth==globalDepth){
                    directory[numDirectory/2 + dirIndex] = buckets.size()-1;
                }else{
                    directory[numDirectory + dirIndex] = buckets.size()-1;
                }
                for(auto y : temp)
                    insertKey(y);
                numBuckets++;
            }
        }
    }
    bool searchKey(int x){
        int dirIndex = hash(x);
        int idx = directory[dirIndex];
        for(int i=0; i<buckets[idx].keys.size(); i++){
            if(buckets[idx].keys[i]==x)
            return true;
        }
        return false;
    }
    bool deleteKey(int x){
        int dirIndex = hash(x);
        int idx = directory[dirIndex];
        for(int i=0; i<buckets[idx].keys.size(); i++){
            if(buckets[idx].keys[i]==x){
                buckets[idx].keys.erase(buckets[idx].keys.begin()+i);
                return true;
            }
        }
        return false;

    }
    void display(){
        cout<<globalDepth<<"\n";
        cout<<buckets.size()<<"\n";
        for(auto bucket : buckets){
            cout<<bucket.keys.size()<<" "<<bucket.localDepth<<"\n";
        }
    }
    void displayDirectory(){
        for(int i=0; i<directory.size(); i++)
            cout<<directory[i]<<"\n";

    }

};

int main(){
    int globalDepth;
    int bucketCapacity;
    cin>>globalDepth;
    cin>>bucketCapacity;
    int operation;
    int x;
    HashTable table(globalDepth,bucketCapacity);
    while(1){
        cin>>operation;
        switch(operation){
            case 2: { // Insert new value
                cin>>x;
                table.insertKey(x);
            }
            break;
            case 3: { // Search a value
                cin>>x;
                bool isFind = table.searchKey(x);
                // if(isFind)
                // cout<<"Yes, "<<x<<" is present in the hashtable\n";
                // else
                // cout<<"No, "<<x<<" is not present in the hashtable\n";
            }
            break;
            case 4: { // Delete a value
                cin>>x;
                table.deleteKey(x);
            }
            break;
            case 5: { // Display status of the hash table
               table.display();
            }
            break;
            case 6: { // Quit
                return 0;
            }
        }
    }

}
