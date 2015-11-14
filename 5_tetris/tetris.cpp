#include "tetris.hpp"
#include <iostream>
#include <cstring>

CharArray::CharArray() : n{0}, ptr{nullptr} {}

CharArray::CharArray(int n) : n{n}
{
    ptr = std::unique_ptr<char[]>(new char[n*n + 1]);
    for(int i = 0; i < n*n; i++)
        ptr[i] = ' ';
    ptr[n*n] = '\0';
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
    ptr[n*n] = '\0';
}

CharArray::CharArray(const CharArray& rhs) : n{rhs.n}
{
    ptr = std::unique_ptr<char[]>(new char[n*n]);

    //Cant use operator= because of const in operator[]...
    for(int i = 0; i < n*n; i++)
    {
        ptr[i] = rhs.ptr[i];
    }
    ptr[n*n] = '\0';

}

CharArray& CharArray::operator= (CharArray& rhs)
{
    n = rhs.n;
    ptr = std::unique_ptr<char[]>(new char[n * n]);

    for(int i = 0; i< n*n; i++)
    {
        ptr[i] = rhs.ptr[i];
    }
    ptr[n*n] = '\0';

    return *this;
}

void CharArray::print()
{
    for(int i = 0; i < n; i++)
    {
        for(int j= 0; j <n ; j++)
        {
            std::cout << ptr[i*n + j] << " ";
        }
        std::cout << std::endl;
    }
}

bool CharArray::operator< (const CharArray& rhs) const
{
    return strcmp(ptr.get(), rhs.ptr.get()) < 0;
}

bool CharArray::operator== (const CharArray& rhs) const
{
    for(int i = 0; i < n * n; i++)
    {
        if(rhs.ptr[i] != ptr[i]) return false;
    }

    return true;
}

char* CharArray::operator[] (int row)
{
    return ptr.get() + row*n;
}

int CharArray::get_len() const
{
    return strlen(ptr.get());
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

bool Shape::operator< (const Shape& rhs) const
{
    return array < rhs.array;
}

//Parameter is not const because of the usage of operator[]
bool Shape::operator== (const Shape& rhs) const
{
    if (rhs.n != n) return false;

    return rhs.array == array;
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
            array[i][n - cnt - 1] = ' ';
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
        for(int i = 0; i < n-1; i++)
        {
            for(int j = 0; j < n; j++)
            {
                array[i][j] = array[i + 1][j];
            }
        }

        //Fill the last row with ' '
        for(int i = 0; i < n; i++)
        {
            array[n - cnt -1][i] = ' ';
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
            array[i][cnt] = ' ';
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
    new_shapes.reserve(100);
    //For each X in the matrix check top, down, left, right
    int cnt = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(cmp_shape.array[i][j] == 'X')
            {
                cnt++;
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

                        if(!this->has_hole())
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

                        if(!this->has_hole())
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

                        if(!this->has_hole())
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

                        if(!this->has_hole())
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

                        if(!this->has_hole())
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

                        if(!this->has_hole())
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

                        if(!this->has_hole())
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

                        if(!this->has_hole())
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

                        if(!this->has_hole())
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

                        if(!this->has_hole())
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

                        if(!this->has_hole())
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

                        if(!this->has_hole())
                        {
                            new_shape.shift_top_left();
                            new_shapes.push_back(new_shape);
                        }
                    }
                }
            }

            if(cnt == n * 2) break;
        }
    }

    return new_shapes;
}

int Shape::get_len() const
{
    return array.get_len();
}
