# MyTest Library

This library started as a little uni project developed for the following reasons:
- wanting to put software engeneering skills to use (and mainly understanding if I was able to develop any of those skills);
- wanting to develop a test library to then use as a building block for a more developed testing suite.

It shouldn't be considered as a bomb-proof test framework, that was never in the plans.

The principles I tried to follow:
- this library should be as platform indipendent as possible;
- this library should try to organize tests in a simple structure, giving
developers the possibility to group tests together inside categories;
- each test should be able to return a report detailing the test results
and its status;
- each test unit should be written directly by the developers using the library.

## Structure

This library follows a simple design: 

the **inc/** and **src/** folders contain respectively the library's interfaces and implementations, while the **test/** folder contains a simple test suite meant to both test the library (the "test library's tests" ;D) and show a way you could utilize it.