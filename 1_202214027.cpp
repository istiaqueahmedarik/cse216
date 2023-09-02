#include <bits/stdc++.h>
template <class T>
class Heap
{
protected:
    T *heap;
    unsigned long long heapSize, lastLeafIndex;

    void heapSizeMaintainer()
    {
        if (heapSize > lastLeafIndex + 1)
            return;
        T *temp_heap = new T[2 * heapSize];
        heapSize *= 2;
        for (unsigned long long i = 0; i <= lastLeafIndex; i++)
            temp_heap[i] = heap[i];
        delete[] heap;
        heap = temp_heap;
    }
    static inline unsigned long long parent(unsigned long long i) { return i == 1 ? 1 : i / 2; }
    static inline unsigned long long left(unsigned long long i) { return i * 2; }
    static inline unsigned long long right(unsigned long long i) { return i * 2 + 1; }

    bool isPresent(unsigned long long i) { return i <= lastLeafIndex; }

    T minLimit() { return std::numeric_limits<T>::min(); }

    bool HeapProperty(unsigned long long i) { return heap[parent(i)] >= heap[i]; }

    T getMaxAmongParentAndChildren(unsigned long long i)
    {
        bool leftPresence = isPresent(left(i)), rightPresence = isPresent(right(i));
        return std::max({heap[i], leftPresence ? heap[left(i)] : minLimit(), rightPresence ? heap[right(i)] : minLimit()});
    }

    void down_hepify(unsigned long long i)
    {
        if (!isPresent(i))
            return;
        bool leftPresence = isPresent(left(i)), rightPresence = isPresent(right(i));
        T factor = getMaxAmongParentAndChildren(i);

        if (factor == heap[i])
            return;

        if (leftPresence and heap[left(i)] == factor)
            std::swap(heap[i], heap[left(i)]), down_hepify(left(i));

        else if (rightPresence and heap[right(i)] == factor)
            std::swap(heap[i], heap[right(i)]), down_hepify(right(i));
    }
    void up_heapify(unsigned long long i)
    {
        if (not isPresent(i))
            return;
        if (not HeapProperty(i))
            std::swap(heap[i], heap[parent(i)]), up_heapify(parent(i));
    }

public:
    // true means max heap and false means min heap
    Heap(unsigned long long size = 2) : heapSize(size), lastLeafIndex(0)
    {
        this->heap = new T[size];
    }
    Heap(const Heap &h) : heapSize(h.heapSize), lastLeafIndex(h.lastLeafIndex)
    {
        this->heap = new T[heapSize];
        for (unsigned long long i = 0; i <= lastLeafIndex; i++)
        {
            this->heap[i] = h.heap[i];
        }
        build_heap();
    }
    ~Heap() { delete[] heap; }

    void insert(T data)
    {
        heapSizeMaintainer();
        heap[++lastLeafIndex] = data;
        up_heapify(lastLeafIndex);
    }
    T top()
    {
        if (lastLeafIndex == 0)
        {
            std::cerr << "empty" << std::endl;
            throw std::runtime_error("empty!");
        }
        return heap[1];
    }
    void build_heap()
    {
        for (unsigned long long i = lastLeafIndex / 2; i > 0; i--)
            down_hepify(i);
    }

    void print(std::ostream &os = std::cout)
    {
        for (unsigned long long i = 1; i <= lastLeafIndex; i++)
            os << heap[i] << " ";
        os << std::endl;
    }
    unsigned long long size() { return lastLeafIndex; }
    bool empty() { return lastLeafIndex == 0; }
    void clear()
    {
        lastLeafIndex = 0;
        print();
    }
    T extractMax()
    {
        if (lastLeafIndex == 0)
        {
            std::cerr << "underflow" << std::endl;
            throw std::underflow_error("underflow");
        }
        T ret = heap[1];
        heap[1] = heap[lastLeafIndex--];
        down_hepify(1);
        return ret;
    }
};

template <class T>
class Priority_queue : Heap<T>
{
public:
    Priority_queue(bool IsMaxHeap = true) : Heap<T>(IsMaxHeap) {}
    void push(T data) { Heap<T>::insert(data); }
    T top() { return Heap<T>::top(); }
    void pop() { Heap<T>::pop(); }
    T extractMax() { return Heap<T>::extractMax(); }
    void print() { Heap<T>::print(); }
};
int main()
{
    Priority_queue<int> pq;
    while (1)
    {
        std::cout << "1: insert\n2: top\n3: extractMax\n4: print\n";
        int choice;
        std::cin >> choice;
        if (choice == 1)
        {
            int x;
            std::cout << "Value: ";
            std::cin >> x;
            pq.push(x);
        }
        else if (choice == 2)
        {
            std::cout << "Top: " << pq.top() << "\n";
        }
        else if (choice == 3)
        {
            std::cout << "Top: " << pq.extractMax() << "\n";
        }
        else if (choice == 4)
        {
            pq.print();
        }
        else
            break;
    }
}