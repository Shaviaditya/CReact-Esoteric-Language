## Step 2: Working with Data Types and Input/Output

First of all we shall declare some variables in our map and their types equivalent in C language.
```
    in => int => %d
    ch => char => %c

```
For CReact the above syntax shall be used to map in 4 pairs of values in our dictionary.
Now any variable can be declared in a syntax such that it is easily recognisable by the transpiler and easy to work with as well, for CReact we follow a simple pattern of self-closing tags that is :

```
    <in var1 = 9,>
```
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

This formatted string along with their variable names are passed onto their respective print statements hence facilitating multi-variable output