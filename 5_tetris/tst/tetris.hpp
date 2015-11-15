#include <set>
#include <memory>

class Shape
{
    private:
        int n;
        char ptr[32];

        bool first_row_empty();
        bool first_col_empty();
        void shift_left();
        void shift_right();
        void shift_up();
        void shift_down();
        void shift_top_left();
        bool is_hole(int, int);

    public:
        Shape(const int& n);
        Shape(const Shape&);

        Shape& operator= (const Shape&);
        bool operator< (const Shape&) const;
        bool operator== (const Shape&) const;
        void print(int size);
        void rotate();
        std::set<Shape> extend() const;
        bool has_hole() const;
        unsigned int get_id(const int&, const int&) const;
        void set_id(const int&, const int&, const int);
};
