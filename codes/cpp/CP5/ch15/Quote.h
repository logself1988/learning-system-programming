#ifndef CH15_QUOTE
#define CH15_QUOTE

#include <string>

class Quote {
public:
  Quote() = default;
  Quote(const std::string &book, double sales_price)
      : bookNo(book), price(sales_price) {}

  std::string isbn() { return bookNo; }

  //!< return the total sales price for the specified number of items
  virtual double net_price(std::size_t n) const { return n * price; }

  virtual ~Quote() = default; //!< dynamic binding for the dtor

private:
  std::string bookNo; //!< ISBN number of this item

protected:
  double price = 0.0; //!< normal, undiscounted price
};

// class Bulk_quote : public Quote {
// public:
//   Bulk_quote() = default;
//   Bulk_quote(const std::string book, double p, std::size_t qty, double disc)
//       : Quote(book, p), min_qty(qty), discount(disc) {}

//   double net_price(std::size_t) const override;

// private:
//   std::size_t min_qty = 0; //!< minimum purchase for the discount to apply
//   double discount = 0.0;   //!< fractional discount to apply
// };

// double Bulk_quote::net_price(std::size_t cnt) const {
//   if (cnt >= min_qty) {
//     return cnt * (1 - discount) * price;
//   } else {
//     return cnt * price;
//   }
// }

//! pricing strategies using discout rate and quantity
class Disc_quote : public Quote {
public:
  Disc_quote() = default;
  Disc_quote(const std::string &book, double price, std::size_t qty,
             double disc)
      : Quote(book, price), quantity(qty), discount(disc) {}

  double net_price(std::size_t) const = 0; //!< pure virtual function

  std::pair<size_t, double> discount_policy() const {
    return {quantity, discount};
  }

protected:
  std::size_t quantity = 0; //!< purchase size for the discount to apply
  double discount = 0.0;    //!< fractional discount to apply
};

//! reimplementation
class Bulk_quote : public Disc_quote {
public:
  Bulk_quote() = default;
  Bulk_quote(const std::string book, double p, std::size_t qty, double disc)
      : Disc_quote(book, p, qty, disc) {}

  double net_price(std::size_t) const override;
};

double Bulk_quote::net_price(std::size_t cnt) const {
  if (cnt >= quantity) {
    return cnt * (1 - discount) * price;
  } else {
    return cnt * price;
  }
}

#endif /* CH15_QUOTE */
