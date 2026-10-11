> [!NOTE]
> **Seamwork transition — ABSORB.** This repository is no longer an active standalone product. Useful dice/randomness/domain behavior is being absorbed into focused Seamwork studies rather than maintained as a standalone general-purpose library. See [Seamwork](https://github.com/ryjen/seamwork) for current C++23 interface and architecture refinement work.

coda_dice
=======


[![Build Status](http://img.shields.io/travis/ryjen/dice.svg)](https://travis-ci.org/ryjen/dice)
[![Coverage Status](https://coveralls.io/repos/ryjen/dice/badge.svg?branch=master&service=github)](https://coveralls.io/github/ryjen/dice?branch=master)
[![License](http://img.shields.io/:license-mit-blue.svg)](http://ryjen.mit-license.org)

A c++17 library for working with dice.  Implementations for different dice games (Yahtzee, etc.)

Building
--------

After cloning run the following command to initialize submodules:

```bash
git submodule update --init --recursive
```

you can use [cmake](https://cmake.org) to generate for the build system of your choice.

```bash
mkdir debug; cd debug; 
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
make test
```

options supported are:

    -DENABLE_COVERAGE=ON   :   enable code coverage using lcov
    -DENABLE_MEMCHECK=ON   :   enable valgrind memory checking on tests

Examples
--------

*Simple Example*

```c++
coda::dice d10(10, 10); // 10 dice with 10 sides each

auto val = d10.roll(); // random value
```

*Complex Example*

```c++
class logger_die_engine : public coda::die::engine
{
public:
    die::value_type generate(die::value_type from, die::value_type to)
    {
    	// pseudo code
    	auto value = generate_random_number(from, to);

    	cout << "Generated random number: " << value << endl;

    	return value;
    }
};

logger_die_engine my_engine;

coda::dice d10(10, 10, &my_engine);

auto val = d10.roll(); // logs the random number
```

