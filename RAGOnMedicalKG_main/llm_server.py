# coding = utf-8
import os
import re
from tqdm import tqdm
import requests
import json
import time


class ModelAPI():
    def __init__(self, MODEL_URL):
        self.url = MODEL_URL
        return

    def send_request(self, message, history):
        data = json.dumps({"message":message, "history":history})
        headers = {'Content-Type': 'application/json'}
        try:
            res = requests.post(self.url, data=data, headers=headers)
            print(res)
            predict = json.loads(res.text)["output"][0]
            history = json.loads(res.text)["history"]
            return predict, history
        except Exception as e:
            print("request error", e)
            return "", []

    ## 防止并不稳定，需要多次访问
    def chat(self, query, history=[]):
        message = [{"role": "user", "content": query}]
        count = 0
        response = ''
        history = []
        while count <=10:
            try:
                count +=1
                response, history = self.send_request(message, history)
                if response:
                    return response, history
            except Exception as e:
                print('Exception:', e)
                time.sleep(1)
        return response, history
    
class PuyuModelAPI():
    def __init__(self, MODEL_URL='https://internlm-chat.intern-ai.org.cn/puyu/api/v1/chat/completions'):
        self.url = MODEL_URL
        self.header={
                        'Content-Type':'application/json',
                        "Authorization":"Bearer eyJ0eXBlIjoiSldUIiwiYWxnIjoiSFM1MTIifQ.eyJqdGkiOiI1MDIxMTAxNyIsInJvbCI6IlJPTEVfUkVHSVNURVIiLCJpc3MiOiJPcGVuWExhYiIsImlhdCI6MTcyMDYwNTMyNSwiY2xpZW50SWQiOiJlYm1ydm9kNnlvMG5semFlazF5cCIsInBob25lIjoiMTc3NjUxMjI5MDIiLCJ1dWlkIjoiNDg5NTFlN2ItYjFlZi00ODE1LTkzZDgtYzUxOThjMjI0YmU1IiwiZW1haWwiOiJjYWlfamlueXVAc2p0dS5lZHUuY24iLCJleHAiOjE3MzYxNTczMjV9.e4UySyg3vLVJOgx8xg-cRhsi0tf2oPrm4Q3zfukY_2Y-_ui01UXe84LI8U9W653LCMkaMO784FAb7q2yQ_rygg"
                    }
        

    def send_request(self, message, history):
        data = json.dumps({"message":message, "history":history})
        headers = {'Content-Type': 'application/json'}
        try:
            res = requests.post(self.url, data=data, headers=headers)
            print(res)
            predict = json.loads(res.text)["output"][0]
            history = json.loads(res.text)["history"]
            return predict, history
        except Exception as e:
            print("request error", e)
            return "", []

    def chat(self, query, history=[]):
        data = {
                    "model": "internlm2-latest",  
                    "messages": [{
                        "role": "user",
                        "text": query
                    }],
                    "n": 1,
                    "temperature": 0.0,
                    "top_p": 0.9
                }
        res = requests.post(self.url, headers=self.header, data=json.dumps(data))
        if "choices" in res.json():
            return res.json()["choices"][0]["message"]["content"],res
        else:
            return None,res

        


if __name__ == '__main__':
    model = PuyuModelAPI()
    res= model.chat(query="你叫啥", history=[])
    print(res)
