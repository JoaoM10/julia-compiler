a = 0
b = 1.4
c = 10

x = z

while c > 0
  tmp = b
  b = a + b
  a = tmp
  c = c - 1
end

if a < b
  c = 73
end

if a < b
  a = b
  b = c
elseif b < c
  b = c
else
  c = a + c * b
end

xpto = -73

println(a,c)
println(a)
