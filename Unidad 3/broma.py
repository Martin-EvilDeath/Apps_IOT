import requests

url = "https://humor-jokes-and-memes.p.rapidapi.com/jokes/search"

querystring = {"exclude-tags":"nsfw","keywords":"rocket","min-rating":"7","include-tags":"one_liner","number":"3","max-length":"200"}

headers = {
	"X-RapidAPI-Key": "cfd2abb8b9msh30bd50d80bc3141p1cd901jsnc18b6fbb4199",
	"X-RapidAPI-Host": "humor-jokes-and-memes.p.rapidapi.com"
}

response = requests.get(url, headers=headers, params=querystring)

obj = response.json()

print(obj['jokes'][0]['joke'])