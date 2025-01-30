Floating Point Conversion
=========================

![IEEE 754 Diagram](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d2/Float_example.svg/1180px-Float_example.svg.png)

This assignment demonstrates converting from a floating point number to an integer using only integer and bitwise operations.

Learning Objectives
-------------------

After completing this assignment, students will be able to:

- Use bitwise operations to mask bit fields
- Access the individual components of floating point numbers
- Convert floating point numbers to integers

Task
----

You will create implementations for the following functions:

- `is_negative`
- `get_raw_exponent`
- `get_exponent`
- `get_raw_mantissa`
- `get_mantissa`
- `float_to_int`

The first five functions provide the framework to create a software-based float to int converter. These function will then be combined to create a float to int converter in the function `float_to_int`.

This [tool](https://www.h-schmidt.net/FloatConverter/IEEE754.html) may be useful for exploring floating point numbers.

Implementation Notes
--------------------

The [IEEE Standard for Floating-Point Arithmetic](https://en.wikipedia.org/wiki/IEEE_754) includes a number of special cases. The implementation in this assignment need only properly handle [normal numbers](https://en.wikipedia.org/wiki/Normal_number_(computing)). It could be extended to support other numbers, such as [zero](https://en.wikipedia.org/wiki/Signed_zero).

Testing
-------

The included makefile will build the fp.c file and run a series of tests to confirm that a valid implementation has been added to the file. The tests can be run by executing:

```
make test
```

It is strongly recommend to read the tests included at the bottom of the `fp.c` program in order to help understand the specification for each of the functions to be implemented.
