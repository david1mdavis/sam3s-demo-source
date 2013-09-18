#Exercise 24: More Practice

print ("Let us practice everything.")
print ("you'd need to know 'bout escaptes with \\ that do \n newlines and \t tabs.")

poem = """
\tThe lovely world
with logic so firmly planted
can't discern \n the needs of love
nor comprehend passion from intuition
and requires an explanation
\n\t\twhere there is none.
"""

print ('-------------------')
print(poem)
print ('-------------------')

five = 10 - 2 + 3 - 6
print ("This should be five: %s" %five)

def secret_formula(started):
    jelly_beans = started*500 #this jelly_beans is local variable
    jars = jelly_beans / 1000
    crates = jars / 100
    return jelly_beans, jars, crates

start_point = 10000
jelly_beans, jars, crates = secret_formula(start_point)#this jelly_beans is global variable

print ("with a starting point of: %d" %start_point)
print ("we'd have %d beans, %d jars, and %d crates." %(jelly_beans, jars, crates))
