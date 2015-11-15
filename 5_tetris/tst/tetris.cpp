#include "tetris.hpp"
#include <iostream>
#include <cstring>

Shape::Shape(const int& n) : n{n}
{
    for(int i = 0; i < 32; i++) ptr[i] = 0x0;
}

Shape::Shape(const Shape& rhs) : n{rhs.n}
{
    for(int i = 0; i < 32; i++)
    {
        ptr[i] = rhs.ptr[i];
    }
}

Shape& Shape::operator= (const Shape& rhs)
{
    n = rhs.n;

    for(int i = 0; i < 32; i++) ptr[i] = rhs.ptr[i];

    return *this;
}

unsigned int Shape::get_id(const int& n, const int& m) const
{
    return (ptr[n * 2 + m / 8] >> (8 - (m % 8) -1)) & 1;
}

void Shape::set_id(const int& n, const int& m, const int val)
{
    if(val == 1) ptr[n * 2 + m / 8] |= val << (8 - (m % 8) - 1);
    else
    {
        unsigned int mask = ~((1 << 9) | (1 << (8 - (m % 8) -1)));
        ptr[n * 2 + m / 8] &= mask;
    }
}

void Shape::shift_left()
{
    for(int i = 0; i < n * 2; i += 2)
    {
        ptr[i] <<= 1;
        set_id(i/2, 7, get_id(i/2, 8));
        ptr[i+1] <<= 1;
    }
}

void Shape::shift_right()
{
    for(int i = 0; i < n * 2; i += 2)
    {
        ptr[i + 1] >>= 1;
        set_id(i/2, 8, get_id(i/2, 7));
        ptr[i] >>= 1;
        set_id(i/2, 0, 0);
    }
}

void Shape::shift_up()
{
    //Shift every line but the last up by one
    for(int i = 0; i < (16 * 2) -1; i+=2)
    {
        ptr[i] = ptr[i+2];
        ptr[i + 1] = ptr[i + 3];
    }

    //Fill the last row with ' '
    ptr[30] = 0x0;
    ptr[31] = 0x0;
}

void Shape::shift_down()
{
    //Shift every line but the last up by one
    for(int i = n*2; i > 1; i -= 2)
    {
        ptr[i] = ptr[i - 2];
        ptr[i - 1] = ptr[i - 3];
    }

    //Fill the last row with ' '
    ptr[0] = 0x0;
    ptr[1] = 0x0;
}

bool Shape::first_row_empty()
{
    return ptr[0] == 0x0 && ptr[1] == 0;
}

bool Shape::first_col_empty()
{
    for(int i = 0; i < 16; i++)
    {
        if(get_id(i, 0) != 0) return false;
    }

    return true;
}

void Shape::shift_top_left()
{
    while(first_row_empty()) shift_up();
    while(first_col_empty()) shift_left();

}

void Shape::rotate()
{
    Shape tmp(n);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            tmp.set_id(i, j, get_id(n - (j + 1), i));
        }
    }

    *this = tmp;
    shift_top_left();
}

void Shape::print(int size)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            char c = get_id(i, j) == 0 ? ' ' : 'X';
            std::cout << c;
        }
        std::cout << std::endl;
    }
}

bool Shape::is_hole(int i, int j)
{
    if(i ==0 || j == 0 || i == 8 || j == 8) return false;

    bool a = true;
    if (get_id(i, j-1) == 0)
    {
        set_id(i, j, 1);
        a = is_hole(i, j-1);//bal
    }
    if (get_id(i-1, j) == 0)
    {
        set_id(i, j, 1);
        a &= is_hole(i-1, j);//fel
    }
    if (get_id(i, j+1) == 0)
    {
        set_id(i, j, 1);
        a &= is_hole(i, j+1);//jobb
    }
    if (get_id(i+1, j) == 0)
    {
        set_id(i,j, 1);
        a &= is_hole(i+1, j);//le
    }

    return a;
}


bool Shape::has_hole() const
{
    Shape tmp(*this);

    for (int i = 1; i < 7; i++)
    {
        for (int j = 1; j < 7; j++)
        {
            if (tmp.get_id(i, j) == 0)
            {
                if (tmp.is_hole(i,j)) return true;

            }
        }
    }

    return false;
}

bool Shape::operator< (const Shape& rhs) const
{
    int i =0;
    while(ptr[i] == rhs.ptr[i])
    {
        if(++i == 31) return false;
    }

    return ptr[i] > rhs.ptr[i];
}

bool Shape::operator== (const Shape& rhs) const
{
    for(int i = 0; i < 32; i++)
    {
        if(ptr[i] != rhs.ptr[i]) return false;
    }

    return true;
}

std::set<Shape> Shape::extend() const
{
    std::set<Shape> new_shapes;

    Shape cmp_shape(*this);
    int cnt = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            int n = i-j;
            int m = j;

            if(get_id(n,m) == 1)
            {
                cnt++;
                //Top
                cmp_shape.shift_down();
                cmp_shape.shift_down();
                if (cmp_shape.get_id(n + 2 -1, m) == 0)
                {
                    //Horizontal_1
                    //**
                    // X
                    cmp_shape.shift_right();
                    cmp_shape.shift_right();
                    if(cmp_shape.get_id(n+2-1, m + 2 -1) == 0)
                     {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n + 2 -1, m + 2 -1,1);
                        new_shape.set_id(n + 2 -1, m + 2, 1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                      }
                    }

                    //Horizontal_2
                    // **
                    // X
                    cmp_shape.shift_left(); //It should restore j index
                    cmp_shape.shift_left();
                    if(cmp_shape.get_id(n + 2 -1, j+1) == 0)
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n + 2 -1,m + 1,1);
                        new_shape.set_id(n + 2 -1, m, 1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                        }
                    }

                    //Vertical
                    // *
                    // *
                    // X
                    if(cmp_shape.get_id(n + 2-2, m) == 0)
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n + 2 -2, m, 1);
                        new_shape.set_id(n + 2 -1, m,1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                        }
                    }
                }

                //Down
                cmp_shape.shift_up(); //Should restore i
                cmp_shape.shift_up();
                if(cmp_shape.get_id(n+1,m) == 0)
                {
                    //Horizontal_1
                    // X
                    //**
                    cmp_shape.shift_right();
                    cmp_shape.shift_right();
                    if(cmp_shape.get_id(n+1, m + 2 -1) == 0)
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n + 1,m + 2 -1, 1);
                        new_shape.set_id(n + 1, m + 2, 1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                        }
                    }

                    cmp_shape.shift_left(); //Should restore j
                    cmp_shape.shift_left();
                    //Horizontal_2
                    // X
                    // **
                    if(cmp_shape.get_id(n+1, m+1) == 0)
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n+1, m+1, 1);
                        new_shape.set_id(n+1, m,1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                        }
                    }

                    //Vertical
                    // X
                    // *
                    // *
                    if(cmp_shape.get_id(n+2,m) == 0)
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n+1,m,1);
                        new_shape.set_id(n+2,m,1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                        }
                    }
                }

                //Left
                cmp_shape.shift_right();
                cmp_shape.shift_right();
                if(cmp_shape.get_id(n,m + 2 -1) == 0)
                {
                    //Vertical_1
                    // *
                    // *X
                    cmp_shape.shift_down();
                    cmp_shape.shift_down();
                    if(cmp_shape.get_id(n + 2- 1, m + 2 -1) == 0)
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n + 2 -1, m + 2 -1,1);
                        new_shape.set_id(n + 2,m + 2 -1, 1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                        }
                    }

                    //Vertical_2
                    // *X
                    // *
                    cmp_shape.shift_up(); //Should restore i
                    cmp_shape.shift_up();
                    if(cmp_shape.get_id(n + 1, m + 2 -1) == 0)
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n + 1, m + 2 -1,1);
                        new_shape.set_id(n, m + 2 -1, 1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                        }
                    }

                    //Horizontal
                    // **X
                    if(cmp_shape.get_id(n,m + 2 -2) == 0)
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n, m+ 2 -2, 1);
                        new_shape.set_id(n,m + 2 -1, 1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                        }
                    }
                }

                //Right
                cmp_shape.shift_left(); //Should restore j
                cmp_shape.shift_left();
                if(cmp_shape.get_id(n,m + 1) == 0)
                {
                    //Vertical_1
                    //  *
                    // X*
                    cmp_shape.shift_down();
                    cmp_shape.shift_down();
                    if(cmp_shape.get_id(n + 2 -1,m + 1) == 0)
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n + 2 -1, m + 1, 1);
                        new_shape.set_id(n + 2, m + 1, 1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                        }
                    }

                    //Vertical_2
                    // X*
                    //  *
                    cmp_shape.shift_up(); //Should restore i
                    cmp_shape.shift_up();
                    if(cmp_shape.get_id(n + 1,m + 1) == 0)
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n + 1, m + 1, 1);
                        new_shape.set_id(n, m + 1, 1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                        }
                    }

                    //Horizontal
                    // X**
                    if(cmp_shape.get_id(n,m + 2) == 0)
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n, m + 1, 1);
                        new_shape.set_id(n, m + 2, 1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                        }
                    }
                }
            }

            if(cnt == n * 2) break;
        }
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = n-1; j >= i; j--)
        {
            int n = i + (16-j);
            int m = j;
            if(get_id(n,m) == 1)
            {
                cnt++;
                //Top
                cmp_shape.shift_down();
                cmp_shape.shift_down();
                if (cmp_shape.get_id(n + 2 -1, m) == 0)
                {
                    //Horizontal_1
                    //**
                    // X
                    cmp_shape.shift_right();
                    cmp_shape.shift_right();
                    if(cmp_shape.get_id(n+2-1, m + 2 -1) == 0)
                     {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n + 2 -1, m + 2 -1,1);
                        new_shape.set_id(n + 2 -1, m + 2, 1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                      }
                    }

                    //Horizontal_2
                    // **
                    // X
                    cmp_shape.shift_left(); //It should restore j index
                    cmp_shape.shift_left();
                    if(cmp_shape.get_id(n + 2 -1, j+1) == 0)
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n + 2 -1,m + 1,1);
                        new_shape.set_id(n + 2 -1, m, 1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                        }
                    }

                    //Vertical
                    // *
                    // *
                    // X
                    if(cmp_shape.get_id(n + 2-2, m) == 0)
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n + 2 -2, m, 1);
                        new_shape.set_id(n + 2 -1, m,1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                        }
                    }
                }

                //Down
                cmp_shape.shift_up(); //Should restore i
                cmp_shape.shift_up();
                if(cmp_shape.get_id(n+1,m) == 0)
                {
                    //Horizontal_1
                    // X
                    //**
                    cmp_shape.shift_right();
                    cmp_shape.shift_right();
                    if(cmp_shape.get_id(n+1, m + 2 -1) == 0)
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n + 1,m + 2 -1, 1);
                        new_shape.set_id(n + 1, m + 2, 1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                        }
                    }

                    cmp_shape.shift_left(); //Should restore j
                    cmp_shape.shift_left();
                    //Horizontal_2
                    // X
                    // **
                    if(cmp_shape.get_id(n+1, m+1) == 0)
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n+1, m+1, 1);
                        new_shape.set_id(n+1, m,1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                        }
                    }

                    //Vertical
                    // X
                    // *
                    // *
                    if(cmp_shape.get_id(n+2,m) == 0)
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n+1,m,1);
                        new_shape.set_id(n+2,m,1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                        }
                    }
                }

                //Left
                cmp_shape.shift_right();
                cmp_shape.shift_right();
                if(cmp_shape.get_id(n,m + 2 -1) == 0)
                {
                    //Vertical_1
                    // *
                    // *X
                    cmp_shape.shift_down();
                    cmp_shape.shift_down();
                    if(cmp_shape.get_id(n + 2- 1, m + 2 -1) == 0)
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n + 2 -1, m + 2 -1,1);
                        new_shape.set_id(n + 2,m + 2 -1, 1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                        }
                    }

                    //Vertical_2
                    // *X
                    // *
                    cmp_shape.shift_up(); //Should restore i
                    cmp_shape.shift_up();
                    if(cmp_shape.get_id(n + 1, m + 2 -1) == 0)
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n + 1, m + 2 -1,1);
                        new_shape.set_id(n, m + 2 -1, 1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                        }
                    }

                    //Horizontal
                    // **X
                    if(cmp_shape.get_id(n,m + 2 -2) == 0)
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n, m+ 2 -2, 1);
                        new_shape.set_id(n,m + 2 -1, 1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                        }
                    }
                }

                //Right
                cmp_shape.shift_left(); //Should restore j
                cmp_shape.shift_left();
                if(cmp_shape.get_id(n,m + 1) == 0)
                {
                    //Vertical_1
                    //  *
                    // X*
                    cmp_shape.shift_down();
                    cmp_shape.shift_down();
                    if(cmp_shape.get_id(n + 2 -1,m + 1) == 0)
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n + 2 -1, m + 1, 1);
                        new_shape.set_id(n + 2, m + 1, 1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                        }
                    }

                    //Vertical_2
                    // X*
                    //  *
                    cmp_shape.shift_up(); //Should restore i
                    cmp_shape.shift_up();
                    if(cmp_shape.get_id(n + 1,m + 1) == 0)
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n + 1, m + 1, 1);
                        new_shape.set_id(n, m + 1, 1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                        }
                    }

                    //Horizontal
                    // X**
                    if(cmp_shape.get_id(n,m + 2) == 0)
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.set_id(n, m + 1, 1);
                        new_shape.set_id(n, m + 2, 1);
                        new_shape.shift_top_left();

                        if(!new_shape.has_hole())
                        {
                            new_shapes.insert(new_shape);
                        }
                    }
                }
            }

            if(cnt == n * 2) break;
        }
    }

    return new_shapes;
}
