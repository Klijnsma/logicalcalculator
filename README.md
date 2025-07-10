# logicalcalculator
Calculator for propositional logic.

Takes in propositions from a csv file and calculates a truth table for and the validity of the argument they form.

## Building
Run the following commands:

    cd output_files/
    cmake ../
    make
The executable is generated as output_files/logicalcalculator

## Usage
Run one of the following commands form the project directory, replacing *csv_file* with the (path to the) csv file you wish to use:

    output_files/logicalcalculator csv_file
or

    output_files/logicalcalculator -i csv_file

## Csv formatting
The csv file can only use commas as separators. The lines should be filled in like this:

    [truth function keyword],[parameter 1],[parameter 2]
for truth functions and

    [variable name]
for variables. Variable names are case-sensitive, while all other text is not. Currently, variable names can only be one character long.

The following truth function keywords are recognized:

    conjunction
    exclusive disjunction
    inclusive disjunction or disjunction
    material equivalence, material biconditional or biconditional
    material implication

Truth function parameters can be both truth functions and variables.
If a truth function is used it will have two parameters as well, which should be placed in the next two fields, before the parent truth function's next parameter.

After all the premises, there must be a line containing nothing but 'conclusion' to indicate that the following line is the conclusion. 
The conclusion can currently only be one line, and is formatted the same way as the premises.