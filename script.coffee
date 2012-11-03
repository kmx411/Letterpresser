dictionary = ["abc", "def", "ghij", "klmnop"]
alphabet = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
nonLetters = []

fillLetters = (letterSet) ->
  nonLetters = _.difference( alphabet, letterSet.split('') )

check = (word) ->
  result = true
  for letter in word.split('')
    for nonLetter in nonLetters
      if letter == nonLetter
        result = false

  if result == true
    console.log word

$(document).ready ->
  fillLetters 'ackhlmnop'
  console.log nonLetters
  check word for word in dictionary


