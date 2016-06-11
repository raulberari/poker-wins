import random

textFile = open("carti.txt", "w")

def areTheValuesDifferent(arr):
	for i in range(0, len(arr) - 1):
		for j in range (i+1, len(arr)):
			if arr[i] == arr[j]:
				return False

	return True

arr = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
n = 1000

textFile.write (str(n) + "\n")

for i in range(0, n):
	for k in range(0, 10):
		nr = int(random.random() * 13) + 2
		nr2 = str(nr)
		culoare = int(random.random() * 4)

		if nr == 10:
			nr2 = 'T'
		elif nr == 11:
			nr2 = 'J'
		elif nr == 12:
			nr2 = 'Q'
		elif nr == 13:
			nr2 = 'K'
		elif nr == 14:
			nr2 = 'A'

		if culoare == 0:
			arr[k] = nr2 + 'S'
		elif culoare == 1:
			arr[k] = nr2 + 'C'
		elif culoare == 2:
			arr[k] = nr2 + 'H'
		elif culoare == 3:
			arr[k] = nr2 + 'D'

	while not areTheValuesDifferent(arr):
		for k in range(0, 10):
			nr = int(random.random() * 13) + 2
			nr2 = str(nr)
			culoare = int(random.random() * 4)

			if nr == 10:
				nr2 = 'T'
			elif nr == 11:
				nr2 = 'J'
			elif nr == 12:
				nr2 = 'Q'
			elif nr == 13:
				nr2 = 'K'
			elif nr == 14:
				nr2 = 'A'

			if culoare == 0:
				arr[k] = nr2 + 'S'
			elif culoare == 1:
				arr[k] = nr2 + 'C'
			elif culoare == 2:
				arr[k] = nr2 + 'H' 
			elif culoare == 3:
				arr[k] = nr2 + 'D'


	for k in range(0, 10):
		textFile.write (arr[k] + " ")
	textFile.write ("\n")

textFile.close()
