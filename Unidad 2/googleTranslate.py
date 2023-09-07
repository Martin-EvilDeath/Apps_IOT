import requests

url = "https://google-translate1.p.rapidapi.com/language/translate/v2/detect"

payload = { "q": "English is hard, but detectably so" }
headers = {
	"content-type": "application/x-www-form-urlencoded",
	"Accept-Encoding": "application/gzip",
}

response = requests.post(url, data=payload, headers=headers)

print(response.json())