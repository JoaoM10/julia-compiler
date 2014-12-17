a = 0
b = 1
c = 10
println(a)
while c > 0
      tmp = b
      b = a + b
      a = tmp
      c = c - 1
      println(a)
end
#println(a,c)
println(a)