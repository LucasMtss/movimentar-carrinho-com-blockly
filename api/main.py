from flask import Flask, request
from flask_cors import CORS

app = Flask('__name__')
app.config['JSON_AS_ASCII'] = False

cors = CORS(app, resources={r"/api/*": {"origins": "*"}})

cache = {}

def getTweetsOfNews(news):
  return getTwetsOffAllNotices(news)


@app.route('/api/movimentos', methods=['POST'])
def post():
    body = request.json
    print(body)
    return 'TESTE'
   


app.config['DEBUG'] = True
app.run()