#include "std_lib_facilities.h"

class Token
{
public:
  char kind; //<! kind of token: '(', ')', '+', '-', '*', '/', '8' (for number)
  double value; //!< for numbers: a value
  Token (char ch, double val) : kind (ch), value (val)
  {
    cout << "Token = '" << kind << "' " << value << '\n';
  }
  Token (char ch) : kind (ch), value (0)
  {
    cout << "Token = '" << kind << "' " << '\n';
  }
};

class Token_stream
{
public:
  Token_stream ();
  Token get ();           //<! get a Token
  void putback (Token t); //!< put a Token back

private:
  bool full{ false }; //!< is threre a Token in the buffer?
  Token buffer;       //!< where we keep a Token put back
};

Token_stream::Token_stream () : full (false), buffer ('\0') {}

Token
Token_stream::get ()
{
  if (full)
    {
      full = false;
      return buffer;
    }

  char ch;
  cin >> ch;

  switch (ch)
    {
    case ';': // for print
    case 'q': // for quit
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
      return Token{ ch };

    case '.':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      {
        cin.putback (ch); // put digit back into the input stream
        double val;
        cin >> val;
        return Token{ '8', val };
      }

    default:
      error ("Bad token");
    }
}

void
Token_stream::putback (Token t)
{
  if (full)
    error ("putback() into a full buffer");
  buffer = t;
  full = true;
}

Token_stream ts;
double expression ();

//! Primary:
//!   Number
//!   "(" Expression ")" // grouping
double
primary ()
{
  Token t = ts.get ();
  switch (t.kind)
    {
    case '(':
      {
        double d = expression ();
        t = ts.get ();
        if (t.kind != ')')
          error ("')' expected");
        return d;
      }
    case '8':
      return t.value;
    default:
      ostringstream os;
      os << "primary expected: '" << t.kind << "' " << t.value;
      error (os.str ());
    }
}

//! Term:
//!   Primary
//!   Primary "*" Term        // multiplication
//!   Primary "/" Term        // division
//!   Primary "%" Term        // remainder

double
term ()
{
  double left = primary ();
  Token t = ts.get ();
  while (true)
    {
      switch (t.kind)
        {
        case '*':
          left *= primary ();
          t = ts.get ();
          break;
        case '/':
          {
            double d = primary ();
            if (d == 0)
              error ("divide by zero");
            left /= d;
            t = ts.get ();
            break;
          }
        default:
          ts.putback (t);
          return left;
        }
    }
}

//! Expression:
//!   Term
//!   Term "+" Expression     // addition
//!   Term "-" Expression     // subtraction
double
expression ()
{
  double left = term ();
  Token t = ts.get ();

  while (true)
    {
      switch (t.kind)
        {
        case '+':
          left += term ();
          t = ts.get ();
          break;
        case '-':
          left -= term ();
          t = ts.get ();
          break;
        default:
          ts.putback (t);
          return left;
        }
    }
}

int
main (int argc, char const *argv[])
{
  try
    {
      double val = 0;
      while (cin)
        {
          Token t = ts.get ();

          if (t.kind == 'q')
            break; // 'q' for quit

          if (t.kind == ';')
            {
              cout << "=" << val << '\n'; // ';' for print now
              continue;
            }
          else
            ts.putback (t);

          val = expression ();
        }
      keep_window_open ();
    }
  catch (exception &e)
    {
      cerr << e.what () << '\n';
      keep_window_open ();
      return 1;
    }
  catch (...)
    {
      cerr << "exception \n";
      keep_window_open ();
      return 2;
    }
  return 0;
}
