import requests

url = "https://matchilling-chuck-norris-jokes-v1.p.rapidapi.com/jokes/random"

headers = {
	"accept": "application/json",
	"X-RapidAPI-Key": "cfd2abb8b9msh30bd50d80bc3141p1cd901jsnc18b6fbb4199",
	"X-RapidAPI-Host": "matchilling-chuck-norris-jokes-v1.p.rapidapi.com"
}

response = requests.get(url, headers=headers)

# Verificar si la solicitud fue exitosa (código de respuesta 200)
if response.status_code == 200:
    # Parsear la respuesta JSON
    joke_data = response.json()

    # Acceder al valor de la broma
    joke_value = joke_data['value']

    # Imprimir la broma
    print(f"Broma: {joke_value}")
else:
    print(f"Error en la solicitud. Código de respuesta: {response.status_code}")
