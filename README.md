# CReact- An Programmable HyperText Markup Esoteric Language

“ What if we could hack NASA with HTML!” - a dream of every programmer

Well we took it seriously, so let's make something that could extend HTML beyond its limits, so we went to the GOD of all languages to seek some help, yea it's not python it’s the old age C, and guess what we got ourselves…..

CReact is a brand new crazy language that does all, plus its open-source add more layers to it make it more powerful :)

So we would be building a new esoteric (basically means crazy) language that gets interpreted to C language and gets compiled to give any result you want: conditionals, loops, characters, arithmetic, functions, recursion...

## Prerequisites :

    1. A tad bit of knowledge on C and CPP both...

    2. Slight overview of bash scripting and makefile.

So here we shall go step by step and understand how to transpile our code in any format to a proper C code for easier reference. We have used a simple language like HTML to work with.

## Installation and setup of VS Code and MinGW on Windows -
 for minGW setup -                         https://www.msys2.org/
 for running you first code in vs code -   https://code.visualstudio.com/docs/cpp/config-mingw

## Introduction Resources :

    - Overview Of C++ Language (Docs)  : https://www.cplusplus.com/reference/
    - Overview Of C++ Language (Docs)  : https://docs.microsoft.com/en-us/cpp/cpp/?view=msvc-160
    - Overview Of C++ Language (Video) : https://www.youtube.com/watch?v=vLnPwxZdW4Y&t=10067s
    - Overview Of Pointers in C/C++    : https://www.youtube.com/watch?v=zuegQmMdy8M

## Step 0 : Basics

### An overview of STL and its concepts :

The Standard Template Library (STL) is a set of C++ template classes to provide common programming data structures and functions such as lists, stacks, arrays, etc. It is a library of container classes, algorithms, and iterators. It is a generalized library and so, its components are parameterized.

Containers or container classes store objects and data.
Each container contains some inbuilt functions that help in operating on the containers and manipulating
them to store as well modify data in it. These containers work as parameterized template classes, which are called from the library appropriately when required, lets look at 2 main examples of containers that are being used in our project :

1. Vectors: Vectors are the same as dynamic arrays with the ability to resize themselves automatically when an element is inserted or deleted, with their storage being handled automatically by the container. Vector elements are placed in contiguous storage so that they can be accessed and traversed using iterators. In vectors, data is inserted at the end. Inserting at the end takes differential time, as sometimes there may be a need of extending the array. Removing the last element takes only constant time because no resizing happens.

For example :

```cpp

    vector<_datatype> _variablename;
    Some basic functions include :
    For a vector<int> v;
    - v.push_back(val);
    - v.pop(val);
    - v.size();

```

For more details check out this link: https://www.cplusplus.com/reference/vector/vector/

2. Unordered-Maps: unordered_map is an associated container that stores elements formed by the combination of key-value and a mapped value. The key value is used to uniquely identify the element and the mapped value is the content associated with the key. Both key and value can be of any type predefined or user-defined.

```cpp

    unordered_map<_datatype1,_datatype2> _variablename;
    Some basic methods for an unordered_map mp include :
    - mp.insert({val1,val2});
    - mp.find(val1)->first = val1
    - mp.find(val1)->second = val2
```

For more details check out this link: https://www.cplusplus.com/reference/unordered_map/unordered_map/

### A Symbol Table :

Though it sounds very tricky rather it isn't, so what does a symbol table does, in layman terms it helps us search for a particular data or a particular value based on our query, so here our query can be based on keywords which would be the basic constructs of the language which shouldn’t be modified and should inject predetermined code whenever needed in the program this can significantly reduce the time complexity of the code making it more efficient.

A basic implementation of such a table will be storing a collection of tuples having a key-value pair to be used to insert code snippets on the go.

For example: let's say I stored a string named HTML having a value of say “#include” or say “import” in java so at first instance it can pop this value to be stored on a container.

Ex-Tuple Container : [{“html”:”#include”},{ “h1”:”headers”} ,.....likewise].

### File Input/Output in programming :

While handling files we should take care of the commands that are used with them, which generally are associated with reading/write operations...

In Read-only operations it can read each line of string which is written in another file and character by character arranges it to form each line in the file

In write operations, we can work out by rendering or parsing the text lines by manipulating the string statements and writing them in a file.

In C++, we have the file operations contained in the header called `#include<fstream>`
which can be included to do the following operations :

    -ifstream = Reading from a file.
    -ofstream = Writing to a file.
    -fstream = to do both the operations.

Basic Syntax :

```cpp
    - Reading:
    string st;
    ifstream myfile("<filename>")
    while(getline(myfile,st)){
        //Here we get each line from the txt file given above
    }
    - Writing:
    ofstream writeIn("<filename>")
    writeIn << /* statement */ <<"\n"

```

For more details on file handling in Cpp checkout: https://www.cplusplus.com/doc/tutorial/files/

In the project, as we shall be writing the code on a .txt file so your transpiler script shall read the esolang-code from the file line by line and parse each line as a collection of characters, so here we shall take each line as an input from the base .txt file and parse it accordingly and store it in a container which shall allow us to make changes in the placement of values whenever writing in the result file at last (this seems unnecessary and rather it is more practical to just inject code inside the output file directly but there's a catch to do so which we'll get through later..)


## Step 1: INITIAL STEPS: WRITING A HELLO WORLD OR PRINTING PROGRAM IN THE ESOLANG

The given eso-lang follows an HTML syntax construct so for example we have used here the following syntax :

```html
<htpl>
  <main>
    <log>Hello World </log>
  </main>
</htpl>
```

The snippet is a very simple code so let's de-structure it to understand the working behind the scenes.

The principal thing is removing the initial spaces from each string line, the reason being we just require what's given the extra spaces will only cause a hindrance so it's better to remove them & only work with what's required...

For this, we can implement a basic loop function that reads the string, and as a character other than " " is encountered would refactor itself...

### Pseudocode

```
    INPUT a string variable
    FOR i in string_var
        IF i != ' '
            string_var = string_var[i,length of string_var-i]
            BREAK

```

Now working with tags:

Here the 1st thing which is the `<htpl>` tag is a constant keyword identifier, as it will be always written to start coding in your esolang...

So for that instance, we can store the appropriate code for this specific tag in our globally defined tuple collection, and on recognizing this specific tag can push the appropriate code inside our result container which will be pushed in the parsed file later.

Now in this case we have a string with log as `<log>(word)</log>`, so the only way to parse it is breaking the string in parts and getting the required portion in this case checking for a keyword “log” that in our tuple collection stores a value of PRINT statement,

So using string manipulation extracting the word “log” we can get the statement print identifier of the result programming language; it can be “printf for C”, “System.out.print for Java” or “console.log for Javascript” etc which can be inserted in the container.

Whereas the respective closing tag can be distinguished with a starting 2 indexes of “<\”
It can be replaced by any sequence user likes say “); for C”, or simply “)” for python or Js, in a similar way the material to be inserted can be extracted by manipulating the strings.

Now arises a concern say we are printing a large number of words as shown as :

```html
<log>
  (some words --------------------------------------------
  ------------------------------------------------------------
  --------------------------------------------------end)
</log>
```

Here we can’t simply extract the string in between and work on it as each line is read separately so for this reason we can extract part of the string having the tags opening/closing and adding on to it to construct the whole paragraph present between the log tags…

So this points out that simply parsing and writing in an output file won’t do for that we have another solution which is using that same container in which we are storing the parsed values accordingly in a specific pattern so that it can be arranged to get the desired parsed code in the output file...

The list shall store in the strings inside it which are to be inserted and at the creation and scripting period would be activated to fill in the string nodes line after line.

The printf implementation :

```py

    [   {   “print()“   }  ,  { “Material to be inserted i.e connected parts of a multiline <log> ” }  ,  {   “;”    }];

```

So it can be parsed as ==========> [ { “ print(“material---------”); “ } ]

and then re-inserted at the head node whereas removing the already present nodes.

This way we can create a simple printing program in our language.

### Automating compilation using makefile and bash scripting

#### Makefile

        Make is a Unix utility that is designed to start the execution of a makefile. A makefile is a special file, containing shell commands, that you create and name makefile (or Makefile depending upon the system). While in the directory containing this makefile, you will typically make and the commands in the makefile will be executed

        Make keeps track of the last time files (normally object files) were updated and only updates those files which are required (ones containing changes) to keep the source file up-to-date.

        With this, you don't have to compile the code repeatedly, a simple make command in the terminal will compile the changed code

#### Bash scripting

    A bash script file is a file containing several bash commands, all of which gets executed once the bash script file is run on the system
    In this project contents of the bash script file include
        1. Changing working directory to Main
        2. make command
        3. Running transpiler binary with the file name
        4. Compiling transpiled program using g++
        5. Executing transpiled binary
        6. Removing transpiled c file and binary
    Bash script files can be run using the command ./script.sh

Note: you might need to allow execution of the bash script in your system by using:` chmod +x script.sh` or ` chmod 777 script.sh`

#### Executing the program

    You need to place a .txt file in the Main folder with contents of CReact code to be executed
    then change directory to root of the project (if you are not already there) then execute the commands

```
chmod +x script.sh
./script.sh input.txt # assuming name of the file is input.txt
```

## Step 2: Working with Data Types and Input/Output

Taking user input is a very basic task that is expected of our esolang. For convenience let us assume that we have already declared a variable of integer type (we will see how to do that later in this section).

To understand how to achieve this, our first step is to decide what our user input syntax is going to look like. In CReact, the syntax that we have defined is as follows :

```js
    declare the integer variable named var
    <take var/>
```

Our motive is to parse this syntax in such a way, that the desired output in our C file looks like :

```c
    declared variable var
    scanf("%d",&var);
```

To execute the above-mentioned translation, we use string manipulation to extract the word “take” to get the statement scan identifier of the result programming language(scanf in our case) from the predefined map, which can be inserted in the output file.

Whereas the respective closing tag can be distinguished with a starting 2 indexes of “<\”
It can be replaced by any sequence user likes say “); for C”, or simply “)” for python or Js, in a similar way the material to be inserted can be extracted by manipulating the strings.

Now, very similar to the fashion in which we implemented the print function above, we have to use a dynamic array or list that stores the parsed values.

Say a list has the contents for the print statement parsed as :

```js
 [  {   “scanf()“   }  ,  { “variable_name” }  ,  {   “;”    }];
```

So it can be parsed as ==========> [ { “ scanf(“variable_name---------”); “ } ]
and then re-inserted at the head node whereas removing the already present nodes.

This is how we achieve a basic implementation of user input in our esolang.

Now a programming language is incomplete without providing a base to specify its variables as anything that we write must have a meaning so to use certain variables for different purposes, in CReact an easy and simple method to define data types and introduce similarities with other programming languages we have created some predefined datatypes so that we can work with alphanumeric values :

It is generally defined using keywords like "in" and "ch" with denotes the integer and character respectively in CReact, for making things crazier u can define it yourselves as anything u wish to...

Maintaining the norms of React a variable can be statically initialized with a value under a self-closing bracket value :

### Syntax

```js
    For static allocation :
    < data_type variable_name = value />

    For Dynamically allocation it can be written as :
    < data_type variable_name, variable_name1 />

    Example -> For integers it can be written as :  <in val = 75/>

```

Now to parse this we have to update our tuple data - collection my adding another tuple that can convert the defined identifier to the datatype and while reading the string statement just replace that with the value from the collection and parse that statement into the temporary storage container to push into the file at the end...

The second part comes into initializing the same into our lang of choice when required, for eg in C we use different identifiers when taking input like for

- Integer is denoted by %d in C
- Character is denoted by %c in C

So in the tuple collector, we shall initialize these identifiers with that of respective datatypes and while taking input using **<take var_name />** just write insert
respective identifier and reconfigure the string in the same order as :

```js
    <take var_name/>
    scanf("\\identifier\\",&var_name);

```

As this specific practice is followed in C language and this whole string is inserted into the temp_container to write afterward in the file...

### Printing Multi Variables

In this language es6 standards for formatting and printing the expression is used here, i.e. using ${varName}

### Syntax

```js
<log>
  {" "}
  ${varName1} ${varName2}{" "}
</log>
```

For example:-

```js
    <htpl>
        <in a=3,b=4 />
        <log>
        Printing value of a and b : ${a} ${b}
        </log>
    </htpl>

```

In the log function, the string between the htpl log tags are parsed into an equivalent format string statement one letter at a time until it has encountered a "${" string

### Pseudocode:

    Function(string param)
        Let str be an empty string to hold the result
        Iterate 1 letter at a time over the string
        if (given letter word is equal to '$' and next letter is '{')
        search for variables declared before with the name between the braces
        if a search was successful
            add an appropriate modifier to str
        else
            add string including the braces as it is to str
        else
        add a string as it is to str
    Return str

The code in the above example converts into a format string
for eg in C
("Printing value of a and b : %d %d",a,b)
while in python it would look like:
f'Printing value of a and b : {a} {b}'

This formatted string along with their variable names are passed onto their respective print statements hence facilitating multi-variable output.

## Step 3: Implementing arithmetic operations

An esolang is incomplete if it cannot perform all the basic mathematical operations. Since we are following the syntax of HTML, we needed a specific way to tell the transpiler that the following line to be parsed is a mathematical operation. So the operator that we have used is '%'.

```js
    An example of a mathematical statement in Creact :

    <% x = (x+(2*y)/z) %>

```

Achieving this transpilation is significantly simpler than you might be thinking. Note that we are just making a transpiler and not an actual compiler. So we just need to parse the statement and translate it to C/C++ and the GCC call does the rest of the work for us.

So we parse the line after checking the presence of '%' and then transpile the mathematical statement with the help of a temporary vector to push into the parent vector string that must be transpiled. One point of caution in such parsing is checking that the spaces between different terms don't affect the process of parsing. Using the brute force method to check positions will not help and may lead to the code crashing. So instead use a temporary vector to push the different characters.

In conclusion, we perform all the mathematical operations in Creact inside blocks that are labeled with '%' for easier understanding of the transpiler and maintaining the syntax of the language.


## Step 4: Conditional Statements

Whenever we have to implement a logic it doesn't end with just mathematical operations, sometimes to check whether what we are working with is logically apt or not generally we use an if-else block that makes it easier to question and follow a certain pathway in that manner.

Any modern-day programming language is always equipped with the power to question a certain course of action and chalk out a working plan accordingly, this helps us execute tasks in a much simpler way and integrate segmented code to make it multi-functional.

In basic programming lang a simple if-else block is generally written as :

```
Pseudocode :

    IF(cond1)
        Execute this part
    ELSE IF(cond2)
        Execute this part
    ELSE
        Execute this last part

```

In our CReact Esolang to make things more intuitive and much simpler to understand we follow the following syntax :

```js
If block clause :

    <? if(cond1)
        statement1
    ?>
    <? elif(cond2)
        statement2
    ?>

```

Take it as a fragment that renders an if-else construct to work with, here we shall first look for the special tag such that the angular brackets have "?" inside it which triggers a function that works with conditionals, here we shall strip down the spaces again, this shall then give us only the required string to work with, after which we shall look for some general keyword associated with conditionals and look for them to properly format the substring to arrange the condition properly and add an opening a "{" then push in the required statements inside temp-container and use the last identifier "?>" that can push in the required the closing bracket as "}".

### A basic conversion:

```js
                       <? if(cond1)              if(cond1){
                           statement1               statement1;
                       ?>                        }

```

Now to add to more functionality we shall implement nested conditions in the if-else block and differentiate it from the outside marker we shall implement a unique identifier logic that works with the help of indentation, like in the CReact we have made nest if-else block logic work by the help of adding indentation based on the no. of '?' one adds to identify where is the block lying for instance

### Example helper

```js

(space)  <?
(space)        if(cond1)
(space)(space)<??
                    if(cond2)
(space)(space)??>
(space)  ?>

```

Here if you can see a pattern if the nested condition increases so does the number of '?' in the tags, this does what is it

    * Firstly helps the interpreter parse the conditionals easily as it will be able to differentiate between the 2 blocks and put the C interpretation more clearly

    * Make code look easier to design.

So that's how we develop the power of conditions in our programming language.
## Step 5: Loops

Loops are an essential programming language utility to instruct the sequence of operations to repeat itself a set number of times or until a certain condition is met. Loops reduce redundancy in code and also the effort to repeat operations in a programming language

In general, the syntax of common loops in modern-day programming languages are

```
Pseudocode :

    FOR(DECLARATION; CONDITION; ITERATION)                  WHILE(CONDITION)
        Execute Statement                                       Execute Statement

```

## Syntax

In our CReact Esolang to make things more intuitive and much simpler to understand we follow the following syntax :

```js

FOR CLAUSE :                                                WHILE CLAUSE:
                <# f (declaration,condition,iteration)              <# w(condition)
                    Statement                                           Statement
                #>                                                  #>
```

Loops have a characteristic tag of '#' and the two loops are differentiated concerning the letter that shows at the start of
the loop syntax, which is 'f' referring to for loop while 'w' for while loop, the traspiling program looks specifically for the '#'
symbol to execute a function to parse loops. The function first strips off spaces from the statements and first determines which
category of the loop the statements belong to (i.e. for or while). The statements are then compiled into the compiling programming language
syntax for example:

```c
In C:                                       In python

    for(var=1;var<10;var++)                      for var in range(1,10,1):

    while(var>10)                                while var > 10:

```

the beginning and conclusion of the statements in CReact are determined by the "<#" and "#>" respectively.

## Nested loops

Nested loops are much required in programming languages and in CReact, the level of nesting is described by the number of '#'
in the first line of the loop syntax.

```js
<# f (var=1,var<5,var++)
    <## f (var1=1,var1<5;var1++)
        Statements
    ##>
#>

```

This way you can nest multiple while loops or for loops in while loops and vice-versa
This process of transpiling is not very different from what is used in conditional statements

## Step 6: Functions

Now implementing functions requires two components of the process that must be implemented in our esolang. One is the statement where the function is defined, and the other being the statement where the function is called in our main function. ( Please note that Creact does not have a single main function wherein all the code resides, but may have multiple functions outside the main function as well just like C/C++).

An example of function definition syntax in Creact -

```
     <fx in gcd_algo(in a,in b)>
        <? if(a==0)
            <throw b/>
        ?>
        <? else
            <throw gcd_algo(b%a,a)/>
        ?>
    </gcd_algo>

```

As you can see from the above snippet, the functions are defined using 'fx', which is followed by the return type of the function. The function name takes the parameters of the function, and then we write the function body. 'throw' is the keyword to return a value. (similar to the keyword return in C/C++)

An example of function call syntax in the main function in Creact -

```
    <fx res=gcd_algo(val1,val) />
```

Here, our transpiler understands that a function is being called from 'fx'. We have defined an integer 'res' previously, which will store the returned value from the function 'gcd_algo'. ''val1' and 'val' are the parameters being sent to the function.

We check for the 'fx' term in the statement to check if it is a functional block.

Now, before we start parsing, we need to check if our statement is the definition of the function or the function call in the main function.
If the statement is a function call, we need to parse it in the following way :

```
    <fx res=gcd_algo(val1,val) />      ===========>        res=gcd_algo(val1,val);
```

At this point, this is comparatively one of the simpler parsings that we do, using a temporary string vector. We also need to make sure that if any variables are defined in the statement, we find their respective values from the 'varKey' database that we have predefined.

If the statement is a function definition instead, we parse the return type from 'varKey' and then parse the parameters as done previously.
The body of the function shall be parsed as it is, as our previously defined functions such as arithmetic take care of everything. We do this parsing until we reach the end of the function.

As we are converting our esolang file to a C file, and by the syntax of C we already know that a function defined anywhere in the program should be defined with a function signature at the beginning of the program as shown in an example snippet below :

```c
int func(param); // This is a function signature so for each function defined a signature needs to be added while parsing
int main(){
    func(setter)
}
int func(param){
    //statements
}

```

To execute this task we have to first start extracting the instance of function from the line it is written first in the htpl, say anywhere before the `<main></main>` or even after it, while reading through it, we shall store all such functions in a vector set of strings during the moment that function statement is parsed as the syntax for functions signature is same as that of a function call,

### Helper snippet :

```js

<main>
    //some statements
</main>
<fx _datatype func_name(_datatype param1) /> //This statement in C becomes _datatype func_name(_datatype param1)
    //inner statements
</func_name>

```

Now as we have the function signature in another vector, while writing the equivalent C code in a file we shall, after insertion of the headers we shall check whether such a vector exists or not, if yes then insert all the signatures at that point else move on with insertion of other parts of the code.

## Step 7: Dynamic Arrays

If you came this far you would surely know how much we have worked with vectors in the whole project, so let's try to make one in esolang, it would work as a normal vector as usual just would be able to work with integers.

To understand how to implement it, let's focus on memory a bit :

In arrays, we always statically ask for some contiguous block of memory from the heap, which once given cant be extended furthermore this restricts it to work furthermore with a humongous amount of data.

So for this, we have to delve deep into the domain of memory management, and one of the chief reasons we're working on this project in C/C++ is because memory management is offered best by C/C++ due to the age-old concept of pointers.
In C we have 2 very interesting functions in stdlib.h library which include the malloc & realloc see their definition bellow :

1. malloc() :- The “malloc” or “memory allocation” method in C is used to dynamically allocate a single large block of memory with the specified size. It returns a pointer of type void which can be cast into a pointer of any form.

Syntax : `ptr = (cast-type*) malloc(byte-size)`

2. realloc() :- “realloc” or “re-allocation” method in C is used to dynamically change the memory allocation of a previously allocated memory. In other words, if the memory previously allocated with the help of malloc or calloc is insufficient, realloc can be used to dynamically re-allocate memory.

Syntax : `ptr = realloc(ptr, newSize)` ,where ptr is an previously allocated pointer

So how can we use these functions to implement dynamic arrays, basically we will be using a pointer by allocating a fixed amount of space initially, say 2 blocks of memory, and to keep things simple we shall be using an integer array, so say :

```cpp
int* ptr = (int*)malloc(sizeof(int)*2);

```

This allocates 2 blocks of memory to the ptr variable to store 2 values, but say we have to enter more variables so we shall be using realloc module and reallocating ourselves more space for comfort it shall be double the present size of the array, so initially, if it is 2 it shall become 4, then 8, 16 likewise :

```cpp
ptr = (int*)realloc(ptr,sizeof(int)*present_size*2)

```

Likewise, the extended memory allocation works, but remember this reallocation can work effectively when used in the present block of memory is completely used up, so we can use an if-else block to keep a check and insert if and only if the present allocated space is completely used up.

Now in our CReact how shall we implement this, for dynamic arrays we are using a special syntax and tags which include :

Syntax `<<stream::(_datatype) _varname>>`

This initializes a pointer variable as shown as well as allocates the constant 2 blocks memory as well as can be programmed to trigger the insertion of important headers in the program like `stdlib.h` or any preprocessor derivatives.

Now, this is not the only thing that shall complete the allocation completely as we have to put in more layers to the code,

1. Firstly, say a user initializes 10 such dynamic arrays each can be initialized with the same size i.e 2 but while working on the push/pop operations the total size of each array might vary considering that fact the variable that works as size-reallocator, should be assigned a unique value that should only control the size of that specific array...

2. Secondly say an array initially 2, extended to 16 sizes and filled with only 10 elements, so while operating why should we work with that extra 6 spaces as a pop function will give errors at that part, so we shall be using a flag-pointer that shall always point to the last element pushed inside and if more are pushed inside then do a flag++ with that of the pointer else on popping flag-- to get the required answer, moreover the counter-flag for each array should also be unique as several elements in them can vary as well.

This shall help with the proper allocation.

Now, let's move to its functions, we have :

    - plus() : To push in values, but there is a check if the size is full/not, because then we have to reallocate, now unlike in a loop, it can be called anywhere so for that reason, we have to constantly check whether the size limit is reached because then we have to apply an if-else check which on each push operation would make it more cumbersome, so we shall write the important functions in a helper.txt file and write those functions in the main file just after the headers, as it shall help in quick reallocation and prevent writing an if-else check before each push-back.

    - minus() : To pop out elements, we have to work with the counter-flag which shall decrease by 1 automatically if a function is encountered.

    -show() : As this is a regular function so we shall insert it with the reallocation construct from a file to display the number of elements up to the flag.

To work with them we shall manipulate the strings and display them in the correct format :

For example :

```cpp

    v.plus(x);      ===============>    *(v+cnt++) = x; , where cnt is the counter flag

```

Now lastly 2 other operations that should work on it are updating a specific position & assigning the value of a specific block of the array to a variable, as both come under the mathematical/logical operations so it is done using the `<% %>` tags :

For example :

```cpp

Update operations :

    v[position] = x;    ===============>    *(v+position) = x;

Assigning Operations :

    x = v[position];    ===============>    x = *(v+position);

```

Now to parse it correctly we can look for the position of '=', divide the strings into 2 halves then on each half tokenize the parts like a variable name, value and place it accordingly.

So that's how we can work with dynamic arrays in CReact.
