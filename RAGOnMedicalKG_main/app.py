from flask import Flask, render_template, request, jsonify
import os
import json
from chat_with_llm import KGRAG_test

app = Flask(__name__)
chatbot = KGRAG_test()
chat_history = []

@app.route('/')
def index():
    return render_template('form_new.html')


@app.route('/submit', methods=['POST'])
def submit():
    global chat_history
    input_text = request.form['input_text']
    # 蔡姐代码放这里👇
    output_text = chatbot.chat(input_text)
    # 👆
    # 添加用户消息到聊天记录
    chat_history.append({'role': 'user', 'content': input_text})
    # 添加助手消息到聊天记录
    chat_history.append({'role': 'assistant', 'content': output_text})

    # 返回新的聊天记录
    return jsonify(chat_history)

@app.route('/save', methods=['POST'])
def save():
    # 这里可以添加保存聊天记录的逻辑，例如保存到文件或数据库
    # 为了示例，我们简单地返回一个成功的状态和一个假定的文件名

    # 假设保存操作成功
    # filename = "chat_history.txt"  # 这是一个示例文件名，实际应用中可能会不同
    file_name, entity=chatbot.save_to_file()  # 调用保存聊天记录的方法
    chat_history.clear()  # 清空当前聊天记录
    # 返回 JSON 响应
    return jsonify(status='ok', filename=file_name, entity=','.join(entity.keys()))

@app.route('/load', methods=['GET'])
def load_chat():
    global chat_history
    filename = request.args.get('filename')
    if not filename:
        return jsonify({'error': 'Filename is required'}), 400

    
    history = chatbot.load_history(file_path=filename)
    chat_history=[item for item in history if item['role'] in ['user','assistant']]
    print(chat_history)
    if history is not None:
        return jsonify(chat_history)
    else:
        return jsonify({'error': 'File not found'})

if __name__ == '__main__':
    app.run(debug=True,port=5001)