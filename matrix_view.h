#include <iterator>

template<class T>
struct MatrixView {
    struct StepIterator {
        using self_type = StepIterator;
        using value_type = typename T::value_type;
        using reference = typename T::reference;
        using const_reference = typename T::const_reference;
        using pointer = typename T::pointer;
        using const_pointer = typename T::const_pointer;
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = int;
       
        StepIterator(pointer ptr, difference_type idx, difference_type step): _ptr(ptr), _idx(idx), _step(step) {}
        StepIterator(const self_type& other) = default;
        self_type& operator=(const self_type& other) = default;

        reference operator*() { return _ptr[_idx]; }
        const_reference operator*() const { return _ptr[_idx]; }
        pointer operator->() { return _ptr + _idx; }
        const pointer operator->() const { return _ptr + _idx; }

        // arithmetic
        //self_type& operator+=(const difference_type& rhs) {_idx += _step * rhs; return *this;}
        //self_type& operator-=(const difference_type& rhs) {_idx -= _step * rhs; return *this;}
        self_type operator++(int) { self_type i = *this; _idx += _step; return i; }
        self_type operator++() { _idx += _step; return *this; }
        self_type operator--(int) { self_type i = *this; _idx -= _step; return i; }
        self_type operator--() { _idx -= _step; return *this; }
        //difference_type operator-(const self_type& rhs) {return (_idx - rhs.idx) / _step;}
        //self_type operator+(const int& rhs) {return self_type(_idx + rhs, _step);}
        //self_type operator-(const int& rhs) {return self_type(_idx - rhs, _step);}


        // comparison
        bool operator==(const self_type& rhs) { return _idx == rhs._idx; }
        bool operator!=(const self_type& rhs) { return !(*this == rhs); }
        /*inline bool operator>(const self_type& rhs) {return _idx > rhs._idx;}
        inline bool operator<(const self_type& rhs) {return _idx < rhs._idx;}
        inline bool operator>=(const self_type& rhs) {return _idx >= rhs._idx;}
        inline bool operator<=(const self_type& rhs) {return _idx <= rhs._idx;}*/
        

        pointer _ptr;
        difference_type _idx;
        difference_type _step;
    };

    MatrixView (T& data, int width, int height) : _data(data), _width(width), _height(height) {}

    StepIterator begin_row(int idx) { return StepIterator(&_data[0], idx * _width, 1); }
    StepIterator end_row(int idx) { return StepIterator(&_data[0], (idx + 1) * _width, 1); }
    StepIterator begin_col(int idx) { return StepIterator(&_data[0], idx, _width); }
    StepIterator end_col(int idx) { return StepIterator(&_data[0], _width * _height + idx, _width); }

    void print() const {
        for (int i = 0; i < _height; ++i) {
            for (int j = 0; j < _width; ++j) {
                cout << _data[i * _width + j] << '\t';
            }
            cout << '\n';
        }
    }

    T& _data;
    int _width;
    int _height;
};
