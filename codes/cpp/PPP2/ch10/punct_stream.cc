#include "std_lib_facilities.h"

class Punct_stream
{
public:
  Punct_stream (istream &is) : source (is), sensitive (true) {}

  void
  whitespace (const string &s)
  {
    white = s;
  }
  void
  add_white (char c)
  {
    white += c;
  }
  bool is_whitespace (char c);
  void
  case_sensitive (bool b)
  {
    sensitive = b;
  }
  Punct_stream &operator>> (string &s);
  operator bool ();

private:
  istream &source;      //<! character source
  istringstream buffer; //<! use buffer for formating
  string white;         //<! characters considered whitespace
  bool sensitive;       //<! is stream case sensitive?
};

Punct_stream &
Punct_stream::operator>> (string &s)
{
  while (!(buffer >> s))
    {
      if (buffer.bad () || !source.good ())
        return *this;
      buffer.clear ();

      string line;
      getline (source, line); // get a line from source

      // do character replacement as needed
      for (char &ch : line)
        {
          if (is_whitespace (ch))
            ch = ' ';
          else if (!sensitive)
            ch = tolower (ch);
        }
      buffer.str (line); // put string into stream
    }
  return *this;
}

bool
Punct_stream::is_whitespace (char c)
{
  for (char w : white)
    if (c == w)
      return true;
  return false;
}

Punct_stream::operator bool ()
{
  return !(source.fail () || source.bad ()) && source.good ();
}

int
main (int argc, char const *argv[])
{
  Punct_stream ps{ cin };
  ps.whitespace (";:,.?!()\"{}<>/&$@#%^*|~");
  ps.case_sensitive (false);

  cout << "please enter words\n";

  vector<string> words;
  for (string word; ps >> word;)
    words.push_back (word);

  sort (words.begin (), words.end ()); // sort words

  // for (const string &word : words)
  //   cout << word << '\n';
  for (int i = 0; i < words.size (); i++)
    {
      if (i == 0 || words[i] != words[i - 1])
        cout << words[i] << '\n';
    }

  return 0;
}
