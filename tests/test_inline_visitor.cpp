#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
#include <catch.hpp>
#include "inline_visitor/inline_visitor.h"
#include <string>

using namespace std::string_literals;

struct ShapeVisitor;
struct Shape {
  virtual ~Shape() = default;
  virtual void Accept(ShapeVisitor &v) const = 0;
};

struct Circle;
struct Triangle;
struct Square;

struct ShapeVisitor {
  virtual ~ShapeVisitor() = default;
  virtual void Visit(const Circle&) = 0;
  virtual void Visit(const Triangle&) = 0;
  virtual void Visit(const Square&) = 0;
};

struct Square : Shape {
  void Accept(ShapeVisitor &v) const final { v.Visit(*this); }
};
struct Circle : Shape {
  void Accept(ShapeVisitor &v) const final { v.Visit(*this); }
};
struct Triangle : Shape {
  void Accept(ShapeVisitor &v) const final { v.Visit(*this); }
};

TEST_CASE("Inline visitor can identify all types", "[inline_visitor]") 
{
  int sides = 1;

  auto v = begin_visitor<ShapeVisitor>()
               .on<const Circle>([&sides](const Circle &) { sides = 1; })
               .on<const Square>([&sides](const Square &) { sides = 4; })
               .on<const Triangle>([&sides](const Triangle &) { sides = 3; })
               .end_visitor();

  Circle().Accept(v);
  REQUIRE(sides == 1);
  
  Square().Accept(v);
  REQUIRE(sides == 4);
  
  Triangle().Accept(v);
  REQUIRE(sides == 3);
}
