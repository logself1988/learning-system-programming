# Part II Input and Output

## 10 Input and Output Streams
### 10.1 Input and output
### 10.2 The I/O stream model

``` c++
istream
ostream
```

### 10.3 Files
### 10.4 Opening a file

``` c++
ifstream
ofstream
fstream
```

opening the file implicitly as part of the creation of an `ostream` or an `istream` and relying on the scope of the stream to take care of closing the file is the ideal.


### 10.5 Reading and writing a file
### 10.6 I/O error handling

stream state:

- `good()`: the operations succeeded.
- `eof()`: we hit end of input/file,
- `fail()`: something unexpected happened, e.g. we looked for a digit and found 'x',
- `bad()`: something unexpected and serious happend, e.g. a disk read error.

`clear()` with an argument actually setss the stream state flags (bits) mentioned and only clears flags not mentioned.

### 10.7 Reading a single value
### 10.8 User-defined output operators

``` c++
ostream& operator<<(ostream& os, const Date& d);
```

### 10.9 User-defined input operators

``` c++
istream& operator>>(istream& is, Date& dd);
```

### 10.10 A standard input loop

``` c++
istream ist;

ist.exceptions(ist.exceptions() | ios_base::badbit);

void end_of_loop(istream& ist, char teminator, const string& msg)
{
  if (ist.fail()) {
    ist.clear();
    char ch;
    if (ist >> ch && ch == teminator) return;
    error(msg);
  }
}


for(My_type var; ist >> var;) {
  // validation and usage of var
}

end_of_loop(ist, '|', "bad termination of file");
```

### 10.11 Reading a structured file

## 11 Customizing Input and Output
### 11.1 Regularity and irregularity
### 11.2 Output formatting

integer output:

``` c++
<< hex
<< oct
<< dec

<< showbase
<< nowshowbase
```

integer input:

``` c++
>> hex
>> oct
>> dec

cin.unsetf(ios::dec);
cin.unsetf(ios::oct);
cin.unsetf(ios::hex);
```

floating-point output:

``` c++
<< fixed
<< scientific
<< defaultfloat
```

precision:

``` c++
<< setprecision(5)
```

- `defaultfloat`: precision is the total number of digits,
- `scientific`: precision is the number of digits after the decimal point,
- `fixed`: precision is the number of digits after the decimal point.

fields:

``` c++
<< setw()
```


### 11.3 File opening and positioning

``` c++
ifstream
ofstream
fstream
```

file stream open modes:

- `ios_base::app`: append,
- `ios_base::ate`: at end,
- `ios_base::binary`: binary mode,
- `ios_base::in`: for reading,
- `ios_base::out`: for writing,
- `ios_base::trunc`: truncate file to 0 length.

read/get position, write/put position:

``` c++
seekg(int); // g for get
seekp(int); // p for put
```


### 11.4 String streams

``` c++
istringstream
ostringstream
stringstream
```

### 11.5 Line-oriented input

``` c++
std::getline(std::basic_istream, std::basic_string);
```

### 11.6 Character classification

``` c++
for(char ch; cin.get(ch);) {
  // ...
}
```

character classification:

``` c++
isspace(ch)   // whitespace
isalpha(ch)   // letter
isdigit(ch)   // decimal digit
isxdigit(ch)  // hexadecimal digit
isupper(ch)   // uppercase letter
islower(ch)   // lowercase letter
isalnum(ch)   // letter or decimal digit
iscntrl(ch)   // control character: ASCII 0..31, 127
ispunct(ch)   // not a letter, digit, whitespace, or invisible control character
isprint(ch)   // printable: ASCII ' '...'~'
isgraph(ch)   // isalpha(ch) or isdigit(ch) or ispunct(ch)
```

character case:

``` c++
toupper(ch)
tolower(ch)
```

### 11.7 Using nonstandard separators

``` c++
class Punct_stream {};
```

### 11.8 And there is so much more

## 12 A Display Model
### 12.1 Why graphics?
### 12.2 A display model
### 12.3 A first example
### 12.4 Using a GUI library
### 12.5 Coordinates

```
0------> x
|
v
y
```

### 12.6 Shapes


```
Window
|-- Simple_window

Point

Shape
|-- Line
|-- Lines
|-- Polygon
|-- Axis
|-- Rectangle
|-- Text
|-- Image

Line_style
Color

Button, In_box, Menu // GUI classes

Spline, Grid, Block_chart, Pie_chart
```


### 12.7 Using Shape primitives
### 12.8 Getting this to run

## 13 Graphics Classes
### 13.1 Overview of graphics classes

graphics interface classes:

|Name             |Description|
|:---             |:---|
|Color            | used for lines, text, and filling shapes|
|Line_style       | used to draw lines|
|Point            | used to expression location on a screen and winthin a `Window`|
|Line             | a line segment as we see it on the screen, defined by its two end `Point`s|
|Open_polyline    | a sequence of connected line segments defined bu a sequence of `Point`s|
|Closed_polyline  | like an `Open_polyline`, except that a line segment connects the last `Point` to the first|
|Polygon          | a `Closed_polyline` where no two line segments intersect|
|Text             | a string of characters|
|Lines            | a set of line segments defined by pairs of `Point`s|
|Rectangle        | a common shape optimized for quick and convenient display|
|Circle           | a circle defined by a center and a radius|
|Ellipse          | an ellipse defined by a center and two axes|
|Function         | a function of on variable graphaed in a range|
|Axis             | a labeled axis|
|Mark             | a point marked by a character, such as `x` or `o`|
|Makrs            | a sequence of points indicated by marks, such as `x` and `o`|
|Marked_polyline  | an `Open_polyline` with its points indicated by marks|
|Image            | the contents of an inage file|


GUI interface classes:

|Name             |Description|
|:---             |:---|
|Window           | an area of the screen in which we display our graphics objects|
|Simple_window    | a window with a "Next" button|
|Button           |a rectangle, usually labeled, in a window that wen can press to run one of our functions|
|In_box           | a box, usually labeled, in a window into which a use can type a string|
|Out_box          | a box, usually labeled, in a window into which out program can write a string|
|Menu             | a vector of `Button`s|

container of `Shape` or `Widget`:


|Name             |Description|
|:---             |:---|
|Vector_ref       | a `vector` with an interface that makes it convenient for holding unnamed elements|

### 13.2 Point and Line
### 13.3 Lines
### 13.4 Color
### 13.5 Line_style
### 13.6 Open_polyline
### 13.7 Closed_polyline
### 13.8 Polygon
### 13.9 Rectangle
### 13.10 Managing unnamed objects
### 13.11 Text
### 13.12 Circle
### 13.13 Ellipse
### 13.14 Marked_polyline
### 13.15 Marks
### 13.16 Mark
### 13.17 Images

## 14 Graphics Class Design
### 14.1 Design principles
### 14.2 Shape

``` c++
class Shape { // deals with color and style and holds sequence of lines
public:
  void draw() const;                  // deal with color and draw lines
  virtual void move(int dx, int dy);  // move the shape +=dx and +=dy

  void set_color(Color col);
  Color color() const;

  void set_style(Line_style sty);
  Line_style style() const;

  void set_fill_color(Color col);
  Color fill_color() const;

  Point point(int i) const;           // read-only access to points
  int number_of_points() const;

  Shape(const Shape&) = delete;             // copy construcotr, prevent copying
  Shape& operator=(const Shape&) = delete;  // copy assignment

  virtual ~Shape() { }                // virtual destructor

protected:
  Shape() { }                         // default constructor
  Shape(initializer_list<Point> lst); // initializer-list constructor: add() the Points to this Shape

  virtual void draw_lines() const;    // draw the appropriate lines
  void add(Point p);                  // add p to points
  void set_point(int i, Point p);     // points[i]=p;

private:
  vector<Point> points;               // not used by all shapes
  Color lcolor {fl_color()};          // color for lines and characters (with default)
  Line_style ls {0};
  Color fcolor {Color::invisible};    // fill color
};
```

the constructors are `protected`, means that they can only be used directly from classes derived from `Shape`.

access control: `private`, `protected`, `public`.

**overriding**: defining a function in a derived class so that it can be used through the interfaces provided by a base is called overriding.

### 14.3 Base and derived classes

**derivation**: a way to build one class from another so that the new class can be used in place of the original. often called **inheritance**.

**virtual functions**: the ability to define a function in a base class and have a function of the same name and type in a derived class called when a user calls the base class definition. ofen called **run-time polymorphism**, **dynamic dispatch**, or **run-time dispatch**.

**private and protected members**: keep the implementation details of our classes private to protect them from direct use that could complicate maintenance. often called **encapsulation**.

#### 14.3.1 Object layout

`vtbl`: virtual table, virtual function table

`vptr`: virtual pointer

#### 14.3.2 Deriving classes and defining virtual functions
#### 14.3.3 Overriding

`override`:

``` c++
struct B {
  virtual void f() const { cout << "B::f "; }
  void g() const { cout << "B::g "; }           // not virtual
};

struct D : B {
  void f() const override { cout << "D::f "; }  // overrides B::f
  void g() override { cout << "D::g "; }  // error: no virtual B::g to override
};
```

#### 14.3.4 Access
#### 14.3.5 Pure virtual functions

``` c++
class B {                 // abstract base class
public:
  virtual void f() = 0;   // pure virtual function
  virtual void g() = 0;
};

B b;  // error: B is abstract
```

``` c++
class D1: public B {
public:
  void f() override;
  void g() override;
};

D1 d1; // ok

class D2: public B {
public:
  void f() override;
  // no g();
};

D2 d2; // error: D2 is still abstract

class D3: public D2 {
public:
  void g() override;
};

D3 d3; // ok
```

### 14.4 Benefits of object-oriented programming

## 15 Graphing Functions and Data
### 15.1 Introduction
### 15.2 Graphing simple functions
### 15.3 Function

`Function` is a `Shape` with a constructor that generates a lot of line segments and stores them in its `Shape` part.

Those line segments approximate the values of function `f`, with range `[r1, r2)` and *x* coordinates scaled by `xscale`, *y* coordinates scaled by `yscale`.

``` c++
typedef double Fct (double);

Function (Fct f, double r1, double r2, Point orig, int count = 100,
          double xscale = 25, double yscale = 25);
```

default arguments: `count`, `xscale`, `yscale`; can only define default arguments for trailing parameters

lambda expression:

``` c++
[](double x) { return cos(x)+slope(x); }

// specify the return type explicitly
[](double x) -> double { return cos(x)+slope(x); }
```

### 15.4 Axis

An `Axis` consits of a line, a number of "notches" on that line, and a text label.

### 15.5 Approximation

animate:

$$
e^{x} = 1 + x + x^{2}/2! + x^{3}/3! + x^{4}/4! + \cdots
$$

### 15.6 Graphing data


## 16 Graphical User Interfaces
### 16.1 User interface alternatives
### 16.2 The “Next” button
### 16.3 A simple window
### 16.4 Button and other Widgets
### 16.5 An example
### 16.6 Control inversion
### 16.7 Adding a menu
### 16.8 Debugging GUI code
