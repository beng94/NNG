#include "tetris.hpp"
#include <iostream>

CharArray::CharArray(int n) : n{n}
{
    ptr = std::unique_ptr<char[]>(new char[n*n]);
    for(int i = 0; i < n*n; i++)
        ptr[i] = ' ';
}

CharArray::CharArray(int n, const CharArray& rhs) : CharArray{n}
{
    for(int i = 0; i < rhs.n; i++)
    {
        for(int j = 0; j < rhs.n; j++)
        {
            ptr[i * rhs.n + i * 2 + j] = rhs.ptr[i * rhs.n + j];
        }
    }
}

CharArray::CharArray(const CharArray& rhs) : CharArray{n}
{
    //Cant use operator= because of const in operator[]...
    for(int i = 0; i < n*n; i++)
    {
        ptr[i] = rhs.ptr[i];
    }
}

CharArray& CharArray::operator= (CharArray& rhs)
{
    for(int i = 0; i< n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            (*this)[i][j] = rhs[i][j];
        }
    }

    return *this;
}

char* CharArray::operator[] (int row)
{
    return ptr.get() + row*n;
}

Shape::Shape(int n, bool init) : n{n}, array{n}
{
    if(init)
    {
        array[0][0] = 'X';
        array[0][1] = 'X';
    }
}

Shape::Shape(int n, const Shape& rhs) : n{n}, array{n, rhs.array} {}

Shape::Shape(const Shape& rhs) : n{rhs.n}, array{rhs.array} {}

Shape& Shape::operator= (Shape& rhs)
{
    n = rhs.n;
    array = rhs.array;

    return *this;
}

//Parameter is not const because of the usage of operator[]
bool Shape::operator== (Shape& rhs)
{
    if (rhs.n != n) return false;

    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            if(array[i][j] != rhs.array[i][j]) return false;
        }
    }

    return true;
}

void Shape::print()
{
    for(int i = 0; i < n; i++)
    {
        for(int j =0; j < n; j++)
        {
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool Shape::first_col_empty()
{
    for(int i = 0; i < n; i++)
    {
        if (array[i][0] == 'X') return false;
    }

    return true;
}

bool Shape::first_row_empty()
{
    for(int i = 0; i < n; i++)
    {
        if (array[0][i] == 'X') return false;
    }

    return true;
}

bool Shape::last_col_empty()
{
    for(int i = 0; i < n; i++)
    {
        if(array[i][n-1] == 'X') return false;
    }

    return true;
}

bool Shape::last_row_empty()
{
    for(int i = 0; i < n; i++)
    {
        if(array[n-1][i] == 'X') return false;
    }

    return true;
}

int Shape::shift_left()
{
    int cnt = 0;
    while (this->first_col_empty())
    {
        //Shift every column but the last to the left by one
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n-1; j++)
            {
                array[i][j] = array[i][j + 1];
            }
        }

        //Fill the last col with ' '
        for(int i = 0; i < n; i++)
        {
            array[i][n-1] = ' ';
        }

        cnt++;
    }

    return cnt;
}

int Shape::shift_up()
{
    int cnt = 0;
    while (this->first_row_empty())
    {
        //Shift every line but the last up by one
        for(int i = 0; i < n -1; i++)
        {
            for(int j = 0; j < n; j++)
            {
                array[i][j] = array[i + 1][j];
            }
        }

        //Fill the last row with ' '
        for(int i = 0; i < n; i++)
        {
            array[n-1][i] = ' ';
        }

        cnt++;
    }

    return cnt;
}

int Shape::shift_right()
{
    int cnt = 0;
    while (this->last_col_empty())
    {
        //Shift every column but the last to the right by one
        for(int i = 0; i < n; i++)
        {
            for(int j = n -1; j > 0; j--)
            {
                array[i][j] = array[i][j - 1];
            }
        }

        //Fill the first col with ' '
        for(int i = 0; i < n; i++)
        {
            array[i][0] = ' ';
        }

        cnt++;
    }

    return cnt;
}

int Shape::shift_down()
{
    int cnt = 0;
    while (this->last_row_empty())
    {
        //Shift every line but the last up by one
        for(int i = n - 1; i > cnt; i--)
        {
            for(int j = 0; j < n; j++)
            {
                array[i][j] = array[i - 1][j];
            }
        }

        //Fill the first row with ' '
        for(int i = 0; i < n; i++)
        {
            array[cnt][i] = ' ';
        }

        cnt++;
    }

    return cnt;
}

void Shape::shift_top_left()
{
    this->shift_left();
    this->shift_up();
}

Shape& Shape::rotate()
{
    CharArray tmp(n);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            tmp[i][j] = array[n - (j + 1)][i];
        }
    }

    array = tmp;

    this->shift_top_left();

    return *this;
}

bool Shape::surrounded(int n, int m)
{
    return array[n-1][m] == 'X' && array[n+1][m] == 'X' &&
           array[n][m-1] == 'X' && array[n][m+1] == 'X';
}

bool Shape::has_hole()
{
    for (int i = 1; i < n-1; i++)
    {
        for (int j = 1; j < n-1; j++)
        {
            if (this->surrounded(i, j)) return true;
        }
    }

    return false;
}

std::vector<Shape> Shape::extend()
{
    Shape cmp_shape(n + 2, *this);

    std::vector<Shape> new_shapes;
    //For each X in the matrix check top, down, left, right
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(cmp_shape.array[i][j] == 'X')
            {
                //Top
                int down = cmp_shape.shift_down();
                if (cmp_shape.array[i + down - 1][j] == ' ')
                {
                    //Horizontal_1
                    //**
                    // X
                    int right = cmp_shape.shift_right();
                    if(cmp_shape.array[i + down -1][j + right - 1] == ' ')
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.array[i + down -1][j + right -1] = 'X';
                        new_shape.array[i + down -1][j + right] = 'X';
                        new_shape.shift_top_left();

                        if(!this->has_hole() &&
                           !new_shape.exists(new_shapes))
                        {
                            new_shape.shift_top_left();
                            new_shapes.push_back(new_shape);
                        }
                    }

                    //Horizontal_2
                    // **
                    // X
                    cmp_shape.shift_left(); //It should restore j index
                    if(cmp_shape.array[i + down -1][j + 1] == ' ')
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.array[i + down -1][j + 1] = 'X';
                        new_shape.array[i + down -1][j] = 'X';
                        new_shape.shift_top_left();

                        if(!this->has_hole() &&
                           !new_shape.exists(new_shapes))
                        {
                            new_shape.shift_top_left();
                            new_shapes.push_back(new_shape);
                        }
                    }

                    //Vertical
                    // *
                    // *
                    // X
                    if(cmp_shape.array[i + down-2][j] == ' ')
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.array[i + down -2][j] = 'X';
                        new_shape.array[i + down -1][j] = 'X';
                        new_shape.shift_top_left();

                        if(!this->has_hole() &&
                           !new_shape.exists(new_shapes))
                        {
                            new_shape.shift_top_left();
                            new_shapes.push_back(new_shape);
                        }
                    }
                }

                //Down
                cmp_shape.shift_up(); //Should restore i
                if(cmp_shape.array[i+1][j] == ' ')
                {
                    //Horizontal_1
                    // X
                    //**
                    int right = cmp_shape.shift_right();
                    if(cmp_shape.array[i+1][j + right -1] == ' ')
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.array[i + 1][j + right -1] = 'X';
                        new_shape.array[i + 1][j + right] = 'X';
                        new_shape.shift_top_left();

                        if(!this->has_hole() &&
                           !new_shape.exists(new_shapes))
                         {
                            new_shape.shift_top_left();
                            new_shapes.push_back(new_shape);
                        }
                    }

                    cmp_shape.shift_left(); //Should restore j
                    //Horizontal_2
                    // X
                    // **
                    if(cmp_shape.array[i+1][j+1] == ' ')
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.array[i+1][j+1] = 'X';
                        new_shape.array[i+1][j] = 'X';
                        new_shape.shift_top_left();

                        if(!this->has_hole() &&
                           !new_shape.exists(new_shapes))
                        {
                            new_shape.shift_top_left();
                            new_shapes.push_back(new_shape);
                        }
                    }

                    //Vertical
                    // X
                    // *
                    // *
                    if(cmp_shape.array[i+2][j] == ' ')
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.array[i+1][j] = 'X';
                        new_shape.array[i+2][j] = 'X';
                        new_shape.shift_top_left();

                        if(!this->has_hole() &&
                           !new_shape.exists(new_shapes))
                        {
                            new_shape.shift_top_left();
                            new_shapes.push_back(new_shape);
                        }
                    }
                }

                //Left
                int right = cmp_shape.shift_right();
                if(cmp_shape.array[i][j + right -1] == ' ')
                {
                    //Vertical_1
                    // *
                    // *X
                    int down = cmp_shape.shift_down();
                    if(cmp_shape.array[i + down - 1][j + right -1] == ' ')
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.array[i + down -1][j + right -1] = 'X';
                        new_shape.array[i + down][j + right -1] = 'X';
                        new_shape.shift_top_left();

                        if(!this->has_hole() &&
                           !new_shape.exists(new_shapes))
                        {
                            new_shape.shift_top_left();
                            new_shapes.push_back(new_shape);
                        }
                    }

                    //Vertical_2
                    // *X
                    // *
                    cmp_shape.shift_up(); //Should restore i
                    if(cmp_shape.array[i + 1][j + right -1] == ' ')
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.array[i + 1][j + right -1] = 'X';
                        new_shape.array[i][j + right -1] = 'X';
                        new_shape.shift_top_left();

                        if(!this->has_hole() &&
                           !new_shape.exists(new_shapes))
                        {
                            new_shape.shift_top_left();
                            new_shapes.push_back(new_shape);
                        }
                    }

                    //Horizontal
                    // **X
                    if(cmp_shape.array[i][j + right -2] == ' ')
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.array[i][j + right -2] = 'X';
                        new_shape.array[i][j + right -1] = 'X';
                        new_shape.shift_top_left();

                        if(!this->has_hole() &&
                           !new_shape.exists(new_shapes))
                        {
                            new_shape.shift_top_left();
                            new_shapes.push_back(new_shape);
                        }
                    }
                }

                //Right
                cmp_shape.shift_left(); //Should restore j
                if(cmp_shape.array[i][j + 1] == ' ')
                {
                    //Vertical_1
                    //  *
                    // X*
                    int down = cmp_shape.shift_down();
                    if(cmp_shape.array[i + down -1][j + 1] == ' ')
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.array[i + down -1][j + 1] = 'X';
                        new_shape.array[i + down][j + 1] = 'X';
                        new_shape.shift_top_left();

                        if(!this->has_hole() &&
                           !new_shape.exists(new_shapes))
                        {
                            new_shape.shift_top_left();
                            new_shapes.push_back(new_shape);
                        }
                    }

                    //Vertical_2
                    // X*
                    //  *
                    cmp_shape.shift_up(); //Should restore i
                    if(cmp_shape.array[i + 1][j + 1] == ' ')
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.array[i + 1][j + 1] = 'X';
                        new_shape.array[i][j + 1] = 'X';
                        new_shape.shift_top_left();

                        if(!this->has_hole() &&
                           !new_shape.exists(new_shapes))
                        {
                            new_shape.shift_top_left();
                            new_shapes.push_back(new_shape);
                        }
                    }

                    //Horizontal
                    // X**
                    if(cmp_shape.array[i][j + 2] == ' ')
                    {
                        Shape new_shape(cmp_shape);
                        new_shape.array[i][j + 1] = 'X';
                        new_shape.array[i][j + 2] = 'X';
                        new_shape.shift_top_left();

                        if(!this->has_hole() &&
                           !new_shape.exists(new_shapes))
                        {
                            new_shape.shift_top_left();
                            new_shapes.push_back(new_shape);
                        }
                    }
                }
            }
        }
    }

    return new_shapes;
}

//TODO: make sure parameters remain const
//Parameter is copied so I can rotate it
bool Shape::equals(Shape rhs)
{
    if (rhs == *this) return true;
    else if(rhs.rotate() == *this) return true;
    else if(rhs.rotate() == *this) return true;
    else if(rhs.rotate() == *this) return true;

    return false;
}

bool Shape::exists(std::vector<Shape>& vec)
{
    for(auto s: vec)
    {
        if(this->equals(s)) return true;
    }

    return false;
}
