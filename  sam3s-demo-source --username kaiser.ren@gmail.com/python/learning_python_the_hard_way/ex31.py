#Exercise 31: Making Decisions

print ("you enter a dark romm with two doors. do you go through door #1 or door #2?")

door =input ("<")

if door == '1':
    print ("there is a giant bear here eating a cheese cake. what do you do?")
    print ("1. take the cake.")
    print ("2. scream at the bear.")

    bear = input("<")

    if bear == '1':
        print ("The bear eats your face off.  Good job!")
    elif bear == '2':
        print ("The bear eats your legs off. good job!")
    else:
        print ("well, doing %s is probably letter. Bear runs away." %bear)

elif door == '2':
    print ("You stare into the endless abyss at Cthuhlu's retina.")
    print ("1. Blueberries.")
    print ("2. Yellow jacket clothespins.")
    print ("3. Understanding revolvers yelling melodies.")

    insanity = input("< ")

    if insanity == '1' or insanity == 's':
        print ("Your body survives powered by a mind of jello.  Good job!")
    else:
        print ("The insanity rots your eyes into a pool of muck.  Good job!")

else:
    print ("You stumble around and fall on a knife and die. good job!")
