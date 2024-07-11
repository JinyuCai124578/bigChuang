from flask import Flask, render_template, request
from chat_with_llm import KGRAG_test

app = Flask(__name__)


@app.route('/')
def index():
    return render_template('form.html')


@app.route('/submit', methods=['POST'])
def submit():
    chatbot = KGRAG_test()
    input_text = request.form['input_text']
    # 蔡姐代码放这里👇
    output_text = chatbot.chat(input_text)
    # 👆
    return render_template('form.html', output=output_text, input = input_text)


if __name__ == '__main__':
    app.run(debug=True,port=5001)