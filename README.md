# GassinRT

A lightweight JS runtime for linux (For Now) that can do system level tasks through JavaScript

# Build Instructions 

<h1>Step 1:</h1>

Git clone this repository:

<code>git clone https://github.com/Adock90/GassinRT</code>

Or download as ZIP

<h1>Step 2:</h1>

Run the build file (you might need to enable execute permissions).

<code>./build.sh</code>

For changing permissions.

<code>chmod +x ./build.sh</code>

Alternatively run:

<code>g++ -o build/GassinRT main.cpp -luv -lv8 -std=c++20</code>

or

<code>clang++ -o build/GassinRT main.cpp -luv -lv8 -std=c++20</code>

<h1>Step 3</h1>

cd into the build directory.

<code>cd build/</code>

Run with your .js file as the first argument.

<code>./GassinRT hi.js</code>
