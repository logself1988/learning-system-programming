#include "std_lib_facilities.h"

const char tok_number = '8';
const char tok_quit = 'q';
const char tok_print = ';';
const char tok_name = 'a'; //!< name token
const char tok_let = 'L';  //!< declaration token

const string prompt = "> ";
const string result = "= ";
const string declkey = "let"; //!< declaration keyword

class Token
{
public:
  char kind; //<! kind of token: '(', ')', '+', '-', '*', '/', '8' (for number)
  double value; //!< for numbers: a value
  string name;
  Token (char ch, double val) : kind (ch), value (val)
  {
#ifdef PPP2_DEBUG
    cout << "Token = '" << kind << "' " << value << '\n';
#endif
  }
  Token (char ch) : kind (ch), value (0)
  {
#ifdef PPP2_DEBUG
    cout << "Token = '" << kind << "' " << '\n';
#endif
  }
  Token (char ch, string n) : kind (ch), name (n)
  {
#ifdef PPP2_DEBUG
    cout << "Token = '" << kind << "' " << name << '\n';
#endif
  }
};

class Variable
{
public:
  Variable (string n, double v);
  string name;
  double value;
};

Variable::Variable (string n, double v) : name (n), value (v)
{
#ifdef PPP2_DEBUG
  cout << "Variable = '" << name << "' " << value << '\n';
#endif
}

vector<Variable> var_table;

double
get_value (string s)
{
  for (const Variable &v : var_table)
    {
      if (v.name == s)
        return v.value;
    }

  error ("get: undefined variable ", s);
}

void
set_value (string s, double d)
{
  for (Variable &v : var_table)
    {
      if (v.name == s)
        {
          v.value = d;
          return;
        }
    }
  error ("set: undefined variable ", s);
}

bool
is_declared (string var)
{
  for (const Variable &v : var_table)
    {
      if (v.name == var)
        return true;
    }
  return false;
}

double
define_name (string var, double val)
{
  if (is_declared (var))
    error (var, " declared twice");
  var_table.push_back (Variable (var, val));
  return val;
}

class Token_stream
{
public:
  Token_stream ();
  Token get ();           //<! get a Token
  void putback (Token t); //!< put a Token back
  void ignore (char c);   //!< discard characters up to and including a c
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
    case tok_print:
    case tok_quit:
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '=':
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
        return Token{ tok_number, val };
      }

    default:
      if (isalpha (ch))
        {
          string s;
          s += ch;
          while (cin.get (ch) && (isalpha (ch) || isdigit (ch)))
            s += ch;
          cin.putback (ch);
          if (s == declkey)
            return Token (tok_let);
          return Token (tok_name, s);
        }
      error ("Bad token: ", to_string (ch));
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

void
Token_stream::ignore (char c)
{
  if (full && c == buffer.kind) // look in buffer
    {
      full = false;
      return;
    }

  full = false;

  char ch = 0;
  while (cin >> ch) // search input
    {
      if (ch == c)
        return;
    }
}

Token_stream ts;
double expression ();

//! Primary:
//!   Number
//!   Name
//!   "(" Expression ")" // grouping
//!   "-" Primary
//!   "+" Primary
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
    case tok_number:
      return t.value;
    case tok_name:
      return get_value (t.name);
    case '-':
      return -primary ();
    case '+':
      return primary ();
    default:
      ostringstream os;
      os << "primary expected, but '" << t.kind << "' " << t.value;
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
        case '%':
          {
            double d = primary ();
            if (d == 0)
              error ("module by zero");
            left = fmod (left, d);
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

void
clean_up_mess ()
{
  ts.ignore (tok_print);
}

//! Declaration:
//!   "let" Name "=" Expression
double
declaration ()
{
  Token t = ts.get ();
  if (t.kind != tok_name)
    error ("name expected in declaration, but", t.kind);
  string var_name = t.name;

  Token t2 = ts.get ();
  if (t2.kind != '=')
    error ("= missing in declaration of", var_name);

  double d = expression ();
  define_name (var_name, d);

  return d;
}

//! Statement:
//!   Declaration
//!   Expression
double
statement ()
{
  Token t = ts.get ();
  switch (t.kind)
    {
    case tok_let:
      return declaration ();
    default:
      ts.putback (t);
      return expression ();
    }
}

//! Calculation:
//!   Statement
//!   Print
//!   Quit
//!   Calculation Statement
void
calculate ()
{
  while (cin)
    {
      try
        {
          cout << prompt;

          Token t = ts.get ();

          while (t.kind == tok_print) // eat print token
            t = ts.get ();

          if (t.kind == tok_quit)
            return;

          ts.putback (t);
          cout << result << statement () << '\n';
        }
      catch (exception &e)
        {
          cerr << e.what () << '\n';
          clean_up_mess ();
        }
    }
}

int
main (int argc, char const *argv[])
{
  try
    {
      // predefined names:
      define_name ("pi", 3.1415926535);
      define_name ("e", 2.7182818284);

      calculate ();
      keep_window_open ();
      return 0;
    }
  catch (exception &e)
    {
      cerr << e.what () << '\n';
      keep_window_open ("~~");
      return 1;
    }
  catch (...)
    {
      cerr << "exception \n";
      keep_window_open ("~~");
      return 2;
    }
}
