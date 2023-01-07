import json
from flask import Flask, request
from flask_cors import CORS

app = Flask('__name__')
app.config['JSON_AS_ASCII'] = False

cors = CORS(app, resources={r"/api/*": {"origins": "*"}})

cache = {}

class Movimentos:
    def __init__(self):
      self.movimentos = []

    def set_movimentos(self, movimentos):
      self.movimentos = convert_moves(movimentos)
      print(self.movimentos)

    def get_movimentos(self):
      return self.movimentos

def convert_moves(movimentos):
    movimentos_string = ""

    for movimento in movimentos['movimentos']:
        if movimento['movimento'] == 'frente':
          movimentos_string += '0'
          continue
        if movimento['movimento'] == 'ré':
          movimentos_string += '1'
          continue
        if movimento['movimento'] == 'direita':
          movimentos_string += '2'
          continue
        if movimento['movimento'] == 'esquerda':
          movimentos_string += '3'
          continue

    return movimentos_string

movimentos = Movimentos()

@app.route('/api/movimentos', methods=['POST'])
def post():
    body = request.json

    movimentos.set_movimentos(body)

    return 'TESTE'
   
@app.route('/api/carrinho', methods=['GET'])
def moviment_car():
    print(movimentos.get_movimentos())

    return movimentos.get_movimentos()


app.config['DEBUG'] = True
app.run(host='0.0.0.0') 