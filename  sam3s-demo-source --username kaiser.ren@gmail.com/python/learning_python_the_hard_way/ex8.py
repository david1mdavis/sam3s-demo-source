#Exercise 8: Printing, Printing
format = "%r%r%r%r"

print (format % (1, 2, 3, 4))
print (format % ('one', 'two', 'three','four'))
print (format % (True, False, True, False))
print (format % (format, format, format, format))
print (format % (
    "I had this thing.",
    'That you could type up right.',
    'But it didn\'t sing.', #owing to ', so print "But it didn't sing."
    'So I\'d said good night.'
    ))
