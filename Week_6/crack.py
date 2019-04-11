from sys import argv
import crypt
from hashes import hashes

def main():
  if len(argv) != 2:
      print("Usage python crack.py <hash>")
      return 1

  hash = argv[1]
  salt = hash[:2]

  alphabet = " abcdefghijklmnopqrstuvwxyz"
  alphabet += alphabet[1:].upper()

  if hash in hashes:
    print(hashes[hash])
    return 0

  for a in alphabet:
    for b in alphabet:
      for c in alphabet:
        for d in alphabet:
          for e in alphabet:
            guess = a + b + c + d + e
            guess_hash = crypt.crypt(guess.strip(), salt)

            hashes[f"{guess_hash}"] = guess

            if guess_hash == hash:
              print(guess.strip())
              save()
              return 0

  print("Password cannot be found...")
  save()
  return 1

def save():
  file = open('hashes.py', 'w')
  file.write(f"hashes = {hashes}")
  file.close()

main()

# brian: TF
# bjbrown: UPenn
# emc: 502sDZxA/ybHs
# greg: FTW
# jana: Yale
# lloyd: lloyd
# malan: maybe
# natmelo: nope
# rob: ROFL
# veronica: hola
# walker: sean
# zamyla: LOL