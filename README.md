# Authbreak 0.6
Generic authentification system injection point based tester for Linux.


# Function and motivation
Authbreak is a tool built to execute attacks that can work on every authentification system, with the same simple and powerful user interface.

In this version, it does:

1. guessing


# Install

```bash
git clone --recursive https://github.com/crazyhouse33/authbreak
cd authbreak/build
cmake ..
# Add -DCMAKE_INSTALL_PREFIX:PATH=/path/to/install to the last command to install in another directory than your system default executable location (need root)
 cmake --build . target install 
```

The binary ends up in the bin directory.

# Usage

The philosophy is to provide a command with some configurable injection points along with boolean combination of some target execution metrics (time, stdout...) to allow differentiation of success and failures. The different backends use what you specified to generate their attacks in the most efficient way they can. They are run in order of efficiency, and can back off if they detetect the method is not working, until it falls down to brutforce. 

authbreak -h for a complete explanation of how this version works.

# Coming

1. Automatic timing attack
2. Big and small performance improvement (use a thread to categorize the previous output and prepare the next while the current one is running, collect only metrics useful to the used classifiers, cache the loading (idk how yet) of the targeted process)
3. User interface improvement (press key to print state, pause and continue later at any interruption, use a more powerful front for classfiers --NOT --success time<5 --success out=="tata" --OR --sucess time=<4, Others classifiers (regexp match, return status))
4. Various furtive control options (hidden cartesian product, waiting in between actions with automatic adjustement in function of previous responses)
5. More control over what's done (pass some attacks )
6. For the file template, filter the guesses to match given charset and len
7. Make it cross platform 

# Repo

Each version of authbreak is a commit in the master branch. The version changelog is the git log of master branch. 

The dev branch contains additional continuous integration files, and has a usual git messy history :)

