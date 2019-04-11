from cs50 import get_int

def main():
    while True:
        num = get_int("Number: ")
        if num > 0:
            break

    if luhns_test(num):
        s = str(num)
        l = len(s)
        if is_amex(s, l):
            print("AMEX")
        if is_mastercard(s, l):
            print("MASTERCARD")
        if is_visa(s, l):
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")

def luhns_test(num):
    even = 0
    odd = 0
    while num > 0:
        even += num % 10
        num = strip_digit(num)

        if num == 0:
            break

        digit = (num % 10) * 2
        num = strip_digit(num)

        while digit > 0:
            odd += digit % 10
            digit = strip_digit(digit)

    if (even + odd) % 10 == 0:
        return True
    return False

def strip_digit(num):
    return (num - (num % 10)) / 10

def is_amex(s, l):
    if l == 15:
        if s[:2] == "37" or s[:2] == "34":
            return True
    return False

def is_mastercard(s, l):
    if l == 16:
        if int(s[:2]) >= 51 and int(s[:2]) <= 55:
            return True
    return False

def is_visa(s, l):
    if l == 16 or l == 13:
        if s[:1] == "4":
            return True
    return False

main()
