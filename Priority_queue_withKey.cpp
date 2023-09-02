#include <bits/stdc++.h>
template <class A>
class Node
{
public:
    A value;
    int priority;
    Node(A value) : value(value), priority(0) {}
    Node(A value = 0, int priority = 0) : value(value), priority(priority) {}
    bool operator<(Node b) { return priority < b.priority; }
    bool operator<=(Node b) { return priority <= b.priority; }
    bool operator>(Node b) { return priority > b.priority; }
    bool operator>=(Node b) { return priority >= b.priority; }
    bool operator==(Node b) { return priority == b.priority; }
};

template <class T>
class Priority_queue
{
    Node<T> *heap;
    unsigned long long heapSize, lastLeafIndex;
    bool IsMaxHeap;

    void heapSizeMaintainer()
    {
        if (heapSize > lastLeafIndex + 1)
            return;
        Node<T> *temp_heap = new Node<T>[2 * heapSize];
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

    T maxLimit() { return std::numeric_limits<T>::max(); }
    T minLimit() { return std::numeric_limits<T>::min(); }

    bool HeapProperty(unsigned long long i) { return IsMaxHeap ? heap[parent(i)] >= heap[i] : heap[parent(i)] <= heap[i]; }

    T getMinAmongParentAndChildren(unsigned long long i)
    {
        bool leftPresence = isPresent(left(i)), rightPresence = isPresent(right(i));
        return std::min({heap[i], leftPresence ? heap[left(i)] : maxLimit(), rightPresence ? heap[right(i)] : maxLimit()});
    }

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
        T factor = IsMaxHeap ? getMaxAmongParentAndChildren(i) : getMinAmongParentAndChildren(i);

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
    Priority_queue(unsigned long long size = 2, bool IsMaxHeap = true) : heapSize(size), lastLeafIndex(0)
    {
        this->IsMaxHeap = IsMaxHeap;
        this->heap = new Node<T>[size];
    }
    Priority_queue(bool IsMaxHeap) : heapSize(2), lastLeafIndex(0)
    {
        this->IsMaxHeap = IsMaxHeap;
        this->heap = new Node<T>[2];
    }
    Priority_queue(const Priority_queue &h) : heapSize(h.heapSize), lastLeafIndex(h.lastLeafIndex)
    {
        this->IsMaxHeap = h.IsMaxHeap;
        this->heap = new Node<T>[heapSize];
        for (unsigned long long i = 0; i <= lastLeafIndex; i++)
            this->heap[i] = h.heap[i];
        build_heap();
    }
    ~Priority_queue() { delete[] heap; }

    Node<T> top()
    {
        if (lastLeafIndex == 0)
        {
            std::cerr << "No element in priority queu" << std::endl;
            throw std::runtime_error("Empty priority queue");
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
    bool is_max_heap() { return IsMaxHeap; }
    bool is_min_heap() { return !IsMaxHeap; }
    void change_IsMaxHeap()
    {
        IsMaxHeap = !IsMaxHeap;
        build_heap();
    }
    void clear()
    {
        lastLeafIndex = 0;
        print();
    }
    Node<T> extractMax()
    {
        if (is_min_heap())
        {
            std::cerr << "max_heap" << std::endl;
            throw std::logic_error();
        }
        if (lastLeafIndex == 0)
        {
            std::cerr << "underflow" << std::endl;
            throw std::underflow_error();
        }
        Node<T> ret = heap[1];
        heap[1] = heap[lastLeafIndex--];
        down_hepify(1);
        return ret;
    }
    Node<T> extractMin()
    {
        if (is_max_heap())
        {
            std::cerr << "min_heap" << std::endl;
            throw std::logic_error();
        }
        if (lastLeafIndex == 0)
        {
            std::cerr << "underflow" << std::endl;
            throw std::underflow_error();
        }
        Node<T> ret = heap[1];
        heap[1] = heap[lastLeafIndex--];
        down_hepify(1);
        return ret;
    }
    void push(T data, int priority)
    {
        heapSizeMaintainer();
        heap[++lastLeafIndex] = IsMaxHeap ? Node<T>(data, minLimit()) : Node<T>(data, maxLimit());
        increase_key(lastLeafIndex, priority);
    }
    void increase_key(int idx, int priority)
    {
        if (IsMaxHeap and heap[idx].priority > priority)
        {
            std::cerr << "Given priority is smaller then previous" << std::endl;
            throw std::runtime_error("Given priority is smaller then previous");
        }
        if (not IsMaxHeap and heap[idx].priority < priority)
        {
            std::cerr << "Given priority is greater then previous" << std::endl;
            throw std::runtime_error("Given priority is greater then previous");
        }
        heap[idx].priority = priority;
        up_heapify(idx);
    }
};
int main()
{
    Priority_queue<int> pq;
    pq.push(10, 5);
    pq.push(2, 1);
    std::cout << pq.top().value << std::endl;
}