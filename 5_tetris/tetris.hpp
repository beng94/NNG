#include <vector>
#include <memory>

class CharArray
{
    private:
        int n;
        std::unique_ptr<char[]> ptr;

    public:
        CharArray(int);
        CharArray(int, const CharArray&);
        CharArray(const CharArray&);

        CharArray& operator= (CharArray&);
        char* operator[] (int);
};

class Shape
{
    private:
        int n;
        CharArray array;

        bool first_col_empty();
        bool first_row_empty();
        bool last_row_empty();
        bool last_col_empty();
        int shift_left();
        int shift_up();
        int shift_right();
        int shift_down();
        bool surrounded(int, int);

    public:
        Shape() = delete;
        Shape(int);
        Shape(int, const Shape&);
        Shape(const Shape&);

        Shape& operator= (const Shape&);
        void shift_top_left();
        void print();
        Shape& rotate();
        bool has_hole();
        std::vector<Shape> extend();
};
