
template<typename T> struct treeNode{
    T data;
    treeNode * left;
    treeNode * right;
};

template <typename T> class BST {
    public:
        int numNodes;
        treeNode * head;
        
        void add(T data);
        void print();
        void remove(T data);
        void find(T data);

};
