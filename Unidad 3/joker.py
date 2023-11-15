import requests

url = "https://programming-memes-images.p.rapidapi.com/v1/memes"

headers = {
	"X-RapidAPI-Key": "cfd2abb8b9msh30bd50d80bc3141p1cd901jsnc18b6fbb4199",
	"X-RapidAPI-Host": "programming-memes-images.p.rapidapi.com"
}

response = requests.get(url, headers=headers)

print(response.json())