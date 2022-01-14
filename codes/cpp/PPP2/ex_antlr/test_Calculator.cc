#include "CalculatorBaseVisitor.h"
#include "CalculatorLexer.h"
#include "CalculatorParser.h"
#include "antlr4-runtime.h"
#include <cmath>
#include <exception>
#include <iostream>
#include <map>
#include <string>

using namespace antlr4;

using std::cout;

class SyntaxError : public std::exception
{
public:
  SyntaxError (std::string m) : msg (m){};
  const char *
  what () const throw ()
  {
    return msg.c_str ();
  }

private:
  std::string msg;
};

class MyCalculatorVisitor : public CalculatorBaseVisitor
{
public:
  antlrcpp::Any
  visitCalculation (CalculatorParser::CalculationContext *ctx) override
  {
    std::vector<tree::ParseTree *> parseTrees = ctx->children;
    if (parseTrees.size () == 1 && parseTrees[0]->getText () == "q")
      {
        cout << "quit" << '\n';
        return antlrcpp::Any{ "quit" };
      }

    if (ctx->calculation () != NULL)
      {
        visitCalculation (ctx->calculation ());
        visitStatement (ctx->statement ());
      }
    else
      {
        visitStatement (ctx->statement ());
      }

    return antlrcpp::Any{ "Calculation" };
  }

  antlrcpp::Any
  visitStatement (CalculatorParser::StatementContext *ctx) override
  {
    if (ctx->declaration () != NULL)
      {
        antlrcpp::Any result = visitDeclaration (ctx->declaration ());
        cout << result.as<std::string> () << '\n';
        return result;
      }
    else
      {
        antlrcpp::Any result = visitExpression (ctx->expression ());
        cout << "=" << result.as<double> () << '\n';
        return result;
      }
  }

  antlrcpp::Any
  visitDeclaration (CalculatorParser::DeclarationContext *ctx) override
  {
    std::string name = ctx->NAME ()->getText ();
    std::map<std::string, double>::iterator iter = symbol_table.find (name);
    if (iter != symbol_table.end ())
      {
        throw SyntaxError{ "Symbol '" + name + "' already defined" };
      }

    antlrcpp::Any expression = visitExpression (ctx->expression ());
    double value = expression.as<double> ();
    symbol_table[name] = value;
    return antlrcpp::Any{ "Declaration: NAME=" + name
                          + ", value=" + std::to_string (value) };
  }

  antlrcpp::Any
  visitExpression (CalculatorParser::ExpressionContext *ctx) override
  {

    if (ctx->expression () == NULL)
      {
        return visitTerm (ctx->term ());
      }
    else
      {
        antlrcpp::Any term = visitTerm (ctx->term ());
        antlrcpp::Any expression = visitExpression (ctx->expression ());
        tree::ParseTree *secondChild = ctx->children[1];
        std::string op = secondChild->getText ();
        cout << "visitExpression: " << expression.as<double> () << " " << op
             << " " << term.as<double> () << '\n';
        if (op == "+")
          return antlrcpp::Any{ expression.as<double> ()
                                + term.as<double> () };

        else if (op == "-")
          return antlrcpp::Any{ expression.as<double> ()
                                - term.as<double> () };
        else
          throw SyntaxError{ "visitExpression: Invalid op " + op };
      }
  }

  antlrcpp::Any
  visitTerm (CalculatorParser::TermContext *ctx) override
  {
    if (ctx->term () == NULL)
      {
        return visitPrimary (ctx->primary ());
      }
    else
      {
        antlrcpp::Any primary = visitPrimary (ctx->primary ());
        antlrcpp::Any term = visitTerm (ctx->term ());
        tree::ParseTree *secondChild = ctx->children[1];
        std::string op = secondChild->getText ();
        if (op == "*")
          {
            return antlrcpp::Any{ primary.as<double> () * term.as<double> () };
          }
        else if (op == "/")
          {
            if (0 == term.as<double> ())
              throw SyntaxError ("divide zero");
            return antlrcpp::Any{ primary.as<double> () / term.as<double> () };
          }
        else if (op == "%")
          {
            if (0 == term.as<double> ())
              throw SyntaxError ("module zero");
            return antlrcpp::Any{ std::fmod (primary.as<double> (),
                                             term.as<double> ()) };
          }
        else
          {
            throw SyntaxError{ "Invalid op: " + op };
          }
      }
  }

  antlrcpp::Any
  visitPrimary (CalculatorParser::PrimaryContext *ctx) override
  {
    if (ctx->NUMBER () != NULL)
      {
        double number = stod (ctx->NUMBER ()->getText ());
        cout << "visitPrimary: NUMBER=" << number << '\n';
        return antlrcpp::Any{ number };
      }

    if (ctx->NAME () != NULL)
      {
        std::string name = ctx->NAME ()->getText ();
        cout << "visitPrimary: NAME=" << name << '\n';
        std::map<std::string, double>::iterator iter
            = symbol_table.find (name);
        if (iter == symbol_table.end ())
          {
            throw SyntaxError{ name + " not found" };
          }
        else
          {
            double value = iter->second;
            cout << "visitPrimary: NAME=" << name << ", value=" << value
                 << '\n';
            return antlrcpp::Any{ value };
          }
      }

    std::string firstToken = ctx->getStart ()->getText ();
    if (firstToken == "(")
      {
        return visitExpression (ctx->expression ());
      }

    else if (firstToken == "-")
      {
        antlrcpp::Any expression = visitPrimary (ctx->primary ());
        return antlrcpp::Any{ -1 * expression.as<double> () };
      }
    else
      {
        return visitPrimary (ctx->primary ());
      }
  }

private:
  std::map<std::string, double> symbol_table;
};

int
main (int argc, char const *argv[])
{
  // std::ifstream stream;
  // stream.open (argv[1]);
  // ANTLRInputStream input (stream);

  std::ostringstream stream;
  stream << "1-2-3; let a=1; a-2-3;";
  ANTLRInputStream input (stream.str ());
  CalculatorLexer lexer (&input);
  CommonTokenStream tokens (&lexer);
  CalculatorParser parser (&tokens);

  tree::ParseTree *tree = parser.calculation ();
  MyCalculatorVisitor visitor;
  visitor.visit (tree);
}