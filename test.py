from myjit._myjithook import install_jit


print("Hello")
install_jit()  # install jit to local thread
print("Hey")
print("Yes")


def apple():
    print("Enter apple()")
    orange()
    print("Exit apple()")


def orange():
    print("Enter orange()")
    print("Exit orange()")

apple()
