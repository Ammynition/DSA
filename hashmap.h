#define STARTING_CAPACITY 8

struct bucket{
    string key;
    void * value;
};

class hash_map{
    public:
        
        vector<bucket<K, V>> buckets;
        size_t (*hash_function)(K key);

        hash_map(size_t (*hash_function)(K key)) {
            this.hash_function = hash_function;
            buckets.resize(STARTING_CAPACITY);
        }






}
