dictionary = window.dictionary
window.alphabet = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']

window.nonLetters = []
window.resultWithDupe = []
window.results = []

fillLetters = (letterSet) ->
  window.nonLetters = _.difference( window.alphabet, letterSet.split('') )
  check word for word in dictionary

check = (word) ->
  result = true
  for letter in word.split('')
    for nonLetter in window.nonLetters
      if letter == nonLetter
        result = false

  if result == true
    window.resultWithDupe.push word

createCount = (letterSet) ->
  letters = letterSet.split('')
  count = {}
  for letter in letters
    if( count[letter] )
      count[letter]++
    else count[letter] = 1

  count

removeRepeatLetters = (count) ->
  for word in window.resultWithDupe
    nonDupe = true
    currentCount = createCount( word )
    for letter in word.split('')
      if currentCount[letter] > count[letter]
        nonDupe = false

    if nonDupe
      window.results.push word

clearGlobals = (callback) ->
  window.nonLetters.length = 0
  window.resultWithDupe.length = 0
  window.results.length = 0
  callback()

fillDOM = ->
  resultCount = window.results.length
  fillOneCount = Math.floor( resultCount / 3 )
  fillThreeCount = resultCount - ( 2 * fillOneCount )

  for word, i in window.results
    if  i < fillOneCount
      $('#fill1').append "<h4>#{word}</h4>"
    else if i < 2*fillOneCount
      $('#fill2').append "<h4>#{word}</h4>"
    else
      $('#fill3').append "<h4>#{word}</h4>"

launchIt = (input) ->
  clearGlobals ->
    fillLetters input
    removeRepeatLetters createCount( input )
    fillDOM()


$(document).ready ->
  $('.btn').click ->
    $('#fill1').html ''
    $('#fill2').html ''
    $('#fill3').html ''

    input = $('#appendedInputButton').val()
    launchIt input
