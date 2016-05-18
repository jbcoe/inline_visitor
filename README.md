Inline Visitor
==============

This is an implementation of "Defining Visitors Inline in Modern C++" from ACCU
Overload 123 by Robert Mill and Jonathan Coe.            

[http://accu.org/index.php/articles/2021]

# Building tests
The inline visitor is a header-only library and as such does not need building.
We have written tests using the Catch testing framework which can be built and
run (from OS X or Linux) using:

```
./scripts/build.py -t
```

CMake, Python 2.7 and a C++14 compiler are required.

Catch is included as an external library using git submodules.

#Continuous integration
**Build status (on Travis-CI):** [![Build Status](https://travis-ci.org/jbcoe/inline_visitor.svg?branch=master)](https://travis-ci.org/jbcoe/inline_visitor)

# Feedback
We welcome feedback concerning the use of this library.

Please use the github issues list to post bugs/requests/questions.
