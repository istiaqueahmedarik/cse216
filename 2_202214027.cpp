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

    T minLimit() { return std::numeric_limits<T>::min(); }

    bool HeapProperty(unsigned long long i) { return heap[parent(i)] >= heap[i]; }

    Node<T> getMaxAmongParentAndChildren(unsigned long long i)
    {
        bool leftPresence = isPresent(left(i)), rightPresence = isPresent(right(i));
        Node<T> ret = heap[i];
        if (leftPresence && ret < heap[left(i)])
            ret = heap[left(i)];
        if (rightPresence && ret < heap[right(i)])
            ret = heap[right(i)];
        return ret;
    }

    void down_hepify(unsigned long long i)
    {
        if (!isPresent(i))
            return;
        bool leftPresence = isPresent(left(i)), rightPresence = isPresent(right(i));
        Node<T> factor = getMaxAmongParentAndChildren(i);

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
    Priority_queue(unsigned long long size = 2) : heapSize(size), lastLeafIndex(0)
    {
        this->heap = new Node<T>[size];
    }
    Priority_queue(const Priority_queue &h) : heapSize(h.heapSize), lastLeafIndex(h.lastLeafIndex)
    {
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
            std::cerr << "No element in priority queue" << std::endl;
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
            os << heap[i].value << " ";
        os << std::endl;
    }
    unsigned long long size() { return lastLeafIndex; }
    bool empty() { return lastLeafIndex == 0; }
    void clear()
    {
        lastLeafIndex = 0;
        print();
    }
    Node<T> extractMax()
    {

        if (lastLeafIndex == 0)
        {
            std::cerr << "underflow" << std::endl;
            throw std::underflow_error("underflow");
        }
        Node<T> ret = heap[1];
        heap[1] = heap[lastLeafIndex--];
        down_hepify(1);
        return ret;
    }
    void push(T data, int priority)
    {
        heapSizeMaintainer();
        heap[++lastLeafIndex] = Node<T>(data, minLimit());
        increase_key(lastLeafIndex, priority);
    }
    void increase_key(int idx, int priority)
    {
        if (heap[idx].priority > priority)
        {
            std::cerr << "Given priority is smaller then previous" << std::endl;
            throw std::runtime_error("Given priority is smaller then previous");
        }
        heap[idx].priority = priority;
        up_heapify(idx);
    }
};
int main()
{
    Priority_queue<int> pq;
    while (1)
    {
        std::cout << "1: insert\n2: top\n3: extractMax\n4: print\n5: increase_key";
        int choice;
        std::cin >> choice;
        if (choice == 1)
        {
            int x;
            std::cout << "Value: ";
            std::cin >> x;
            int y;
            std::cout << "Key: ";
            std::cin >> y;
            pq.push(x, y);
        }
        else if (choice == 2)
        {
            std::cout << "Top: " << pq.top().value << "\n";
        }
        else if (choice == 3)
        {
            std::cout << "Top: " << pq.extractMax().value << "\n";
        }
        else if (choice == 4)
        {
            pq.print();
        }
        else if (choice == 5)
        {
            int x;
            std::cout << "Index: ";
            std::cin >> x;
            int y;
            std::cout << "Key: ";
            std::cin >> y;
            pq.increase_key(x, y);
        }
        else
            break;
    }
}