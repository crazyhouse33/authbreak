# Authbreak 0.6
Generic authentification system injection point based tester for Linux.


# Function and motivation

Authbreak is a tool built to execute attacks that can work on every authentification system, with the same powerful user interface and complete set of feature. It's been done entirely in C ( Because I was willing to try the language Linux was coded with, and god I regret this decision). It also have an insane (first degree of the word) focus on performance. Yet it also follow manual but very strict continious integration, lot of tests including valgrind assisted memory checks, per commit performance auditing...

# Install

```bash
git clone --recursive https://github.com/crazyhouse33/authbreak
cd authbreak/build
cmake ..
# Add -DCMAKE_INSTALL_PREFIX:PATH=/path/to/install to the last command to install in another directory than your system default executable location (need root)
 cmake --build . target install 
```

The binary ends up in the bin directory.

# Repo

Each version of authbreak is a commit in the master branch. The version changelog is the git log of master branch. 

The dev branch contains additional continuous integration files, and has a usual git messy history :)


# Usage

The philosophy is to provide a command with some configurable injection points along with boolean combination of some target execution metrics (time, stdout...) to allow differentiation of success and failures. The different implementeds attacks will try to exploit the target using your inputs in the most efficient way they can to get a success.

authbreak -h for an extensive explanation on every options.


# Attacks

## Brutforcer

The brutforcer iterate once on every possible combination defined by the differents injections points. It does so with an order maximazing cyling size over each injection points. 

If user contains:

```
ansible
root
Jack
Elizabeth
```
And password contains:
```
admiN123 
1234 
password 
gorilla43
```

Then authbreak generate followings output:

```
./authbreak -s status==0 'echo {user} {password}'

/bin/echo ansible admiN123

/bin/echo root 1234

/bin/echo Jack password

/bin/echo Elizabeth gorilla43

/bin/echo ansible 1234

/bin/echo root password

/bin/echo Jack gorilla43

/bin/echo Elizabeth admiN123

/bin/echo ansible password

/bin/echo root gorilla43

/bin/echo Jack admiN123

/bin/echo Elizabeth 1234

/bin/echo ansible gorilla43

/bin/echo root admiN123

/bin/echo Jack 1234

/bin/echo Elizabeth password
```

# Coming

Developpement will fist focus on implementing a really powerfull brutforcer. Then a larger set of generic attacks will be implemented and mixed with a sheduling system.

1. Automatic timing attack over generics shemes: Clear creds comparaison, enummeration assuming weak data structures...
2. Big and small performance improvement (cache the loading (idk how yet) of the targeted process)
3. User interface improvement (press key to print state,  automatic sessioning on interuption/crash, others classifiers (regexp match), better output gestion)
5. More control over what's done 
7. Make it cross platform 
