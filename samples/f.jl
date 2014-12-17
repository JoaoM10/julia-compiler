# Let's make a variable
some_var = 5

# Here is an if statement. Indentation is not meaningful in Julia.
if some_var > 10
    println(1)
elseif some_var < 10    # This elseif clause is optional.
    println(2)
else                    # The else clause is optional too.
    println(3)
end
# => prints "some var is smaller than 10"
