#Exercise 15: Reading Files

#from sys import argv

#script, filename = argv

filename = input('<')

txt = open(filename)

print ("Here's are your file %r" %filename)
print (txt.read(10)) #read ten characters

print ("I'll also ask you to type it again.:")
file_again = input('> ')

txt_again = open(file_again)

print (txt_again.read())
