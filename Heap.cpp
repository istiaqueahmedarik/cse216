#include <bits/stdc++.h>
template <class T>
class Heap
{
    T *heap;
    unsigned long long heapSize, lastLeafIndex;
    bool IsMaxHeap;

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
    Heap(unsigned long long size = 2, bool IsMaxHeap = true) : heapSize(size), lastLeafIndex(0)
    {
        this->IsMaxHeap = IsMaxHeap;
        this->heap = new T[size];
    }
    Heap(bool IsMaxHeap) : heapSize(2), lastLeafIndex(0)
    {
        this->IsMaxHeap = IsMaxHeap;
        this->heap = new T[2];
    }
    Heap(const Heap &h) : heapSize(h.heapSize), lastLeafIndex(h.lastLeafIndex)
    {
        this->IsMaxHeap = h.IsMaxHeap;
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
            return IsMaxHeap ? maxLimit() : minLimit();
        return heap[1];
    }
    void build_heap()
    {
        for (unsigned long long i = lastLeafIndex / 2; i > 0; i--)
            down_hepify(i);
    }

    void pop() { erase(1); }

    void erase(unsigned long long idx)
    {
        if (idx > lastLeafIndex)
        {
            std::cerr << "Heap index out of range" << std::endl;
            throw std::runtime_error("Heap index out of range");
        }

        std::swap(heap[idx], heap[lastLeafIndex--]);
        if (IsMaxHeap)
            (heap[lastLeafIndex + 1] > heap[idx]) ? down_hepify(idx) : up_heapify(idx);
        else
            (heap[lastLeafIndex + 1] < heap[idx]) ? down_hepify(idx) : up_heapify(idx);
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
    void sort()
    {
        int n = lastLeafIndex;
        for (int i = 1; i <= n; i++)
            erase(1);
        lastLeafIndex = n;
        print();
        build_heap();
    }
    T extractMax()
    {
        if (is_min_heap())
        {
            change_IsMaxHeap();
            T ret = top();
            pop();
            change_IsMaxHeap();
            return ret;
        }
        T ret = top();
        pop();
        return ret;
    }
    T extractMin()
    {
        if (is_max_heap())
        {
            change_IsMaxHeap();
            T ret = top();
            pop();
            change_IsMaxHeap();
            return ret;
        }
        T ret = top();
        pop();
        return ret;
    }
};
int main()
{
    Heap<int> h(false);
    h.insert(2);
    h.insert(13);
    h.insert(12);
    h.insert(11);
    h.insert(1);

    // h.pop();
    h.print();
    h.change_IsMaxHeap();
    h.print();
    std::cout << h.extractMin() << std::endl;
}